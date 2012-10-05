#!/usr/bin/env python
from copytree import copytree
from printcolor import printc
from samplesclass import sample
import pickle
import sys
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
import ROOT

argv = sys.argv

#get files info from config
parser = OptionParser()
parser.add_option("-I", "--inPath", dest="pathIn", default="",
                      help="path to the input files")
parser.add_option("-O", "--outPath", dest="pathOut", default="",
                      help="path to the output files")
parser.add_option("-C", "--config", dest="config", default="",
                      help="configuration of samples")
parser.add_option("-U", "--update", dest="update", default=False, action='store_true',
                      help="append sample to existing samples.info")
parser.add_option("-D", "--dry", dest="dry", default=False, action='store_true',
                      help="dry drun - just write samples. info withou copying and skimming trees")
parser.add_option("-S", "--samples", dest="samples", default="",
                      help="List of samples")


(opts, args) = parser.parse_args(argv)

SamplesList=opts.samples.split(',')

pathIN=opts.pathIn
pathOUT=opts.pathOut

print "Config is: %s" %(opts.config)
config = BetterConfigParser()
config.read(opts.config)

prefix=config.get('General','prefix')
newprefix=config.get('General','newprefix')
lumi=float(config.get('General','lumi'))
weightexpression=config.get('General','weightexpression')
#this is only to speed it up, remove for final trees!
Precut=''
info = []

for Sample in config.sections():
    if not config.has_option(Sample,'infile'): continue
    if not SamplesList == [''] and not config.get(Sample,'sampleName') in SamplesList: continue
    infile = config.get(Sample,'infile')
    if not ROOT.TFile.Open(pathIN+prefix+infile+'.root',"READ"):
        print 'WARNING: No file ' + pathIN+prefix+infile+ ' found! '
        continue
    #this need exception handle    
    #if type(eval(config.get(Sample,'sampleName'))) != list: 
    
    
    #Initialize samplecalss element
    sampleName = config.get(Sample,'sampleName')
    sampleType = config.get(Sample,'sampleType')
    cut = config.get(Sample, 'cut')
    info.append(sample(sampleName,sampleType))

    info[-1].addtreecut(cut)
    info[-1].path=pathOUT
    info[-1].identifier=infile
    info[-1].weightexpression=weightexpression
    info[-1].lumi=lumi
    info[-1].prefix=newprefix
    
    if eval(config.get(Sample,'subsamples')):
        info[-1].subsamples=True
        info[-1].group = eval((config.get(Sample,'sampleGroup')))
        info[-1].subcuts = eval((config.get(Sample, 'subcuts')))
        info[-1].subnames = eval((config.get(Sample, 'subnames')))
        if sampleType != 'DATA':
            info[-1].sf = eval((config.get(Sample, 'SF')))
            info[-1].xsec = eval((config.get(Sample,'xSec')))    
    else:
        info[-1].group = config.get(Sample,'sampleGroup')
        if sampleType != 'DATA':
            info[-1].sf = config.get(Sample, 'SF')
            info[-1].xsec = config.get(Sample,'xSec')

    if not opts.dry:    
        copytree(pathIN,pathOUT,prefix,newprefix,infile,'',cut+Precut)

#dump info
if opts.update:
    infofile = open(pathOUT+'/samples.info','r')
    info_old = pickle.load(infofile)
    infofile.close()
    
    info += info_old

infofile = open(pathOUT+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()
