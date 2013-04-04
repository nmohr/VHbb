#!/usr/bin/env python
from __future__ import print_function
import sys
import os,subprocess
import ROOT 
from array import array
from math import sqrt
from copy import copy
#suppres the EvalInstace conversion warning bug
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
from optparse import OptionParser
import pickle


#CONFIGURE
ROOT.gROOT.SetBatch(True)
print('hello')
#load config
argv = sys.argv
parser = OptionParser()
parser.add_option("-U", "--update", dest="update", default=0,
                      help="update infofile")
parser.add_option("-D", "--discr", dest="discr", default="",
                      help="discriminators to be added")
parser.add_option("-S", "--samples", dest="names", default="",
                      help="samples you want to run on")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)

if opts.config =="":
        opts.config = "config"

#Import after configure to get help message
from myutils import BetterConfigParser, progbar, printc, ParseInfo, MvaEvaluator

config = BetterConfigParser()
config.read(opts.config)
anaTag = config.get("Analysis","tag")

#get locations:
Wdir=config.get('Directories','Wdir')
samplesinfo=config.get('Directories','samplesinfo')

#systematics
INpath = config.get('Directories','MVAin')
OUTpath = config.get('Directories','MVAout')

info = ParseInfo(samplesinfo,INpath)

arglist=opts.discr #RTight_blavla,bsbsb

namelistIN=opts.names
namelist=namelistIN.split(',')

#doinfo=bool(int(opts.update))

MVAlist=arglist.split(',')

#CONFIG
#factory
factoryname=config.get('factory','factoryname')

#load the namespace
VHbbNameSpace=config.get('VHbbNameSpace','library')
ROOT.gSystem.Load(VHbbNameSpace)

#MVA
MVAinfos=[]
MVAdir=config.get('Directories','vhbbpath')
for MVAname in MVAlist:
    MVAinfofile = open(MVAdir+'/data/'+factoryname+'_'+MVAname+'.info','r')
    MVAinfos.append(pickle.load(MVAinfofile))
    MVAinfofile.close()
    
longe=40
#Workdir
workdir=ROOT.gDirectory.GetPath()



theMVAs = []
for mva in MVAinfos:
    theMVAs.append(MvaEvaluator(config,mva))


#eval

samples = info.get_samples(namelist)
print(samples)
tmpDir = os.environ["TMPDIR"]
for job in samples:
    #get trees:
    print(INpath+'/'+job.prefix+job.identifier+'.root')
    input = ROOT.TFile.Open(INpath+'/'+job.prefix+job.identifier+'.root','read')
    print(OUTpath+'/'+job.prefix+job.identifier+'.root')
    outfile = ROOT.TFile.Open(tmpDir+'/'+job.prefix+job.identifier+'.root','recreate')
    input.cd()
    obj = ROOT.TObject
    for key in ROOT.gDirectory.GetListOfKeys():
        input.cd()
        obj = key.ReadObj()
        #print obj.GetName()
        if obj.GetName() == job.tree:
            continue
        outfile.cd()
        #print key.GetName()
        obj.Write(key.GetName())
    tree = input.Get(job.tree)
    nEntries = tree.GetEntries()
    outfile.cd()
    newtree = tree.CloneTree(0)
            
    #Set branch adress for all vars
    for i in range(0,len(theMVAs)):
        theMVAs[i].setVariables(tree,job)
    outfile.cd()
    #Setup Branches
    mvaVals=[]
    for i in range(0,len(theMVAs)):
        if job.type == 'Data':
            mvaVals.append(array('f',[0]))
            newtree.Branch(MVAinfos[i].MVAname,mvaVals[i],'nominal/F') 
        else:
            mvaVals.append(array('f',[0]*11))
            newtree.Branch(theMVAs[i].MVAname,mvaVals[i],'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down:beff1_up:beff1_down/F')
        MVA_formulas_Nominal = []
        print('\n--> ' + job.name +':')
    #Fill event by event:
    for entry in range(0,nEntries):
        tree.GetEntry(entry)
                            
        for i in range(0,len(theMVAs)):
            theMVAs[i].evaluate(mvaVals[i],job)
        #Fill:
        newtree.Fill()
    newtree.AutoSave()
    outfile.Close()
    targetStorage = OUTpath.replace('gsidcap://t3se01.psi.ch:22128/','srm://t3se01.psi.ch:8443/srm/managerv2?SFN=')+'/'+job.prefix+job.identifier+'.root'
    command = 'lcg-del -b -D srmv2 -l %s' %(targetStorage)
    print(command)
    subprocess.call([command], shell=True)
    command = 'lcg-cp -b -D srmv2 file:///%s %s' %(tmpDir+'/'+job.prefix+job.identifier+'.root',targetStorage)
    print(command)
    subprocess.call([command], shell=True)
                
print('\n')
