#!/usr/bin/env python
from optparse import OptionParser
from myutils import BetterConfigParser, parse_info
import sys

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-S","--samples", dest="samples", default='',
                  help="Sample to split. ( comma separated )")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
parser.add_option("-M", "--max-events", dest='maxEvents', default=10000,
                      help="max number of events per file. Default 10000")


(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
config = BetterConfigParser()
config.read(opts.config)

import ROOT
ROOT.gROOT.SetBatch(True)

namelistIN=opts.samples
namelist=namelistIN.split(',')
samplesinfo=config.get('Directories','samplesinfo')
INpath=config.get('Directories','samplepath')+'/envW/sys/'
OUTpath=INpath # for the moemnt OUTpath = INpath ->> TO FIX
info = parse_info(samplesinfo,INpath)


for job in info:
    if eval(job.active):
        if job.name in namelist:
            #get trees:
            print INpath+'/'+job.prefix+job.identifier+'.root'
            sourceFile = ROOT.TFile.Open(INpath+'/'+job.prefix+job.identifier+'.root','read')
	    Tree = sourceFile.Get('tree')
	    obj = ROOT.TObject
	    nentries = Tree.GetEntries()
	    print nentries
	    maxEvents = long(opts.maxEvents)
            #get the number of files to be created
	    if(maxEvents > 0.):
		    number_of_files = (nentries/maxEvents)+1
	    else :
		    sys.exit('%ERROR: Max number of events per file null or negative.')
	    print 'Splitting in ' + str(number_of_files) +' files'
	    for i in range(number_of_files):
		    print i
	            #create the output file
		    print OUTpath+'/split/'+job.prefix+job.identifier+'_'+str(i)+'.root'
		    output = ROOT.TFile.Open(OUTpath+'/split/'+job.prefix+job.identifier+'_'+str(i)+'.root','recreate')
                    #copy the histograms in the new file
		    sourceFile.cd()
		    for key in ROOT.gDirectory.GetListOfKeys():
			    obj = key.ReadObj()
			    if obj.GetName() == 'tree':
				    continue
			    output.cd()
			    obj.Write(key.GetName())
                    #now split and copy the tree
		    output.cd()
		    outTree = Tree.CopyTree("","",maxEvents*(i+1),maxEvents*i)
		    outTree.AutoSave()
		    output.Write()
		    output.Close()
	    sourceFile.Close()

