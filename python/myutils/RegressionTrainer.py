import sys,re,ROOT
ROOT.gROOT.SetBatch(True)
from sample_parser import ParseInfo
from TreeCache import TreeCache

class RegressionTrainer():
    def __init__(self, config):
        vhbb_name_space = config.get('VHbbNameSpace','library')
        ROOT.gSystem.Load(vhbb_name_space)
        
        self.__weight = config.get("TrainRegression","weight")
        self.__vars = config.get("TrainRegression","vars").split()
        self.__target = config.get("TrainRegression","target")
        self.__cut = config.get("TrainRegression","cut")
        self.__title = config.get("TrainRegression","name")
        self.__signals = config.get("TrainRegression","signals")
        self.__regOptions = config.get("TrainRegression","options")
        path = config.get('Directories','PREPout')
        samplesinfo=config.get('Directories','samplesinfo')
        self.__info = ParseInfo(samplesinfo,path)
        self.__samples = self.__info.get_samples(self.__signals)
        self.__tc = TreeCache([self.__cut],self.__samples,path,config)
        self.__trainCut = config.get("TrainRegression","trainCut")
        self.__testCut = config.get("TrainRegression","testCut")
        self.__config = config
        
    
    def train(self):
        signals = []
        signalsTest = []
        for job in self.__samples:
            print '\tREADING IN %s AS SIG'%job.name
            signals.append(self.__tc.get_tree(job,'%s & %s' %(self.__cut,self.__trainCut)))
            signalsTest.append(self.__tc.get_tree(job,'%s & %s'%(self.__cut,self.__testCut)))
        
        sWeight = 1.
        fnameOutput='training_Reg_%s.root' %(self.__title)
        output = ROOT.TFile.Open(fnameOutput, "RECREATE")

        factory = ROOT.TMVA.Factory('MVA', output, '!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Regression')
        #factory.SetSignalWeightExpression( self.__weight )
        #set input trees
        for i, signal in enumerate(signals):
            factory.AddRegressionTree( signal,  sWeight, ROOT.TMVA.Types.kTraining)
            factory.AddRegressionTree( signalsTest[i],  sWeight, ROOT.TMVA.Types.kTesting)
        self.__apply = []
        p = re.compile(r'hJet_\w+')
        for var in self.__vars:
            factory.AddVariable(var,'D') # add the variables
            self.__apply.append(p.sub(r'\g<0>[0]', var))

        factory.AddTarget( self.__target )
        mycut = ROOT.TCut( self.__cut )
        factory.BookMethod(ROOT.TMVA.Types.kBDT,'BDT_REG_%s'%(self.__title),self.__regOptions) # book an MVA method
        factory.TrainAllMethods()
        factory.TestAllMethods()
        factory.EvaluateAllMethods()
        output.Write()
        regDict = dict(zip(self.__vars, self.__apply)) 
        self.__config.set('Regression', 'regWeight', '../data/MVA_BDT_REG_%s.weights.xml' %self.__title)
        self.__config.set('Regression', 'regDict', '%s' %regDict)
        self.__config.set('Regression', 'regVars', '%s' %self.__vars)
        for section in self.__config.sections():
            if not section == 'Regression':
                self.__config.remove_section(section)
        with open('8TeVconfig/appReg', 'w') as configfile:
            self.__config.write(configfile)
        with open('8TeVconfig/appReg', 'r') as configfile:
            for line in configfile:
                print line.strip()

