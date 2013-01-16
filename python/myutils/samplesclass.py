class sample:
    
    def __init__(self,name,type):
        self.name=name
        #type = bkg, sig or data
        #if type not in ['BKG','SIG','DATA']:
        #    raise Exception("type must be 'BKG', 'SIG', or 'DATA'!")
        self.type=type
        self.prefix=''
        self.identifier=''
        self.active='True'
        self.group=''
        self.path=''
        self.lumi=0.
        self.sf=1.0
        self.xsec=0.
        self.split=1.0
        self.weightexpression=1.0
        self.SYS=['Nominal']
        self.tree='tree'
        self.treecut=''
        self.comment=''
        #for DY falvours
        self.subsamples=False
        self.subnames=[]
        self.subcuts=[]

    def getpath(self):
        return './'+self.prefix+self.identifier+'.root'
        
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
            
    def addprefix(self,prefix):
        self.prefix=prefix+self.prefix

    def addpath(self,path):
        self.path=self.path+path
