#! /usr/bin/env python
import os,shutil,sys,pickle,subprocess,ROOT
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import sample
import getpass


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
btagLibrary = config.get('BTagReshaping','library')
submitDir = os.getcwd()
os.chdir(os.path.dirname(btagLibrary))
if not os.path.exists(btagLibrary):
    ROOT.gROOT.LoadMacro('%s+'%btagLibrary.replace('_h.so','.h')) 
shutil.copyfile(os.path.basename(btagLibrary),'/scratch/%s/%s'%(getpass.getuser(),os.path.basename(btagLibrary)))
shutil.copyfile('/scratch/%s/%s'%(getpass.getuser(),os.path.basename(btagLibrary)),btagLibrary)
os.chdir(submitDir)
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
