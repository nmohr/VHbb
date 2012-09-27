#! /usr/bin/env python
import os,shutil,sys,pickle,subprocess,ROOT
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import sample
import getpass

Test=False

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

#theJobs = ['STbar_tW','ST_tW']
#theJobs = ['ZH110','ZH125','ZH120','Zudsg','Zbb','Zcc','ZH115','ZH130','ZZ','Zudsg70100','Zbb70100','Zcc70100','Zudsg5070','Zbb5070','Zcc5070','Zmm','Zudsg100','Zbb100','Zcc100','ST_s','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
#theJobs = ['ZH110','ZH125']
#theJobs = ['ST_t']
#theJobs = ['ZH110','ZH115','ZH120','ZH125','ZH130','ZH135','DY','DY120','TT','ZZ','WZ','WW','ST_s','ST_t','STbar_s','STbar_t','STbar_tW','ST_tW','Zee','Zmm']

#theJobs = ['ZH110','ZH125','ZH120','DY','ZH115','ZH130','ZH135','ZZ','DY120','Zmm','ST_s','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
#if energy=='8TeV':
#    theJobs = ['ZH110','ZH125','ZH120','DY','DY5070','DY70100','DY100','ZH115','ZH130','ZH135','ZZ','DY120','Zmm','ST_s','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
#if Test:
#	theJobs = ['WZ']


path = config.get("Directories","samplepath")
infofile = open(path+'/env/samples.info','r')
info = pickle.load(infofile)
infofile.close()

#submit('prepare',repDict)

for job in info:
    if Test and job.name == 'WZ':    
    	submit(job.name,repDict)
    elif not Test:
        submit(job.name,repDict)
