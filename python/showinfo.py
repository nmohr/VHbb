#!/usr/bin/env python
from samplesclass import sample
import pickle
import sys

samplepath=sys.argv[1]

infofile = open(samplepath+'/samples.info','r')
info = pickle.load(infofile)

print '\tLOADED INFO OF %s SAMPLES:'%len(info)
print '\n\n\t\033[1;34mLOADED INFO OF %s SAMPLES\033[1;m\n'%len(info)

for job in info:
    print '\t\033[1;31m-->%s: %s\033[1;m'%(job.name,job.group)
    print '\t\tstored in file %s'%job.getpath()
    print '\t\twith luminosity = %s and xsec = %s'%(job.lumi,job.xsec)    
    print '\t\tdefined as type %s'%job.type
    print '\t\tcuts applied: %s'%job.treecut
    print '\t\tScalefactor: %s'%job.sf
    print '\t\tSplitting: %s'%job.split
    
    if job.subsamples:
        print '\t\tSubsamples:'
        print '\t\tGroups: %s'%job.group
        print '\t\tnames: %s'%job.subnames
        print '\t\tcuts: %s'%job.subcuts
    #print job.subcuts
    print '\t\tActive: %s'%job.active
    print '\t\tSystematics available:'
    for sys in job.SYS: print '\t\t\t\033[1;32m- %s\033[1;m'%sys
    comments=str.split(job.comment,'\n')
    print '\t\tsample info:'
    for comment in comments:
        print '\t\t\t'+ comment
    print ''
infofile.close()