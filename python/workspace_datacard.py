#!/usr/bin/env python
import os, sys, ROOT, warnings, pickle
ROOT.gROOT.SetBatch(True)
from array import array
from math import sqrt
from copy import copy, deepcopy
#suppres the EvalInstace conversion warning bug
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
from optparse import OptionParser
from myutils import BetterConfigParser, Sample, progbar, printc, ParseInfo, Rebinner, TreeCache, HistoMaker

#--CONFIGURE---------------------------------------------------------------------
argv = sys.argv
parser = OptionParser()
parser.add_option("-V", "--var", dest="variable", default="",
                      help="variable for shape analysis")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
config = BetterConfigParser()
config.read(opts.config)
var=opts.variable
#-------------------------------------------------------------------------------

#--read variables from config---------------------------------------------------
# 7 or 8TeV Analysis
anaTag = config.get("Analysis","tag")
if not any([anaTag == '7TeV',anaTag == '8TeV']):
    raise Exception("anaTag %s unknown. Specify 8TeV or 7TeV in the general config"%anaTag)
# Directories:
Wdir=config.get('Directories','Wdir')
vhbbpath=config.get('Directories','vhbbpath')
samplesinfo=config.get('Directories','samplesinfo')
path = config.get('Directories','dcSamples')
outpath=config.get('Directories','limits')
try:
    os.stat(outpath)
except:
    os.mkdir(outpath)
# parse histogram config:
hist_conf=config.get('Limit',var)
options = hist_conf.split(',')
if len(options) < 12:
    raise Exception("You have to choose option[11]: either Mjj or BDT")
treevar = options[0]
name = options[1]
title = options[2]
nBins = int(options[3])
xMin = float(options[4])
xMax = float(options[5])
ROOToutname = options[6]
RCut = options[7]
SCut = options[8]
signals = options[9].split(' ')
datas = options[10].split(' ')
anType = options[11]
setup=eval(config.get('LimitGeneral','setup'))
#Systematics:
if config.has_option('LimitGeneral','addSample_sys'):
    addSample_sys = eval(config.get('LimitGeneral','addSample_sys'))
    additionals = [addSample_sys[key] for key in addSample_sys]
else:
    addSample_sys = None
    additionals = []
#find out if BDT or MJJ:
bdt = False
mjj = False
if str(anType) == 'BDT':
    bdt = True
    systematics = eval(config.get('LimitGeneral','sys_BDT'))
elif str(anType) == 'Mjj':
    mjj = True
    systematics = eval(config.get('LimitGeneral','sys_Mjj'))
sys_cut_suffix=eval(config.get('LimitGeneral','sys_cut_suffix'))
systematicsnaming = eval(config.get('LimitGeneral','systematicsnaming'))
sys_factor_dict = eval(config.get('LimitGeneral','sys_factor'))
sys_affecting = eval(config.get('LimitGeneral','sys_affecting'))
# weightF:
weightF = config.get('Weights','weightF')
weightF_sys = eval(config.get('LimitGeneral','weightF_sys'))

# get nominal cutstring:
treecut = config.get('Cuts',RCut)
# Train flag: splitting of samples
TrainFlag = eval(config.get('Analysis','TrainFlag'))
# blind data option:
blind=eval(config.get('LimitGeneral','blind'))
if blind: 
    printc('red','', 'I AM BLINDED!')
#get List of backgrounds in use:
backgrounds = eval(config.get('LimitGeneral','BKG'))
#Groups for adding samples together
Group = eval(config.get('LimitGeneral','Group'))
#naming for DC
Dict= eval(config.get('LimitGeneral','Dict'))
#treating statistics bin-by-bin:
binstat = eval(config.get('LimitGeneral','binstat'))
# Use the rebinning:
rebin_active=eval(config.get('LimitGeneral','rebin_active'))
#max_rel = float(config.get('LimitGeneral','rebin_max_rel'))
signal_inject=config.get('LimitGeneral','signal_inject')
# add signal as background
add_signal_as_bkg=config.get('LimitGeneral','add_signal_as_bkg')
if not add_signal_as_bkg == 'None':
    setup.append(add_signal_as_bkg)
