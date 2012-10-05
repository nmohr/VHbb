#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
import sys
from mvainfos import mvainfo
from gethistofromtree import getScale


#warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#usage: ./train run gui


#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-v", "--verbose", action="store_true", dest="verbose", default=False,
                          help="Verbose mode.")
parser.add_option("-T", "--training", dest="training", default="",
                      help="Training")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"

#load config
config = BetterConfigParser()
config.read(opts.config)
anaTag = config.get("Analysis","tag")
run=opts.training
gui=opts.verbose

#GLOABAL rescale from Train/Test Spliiting:
global_rescale=2.

#get locations:
MVAdir=config.get('Directories','vhbbpath')+'/data/'

#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

weightF=config.get('Weights','weightF')




def getTree(job,cut,path,subsample=-1):
    #print path+'/'+job.getpath()
    newinput = TFile.Open(path+'/'+job.getpath(),'read')
    output.cd()
    Tree = newinput.Get(job.tree)
    #Tree.SetDirectory(0)

      
    if subsample>-1:
        #print 'cut: (%s) & (%s)'%(cut,job.subcuts[subsample]) 
        CuttedTree=Tree.CopyTree('(%s) & (%s)'%(cut,job.subcuts[subsample]))    
        #print '\t--> read in %s'%job.group[subsample]

    else:
        CuttedTree=Tree.CopyTree(cut)
        #print '\t--> read in %s'%job.name
    newinput.Close()

    #CuttedTree.SetDirectory(0)
    return CuttedTree
        
#def getScale(job,subsample=-1):
#    input = TFile.Open(job.getpath())
#    CountWithPU = input.Get("CountWithPU")
#    CountWithPU2011B = input.Get("CountWithPU2011B")
#    #print lumi*xsecs[i]/hist.GetBinContent(1)
#    return float(job.lumi)*float(job.xsec)*float(job.sf)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*2/float(job.split)



#CONFIG
#factory
factoryname=config.get('factory','factoryname')
factorysettings=config.get('factory','factorysettings')
#MVA
MVAtype=config.get(run,'MVAtype')
MVAname=run
MVAsettings=config.get(run,'MVAsettings')
fnameOutput = MVAdir+factoryname+'_'+MVAname+'.root'
#locations
path=config.get(run,'path')

TCutname=config.get(run, 'treeCut')
TCut=config.get('Cuts',TCutname)
#print TCut

#signals
signals=config.get(run,'signals')
signals=signals.split(' ')
#backgrounds
backgrounds=config.get(run,'backgrounds')
backgrounds=backgrounds.split(' ')

treeVarSet=config.get(run,'treeVarSet')
        
#variables
#TreeVar Array
MVA_Vars={}
MVA_Vars['Nominal']=config.get(treeVarSet,'Nominal')
MVA_Vars['Nominal']=MVA_Vars['Nominal'].split(' ')    
#Spectators:
#spectators=config.get(treeVarSet,'spectators')
#spectators=spectators.split(' ')

#TRAINING samples
infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()

#Workdir
workdir=ROOT.gDirectory.GetPath()


TrainCut='%s & EventForTraining==1'%TCut
EvalCut='%s & EventForTraining==0'%TCut

#load TRAIN trees
Tbackgrounds = []
TbScales = []
Tsignals = []
TsScales = []



output = ROOT.TFile.Open(fnameOutput, "RECREATE")

print '\n\t>>> TRAINING EVENTS <<<\n'

