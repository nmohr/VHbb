from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from BetterConfigParser import BetterConfigParser
import sys


#load config
config = BetterConfigParser()
config.read('./config')

#get locations:
Wdir=config.get('Directories','Wdir')
anaTag=config.get('Analysis','tag')



def getScale(job,rescale):
    input = TFile.Open(job.getpath())
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    #print lumi*xsecs[i]/hist.GetBinContent(1)
    theScale = 1.
    if anaTag == '7TeV':
	theScale = float(job.lumi)*float(job.xsec)*float(job.sf)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*rescale/float(job.split)
    elif anaTag == '8TeV':
    	theScale = float(job.lumi)*float(job.xsec)*float(job.sf)/(CountWithPU.GetBinContent(1))*rescale/float(job.split)
    return theScale 

def getHistoFromTree(job,options,rescale=1):
    treeVar=options[0]
    name=job.name
    #title=job.plotname()
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])

    if job.type != 'DATA':
        cutcut=config.get('Cuts',options[7])
        treeCut='%s & EventForTraining == 0'%(cutcut)

    elif job.type == 'DATA':
        cutcut=config.get('Cuts',options[8])
        treeCut='%s & EventForTraining == 0'%(cutcut)


    input = TFile.Open(job.getpath(),'read')

    Tree = input.Get(job.tree)
    #Tree=tmpTree.CloneTree()
    #Tree.SetDirectory(0)
    
    #Tree=tmpTree.Clone()
    weightF=config.get('Weights','weightF')
    #hTree = ROOT.TH1F('%s'%name,'%s'%title,nBins,xMin,xMax)
    #hTree.SetDirectory(0)
    #hTree.Sumw2()
    #print 'drawing...'
    if job.type != 'DATA':
        #print treeCut
        #print job.name
        if Tree.GetEntries():
            Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),'(%s)*(%s)' %(treeCut,weightF), "goff,e")
            full=True
        else:
            full=False
    elif job.type == 'DATA':
    
        if len(options)>10:
            if options[11] == 'blind':
                treeCut = treeCut + '&'+treeVar+'<0'
    
    
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),treeCut, "goff,e")
        full = True
    if full:
        hTree = ROOT.gDirectory.Get(name)
    else:
        hTree = ROOT.TH1F('%s'%name,'%s'%name,nBins,xMin,xMax)
        hTree.Sumw2()
    #print job.name + ' Sumw2', hTree.GetEntries()

    if job.type != 'DATA':
        ScaleFactor = getScale(job,rescale)
        if ScaleFactor != 0:
            hTree.Scale(ScaleFactor)
            
    print '\t-->import %s\t Integral: %s'%(job.name,hTree.Integral())
            
    hTree.SetDirectory(0)
    input.Close()            
    return hTree, job.group
    

######################



def orderandadd(histos,typs,setup):
#ORDER AND ADD TOGETHER

    ordnung=[]
    ordnungtyp=[]
    num=[0]*len(setup)
    for i in range(0,len(setup)):
        for j in range(0,len(histos)):
            if typs[j] in setup[i]:
                num[i]+=1
                ordnung.append(histos[j])
                ordnungtyp.append(typs[j])

    del histos
    del typs

    histos=ordnung
    typs=ordnungtyp

    for k in range(0,len(num)):
        for m in range(0,num[k]):
            if m > 0:
            
                #add
                histos[k].Add(histos[k+1],1)
                printc('magenta','','\t--> added %s to %s'%(typs[k],typs[k+1]))
                del histos[k+1]
                del typs[k+1]

    del histos[len(setup):]
    del typs[len(setup):]

    return histos, typs