#----------------------------------------------------------------------------

#--Setup--------------------------------------------------------------------
#Assign Pt region for sys factors
if 'HighPtLooseBTag' in ROOToutname:
    pt_region = 'HighPtLooseBTag'
elif 'HighPt' in ROOToutname or 'highPt' in ROOToutname or 'medPt' in ROOToutname:
    pt_region = 'HighPt'
elif 'LowPt' in ROOToutname or 'lowPt' in ROOToutname:
    pt_region = 'LowPt'
elif 'ATLAS' in ROOToutname:
    pt_region = 'HighPt'
elif 'Mjj' in ROOToutname:
    pt_region = 'HighPt' 
else:
    print "Unknown Pt region"
    sys.exit("Unknown Pt region")
# Set rescale factor of 2 in case of TrainFalg
if TrainFlag:
    MC_rescale_factor=2.
    print 'I RESCALE BY 2.0'
else: MC_rescale_factor = 1.
#systematics up/down
UD = ['Up','Down']
# rename Bins in DC (?)
if 'RTight' in RCut:
    Datacardbin=options[10]
elif 'RMed' in RCut:
    Datacardbin=options[10]
else:
    Datacardbin=options[10]
#Parse samples configuration
info = ParseInfo(samplesinfo,path)
# get all the treeCut sets
# create different sample Lists
all_samples = info.get_samples(signals+backgrounds+additionals)
signal_samples = info.get_samples(signals) 
background_samples = info.get_samples(backgrounds) 
data_samples = info.get_samples(datas)
#cache all samples
#t_cache = TreeCache(cuts,all_samples,path)
#cache datas
#d_cache = TreeCache(trecut,data_samples,path)
#-------------------------------------------------------------------------------------------------

optionsList=[]

def appendList(): optionsList.append({'cut':copy(_cut),'var':copy(_treevar),'name':copy(_name),'nBins':nBins,'xMin':xMin,'xMax':xMax,'weight':copy(_weight),'blind':copy(_blind)})

#nominal
_cut = treecut
_treevar = treevar
_name = title
_weight = weightF
_blind = blind
appendList()

#the 4 sys
for syst in systematics:
    for Q in UD:
        #default:
        _cut = treecut
        _name = title
        _weight = weightF
        #replace cut string
        new_cut=sys_cut_suffix[syst]
        if not new_cut == 'nominal':
            old_str,new_str=new_cut.split('>')
            _cut = treecut.replace(old_str,new_str.replace('?',Q))
            _name = title
            _weight = weightF
        #replace tree variable
        if bdt == True:
            ff[1]='%s_%s'%(sys,Q.lower())
            _treevar = nominalShape.replace('.nominal','.%s_%s'%(sys,Q.lower()))
        elif mjj == True:
            if sys == 'JER' or sys == 'JES':
                _treevar = 'H_%s.mass_%s'%(sys,Q.lower())
            else:
                _treevar = treevar
        #append
        appendList()

#UEPS
if weightF_sys:
    for _weight in [config.get('Weights','weightF_sys_UP'),config.get('Weights','weightF_sys_DOWN')]:
        _cut = treecut
        _treevar = treevar
        _name = title
        appendList()

#for option in optionsList:
#    print option['cut']


mc_hMaker = HistoMaker(all_samples,path,config,optionsList)
data_hMaker = HistoMaker(data_samples,path,config,[optionsList[0]])
#Calculate lumi
lumi = 0.
nData = 0
for job in data_samples:
    nData += 1
    lumi += float(job.lumi)

if nData > 1:
    lumi = lumi/float(nData)

mc_hMaker.lumi = lumi
data_hMaker.lumi = lumi