for job in info:
    if eval(job.active):
    
        if job.subsamples:
            print '\tREADING IN SUBSAMPLES of %s'%job.name
            for subsample in range(0,len(job.group)):
                if job.subnames[subsample] in signals:
                    print '\t- %s as SIG'%job.group[subsample]
                    Tsignal = getTree(job,TrainCut,path,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    TsScale = getScale(job,path,config,global_rescale,subsample)
                    Tsignals.append(Tsignal)
                    TsScales.append(TsScale)
                    print '\t\t\t%s events'%Tsignal.GetEntries()
                elif job.subnames[subsample] in backgrounds:
                    print '\t- %s as BKG'%job.group[subsample]
                    Tbackground = getTree(job,TrainCut,path,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    TbScale = getScale(job,path,config,global_rescale,subsample)
                    Tbackgrounds.append(Tbackground)
                    TbScales.append(TbScale)
                    print '\t\t\t%s events'%Tbackground.GetEntries()
    
        else:
            if job.name in signals:
                print '\tREADING IN %s AS SIG'%job.name
                Tsignal = getTree(job,TrainCut,path)
                ROOT.gDirectory.Cd(workdir)
                TsScale = getScale(job,path,config,global_rescale)
                Tsignals.append(Tsignal)
                TsScales.append(TsScale)
                print '\t\t\t%s events'%Tsignal.GetEntries()
            elif job.name in backgrounds:
                print '\tREADING IN %s AS BKG'%job.name
                Tbackground = getTree(job,TrainCut,path)
                ROOT.gDirectory.Cd(workdir)
                TbScale = getScale(job,path,config,global_rescale)
                Tbackgrounds.append(Tbackground)
                TbScales.append(TbScale)
                print '\t\t\t%s events'%Tbackground.GetEntries()
            
            
#load EVALUATE trees
Ebackgrounds = []
EbScales = []
Esignals = []
EsScales = []

print '\n\t>>> TESTING EVENTS <<<\n'


for job in info:
    if eval(job.active):
    
        if job.subsamples:
            print '\tREADING IN SUBSAMPLES of %s'%job.name
            for subsample in range(0,len(job.group)):
                if job.subnames[subsample] in signals:
                    print '\t- %s as SIG'%job.group[subsample]
                    Esignal = getTree(job,EvalCut,path,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    EsScale = getScale(job,path,config,global_rescale,subsample)
                    Esignals.append(Esignal)
                    EsScales.append(EsScale)
                    print '\t\t\t%s events'%Esignal.GetEntries()
                elif job.subnames[subsample] in backgrounds:
                    print '\t- %s as BKG'%job.group[subsample]
                    Ebackground = getTree(job,EvalCut,path,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    EbScale = getScale(job,path,config,global_rescale,subsample)
                    Ebackgrounds.append(Ebackground)
                    EbScales.append(EbScale)
                    print '\t\t\t%s events'%Ebackground.GetEntries()

        else:
            if job.name in signals:
                print '\tREADING IN %s AS SIG'%job.name
                Esignal = getTree(job,EvalCut,path)
                ROOT.gDirectory.Cd(workdir)
                EsScale = getScale(job,path,config,global_rescale)
                Esignals.append(Esignal)
                EsScales.append(EsScale)
                print '\t\t\t%s events'%Esignal.GetEntries()
            elif job.name in backgrounds:
                print '\tREADING IN %s AS BKG'%job.name
                Ebackground = getTree(job,EvalCut,path)
                ROOT.gDirectory.Cd(workdir)
                EbScale = getScale(job,path,config,global_rescale)
                Ebackgrounds.append(Ebackground)
                EbScales.append(EbScale)
                print '\t\t\t%s events'%Ebackground.GetEntries()


#output = ROOT.TFile.Open(fnameOutput, "RECREATE")
factory = ROOT.TMVA.Factory(factoryname, output, factorysettings)

#set input trees
for i in range(len(Tsignals)):

    #print 'Number of SIG entries: %s'%Tsignals[i].GetEntries()
    factory.AddSignalTree(Tsignals[i], TsScales[i], ROOT.TMVA.Types.kTraining)
    #print 'Number of SIG entries: %s'%Esignals[i].GetEntries()
    factory.AddSignalTree(Esignals[i], EsScales[i], ROOT.TMVA.Types.kTesting)

for i in range(len(Tbackgrounds)):
    if (Tbackgrounds[i].GetEntries()>0):
        #print 'Number of BKG entries: %s'%Tbackgrounds[i].GetEntries()
        factory.AddBackgroundTree(Tbackgrounds[i], TbScales[i], ROOT.TMVA.Types.kTraining)

    if (Ebackgrounds[i].GetEntries()>0):
        #print 'Number of BKG entries: %s'%Ebackgrounds[i].GetEntries()
        factory.AddBackgroundTree(Ebackgrounds[i], EbScales[i], ROOT.TMVA.Types.kTesting)
        
        
for var in MVA_Vars['Nominal']:
    factory.AddVariable(var,'D') # add the variables
#for var in spectators:
#    factory.AddSpectator(var,'D') #add specators

#Execute TMVA
factory.SetSignalWeightExpression(weightF)
factory.SetBackgroundWeightExpression(weightF)
factory.Verbose()
factory.BookMethod(MVAtype,MVAname,MVAsettings)
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()
output.Write()

#WRITE INFOFILE
infofile = open(MVAdir+factoryname+'_'+MVAname+'.info','w')
info=mvainfo(MVAname)
info.factoryname=factoryname
info.factorysettings=factorysettings
info.MVAtype=MVAtype
info.MVAsettings=MVAsettings
info.weightfilepath=MVAdir
info.path=path
info.varset=treeVarSet
info.vars=MVA_Vars['Nominal']
#info.spectators=spectators
pickle.dump(info,infofile)
infofile.close()

# open the TMVA Gui 
if gui == True: 
    ROOT.gROOT.ProcessLine( ".L TMVAGui.C")
    ROOT.gROOT.ProcessLine( "TMVAGui(\"%s\")" % fnameOutput )
    ROOT.gApplication.Run() 


