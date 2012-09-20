#! /usr/bin/env python
import os,time,subprocess
#energy='8TeV'
energy='7TeV'

def submit(job,en):
	command = 'qsub -V -cwd -q all.q -N %s_%s -o /shome/bortigno/VHbbAnalysis/VHbbTest/LOG/%s.out -e /shome/bortigno/VHbbAnalysis/VHbbTest/LOG/%s.err runAll.sh %s %s' %(job,en,job,job,job,en)
	print command
	subprocess.call([command], shell=True)

#theJobs = ['ZH110','ZH125','ZH120','DY','ZH115','ZH130','ZH135','ZZ','DY120','Zmm','ST_s','ST_t','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
#if energy=='8TeV':
#	theJobs = ['ZH110','ZH125','ZH120','DY','DY5070','DY70100','DY100','ZH115','ZH130','ZH135','ZZ','DY120','Zmm','ST_s','ST_t','TT','Zee','STbar_s','STbar_t','WZ','WW','STbar_tW','ST_tW']
theJobs = ["ZH120"]

for job in theJobs:
	submit(job,energy)
	#time.sleep(10)
