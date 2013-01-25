import os, sys, warnings
from copy import copy
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import Sample

class ParseInfo:
    def __init__(self,samples_config,samples_path):
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

        self._samplelist = []

        self.__fileslist=[]
        if T3:
            ls = os.popen("lcg-ls -b -D srmv2 -l srm://t3se01.psi.ch:8443/srm/managerv2?SFN="+t3_path)
        else:
            ls = os.popen("ls -l "+samples_path)
    
        for line in ls.readlines():
            self.__fileslist.append(line)


        for sample in config.sections():
        
            if not config.has_option(sample,'infile'): continue
            infile = config.get(sample,'infile')
            sampleName = config.get(sample,'sampleName')

            if any(infile in file for file in self.__fileslist):
                print 'Sample %s is present'%(sampleName)
            else:
                warnings.warn('Sample %s is NOT! present'%(sampleName))
                warnings.warn("File %s not present"%(infile))
            #Initialize samplecalss element
            sampleType = config.get(sample,'sampleType')
            cut = config.get(sample, 'cut')
            newsample = Sample(sampleName,sampleType)

            newsample.addtreecut = cut
            newsample.identifier=infile
            newsample.weightexpression=weightexpression
            newsample.lumi=lumi
            newsample.prefix=newprefix
            
            if eval(config.get(sample,'subsamples')):
                subnames = eval((config.get(sample, 'subnames')))
                subcuts = eval((config.get(sample, 'subcuts')))
                subgroups = eval((config.get(sample,'sampleGroup')))
                if sampleType != 'DATA':
                    subxsecs = eval((config.get(sample, 'xSec')))
                    subsfs = eval((config.get(sample, 'SF')))
                newsamples = []
                for i,cut in enumerate(subcuts):
                    newsubsample = copy(newsample)
                    newsubsample.subsample = True
                    newsubsample.name = subnames[i]
                    newsubsample.subcut = subcuts[i]
                    newsubsample.group = subgroups[i]
                    if sampleType != 'DATA':
                        newsubsample.sf = float(subsfs[i])
                        newsubsample.xsec = float(subxsecs[i])
                    newsamples.append(newsubsample)
                self._samplelist.extend(newsamples)
                self._samplelist.append(newsample)
            else:
                if sampleType != 'DATA':
                    newsample.xsec = eval((config.get(sample,'xSec')))    
                    newsample.sf = eval((config.get(sample, 'SF')))
                newsample.group = config.get(sample,'sampleGroup')
                self._samplelist.append(newsample)

    def __iter__(self):
        for sample in self._samplelist:
            if sample.active:
                yield sample

    def get_sample(self, samplename):
        for sample in self._samplelist:
            if sample.name == samplename:
                return sample
        return None
    
    def get_samples(self, samplenames):
        samples = []
        thenames = []
        for sample in self._samplelist:
            if sample.name in samplenames:
                samples.append(sample)
                thenames.append(sample.name)
        return samples
