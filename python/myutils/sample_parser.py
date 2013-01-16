import os, sys
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import sample

def parse_info(samples_config,samples_path):
    try:
        os.stat(samples_config)
    except:
        raise Exception('config file is wrong/missing')
          
    if '/pnfs/psi.ch/cms/' in samples_path:
        T3 = True
        _,p2=samples_path.split('/pnfs/')
        t3_path = '/pnfs/'+p2.strip('\n')
    else:
        T3 = False

    config = BetterConfigParser()
    config.read(samples_config)

    newprefix=config.get('General','newprefix')
    lumi=float(config.get('General','lumi'))
    weightexpression=config.get('General','weightexpression')

    info = []

    fileslist=[]
    if T3:
        ls = os.popen("lcg-ls -b -D srmv2 -l srm://t3se01.psi.ch:8443/srm/managerv2?SFN="+t3_path)
    else:
        ls = os.popen("ls -l "+samples_path)
    
    for line in ls.readlines():
        fileslist.append(line)

    print fileslist

    for Sample in config.sections():
        
        if not config.has_option(Sample,'infile'): continue
        #if not SamplesList == [''] and not config.get(Sample,'sampleName') in SamplesList: continue
        infile = config.get(Sample,'infile')
        sampleName = config.get(Sample,'sampleName')

        if any(infile in file for file in fileslist):
            print 'Sample %s is present'%(sampleName)
        else:
            print 'Sample %s is NOT! present'%(sampleName)
            raise Exception("File %s not present"%(infile))
        #Initialize samplecalss element
        sampleType = config.get(Sample,'sampleType')
        cut = config.get(Sample, 'cut')
        info.append(sample(sampleName,sampleType))

        info[-1].addtreecut(cut)
        info[-1].path=samples_path
        info[-1].identifier=infile
        info[-1].weightexpression=weightexpression
        info[-1].lumi=lumi
        info[-1].prefix=newprefix
        
        if eval(config.get(Sample,'subsamples')):
            info[-1].subsamples=True
            info[-1].group = eval((config.get(Sample,'sampleGroup')))
            info[-1].subcuts = eval((config.get(Sample, 'subcuts')))
            info[-1].subnames = eval((config.get(Sample, 'subnames')))
            if sampleType != 'DATA':
                info[-1].sf = eval((config.get(Sample, 'SF')))
                info[-1].xsec = eval((config.get(Sample,'xSec')))    
        else:
            info[-1].group = config.get(Sample,'sampleGroup')
            if sampleType != 'DATA':
                info[-1].sf = config.get(Sample, 'SF')
                info[-1].xsec = config.get(Sample,'xSec')

    return info
