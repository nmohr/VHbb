#! /usr/bin/env python
from optparse import OptionParser
import sys
import time
import os
import shutil

parser = OptionParser()
parser.add_option("-T", "--tag", dest="tag", default="",
                      help="Tag to run the analysis with, example '8TeV' uses config8TeV and pathConfig8TeV to run the analysis")
parser.add_option("-J", "--task", dest="task", default="",
                      help="Task to be done, i.e. 'dc' for Datacards, 'prep' for preparation of Trees, 'plot' to produce plots or 'eval' to write the MVA output or 'sys' to write regression and systematics (or 'syseval' for both). ")
parser.add_option("-M", "--mass", dest="mass", default="125",
		      help="Mass for DC or Plots, 110...135")
parser.add_option("-S","--samples",dest="samples",default="",
		      help="samples you want to run on")
parser.add_option("-F", "--folderTag", dest="ftag", default="",
                      help="Creats a new folder structure for outputs or uses an existing one with the given name")
parser.add_option("-N", "--number-of-events", dest="nevents_split", default=100000,
                      help="Number of events per file when splitting.")
parser.add_option("-P", "--philipp-love-progress-bars", dest="philipp_love_progress_bars", default=False,
                      help="If you share the love of Philipp...")

(opts, args) = parser.parse_args(sys.argv)

import os,shutil,pickle,subprocess,ROOT,re
ROOT.gROOT.SetBatch(True)
from myutils import BetterConfigParser, Sample, ParseInfo
import getpass

if opts.tag == "":
	print "Please provide tag to run the analysis with, example '-T 8TeV' uses config8TeV and pathConfig8TeV to run the analysis."
	sys.exit(123)

if opts.task == "":
    print "Please provide a task.\n-J prep:\tpreparation of Trees\n-J sys:\t\twrite regression and systematics\n-J eval:\tcreate MVA output\n-J plot:\tproduce Plots\n-J dc:\t\twrite workspaces and datacards"
    sys.exit(123)


en = opts.tag

#create the list with the samples to run over
samplesList=opts.samples.split(",")

timestamp = time.asctime().replace(' ','_').replace(':','-')

configs = ['%sconfig/general'%(en),'%sconfig/paths'%(en),'%sconfig/plots'%(en),'%sconfig/training'%(en),'%sconfig/datacards'%(en),'%sconfig/cuts'%(en)]

pathconfig = BetterConfigParser()
pathconfig.read('%sconfig/paths'%(en))

if not opts.ftag == '':
    tagDir = pathconfig.get('Directories','tagDir')
    DirStruct={'tagDir':tagDir,'ftagdir':'%s/%s/'%(tagDir,opts.ftag),'logpath':'%s/%s/%s/'%(tagDir,opts.ftag,'Logs'),'plotpath':'%s/%s/%s/'%(tagDir,opts.ftag,'Plots'),'limitpath':'%s/%s/%s/'%(tagDir,opts.ftag,'Limits'),'confpath':'%s/%s/%s/'%(tagDir,opts.ftag,'config') }

    for keys in ['tagDir','ftagdir','logpath','plotpath','limitpath','confpath']:
        try:
            os.stat(DirStruct[keys])
        except:
            os.mkdir(DirStruct[keys])

    pathfile = open('%sconfig/paths'%(en))
    buffer = pathfile.readlines()
    pathfile.close()
    os.rename('%sconfig/paths'%(en),'%sconfig/paths.bkp'%(en))
    pathfile = open('%sconfig/paths'%(en),'w')
    for line in buffer:
        if line.startswith('plotpath'):
            line = 'plotpath: %s\n'%DirStruct['plotpath']
        elif line.startswith('logpath'):
            line = 'logpath: %s\n'%DirStruct['logpath']
        elif line.startswith('limits'):
            line = 'limits: %s\n'%DirStruct['limitpath']
        pathfile.write(line)
    pathfile.close()

    #copy config files
    for item in configs:
        shutil.copyfile(item,'%s/%s/%s'%(tagDir,opts.ftag,item.strip(en)))


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

