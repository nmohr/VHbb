#!/usr/bin/env python
import sys
import os
import ROOT 
from array import array
from math import sqrt
from copy import copy
#suppres the EvalInstace conversion warning bug
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
from optparse import OptionParser
import pickle
from myutils import BetterConfigParser, progbar, mvainfo, printc, parse_info


#CONFIGURE
ROOT.gROOT.SetBatch(True)
print 'hello'
#load config
#os.mkdir(path+'/sys')
argv = sys.argv
parser = OptionParser()
parser.add_option("-U", "--update", dest="update", default=0,
                      help="update infofile")
parser.add_option("-D", "--discr", dest="discr", default="",
                      help="discriminators to be added")
#parser.add_option("-I", "--inpath", dest="inpath", default="",
#                      help="path to samples")
#parser.add_option("-O", "--outpath", dest="outpath", default="",
#                      help="path where to store output samples")
parser.add_option("-S", "--samples", dest="names", default="",
                      help="samples you want to run on")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)

#from samplesclass import sample
#from mvainfos import mvainfo
#from progbar import progbar
#from printcolor import printc


if opts.config =="":
        opts.config = "config"
config = BetterConfigParser()
#config.read('./config7TeV_ZZ')
config.read(opts.config)
anaTag = config.get("Analysis","tag")

#get locations:
Wdir=config.get('Directories','Wdir')
samplesinfo=config.get('Directories','samplesinfo')

#systematics


INpath = config.get('Directories','MVAin')
OUTpath = config.get('Directories','MVAout')

info = parse_info(samplesinfo,INpath)

#infofile = open(samplesinfo,'r')
#info = pickle.load(infofile)
#infofile.close()
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


#Apply samples
#infofile = open(samplesinfo,'r')
#Ainfo = pickle.load(infofile)
#infofile.close()


class MvaEvaluater:
    def __init__(self, config, MVAinfo):
        self.varset = MVAinfo.varset
        #Define reader
        self.reader = ROOT.TMVA.Reader("!Color:!Silent")
        MVAdir=config.get('Directories','vhbbpath')
        self.systematics=config.get('systematics','systematics').split(' ')
        self.MVA_Vars={}
        self.MVAname = MVAinfo.MVAname
        for systematic in self.systematics:
            self.MVA_Vars[systematic]=config.get(self.varset,systematic)
            self.MVA_Vars[systematic]=self.MVA_Vars[systematic].split(' ')
        #define variables and specatators
        self.MVA_var_buffer = []
        for i in range(len( self.MVA_Vars['Nominal'])):
            self.MVA_var_buffer.append(array( 'f', [ 0 ] ))
            self.reader.AddVariable( self.MVA_Vars['Nominal'][i],self.MVA_var_buffer[i])
        self.reader.BookMVA(MVAinfo.MVAname,MVAdir+'/data/'+MVAinfo.getweightfile())
        #--> Now the MVA is booked

    def setBranches(self,tree,job):
        #Set formulas for all vars
        self.MVA_formulas={}
        for systematic in self.systematics: 
            if job.type == 'DATA' and not systematic == 'Nominal': continue
            self.MVA_formulas[systematic]=[]
            for j in range(len( self.MVA_Vars['Nominal'])):
                self.MVA_formulas[systematic].append(ROOT.TTreeFormula("MVA_formula%s_%s"%(j,systematic),self.MVA_Vars[systematic][j],tree))

    def evaluate(self,MVAbranches,job):
        #Evaluate all vars and fill the branches
        for systematic in self.systematics:
            for j in range(len( self.MVA_Vars['Nominal'])):
                if job.type == 'DATA' and not systematic == 'Nominal': continue
                self.MVA_var_buffer[j][0] = self.MVA_formulas[systematic][j].EvalInstance()                
            MVAbranches[self.systematics.index(systematic)] = self.reader.EvaluateMVA(self.MVAname)


theMVAs = []
for mva in MVAinfos:
    theMVAs.append(MvaEvaluater(config,mva))


#eval
for job in info:
    if eval(job.active):
        if job.name in namelist:
            #get trees:
            print INpath+'/'+job.prefix+job.identifier+'.root'
            input = ROOT.TFile.Open(INpath+'/'+job.prefix+job.identifier+'.root','read')
            print OUTpath+'/'+job.prefix+job.identifier+'.root'
            outfile = ROOT.TFile.Open(OUTpath+'/'+job.prefix+job.identifier+'.root','recreate')
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
                theMVAs[i].setBranches(tree,job)
            outfile.cd()
            #Setup Branches
            MVAbranches=[]
            for i in range(0,len(theMVAs)):
                if job.type == 'Data':
                    MVAbranches.append(array('f',[0]))
                    newtree.Branch(MVAinfos[i].MVAname,MVAbranches[i],'nominal/F') 
                else:
                    MVAbranches.append(array('f',[0]*11))
                    newtree.Branch(theMVAs[i].MVAname,MVAbranches[i],'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down:beff1_up:beff1_down/F')
                MVA_formulas_Nominal = []
            print '\n--> ' + job.name +':'
            #progbar setup
            if nEntries >= longe:
                step=int(nEntries/longe)
                long=longe
            else:
                long=nEntries
                step = 1
            bar=progbar(long)
            #Fill event by event:
            for entry in range(0,nEntries):
                if entry % step == 0:
                    bar.move()
                #load entry
                tree.GetEntry(entry)
                            
                for i in range(0,len(theMVAs)):
                    theMVAs[i].evaluate(MVAbranches[i],job)
                #Fill:
                newtree.Fill()
            newtree.AutoSave()
            outfile.Close()
                
print '\n'

#Update Info:
#if doinfo:
#    for job in Ainfo:        
#        for MVAinfo in MVAinfos:
#            job.addcomment('Added MVA %s'%MVAinfo.MVAname)
#        job.addpath(MVAdir)
#    infofile = open(samplesinfo,'w')
#    pickle.dump(Ainfo,infofile)
#    infofile.close()
