#! /usr/bin/env python
import os,sys,pickle,subprocess
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import sample

parser = OptionParser()
parser.add_option("-T", "--tag", dest="tag", default="",
                      help="Tag to run the analysis with, example '8TeV' uses config8TeV and pathConfig8TeV to run the analysis")

(opts, args) = parser.parse_args(sys.argv)
if opts.tag == "":
	print "Please provide tag to run the analysis with, example '-T 8TeV' uses config8TeV and pathConfig8TeV to run the analysis."
	sys.exit(123)
en = opts.tag
configs = ['config%s'%(en),'pathConfig%s'%(en)]
print configs
config = BetterConfigParser()
config.read(configs)
logPath = config.get("Directories","logpath")
repDict = {'en':en,'logpath':logPath,'job':''}
def submit(job,repDict):
	repDict['job'] = job
	command = 'qsub -V -cwd -q all.q -N %(job)s_%(en)s -o %(logpath)s/%(job)s_%(en)s.out -e %(logpath)s/%(job)s_%(en)s.err runAll.sh %(job)s %(en)s' %repDict
	print command
	subprocess.call([command], shell=True)

path = config.get("Directories","samplepath")
infofile = open(path+'/env/samples.info','r')
info = pickle.load(infofile)
infofile.close()

for job in info:
	submit(job.name,repDict)
