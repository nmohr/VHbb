#!/usr/bin/env python
import sys
from optparse import OptionParser
from myutils import BetterConfigParser,RegressionTrainer

argv = sys.argv
parser = OptionParser()
parser.add_option("-v", "--verbose", action="store_true", dest="verbose", default=False,
                          help="Verbose mode.")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")

(opts, args) = parser.parse_args(argv)
if opts.config =="":
    opts.config = "config"

#load config
config = BetterConfigParser()
config.read(opts.config)

RegTrainer = RegressionTrainer(config)
RegTrainer.train()

