class sample:
    
    
    #this class is very messy yet....need to remove stuff etc....
    
    
    def __init__(self,name,type):
        if name not in ['Zee','Zmm','Zusdcg','Zusdcg_pt100','Zbb','Zbb_pt100','WW','WZ','ZZ','ZZb','ZZudscg','TT','ST_s','ST_t','ST_tW','STbar_s','STbar_t','STbar_tW','ZH110','ZH115','ZH120','ZH125','ZH130','ZH135']:
            raise Exception("name doesn't exist!")
        self.name=name
        #type = bkg, sig or data
        if type not in ['BKG','SIG','DATA']:
            raise Exception("type must be 'BKG', 'SIG', or 'DATA'!")
        self.type=type
        self.prefix=''
        self.path=''
        self.lumi=0.
        self.xsec=0.
        self.split=1.0
        self.weightexpression=1.0
        self.MVA=''
        self.SYS=['Nominal']
        self.Training=''
        self.weightfiles=''
        self.tree='tree'
        self.treecut=''
        self.comment=''
        
    def getname(self):
        return self.name

    def identifier(self):
        #samples = ['DataZee','DataZmm','udscg_120_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola','udscg_120_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola', 'b_120_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola', 'b_120_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola','WW_TuneZ2_7TeV_pythia6_tauola', 'WZ_TuneZ2_7TeV_pythia6_tauola','ZZ_TuneZ2_7TeV_pythia6_tauola','TTJets_TuneZ2_7TeV-madgraph-tauola','T_TuneZ2_s-channel_7TeV-powheg-tauola','T_TuneZ2_t-channel_7TeV-powheg-tauola', 'T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola','Tbar_TuneZ2_s-channel_7TeV-powheg-tauola','Tbar_TuneZ2_t-channel_7TeV-powheg-tauola', 'Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola','ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp']    
        #samplenames =['Zee','Zmm','Zusdcg','Zusdcg_pt100','Zbb','Zbb_pt100','WW','WZ','ZZ','TT','ST_s','ST_t','ST_tW','STbar_s','STbar_t','STbar_tW','ZH110','ZH115','ZH120','ZH125','ZH130','ZH135']
        samplesdict={'Zmm': 'DataZmm', 'STbar_tW': 'Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola', 'WW': 'WW_TuneZ2_7TeV_pythia6_tauola', 'WZ': 'WZ_TuneZ2_7TeV_pythia6_tauola', 'Zbb': 'b_120_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola', 'ST_tW': 'T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola', 'TT': 'TTJets_TuneZ2_7TeV-madgraph-tauola', 'Zusdcg_pt100': 'udscg_120_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola', 'Zusdcg': 'udscg_120_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola', 'STbar_s': 'Tbar_TuneZ2_s-channel_7TeV-powheg-tauola', 'STbar_t': 'Tbar_TuneZ2_t-channel_7TeV-powheg-tauola', 'ZH115': 'ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp', 'ZH130': 'ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp', 'ZH110': 'ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp', 'ZH135': 'ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp', 'ZZ': 'ZZ_TuneZ2_7TeV_pythia6_tauola','ZZb': 'b_ZZ_TuneZ2_7TeV_pythia6_tauola','ZZudscg': 'udscg_ZZ_TuneZ2_7TeV_pythia6_tauola', 'Zbb_pt100': 'b_120_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola', 'ZH125': 'ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp', 'ZH120': 'ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp', 'Zee': 'DataZee', 'ST_t': 'T_TuneZ2_t-channel_7TeV-powheg-tauola', 'ST_s': 'T_TuneZ2_s-channel_7TeV-powheg-tauola'}
        return samplesdict[self.name]
        
    def getpath(self):
        return self.path+'/'+self.prefix+self.identifier()+'.root'
        
    def addtreecut(self, cut):
        if self.treecut == '':
            self.treecut = cut
        else:
            self.treecut = '(%s) && (%s)'%(self.treecut,cut)
            
    def addcomment(self, comment):
        if self.comment == '':
            self.comment = '- %s'%comment
        else:
            self.comment = '%s\n- %s'%(self.comment,comment)
            
    def plotcolor(self):
        colordict={'Zmm': 1, 'STbar_tW': 602, 'WW': 17, 'ZZb': 17,'ZZudscg': 17, 'WZ': 17, 'Zbb': 5, 'ST_tW': 602, 'TT': 596, 'Zusdcg_pt100': 401, 'Zusdcg': 401, 'STbar_s': 602, 'STbar_t': 602, 'ZH115': 2, 'ZH130': 2, 'ZH110': 2, 'ZH135': 2, 'ZZ': 17, 'Zbb_pt100': 5, 'ZH125': 2, 'ZH120': 2, 'Zee': 1, 'ST_t': 602, 'ST_s': 602}
        return colordict[self.name]
    
    def plotname(self):
        plotnamedict={'Zmm': 'Data (4.7 fb^{-1})', 'STbar_tW': 'Single top', 'WW': 'WW/WZ/ZZ', 'ZZb': 'WW/WZ/ZZ','ZZudscg': 'WW/WZ/ZZ', 'WZ': 'WW/WZ/ZZ', 'Zbb': 'DY jets b', 'ST_tW': 'Single top', 'TT': 'TT-bar', 'Zusdcg_pt100':'DY jets udscg', 'Zusdcg': 'DY jets udscg', 'STbar_s': 'Single top', 'STbar_t': 'Single top', 'ZH115': 'Hbb 115', 'ZH130': 'Hbb 130', 'ZH110': 'Hbb 110', 'ZH135': 'Hbb 135', 'ZZ': 'WW/WZ/ZZ', 'Zbb_pt100': 'DY jets b', 'ZH125': 'Hbb 125', 'ZH120': 'Hbb 120', 'Zee': 'Data (4.7 fb^{-1})', 'ST_t': 'Single top', 'ST_s': 'Single top'}
        return plotnamedict[self.name]
        
    def addprefix(self,prefix):
        self.prefix=prefix+self.prefix

    def addpath(self,path):
        self.path=self.path+path
