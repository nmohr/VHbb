class mvainfo:
    
    def __init__(self,MVAname):
        self.factoryname=''
        self.factorysettings=''
        self.MVAname=MVAname
        self.MVAtype='' #e.g. BDT
        self.MVAsettings=''
        self.weightfilepath=''
        self.weightfiles='' #?
        self.sigs=[]
        self.bkgs=[]
        self.path=''
        self.varset=''
        self.vars=[]
        self.spectators=[]
        self.comment=''
        
    def getweightfile(self):
        return './'+self.factoryname+'_'+self.MVAname+'.weights.xml'
        
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
