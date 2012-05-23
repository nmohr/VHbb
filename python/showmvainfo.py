#!/usr/bin/env python
from samplesclass import sample
import pickle
import sys
import init

filename=sys.argv[1]

infofile = open(init.Wdir+'/weights/'+filename,'r')
job = pickle.load(infofile)

print '\n\n\t\033[1;34mLOADED INFO OF %s MVA\033[1;m\n'%job.MVAname

print '\t\tfactory name:  %s'%job.factoryname
print '\t\tfactorysettings: \033[1;31m%s\033[1;m'%job.factorysettings    
print '\t\tMVAname: %s'%job.MVAname
print '\t\tMVAtype: %s'%job.MVAtype
print '\t\tMVAsettings: \033[1;31m%s\033[1;m'%job.MVAsettings
print '\t\ttrained on: %s'%job.Tpath
print '\t\tevaluated on: %s'%job.Epath
print '\t\tVariables: \033[1;32m%s\033[1;m'%job.vars
print '\t\tSpectators: \033[1;32m%s\033[1;m'%job.spectators
comments=str.split(job.comment,'\n')
print '\t\tsample info:'
for comment in comments:
    print '\t\t\t'+ comment
print ''
infofile.close()