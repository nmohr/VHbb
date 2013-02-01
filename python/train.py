#!/usr/bin/env python
from optparse import OptionParser
import sys
import pickle
import ROOT 
ROOT.gROOT.SetBatch(True)
from array import array
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

#Import after configure to get help message
from myutils import BetterConfigParser, mvainfo, ParseInfo, TreeCache

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
samplesinfo=config.get('Directories','samplesinfo')

#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

weightF=config.get('Weights','weightF')

VHbbNameSpace=config.get('VHbbNameSpace','library')
ROOT.gSystem.Load(VHbbNameSpace)

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
path=config.get('Directories','SYSout')

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

#Infofile
info = ParseInfo(samplesinfo,path)

#Workdir
workdir=ROOT.gDirectory.GetPath()


TrainCut='%s & EventForTraining==1'%TCut
EvalCut='%s & EventForTraining==0'%TCut
cuts = [TrainCut,EvalCut] 


samples = []
samples = info.get_samples(signals+backgrounds)

tc = TreeCache(cuts,samples,path,config)

output = ROOT.TFile.Open(fnameOutput, "RECREATE")

print '\n\t>>> READING EVENTS <<<\n'

signal_samples = info.get_samples(signals)
background_samples = info.get_samples(backgrounds)

#TRAIN trees
Tbackgrounds = []
TbScales = []
Tsignals = []
TsScales = []
#EVAL trees
Ebackgrounds = []
EbScales = []
Esignals = []
EsScales = []

#load trees
for job in signal_samples:
    print '\tREADING IN %s AS SIG'%job.name
    Tsignal = tc.get_tree(job,TrainCut)
    ROOT.gDirectory.Cd(workdir)
    TsScale = tc.get_scale(job,config)*global_rescale    
    Tsignals.append(Tsignal)
    TsScales.append(TsScale)
    Esignal = tc.get_tree(job,EvalCut)
    Esignals.append(Esignal)
    EsScales.append(TsScale)
    print '\t\t\tTraining %s events'%Tsignal.GetEntries()
    print '\t\t\tEval %s events'%Esignal.GetEntries()
for job in background_samples:
    print '\tREADING IN %s AS BKG'%job.name
    Tbackground = tc.get_tree(job,TrainCut)
    ROOT.gDirectory.Cd(workdir)
    TbScale = tc.get_scale(job,config)*global_rescale
    Tbackgrounds.append(Tbackground)
    TbScales.append(TbScale)
    Ebackground = tc.get_tree(job,EvalCut)
    ROOT.gDirectory.Cd(workdir)
    Ebackgrounds.append(Ebackground)
    EbScales.append(TbScale)
    print '\t\t\tTraining %s events'%Tbackground.GetEntries()
    print '\t\t\tEval %s events'%Ebackground.GetEntries()
            

factory = ROOT.TMVA.Factory(factoryname, output, factorysettings)

#set input trees
for i in range(len(Tsignals)):
    factory.AddSignalTree(Tsignals[i], TsScales[i], ROOT.TMVA.Types.kTraining)
    factory.AddSignalTree(Esignals[i], EsScales[i], ROOT.TMVA.Types.kTesting)

for i in range(len(Tbackgrounds)):
    if (Tbackgrounds[i].GetEntries()>0):
        factory.AddBackgroundTree(Tbackgrounds[i], TbScales[i], ROOT.TMVA.Types.kTraining)

    if (Ebackgrounds[i].GetEntries()>0):
        factory.AddBackgroundTree(Ebackgrounds[i], EbScales[i], ROOT.TMVA.Types.kTesting)
        
for var in MVA_Vars['Nominal']:
    factory.AddVariable(var,'D') # add the variables

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
pickle.dump(info,infofile)
infofile.close()

# open the TMVA Gui 
if gui == True: 
    ROOT.gROOT.ProcessLine( ".L myutils/TMVAGui.C")
    ROOT.gROOT.ProcessLine( "TMVAGui(\"%s\")" % fnameOutput )
    ROOT.gApplication.Run() 


