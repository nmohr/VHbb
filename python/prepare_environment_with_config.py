#! /usr/bin/env python
import os, pickle, sys, ROOT
from optparse import OptionParser
from myutils import BetterConfigParser, copytree, printc, sample, parse_info

argv = sys.argv

#get files info from config
parser = OptionParser()
#parser.add_option("-I", "--inPath", dest="pathIn", default="",
#                      help="path to the input files")
#parser.add_option("-O", "--outPath", dest="pathOut", default="",
#                      help="path to the output files")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="directory config")

(opts, args) = parser.parse_args(argv)

#pathIN=opts.pathIn
#pathOUT=opts.pathOut

config = BetterConfigParser()
config.read(opts.config)

pathIN = config.get('Directories','PREPin')
pathOUT = config.get('Directories','PREPout')
samplesinfo=config.get('Directories','samplesinfo')
sampleconf = BetterConfigParser()
sampleconf.read(samplesinfo)
prefix=sampleconf.get('General','prefix')

info = parse_info(samplesinfo,pathIN)

for job in info:
    copytree(pathIN,pathOUT,prefix,job.prefix,job.identifier,'',job.treecut)
