from __future__ import print_function
import os,sys,subprocess,hashlib
import ROOT
from samplesclass import Sample

class TreeCache:
    def __init__(self, cutList, sampleList, path, config):
        ROOT.gROOT.SetBatch(True)
        self.path = path
        self._cutList = []
        for cut in cutList:
            self._cutList.append('(%s)'%cut.replace(' ',''))
        try:
            self.__tmpPath = os.environ["TMPDIR"]
        except KeyError:
            print("\x1b[32;5m %s \x1b[0m" %open('%s/data/vhbb.txt' %config.get('Directories','vhbbpath')).read())
            print("\x1b[31;5;1m\n\t>>> %s: Please set your TMPDIR and try again... <<<\n\x1b[0m" %os.getlogin())
            sys.exit(-1)

        self.__doCache = True
        if config.has_option('Directories','tmpSamples'):
            self.__tmpPath = config.get('Directories','tmpSamples')
        self.__hashDict = {}
        self.minCut = None
        self.__find_min_cut()
        self.__sampleList = sampleList
        print('\n\t>>> Caching FILES <<<\n')
        self.__cache_samples()
    
    def __find_min_cut(self):
        effective_cuts = []
        for cut in self._cutList:
            if not cut in effective_cuts:
                effective_cuts.append(cut)
        self._cutList = effective_cuts
        self.minCut = '||'.join(self._cutList)

    def __trim_tree(self, sample):
        theName = sample.name
        print('Reading sample <<<< %s' %sample)
        source = '%s/%s' %(self.path,sample.get_path)
        checksum = self.get_checksum(source)
        theHash = hashlib.sha224('%s_s%s_%s' %(sample,checksum,self.minCut)).hexdigest()
        self.__hashDict[theName] = theHash
        tmpSource = '%s/tmp_%s.root'%(self.__tmpPath,theHash)
        if self.__doCache and self.file_exists(tmpSource):
            return
        output = ROOT.TFile.Open(tmpSource,'recreate')
        input = ROOT.TFile.Open(source,'read')
        output.cd()
        tree = input.Get(sample.tree)
        CountWithPU = input.Get("CountWithPU")
        CountWithPU2011B = input.Get("CountWithPU2011B")
        sample.count_with_PU = CountWithPU.GetBinContent(1) 
        sample.count_with_PU2011B = CountWithPU2011B.GetBinContent(1) 
        input.cd()
        obj = ROOT.TObject
        for key in ROOT.gDirectory.GetListOfKeys():
            input.cd()
            obj = key.ReadObj()
            if obj.GetName() == 'tree':
                continue
            output.cd()
            obj.Write(key.GetName())
        output.cd()
        theCut = self.minCut
        if sample.subsample:
            theCut += '& (%s)' %(sample.subcut)
        cuttedTree=tree.CopyTree(theCut)
        cuttedTree.Write()
        output.Write()
        input.Close()
        del input
        output.Close()
        del output

    def __cache_samples(self):
        for job in self.__sampleList:
            self.__trim_tree(job)

    def get_tree(self, sample, cut):
        input = ROOT.TFile.Open('%s/tmp_%s.root'%(self.__tmpPath,self.__hashDict[sample.name]),'read')
        tree = input.Get(sample.tree)
        CountWithPU = input.Get("CountWithPU")
        CountWithPU2011B = input.Get("CountWithPU2011B")
        sample.count_with_PU = CountWithPU.GetBinContent(1) 
        sample.count_with_PU2011B = CountWithPU2011B.GetBinContent(1) 
        if sample.subsample:
            cut += '& (%s)' %(sample.subcut)
        ROOT.gROOT.cd()
        cuttedTree=tree.CopyTree(cut)
        cuttedTree.SetDirectory(0)
        input.Close()
        del input
        del tree
        return cuttedTree

    @staticmethod
    def get_scale(sample, config, lumi = None):
        anaTag=config.get('Analysis','tag')
        theScale = 0.
        if not lumi:
            lumi = float(sample.lumi)
        if anaTag == '7TeV':
            theScale = lumi*sample.xsec*sample.sf/(0.46502*sample.count_with_PU+0.53498*sample.count_with_PU2011B)
        elif anaTag == '8TeV':
            theScale = lumi*sample.xsec*sample.sf/(sample.count_with_PU)
        return theScale

    @staticmethod
    def get_checksum(file):
        if 'gsidcap://t3se01.psi.ch:22128' in file:
            srmPath = 'srm://t3se01.psi.ch:8443/srm/managerv2?SFN='
            command = 'lcg-ls -b -D srmv2 -l %s' %file.replace('gsidcap://t3se01.psi.ch:22128/','%s/'%srmPath)
            p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,shell=True)
            lines = p.stdout.readlines()
            if any('No such' in line for line in lines):
                print('File not found')
                print(command)
            line = lines[1].replace('\t* Checksum: ','')
            checksum = line.replace(' (adler32)\n','')
        else:
            command = 'md5sumi %s' %file
            p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,shell=True)
            lines = p.stdout.readlines()
            checksum = lines[0]
        return checksum
    
    @staticmethod
    def file_exists(file):
        if 'gsidcap://t3se01.psi.ch:22128' in file:
            fName = file.replace('gsidcap://t3se01.psi.ch:22128/','')
        else:
            fName = file
        return os.path.exists(fName)