if rebin_active:
    mc_hMaker.calc_rebin(background_samples)
    #transfer rebinning info to data maker
    data_hMaker.norebin_nBins = copy(mc_hMaker.norebin_nBins)
    data_hMaker.rebin_nBins = copy(mc_hMaker.rebin_nBins)
    data_hMaker.mybinning = deepcopy(mc_hMaker.mybinning)
    data_hMaker.rebin = True

#mc_hMaker.rebin = False
#data_hMaker.rebin = False

all_histos = {}
data_histos = {}

for job in all_samples:
    all_histos[job.name] = mc_hMaker.get_histos_from_tree(job)

for job in data_samples:
    data_histos[job.name] = data_hMaker.get_histos_from_tree(job)[0]['DATA']

nData = 0
for job in data_histos:
    if nData == 0:
        theData = data_histos[job]
    else:
        theData.Add(data_histos[i])

#-- Write Files-----------------------------------------------------------------------------------
# generate the TH outfile:
outfile = ROOT.TFile(outpath+'vhbb_TH_'+ROOToutname+'.root', 'RECREATE')
outfile.mkdir(Datacardbin,Datacardbin)
outfile.cd(Datacardbin)
# generate the Workspace:
WS = ROOT.RooWorkspace('%s'%Datacardbin,'%s'%Datacardbin) #Zee
print 'WS initialized'
disc= ROOT.RooRealVar(name,name,xMin,xMax)
obs = ROOT.RooArgList(disc)
#
ROOT.gROOT.SetStyle("Plain")


# ToDo:
#---- get the BKG for the rebinning calculation----
#Rebinner.calculate_binning(hDummyRB,max_rel)
#myBinning=Rebinner(int(nBins),array('d',[-1.0]+[hDummyRB.GetBinLowEdge(i) for i in binlist]),rebin_active)
#--------------------------------------------------

#order and add all together
final_histos = {}

print '\n\t--> Ordering and Adding Histos\n'

#NOMINAL:
final_histos['nominal'] = HistoMaker.orderandadd([all_histos['%s'%job][0] for job in all_samples],setup) 

#SYSTEMATICS:
ind = 1
for syst in systematics:
    for Q in UD:
        final_histos['%s_%s'%(systematicsnaming[syst],Q)] = HistoMaker.orderandadd([all_histos[job.name][ind] for job in all_samples],setup)
        ind+=1

if weightF_sys: 
    for Q in UD:
        final_histos['%s_%s'%(systematicsnaming['weightF_sys'],Q)]= HistoMaker.orderandadd([all_histos[job.name][ind] for job in all_samples],setup)
        ind+=1

def get_alternate_shape(hNominal,hAlternate):
    hVar = hAlternate.Clone()
    hNom = hNominal.Clone()
    hAlt = hNom.Clone()
    hNom.Add(hVar,-1.)
    hAlt.Add(hNom)
    for bin in range(0,hNominal.GetNbinsX()+1):
        if hAlt.GetBinContent(bin) < 0.: hAlt.SetBinContent(bin,0.)
    return hVar,hAlt

def get_alternate_shapes(all_histos,asample_dict,all_samples):
    alternate_shapes_up = []
    alternate_shapes_down = []
    for job in all_samples:
        nominal = all_histos[job.name][0]
        if job.name in asample_dict:
            print 'calc add shape %s'%job
            alternate = copy(all_histos[asample_dict[job.name]][0])
            hUp, hDown = get_alternate_shape(nominal[nominal.keys()[0]],alternate[alternate.keys()[0]])
            alternate_shapes_up.append({nominal.keys()[0]:hUp})
            alternate_shapes_down.append({nominal.keys()[0]:hDown})
        else:
            print 'copy add shape %s'%job
            #hUp, hDown = get_alternate_shape(nominal[nominal.keys()[0]],nominal[nominal.keys()[0]])
            #alternate_shapes_up.append({nominal.keys()[0]:hUp})
            #alternate_shapes_down.append({nominal.keys()[0]:hDown})
            newh=nominal[nominal.keys()[0]].Clone('%s_%s_Up'%(nominal[nominal.keys()[0]].GetName(),'model'))
            alternate_shapes_up.append({nominal.keys()[0]:nominal[nominal.keys()[0]].Clone()})
            alternate_shapes_down.append({nominal.keys()[0]:nominal[nominal.keys()[0]].Clone()})
    return alternate_shapes_up, alternate_shapes_down
        
