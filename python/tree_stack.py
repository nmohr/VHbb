#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from array import array
from BetterConfigParser import BetterConfigParser
import sys, os
from mvainfos import mvainfo
#from gethistofromtree import getHistoFromTree, orderandadd
from optparse import OptionParser
from HistoMaker import HistoMaker, orderandadd
from copy import deepcopy
from StackMaker import StackMaker

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-P", "--path", dest="path", default="",
                      help="path to samples")
parser.add_option("-R", "--reg", dest="region", default="",
                      help="region to plot")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
print opts.config
config = BetterConfigParser()
config.read(opts.config)

path = opts.path
region = opts.region

#get locations:
Wdir=config.get('Directories','Wdir')
samplesinfo=config.get('Directories','samplesinfo')

section='Plot:%s'%region

infofile = open(samplesinfo,'r')
info = pickle.load(infofile)
infofile.close()

#options = plot.split(',')

vars = (config.get(section, 'vars')).split(',')

if 'ZLight' in region or 'TTbar' in region or 'Zbb' in region: SignalRegion = False
else:
    SignalRegion = True
    print 'You are in the Signal Region!'

data = config.get(section,'Datas')

samples=config.get('Plot_general','samples')
samples=samples.split(',')

weightF=config.get('Weights','weightF')
Group = eval(config.get('Plot_general','Group'))


#GETALL AT ONCE
options = []
Stacks = []
for i in range(len(vars)):
    Stacks.append(StackMaker(config,vars[i],region,SignalRegion))
    options.append(Stacks[i].options)

Plotter=HistoMaker(path,config,region,options)

#print '\nProducing Plot of %s\n'%vars[v]
Lhistos = [[] for _ in range(0,len(vars))]
Ltyps = [[] for _ in range(0,len(vars))]
Ldatas = [[] for _ in range(0,len(vars))]
Ldatatyps = [[] for _ in range(0,len(vars))]
Ldatanames = [[] for _ in range(0,len(vars))]


#Find out Lumi:
lumicounter=0.
lumi=0.
for job in info:
    if job.name in data:
        lumi+=float(job.lumi)
        lumicounter+=1.

if lumicounter > 0:
    lumi=lumi/lumicounter

Plotter.lumi=lumi
mass = Stacks[0].mass


for job in info:
    if eval(job.active):
        if job.subsamples:
            for subsample in range(0,len(job.subnames)):
                
                if job.subnames[subsample] in samples:
                    hTempList, typList = Plotter.getHistoFromTree(job,subsample)
                    for v in range(0,len(vars)):
                        Lhistos[v].append(hTempList[v])
                        Ltyps[v].append(Group[job.subnames[subsample]])
                        print job.subnames[subsample]

        else:
            if job.name in samples:
                if job.name == mass:
                    print job.name
                    hTempList, typList = Plotter.getHistoFromTree(job)
                    for v in range(0,len(vars)):
                        if SignalRegion:
                            Lhistos[v].append(hTempList[v])
                            Ltyps[v].append(Group[job.name])
                        Overlaylist= deepcopy(hTempList)
                                                                                                                             
                else:
                    print job.name
                    hTempList, typList = Plotter.getHistoFromTree(job)
                    for v in range(0,len(vars)):
                        Lhistos[v].append(hTempList[v])
                        Ltyps[v].append(Group[job.name])

            elif job.name in data:
                #print 'DATA'
                hTemp, typ = Plotter.getHistoFromTree(job)
                for v in range(0,len(vars)):
                    Ldatas[v].append(hTemp[v])
                    Ldatatyps[v].append(typ[v])
                    Ldatanames[v].append(job.name)


for v in range(0,len(vars)):

    histos = Lhistos[v]
    typs = Ltyps[v]
    Stacks[v].histos = Lhistos[v]
    Stacks[v].typs = Ltyps[v]
    Stacks[v].datas = Ldatas[v]
    Stacks[v].datatyps = Ldatatyps[v]
    Stacks[v].datanames= Ldatanames[v]
    Stacks[v].overlay = Overlaylist[v]
    Stacks[v].lumi = lumi
    
    Stacks[v].doPlot()


    print 'i am done!\n'

sys.exit(0)
