#!/usr/bin/env python
from samplesinfo import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from ConfigParser import SafeConfigParser
import sys
from mvainfos import mvainfo

#warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#usage: ./train run gui


#CONFIGURE

#load config
config = SafeConfigParser()
config.read('./config')

#get locations:
Wdir=config.get('Directories','Wdir')


#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

weightF=config.get('Weights','weightF')


def getTree(job,cut):
    Tree = ROOT.TChain(job.tree)
    Tree.Add(job.getpath())
    #Tree.SetDirectory(0)
    CuttedTree=Tree.CopyTree(cut)
    CuttedTree.SetDirectory(0)
    print '\t--> read in %s'%job.name
    return CuttedTree
        


def getScale(job):
    input = TFile.Open(job.getpath())
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    #print lumi*xsecs[i]/hist.GetBinContent(1)
    return float(job.lumi)*float(job.xsec)*float(job.sf)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*2/float(job.split)




run=sys.argv[1]
gui=sys.argv[2]


#CONFIG
#factory
factoryname=config.get('factory','factoryname')
factorysettings=config.get('factory','factorysettings')
#MVA
MVAtype=config.get(run,'MVAtype')
MVAname=run
MVAsettings=config.get(run,'MVAsettings')
fnameOutput = Wdir +'/weights/'+factoryname+'_'+MVAname+'.root'
#locations
path=config.get(run,'path')

TCutname=config.get(run, 'treeCut')
TCut=config.get('Cuts',TCutname)
print TCut

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
spectators=config.get(treeVarSet,'spectators')
spectators=spectators.split(' ')

#TRAINING samples
infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()

#Workdir
workdir=ROOT.gDirectory.GetPath()


TrainCut='%s && EventForTraining==1'%TCut
EvalCut='%s && EventForTraining==0'%TCut

#load TRAIN trees
Tbackgrounds = []
TbScales = []
Tsignals = []
TsScales = []

for job in info:
    if job.name in signals:
        Tsignal = getTree(job,TrainCut)
        ROOT.gDirectory.Cd(workdir)
        TsScale = getScale(job)
        Tsignals.append(Tsignal)
        TsScales.append(TsScale)
        
    if job.name in backgrounds:
        Tbackground = getTree(job,TrainCut)
        ROOT.gDirectory.Cd(workdir)
        TbScale = getScale(job)
        Tbackgrounds.append(Tbackground)
        TbScales.append(TbScale)
        
#load EVALUATE trees
Ebackgrounds = []
EbScales = []
Esignals = []
EsScales = []

for job in info:
    if job.name in signals:
        Esignal = getTree(job,EvalCut)
        ROOT.gDirectory.Cd(workdir)
        EsScale = getScale(job)
        Esignals.append(Esignal)
        EsScales.append(EsScale)
        
    if job.name in backgrounds:
        Ebackground = getTree(job,EvalCut)
        ROOT.gDirectory.Cd(workdir)
        EbScale = getScale(job)
        Ebackgrounds.append(Ebackground)
        EbScales.append(EbScale)

output = ROOT.TFile.Open(fnameOutput, "RECREATE")
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
#for var in spectators:
#    factory.AddSpectator(var,'D') #add specators

#Execute TMVA
factory.SetSignalWeightExpression(weightF)
factory.Verbose()
factory.BookMethod(MVAtype,MVAname,MVAsettings)
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()
output.Write()

#WRITE INFOFILE
infofile = open(Wdir+'/weights/'+factoryname+'_'+MVAname+'.info','w')
info=mvainfo(MVAname)
info.factoryname=factoryname
info.factorysettings=factorysettings
info.MVAtype=MVAtype
info.MVAsettings=MVAsettings
info.weightfilepath=Wdir+'/weights'
info.path=path
info.varset=treeVarSet
info.vars=MVA_Vars['Nominal']
info.spectators=spectators
pickle.dump(info,infofile)
infofile.close()

# open the TMVA Gui 
if gui == 'gui': 
    ROOT.gROOT.ProcessLine( ".L TMVAGui.C")
    ROOT.gROOT.ProcessLine( "TMVAGui(\"%s\")" % fnameOutput )
    ROOT.gApplication.Run() 


