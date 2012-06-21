#! /usr/bin/env python
import os,time,subprocess

def submit(job):
	command = 'qsub -q all.q -N %s -o /shome/nmohr/VHbbAnalysis/LOG/%s.out -e /shome/nmohr/VHbbAnalysis/LOG/%s.err runAll.sh %s' %(job,job,job,job)
	print command
	subprocess.call([command], shell=True)

#theJobs = ['STbar_tW','ST_tW']
#theJobs = ['ZH110','ZH125','ZH120','Zudsg','Zbb','Zcc','ZH115','ZH130','ZZ','Zudsg70100','Zbb70100','Zcc70100','Zudsg5070','Zbb5070','Zcc5070','Zmm','Zudsg100','Zbb100','Zcc100','ST_s','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
#theJobs = ['ZH110','ZH125']
theJobs = ['ZH110','ZH125','ZH120','Zudsg','Zbb','Zcc','ZH115','ZH130','ZZ','Zudsg70100','Zbb70100','Zcc70100','Zudsg5070','Zbb5070','Zcc5070','Zmm','Zudsg100','Zbb100','Zcc100','ST_s','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']


for job in theJobs:
	submit(job)
	#time.sleep(10)
