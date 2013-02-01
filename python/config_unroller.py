#!/usr/bin/env python
import os,sys,ROOT
from optparse import OptionParser
ROOT.gROOT.SetBatch(True)

#--CONFIGURE---------------------------------------------------------------------
argv = sys.argv
parser = OptionParser()
parser.add_option("-S", "--section", dest="section", default="Cuts",
                              help="Config section")
parser.add_option("-V", "--value", dest="var", default="",
                              help="Config value")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                              help="configuration file")
(opts, args) = parser.parse_args(argv)

from myutils import BetterConfigParser

config = BetterConfigParser()
config.read(opts.config)
print config.get(opts.section,opts.var)