if addSample_sys: 
    aUp, aDown = get_alternate_shapes(all_histos,addSample_sys,all_samples)
    final_histos['%s_Up'%(systematicsnaming['model'])]= HistoMaker.orderandadd(aUp,setup)
    del aUp
    final_histos['%s_Down'%(systematicsnaming['model'])]= HistoMaker.orderandadd(aDown,setup)

#make statistical shapes:
for Q in UD:
    final_histos['%s_%s'%(systematicsnaming['stats'],Q)] = {}
for job,hist in final_histos['nominal'].items():
    for Q in UD:
        final_histos['%s_%s'%(systematicsnaming['stats'],Q)][job] = hist.Clone()
        for j in range(hist.GetNbinsX()+1):
            if Q == 'Up':
                final_histos['%s_%s'%(systematicsnaming['stats'],Q)][job].SetBinContent(j,max(0,hist.GetBinContent(j)+hist.GetBinError(j)))
            if Q == 'Down':
                final_histos['%s_%s'%(systematicsnaming['stats'],Q)][job].SetBinContent(j,max(0,hist.GetBinContent(j)-hist.GetBinError(j)))

#write shapes in WS:
for key in final_histos:
    for job, hist in final_histos[key].items():
        if 'nominal' == key:
            hist.SetName('%s'%(Dict[job]))
            hist.Write()
            rooDataHist = ROOT.RooDataHist('%s' %(Dict[job]),'%s'%(Dict[job]),obs, hist)
            getattr(WS,'import')(rooDataHist)
        for Q in UD:
            if Q in key:
                theSyst = key.replace('_%s'%Q,'')
            else:
                continue
            if systematicsnaming['stats'] in key:
                nameSyst = '%s_%s_%s' %(theSyst,Dict[job],Datacardbin)
            elif systematicsnaming['model'] in key:
                nameSyst = '%s_%s' %(theSyst,Dict[job])
            else:
                nameSyst = theSyst
            hist.SetName('%s%s%s' %(Dict[job],nameSyst,Q))
            hist.Write()
            rooDataHist = ROOT.RooDataHist('%s%s%s' %(Dict[job],nameSyst,Q),'%s%s%s'%(Dict[job],nameSyst,Q),obs, hist)
            getattr(WS,'import')(rooDataHist)

theData.SetName('data_obs')
theData.Write()
rooDataHist = ROOT.RooDataHist('data_obs','data_obs',obs, theData)
getattr(WS,'import')(rooDataHist)

WS.writeToFile(outpath+'vhbb_WS_'+ROOToutname+'.root')

# now we have a Dict final_histos with sets of all grouped MCs for all systematics:
# nominal, ($SYS_Up/Down)*4, weightF_sys_Up/Down, stats_Up/Down

print '\n\t >>> PRINTOUT PRETTY TABLE <<<\n'
#header
printout = ''
printout += '%-25s'%'Process'
printout += ':'
for item, val in final_histos['nominal'].items():
    printout += '%-12s'%item
print printout+'\n'
for key in final_histos:
    printout = ''
    printout += '%-25s'%key
    printout += ':'
    for item, val in final_histos[key].items():
        printout += '%-12s'%str('%0.5f'%val.Integral())
    print printout

#-----------------------------------------------------------------------------------------------------------

