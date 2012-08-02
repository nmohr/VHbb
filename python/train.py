#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from BetterConfigParser import BetterConfigParser
import sys
from mvainfos import mvainfo
from gethistofromtree import getScale


#warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#usage: ./train run gui


#CONFIGURE

#load config
config = BetterConfigParser()
#config.read('./config')
config.read('./config7TeV')


#GLOABAL rescale from Train/Test Spliiting:
global_rescale=2.

#get locations:
Wdir=config.get('Directories','Wdir')

#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

weightF=config.get('Weights','weightF')




def getTree(job,cut,subsample=-1):

    newinput = TFile.Open(job.getpath(),'read')
    output.cd()
    Tree = newinput.Get(job.tree)
    #Tree.SetDirectory(0)

      
    if subsample>-1:
        CuttedTree=Tree.CopyTree('(%s) & (%s)'%(cut,job.subcuts[subsample]))    
        #print '\t--> read in %s'%job.group[subsample]

    else:
        CuttedTree=Tree.CopyTree(cut)
        #print '\t--> read in %s'%job.name


    #CuttedTree.SetDirectory(0)
    return CuttedTree
        
#def getScale(job,subsample=-1):
#    input = TFile.Open(job.getpath())
#    CountWithPU = input.Get("CountWithPU")
#    CountWithPU2011B = input.Get("CountWithPU2011B")
#    #print lumi*xsecs[i]/hist.GetBinContent(1)
#    return float(job.lumi)*float(job.xsec)*float(job.sf)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*2/float(job.split)

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


TrainCut='%s && EventForTraining==1'%TCut
EvalCut='%s && EventForTraining==0'%TCut

#load TRAIN trees
Tbackgrounds = []
TbScales = []
Tsignals = []
TsScales = []



output = ROOT.TFile.Open(fnameOutput, "RECREATE")

print '\n*** TRAINING EVENTS ***\n'

for job in info:
    if eval(job.active):
        if job.name in signals:
            print '\tREADING IN %s AS SIG'%job.name
            Tsignal = getTree(job,TrainCut)
            ROOT.gDirectory.Cd(workdir)
            TsScale = getScale(job,global_rescale)
            Tsignals.append(Tsignal)
            TsScales.append(TsScale)
            
        if job.name in backgrounds:
            if job.subsamples:
                print '\tREADING IN SUBSAMPLES of %s AS BKG'%job.name
                for subsample in range(0,len(job.group)):
                    print '\t- %s'%job.group[subsample]
                    Tbackground = getTree(job,TrainCut,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    TbScale = getScale(job,global_rescale,subsample)
                    Tbackgrounds.append(Tbackground)
                    TbScales.append(TbScale)
            
            
            else:
                print '\tREADING IN %s AS BKG'%job.name
                Tbackground = getTree(job,TrainCut)
                ROOT.gDirectory.Cd(workdir)
                TbScale = getScale(job,global_rescale)
                Tbackgrounds.append(Tbackground)
                TbScales.append(TbScale)
        
#load EVALUATE trees
Ebackgrounds = []
EbScales = []
Esignals = []
EsScales = []

print '\n*** TESTING EVENTS ***\n'


for job in info:
    if eval(job.active):

        if job.name in signals:
            print '\tREADING IN %s AS SIG'%job.name
            Esignal = getTree(job,EvalCut)
            ROOT.gDirectory.Cd(workdir)
            EsScale = getScale(job,global_rescale)
            Esignals.append(Esignal)
            EsScales.append(EsScale)
            
        if job.name in backgrounds:
            if job.subsamples:
                print '\tREADING IN SUBSAMPLES of %s AS BKG'%job.name
                for subsample in range(0,len(job.group)):
                    print '\t- %s'%job.group[subsample]
                    Ebackground = getTree(job,EvalCut,subsample)
                    ROOT.gDirectory.Cd(workdir)
                    EbScale = getScale(job,global_rescale,subsample)
                    Ebackgrounds.append(Ebackground)
                    EbScales.append(EbScale)
            
            
            else:
                print '\tREADING IN %s AS BKG'%job.name
                Ebackground = getTree(job,EvalCut)
                ROOT.gDirectory.Cd(workdir)
                EbScale = getScale(job,global_rescale)
                Ebackgrounds.append(Ebackground)
                EbScales.append(EbScale)
        


#output = ROOT.TFile.Open(fnameOutput, "RECREATE")
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
#info.spectators=spectators
pickle.dump(info,infofile)
infofile.close()

# open the TMVA Gui 
if gui == 'gui': 
    ROOT.gROOT.ProcessLine( ".L TMVAGui.C")
    ROOT.gROOT.ProcessLine( "TMVAGui(\"%s\")" % fnameOutput )
    ROOT.gApplication.Run() 