repDict = {'en':en,'logpath':logPath,'job':'','task':opts.task,'queue': 'all.q','timestamp':timestamp,'additional':'','job_id':''}
def submit(job,repDict):
	repDict['job'] = job
	command = 'qsub -V -cwd -q %(queue)s -l h_vmem=6G -N %(job)s_%(en)s%(task)s -o %(logpath)s/%(timestamp)s_%(job)s_%(en)s_%(task)s.out -e %(logpath)s/%(timestamp)s_%(job)s_%(en)s_%(task)s.err runAll.sh %(job)s %(en)s ' %(repDict) + opts.task + ' ' + repDict['job_id'] + ' ' + repDict['additional']
	print command
	subprocess.call([command], shell=True)

if opts.task == 'train':
    train_list = (config.get('MVALists','List_for_submitscript')).split(',')
    print train_list
    for item in train_list:
        submit(item,repDict)


if opts.task == 'dc':
    #DC_vars = config.items('Limit')
    DC_vars= (config.get('LimitGeneral','List')).split(',')
    print DC_vars

if opts.task == 'plot':
    Plot_vars= (config.get('Plot_general','List')).split(',')

if not opts.task == 'prep':
    path = config.get("Directories","samplepath")
    samplesinfo = config.get("Directories","samplesinfo")
    info = ParseInfo(samplesinfo,path)

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

elif opts.task == 'sys' or opts.task == 'syseval':
    path = config.get("Directories","SYSin")
    samplesinfo = config.get("Directories","samplesinfo")
    info = ParseInfo(samplesinfo,path)
    if ( opts.samples == ""):
        for job in info:
	    if (job.subsample): continue
            submit(job.name,repDict)
    else:
        for sample in samplesList:
            submit(sample,repDict)

elif opts.task == 'eval':
    path = config.get("Directories","MVAin")
    samplesinfo = config.get("Directories","samplesinfo")
    info = ParseInfo(samplesinfo,path)
    if ( opts.samples == ""):
        for job in info:
	    if (job.subsample): continue
            submit(job.name,repDict)
    else:
        for sample in samplesList:
            submit(sample,repDict)


elif( opts.task == 'split' ):
	path = config.get("Directories","SPLITin")
	samplesinfo = config.get("Directories","samplesinfo")
	repDict['additional']=opts.nevents_split
	info = ParseInfo(samplesinfo,path)
	if ( opts.samples == ""):
		for job in info:
			if (job.subsample): continue
			submit(job.name,repDict)
	else:
		for sample in samplesList:
			submit(sample,repDict)

#BDT optimisation
elif opts.task == 'mva_opt':
	total_number_of_steps=1
	setting = ''
	for par in (config.get('Optimisation','parameters').split(',')):
		scan_par=eval(config.get('Optimisation',par))
		setting+=par+'='+str(scan_par[0])+':'
		if len(scan_par) > 1 and scan_par[2] != 0:
			total_number_of_steps+=scan_par[2]
	setting=setting[:-1] # eliminate last column at the end of the setting string
	print setting
	repDict['additional']=setting
	repDict['job_id']=config.get('Optimisation','training')
	submit('OPT_main_set',repDict)
	main_setting=setting

	#Scanning all the parameters found in the training config in the Optimisation sector
	for par in (config.get('Optimisation','parameters').split(',')):
		scan_par=eval(config.get('Optimisation',par))
		print par
		if len(scan_par) > 1 and scan_par[2] != 0:
			for step in range(scan_par[2]):
				value = (scan_par[0])+((1+step)*(scan_par[1]-scan_par[0])/scan_par[2])
				print value
				setting=re.sub(par+'.*?:',par+'='+str(value)+':',main_setting)
				repDict['additional']=setting
#				repDict['job_id']=config.get('Optimisation','training')
				submit('OPT_'+par+str(value),repDict)
#				submit(config.get('Optimisation','training'),repDict)
				print setting


os.system('qstat')
if (opts.philipp_love_progress_bars):
	os.system('./qstat.py') 