# -------------------- write DATAcard: ----------------------------------------------------------------------
DCprocessseparatordict = {'WS':':','TH':'/'}
# create two datacards: for TH an WS
for DCtype in ['WS','TH']:
    columns=len(setup)
    f = open(outpath+'vhbb_DC_%s_%s.txt'%(DCtype,ROOToutname),'w')
    f.write('imax\t1\tnumber of channels\n')
    f.write('jmax\t%s\tnumber of backgrounds (\'*\' = automatic)\n'%(columns-1))
    f.write('kmax\t*\tnumber of nuisance parameters (sources of systematical uncertainties)\n\n')
    f.write('shapes * * vhbb_%s_%s.root $CHANNEL%s$PROCESS $CHANNEL%s$PROCESS$SYSTEMATIC\n\n'%(DCtype,ROOToutname,DCprocessseparatordict[DCtype],DCprocessseparatordict[DCtype]))
    f.write('bin\t%s\n\n'%Datacardbin)
    f.write('observation\t%s\n\n'%(int(theData.Integral())))
    # datacard bin
    f.write('bin')
    for c in range(0,columns): f.write('\t%s'%Datacardbin)
    f.write('\n')
    # datacard process
    f.write('process')
    for c in setup: f.write('\t%s'%Dict[c])
    f.write('\n')
    f.write('process')
    for c in range(0,columns): f.write('\t%s'%c)
    f.write('\n')
    # datacard yields
    f.write('rate')
    for c in setup: 
        f.write('\t%s'%final_histos['nominal'][c].Integral())
    f.write('\n')
    # get list of systematics in use
    InUse=eval(config.get('Datacard','InUse_%s'%pt_region))
    # write non-shape systematics
    for item in InUse:
        f.write(item)
        what=eval(config.get('Datacard',item))
        f.write('\t%s'%what['type'])
        for c in setup:
            if c in what:
                if item == 'CMS_eff_e' and 'Zmm' in options[10]: f.write('\t-')
                elif item == 'CMS_eff_m' and 'Zee' in options[10]: f.write('\t-')
                elif item == 'CMS_trigger_e' and 'Zmm' in options[10]: f.write('\t-')
                elif item == 'CMS_trigger_m' and 'Zee' in options[10]: f.write('\t-')
                else:
                    f.write('\t%s'%what[c])
            else:
                f.write('\t-')
        f.write('\n')
    # Write statistical shape variations
    if binstat:
        for c in setup:
            for bin in range(0,nBins):
                f.write('%s_%s_%s_%s\tshape'%(systematicsnaming['stats'],Dict[c], bin, options[10]))
                for it in range(0,columns):
                    if it == setup.index(c):
                        f.write('\t1.0')
                    else:
                        f.write('\t-')
                f.write('\n')
    else:
        for c in setup:
            f.write('%s_%s_%s\tshape'%(systematicsnaming['stats'],Dict[c], options[10]))
            for it in range(0,columns):
                if it == setup.index(c):
                    f.write('\t1.0')
                else:
                    f.write('\t-')
            f.write('\n')
    # UEPS systematics
    if weightF_sys:
        f.write('UEPS\tshape')
        for it in range(0,columns): f.write('\t1.0')
        f.write('\n')
    # additional sample systematics
    if addSample_sys:
        alreadyAdded = []
        for newSample in addSample_sys.iterkeys():
            for c in setup:
                if not c == Group[newSample]: continue
                if Dict[c] in alreadyAdded: continue
                f.write('%s_%s\tshape'%(systematicsnaming['model'],Dict[c]))
                for it in range(0,columns):
                    if it == setup.index(c):
                         f.write('\t1.0')
                    else:
                         f.write('\t-')
                f.write('\n')
                alreadyAdded.append(Dict[c])
    # regular systematics
    for sys in systematics:
        sys_factor=sys_factor_dict[sys]
        f.write('%s\tshape'%systematicsnaming[sys])
        for c in setup:
            if c in sys_affecting[sys]:
                f.write('\t%s'%sys_factor)
            else:
                f.write('\t-')
        f.write('\n')
    f.close()
# --------------------------------------------------------------------------




outfile.Close()
