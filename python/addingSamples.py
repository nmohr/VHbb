#!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import ROOT
from array import array


def getObj( infile, name ):
    infile.cd()
    for key in ROOT.gDirectory.GetListOfKeys():
        obj = key.ReadObj()
        print obj.GetName()
        if obj.GetName() == name:
            return obj;


def updateEventArray( tree, lheBin, N ):
    for bin in lheBin:
        print bin
        N.append( (bin, 1.*tree.GetEntries(bin) ) )
    return N
    
def getTotal( bin, fileList ):
    total = 0.
    for i in range(0,len(fileList)):
        total = total + fileList[i][2][bin]
        #print total[bin]
    return total
    
inc = []
j1 = []
j2 = []
j3 = []
j4 = []
pt5070 = []
pt70100 = []
pt100 = []
ht200400 = []
ht400 = []

prefix='DiJetPt_'
fileList = [ [prefix+'DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root' , 2950.0, inc ] ,
             [prefix+'DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root' , 93.8, pt5070 ],
             [prefix+'DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root' , 52.31, pt70100 ],
             [prefix+'DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root' , 34.1, pt100 ],
             [prefix+'DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root' , 561.0, j1 ] ,
             [prefix+'DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root' , 181.0, j2 ] ,
#             [prefix+'DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root' , 51.1, j3 ] , # not ready in 53X
             [prefix+'DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root' , 23.04, j4 ] ]

#look here https://www.evernote.com/shard/s186/sh/8ffc289c-ede2-4e09-83ba-1e1981f13617/4d5aac2f42a9fd480dc66f9303c1c217

lheBin = ['lheV_pt < 50 & lheNj == 0',
          'lheV_pt > 50 & lheV_pt < 70 & lheNj == 0',
          'lheV_pt > 70 & lheV_pt < 100 & lheNj == 0',
          'lheV_pt > 100 & lheNj == 0',

          'lheV_pt < 50 & lheNj == 1',
          'lheV_pt > 50 & lheV_pt < 70 & lheNj == 1',
          'lheV_pt > 70 & lheV_pt < 100 & lheNj == 1',
          'lheV_pt > 100 & lheNj == 1',
          
          'lheV_pt < 50 & lheNj == 2',
          'lheV_pt > 50 & lheV_pt < 70 & lheNj == 2',
          'lheV_pt > 70 & lheV_pt < 100 & lheNj == 2',
          'lheV_pt > 100 & lheNj == 2',
          
          'lheV_pt < 50 & lheNj == 3',
          'lheV_pt > 50 & lheV_pt < 70 & lheNj == 3',
          'lheV_pt > 70 & lheV_pt < 100 & lheNj == 3',
          'lheV_pt > 100 & lheNj == 3',
          
          'lheV_pt < 50 & lheNj == 4',
          'lheV_pt > 50 & lheV_pt < 70 & lheNj == 4',
          'lheV_pt > 70 & lheV_pt < 100 & lheNj == 4',
          'lheV_pt > 100 & lheNj == 4'          ]

eventList = {}
num = []
for file in fileList:
    print file
    infile = ROOT.TFile(file[0],"READ")
    tree = getObj(infile, 'tree')
    for bin in lheBin:
        print bin
        file[2].append( 1.*tree.GetEntries(bin) )
#    file[2] = updateEventArray( tree, lheBin, file[2] )
    count = getObj( infile, 'CountWithPU' )
    file.append( count.GetBinContent(1) )
    print fileList

CountIncl = fileList[0][3]
print fileList


#print num[fileList[1]]

#total -> total numer of events in each lheBin
print 'Calculating total'
total = []
weight= []
for bin in range(0, len(lheBin) ):
    total.append(getTotal(bin, fileList))
    print bin
        #to better stich we need the highest stat (that should correspond to the binned sample relative to the bin)
    fileList.sort( key=lambda file: file[2][bin], reverse=True )
    print 'After sorting'
    print fileList
    if total[bin] > 0.:
        #the first is always the one with the highest N in the bin: 
        weight.append( (fileList[0][1]/fileList[0][3]) * (CountIncl/2950.0) * fileList[0][2][bin]/total[bin] )
        print weight[bin]
    else:
        weight.append(1.)

print weight
    
#now add the branch with the weight normalized to the inclusive
for file in fileList:
    infile = ROOT.TFile(file[0],"READ")
    outfile = ROOT.TFile('lheWeight.'+file[0],'RECREATE')

    infile.cd()
    tree = infile.Get('tree')
    outfile.cd()
    newtree = tree.CloneTree(0)
    lheWeight = array('f',[0])
    newtree.Branch('lheWeight',lheWeight,'lheWeight/F')

    nEntries = tree.GetEntries()
    for entry in range(0,nEntries):
        tree.GetEntry(entry)

        if tree.lheV_pt < 50 and tree.lheNj == 0:
            lheWeight[0] = weight[0]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70 and tree.lheNj == 0:
            lheWeight[0] = weight[1]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100 and tree.lheNj == 0:
            lheWeight[0] = weight[2]
        elif tree.lheV_pt > 100 and tree.lheNj == 0:
            lheWeight[0] = weight[3]

        elif tree.lheV_pt < 50 and tree.lheNj == 1:
            lheWeight[0] = weight[4]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70 and tree.lheNj == 1:
            lheWeight[0] = weight[5]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100 and tree.lheNj == 1:
            lheWeight[0] = weight[6]
        elif tree.lheV_pt > 100 and tree.lheNj == 1:
            lheWeight[0] = weight[7]

        elif tree.lheV_pt < 50 and tree.lheNj == 2:
            lheWeight[0] = weight[8]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70 and tree.lheNj == 2:
            lheWeight[0] = weight[9]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100 and tree.lheNj == 2:
            lheWeight[0] = weight[10]
        elif tree.lheV_pt > 100 and tree.lheNj == 2:
            lheWeight[0] = weight[11]

        elif tree.lheV_pt < 50 and tree.lheNj == 3:
            lheWeight[0] = weight[12]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70 and tree.lheNj == 3:
            lheWeight[0] = weight[13]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100 and tree.lheNj == 3:
            lheWeight[0] = weight[14]
        elif tree.lheV_pt > 100 and tree.lheNj == 3:
            lheWeight[0] = weight[15]
            
        elif tree.lheV_pt < 50 and tree.lheNj == 4:
            lheWeight[0] = weight[16]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70 and tree.lheNj == 4:
            lheWeight[0] = weight[17]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100 and tree.lheNj == 4:
            lheWeight[0] = weight[18]
        elif tree.lheV_pt > 100 and tree.lheNj == 4:
            lheWeight[0] = weight[19]

        else:
            lheWeight[0] = 1.

            
        newtree.Fill()
                   
    newtree.AutoSave()
    outfile.Write()
    outfile.Close()

