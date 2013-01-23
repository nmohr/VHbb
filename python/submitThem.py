#! /usr/bin/env python
from optparse import OptionParser
import sys

parser = OptionParser()
parser.add_option("-T", "--tag", dest="tag", default="",
                      help="Tag to run the analysis with, example '8TeV' uses config8TeV and pathConfig8TeV to run the analysis")
parser.add_option("-J", "--task", dest="task", default="",
                      help="Task to be done, i.e. 'dc' for Datacards, 'prep' for preparation of Trees, 'plot' to produce plots or 'eval' to write the MVA output or 'sys' to write regression and systematics (or 'syseval' for both). ")
parser.add_option("-M", "--mass", dest="mass", default="125",
		      help="Mass for DC or Plots, 110...135")
parser.add_option("-S","--samples",dest="samples",default="",
		      help="samples you want to run on")

(opts, args) = parser.parse_args(sys.argv)

import os,shutil,pickle,subprocess,ROOT
from myutils import BetterConfigParser, sample, parse_info
import getpass

if opts.tag == "":
	print "Please provide tag to run the analysis with, example '-T 8TeV' uses config8TeV and pathConfig8TeV to run the analysis."
	sys.exit(123)

if opts.task == "":
    print "Please provide a task.\n-J prep:\tpreparation of Trees\n-J sys:\t\twrite regression and systematics\n-J eval:\tcreate MVA output\n-J plot:\tproduce Plots\n-J dc:\t\twrite workspaces and datacards"
    sys.exit(123)

#create the list with the samples to run over
samplesList=opts.samples.split(",")

en = opts.tag
configs = ['%sconfig/general'%(en),'%sconfig/paths'%(en),'%sconfig/plots'%(en),'%sconfig/training'%(en),'%sconfig/datacards'%(en),'%sconfig/cuts'%(en)]
	
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
#check if the logPath exist. If not exit
if( not os.path.isdir(logPath) ):
	print 'ERROR: ' + logPath + ': dir not found.'
	print 'ERROR: Create it before submitting '
	print 'Exit'
	sys.exit(-1)

repDict = {'en':en,'logpath':logPath,'job':'','task':opts.task,'queue': 'all.q'}
def submit(job,repDict):
	repDict['job'] = job
	command = 'qsub -V -cwd -q %(queue)s -N %(job)s_%(en)s%(task)s -o %(logpath)s/%(job)s_%(en)s_%(task)s.out -e %(logpath)s/%(job)s_%(en)s_%(task)s.err runAll.sh %(job)s %(en)s ' %(repDict) + opts.task
	print command
	subprocess.call([command], shell=True)

if opts.task == 'dc':
    #DC_vars = config.items('Limit')
    DC_vars= (config.get('LimitGeneral','List')).split(',')
    print DC_vars

if opts.task == 'plot':
    Plot_vars= (config.get('Plot_general','List')).split(',')

if not opts.task == 'prep':
    path = config.get("Directories","samplepath")
    samplesinfo = config.get("Directories","samplesinfo")
    info = parse_info(samplesinfo,path)

if opts.task == 'plot': 
    repDict['queue'] = 'all.q'
    for item in Plot_vars:
        submit(item,repDict)

elif opts.task == 'dc':
    repDict['queue'] = 'all.q'
    for item in DC_vars:
        if 'ZH%s'%opts.mass in item:
            submit(item,repDict) 
        elif 'ZH' in item and opts.mass == 'all':
            submit(item,repDict)
            
elif opts.task == 'prep':
    submit('prepare',repDict)

elif opts.task == 'eval' or opts.task == 'sys' or opts.task == 'syseval':
    if ( opts.samples == ""):
        for job in info:
            submit(job.name,repDict)
    else:
        for sample in samplesList:
            submit(sample,repDict)

os.system('qstat') 
