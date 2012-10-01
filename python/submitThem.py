#! /usr/bin/env python
import os,shutil,sys,pickle,subprocess,ROOT
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import sample
import getpass

parser = OptionParser()
parser.add_option("-T", "--tag", dest="tag", default="",
                      help="Tag to run the analysis with, example '8TeV' uses config8TeV and pathConfig8TeV to run the analysis")
parser.add_option("-J", "--task", dest="task", default="",
                      help="Task to be done, i.e. 'dc' for Datacards, 'prep' for preparation of Trees, 'plot' to produce plots or 'eval' to write the MVA output or 'sys' to write regression and systematics. ")
parser.add_option("-M", "--mass", dest="mass", default="125",
		      help="Mass for DC or Plots, 110...135")
parser.add_option("-S","--samples",dest="samples",default="",
		      help="samples you want to run on")


(opts, args) = parser.parse_args(sys.argv)
if opts.tag == "":
	print "Please provide tag to run the analysis with, example '-T 8TeV' uses config8TeV and pathConfig8TeV to run the analysis."
	sys.exit(123)

if opts.task == "":
    print "Please provide a task.\n-J prep:\tpreparation of Trees\n-J sys:\t\twrite regression and systematics\n-J eval:\tcreate MVA output\n-J plot:\tproduce Plots\n-J dc:\t\twrite workspaces and datacards"
    sys.exit(123)

#create the list with the samples to run over
samplesList=opts.samples.split(",")

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
	command = 'qsub -V -cwd -q all.q -N %(job)s_%(en)s -o %(logpath)s/%(job)s_%(en)s.out -e %(logpath)s/%(job)s_%(en)s.err runAll.sh %(job)s %(en)s ' %(repDict) + opts.task
	print command
	subprocess.call([command], shell=True)

if opts.task == 'dc':
    DC_vars = config.items('Limit')
if opts.task == 'plot':
    Plot_vars= config.items('Plot')

if not opts.task == 'prep':
    path = config.get("Directories","samplepath")
    infofile = open(path+'/env/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()


if opts.task == 'plot': 
    for item in Plot_vars:
        if 'ZH%s'%opts.mass in item[0]:
            submit(item[0],repDict)
        elif opts.mass == '' and 'ZH' in item[0]:
            submit(item[0],repDict)

elif opts.task == 'dc':
    for item in DC_vars:
        if 'ZH%s'%opts.mass in item[0] and opts.tag in item[0]:
            submit(item[0],repDict) 
        elif 'ZH' in item[0] and opts.tag in item[0] and opts.mass == '*':
            submit(item[0],repDict)
elif opts.task == 'prep':
    submit('prepare',repDict)

elif opts.task == 'eval' or opts.task == 'sys':
    if ( opts.samples == ""):
        for job in info:
            submit(job.name,repDict)
    else:
        for sample in samplesList:
            submit(sample,repDict)
            
