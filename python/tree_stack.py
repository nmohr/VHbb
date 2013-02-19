#!/usr/bin/env python
import pickle
import ROOT 
from array import array
import sys, os
from optparse import OptionParser
from copy import copy,deepcopy
from math import sqrt
ROOT.gROOT.SetBatch(True)

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-R", "--reg", dest="region", default="",
                      help="region to plot")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
        
from myutils import BetterConfigParser, printc, ParseInfo, mvainfo, StackMaker, HistoMaker

print opts.config
opts.config.append('8TeVconfig/vhbbPlotDef.ini')
config = BetterConfigParser()
config.read(opts.config)

#path = opts.path
region = opts.region

#get locations:
Wdir=config.get('Directories','Wdir')
samplesinfo=config.get('Directories','samplesinfo')

path = config.get('Directories','plottingSamples')

section='Plot:%s'%region

info = ParseInfo(samplesinfo,path)

#----------Histo from trees------------
def doPlot():
    vars = (config.get(section, 'vars')).split(',')

    if 'ZLight' in region or 'TTbar' in region or 'Zbb' in region: 
        SignalRegion = False
    else:
        SignalRegion = True
        print 'You are in the Signal Region!'

    data = config.get(section,'Datas')

    mc=eval(config.get('Plot_general','samples'))

    datasamples = info.get_samples(data)
    mcsamples = info.get_samples(mc)

    GroupDict = eval(config.get('Plot_general','Group'))

    #GETALL AT ONCE
    options = []
    Stacks = []
    for i in range(len(vars)):
        Stacks.append(StackMaker(config,vars[i],region,SignalRegion))
        options.append(Stacks[i].options)
    print options

    Plotter=HistoMaker(mcsamples+datasamples,path,config,options,GroupDict)

    #print '\nProducing Plot of %s\n'%vars[v]
    Lhistos = [[] for _ in range(0,len(vars))]
    Ltyps = [[] for _ in range(0,len(vars))]
    Ldatas = [[] for _ in range(0,len(vars))]
    Ldatatyps = [[] for _ in range(0,len(vars))]
    Ldatanames = [[] for _ in range(0,len(vars))]

    #Find out Lumi:
    lumicounter=0.
    lumi=0.
    for job in datasamples:
        lumi+=float(job.lumi)
        lumicounter+=1.

    if lumicounter > 0:
        lumi=lumi/lumicounter

    Plotter.lumi=lumi
    mass = Stacks[0].mass

    for job in mcsamples:
        #hTempList, typList = Plotter.get_histos_from_tree(job)
        hDictList = Plotter.get_histos_from_tree(job)
        if job.name == mass:
            print job.name
            Overlaylist= deepcopy([hDictList[v].values()[0] for v in range(0,len(vars))])
        for v in range(0,len(vars)):
            Lhistos[v].append(hDictList[v].values()[0])
            Ltyps[v].append(hDictList[v].keys()[0])

    for job in datasamples:
        #hTemp, typ = Plotter.get_histos_from_tree(job)
        dDictList = Plotter.get_histos_from_tree(job)
        for v in range(0,len(vars)):
            Ldatas[v].append(dDictList[v].values()[0])
            Ldatatyps[v].append(dDictList[v].keys()[0])
            Ldatanames[v].append(job.name)

    for v in range(0,len(vars)):

        histos = Lhistos[v]
        typs = Ltyps[v]
        Stacks[v].histos = Lhistos[v]
        Stacks[v].typs = Ltyps[v]
        Stacks[v].datas = Ldatas[v]
        Stacks[v].datatyps = Ldatatyps[v]
        Stacks[v].datanames= Ldatanames[v]
        if SignalRegion:
            Stacks[v].overlay = Overlaylist[v]
        Stacks[v].lumi = lumi
        Stacks[v].doPlot()
        print 'i am done!\n'
#----------------------------------------------------
doPlot()
sys.exit(0)
