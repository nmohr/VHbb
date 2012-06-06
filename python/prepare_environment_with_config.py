#!/usr/bin/env python2.6
from copytree import copytree
from printcolor import printc
from samplesclass import sample
import pickle
import sys
from ConfigParser import SafeConfigParser
import ROOT

pathIN=sys.argv[1]
pathOUT=sys.argv[2]

weightexpression='(PUweight*weightTrig)'
#this is only to speed it up, remove for final trees!
Precut=''
info = []

#get files info from config
config = SafeConfigParser()
config.read('./8TeVsamples.cfg')

prefix=config.get('General','prefix')
lumi=float(config.get('General','lumi'))

for Sample in config.sections():
    if not config.has_option(Sample,'infile'): continue
    infile = config.get(Sample,'infile')
    if not ROOT.TFile.Open(pathIN+prefix+infile+'.root',"READ"):
        print 'WARNING: No file ' + pathIN+prefix+infile+ ' found! '
        continue
#this need exception handle    
    #if type(eval(config.get(Sample,'sampleName'))) != list: 
    if len(config.get(Sample,'sampleName').split(",")) == 1:
        sampleName = [(config.get(Sample,'sampleName'))]
        sampleType = [(config.get(Sample,'sampleType'))]
        sampleGroup = [(config.get(Sample,'sampleGroup'))]
        Aprefix = [(config.get(Sample,'Aprefix'))]
        cut = [(config.get(Sample, 'cut'))]
        if sampleType[0] != 'DATA':
            SF = [(config.get(Sample, 'SF'))]
            xSec = [(config.get(Sample,'xSec'))]        
    else:
        sampleName = eval(config.get(Sample,'sampleName'))
        sampleType = eval(config.get(Sample,'sampleType'))
        sampleGroup = eval(config.get(Sample,'sampleGroup'))
        Aprefix = eval(config.get(Sample,'Aprefix'))
        cut = eval(config.get(Sample, 'cut'))
        if sampleType[0] != 'DATA':
            SF = eval(config.get(Sample, 'SF'))
            xSec = eval(config.get(Sample,'xSec'))
        
    for i in range(0,len(sampleName)):
        print cut[i]
        print Aprefix[i]
        copytree(pathIN,pathOUT,prefix,infile,Aprefix[i],cut[i]+Precut)
        info.append(sample(sampleName[i],sampleType[i]))
        info[-1].path=pathOUT
        info[-1].identifier=Aprefix[i]+infile
        info[-1].weightexpression=weightexpression
        info[-1].group=sampleGroup[i]
        info[-1].lumi=lumi
        info[-1].prefix=prefix
        info[-1].addtreecut(cut[i])
        if sampleType[i] != 'DATA':
            info[-1].xsec=(xSec[i])
            info[-1].sf=(SF[i])
        
#dump info   
infofile = open(pathOUT+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()
