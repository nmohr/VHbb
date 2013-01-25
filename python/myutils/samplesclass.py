class Sample:
    def __init__(self,name,type):
        self.name=name
        self.type=type
        self.identifier=''
        self.prefix=''
        self.active=True
        self.group=''
        self.lumi=0.
        self.sf=1.
        self.xsec=0.
        self.weightexpression=1.0
        self.tree='tree'
        self.treecut=''
        self.count_with_PU=1.
        self.count_with_PU2011B=1.
        self.subsample=False
        self.subcut='1'

    @property
    def get_path(self):
        return './%s%s.root' %(self.prefix,self.identifier)

    def __str__(self):
        return '%s' %self.name
    
    def __eq__(self,other):
        return self.name == other.name
