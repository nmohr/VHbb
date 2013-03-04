import os, sys, warnings
from copy import copy
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
from samplesclass import Sample

def findnth(haystack, needle, n):
        parts= haystack.split(needle, n+1)
        if len(parts)<=n+1:
            return -1
        return len(haystack)-len(parts[-1])-len(needle)


def test_samples(run_on_fileList,__fileslist,config_sections):
        for _listed_file,_config_entry in map(None,__fileslist,config_sections): # loop in both, fileList and config
                if( run_on_fileList and _listed_file == None ): # check the option to know whether to run in fileList mode or in config mode
                        return False
                elif( (not run_on_fileList) and _config_entry == None ):
                        return False
                else: return True

def check_correspondency(sample,list,config):
        if any( sample in file for file in list ):
                print '@INFO: Sample %s is present'%(config.get(sample,'sampleName'))
        else:
                warnings.warn('@INFO: Sample %s is NOT! present'%(config.get(sample,'sampleName')))
                warnings.warn("@INFO: File %s not present"%(config.get(sample,'infile')))


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
                if('.root' in line):
                        truncated_line = line[line.rfind('/')+1:]
                        _p = findnth(truncated_line,'.',2)
                        #print truncated_line[_p+1:]
                        self.__fileslist.append(truncated_line[_p+1:truncated_line.rfind('.')])

        print '@DEBUG: ' + str(self.__fileslist)

        run_on_fileList = eval(config.get('Samples_running','run_on_fileList'))

        if( not test_samples(run_on_fileList,self.__fileslist,config.sections()) ): # stop if it finds None as sample
                sys.exit('@ERROR: Sample == None. Check RunOnFileList flag in section General, the sample_config of the sample directory.')

        for _listed_file,_config_entry in map(None,self.__fileslist,config.sections()): # loop in both, fileList and config
            if( run_on_fileList ): # check the option to know whether to run in fileList mode or in config mode
                _sample = _listed_file
                self._list = self.__fileslist
            else:
                _sample = _config_entry
                self._list = config.sections()

            sample = self.checkSplittedSample(_sample)
            if not config.has_option(sample,'infile'): continue
            infile = _sample
            sampleName = config.get(sample,'sampleName')
            print _sample
            
            check_correspondency(sample,self._list,config)

#               if ( run_on_file_list and any( sample in file for file in config.sections() ) ) or ( !run_on_file_list and any (sample in file for file in self.__fileList) ):
#                   print 'Sample %s is present'%(sampleName)
#               else:
#                   warnings.warn('Sample %s is NOT! present'%(sampleName))
#                   warnings.warn("File %s not present"%(infile))
                    
            
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

    #NOT USED. STILL NEEDED?
    def get_sample(self, samplename):
            if (checkSplittedSampleName(samplename)):
                    print('@WARNING: Running on splitted samples')
            for sample in self._samplelist:
                    if sample.name == samplename:
                            return sample
                    return None
    
    def get_samples(self, samplenames):
        print '### GET SAMPLES ###'
        samples = []
        thenames = []
        #for splitted samples use the identifier. There is always only one. if list, they are all true
        print(self.checkSplittedSampleName(samplenames[0]))
        if (self.checkSplittedSampleName(samplenames[0])):
                for sample in self._samplelist:
                        if (sample.subsample): continue #avoid multiple submissions from subsamples
                        print '@DEBUG: samplenames ' + samplenames[0]
                        print '@DEBUG: sample identifier ' + sample.identifier
                        if sample.identifier == samplenames[0]:
                                samples.append(sample)
                                thenames.append(sample.name)
        #else check the name
        else:
                for sample in self._samplelist:
                        if sample.name in samplenames:
                                #if (sample.subsample): continue #avoid multiple submissions from subsamples
                                samples.append(sample)
                                thenames.append(sample.name)
        return samples


    #it checks whether filename is a splitted sample or is a pure samples and returns the file name without the _#
    def checkSplittedSample(self, filename):
            print '### CHECKSPLITTEDSAMPLE ###'
            try:
                    isinstance( eval(filename[filename.rfind('_')+1:] ) , int )
                    print isinstance( eval(filename[filename.rfind('_')+1:] ) , int )
                    print '@DEBUG: fileName in CHECKSPLITTEDSAMPLE : ' + filename
                    print '@DEBUG: return in CHECKSPLITTEDSAMPLE : ' + filename[:filename.rfind('_')]
                    return filename[:filename.rfind('_')]
            except:
                    return filename

    #bool
    def checkSplittedSampleName(self,filename):
            print '### CHECKSPLITTEDSAMPLENAME ###'
            print filename
            # if there is an underscore in the filename
            if ( filename.rfind('_') > 0. ) :
                    try:
                            return isinstance( eval(filename[filename.rfind('_')+1:] ) , int )
                    except:
                            return False
            else:
                    return False
            
