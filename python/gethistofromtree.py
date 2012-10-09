from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from BetterConfigParser import BetterConfigParser
import sys


def getScale(job,path,config,rescale,subsample=-1):
    anaTag=config.get('Analysis','tag')
    input = TFile.Open(path+'/'+job.getpath())
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    #print lumi*xsecs[i]/hist.GetBinContent(1)
    
    if subsample>-1:
        xsec=float(job.xsec[subsample])
        sf=float(job.sf[subsample])
    else:
        xsec=float(job.xsec)
        sf=float(job.sf)
    
    
    theScale = 1.
    if anaTag == '7TeV':
        theScale = float(job.lumi)*xsec*sf/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*rescale/float(job.split)
    elif anaTag == '8TeV':
    	theScale = float(job.lumi)*xsec*sf/(CountWithPU.GetBinContent(1))*rescale/float(job.split)
    return theScale 

def getHistoFromTree(job,path,config,options,rescale=1,subsample=-1,which_weightF='weightF'):

    #print job.getpath()
    #print options
    treeVar=options[0]
    if subsample>-1:
        name=job.subnames[subsample]
        group=job.group[subsample]
    else:
        name=job.name
        group=job.group

    #title=job.plotname()
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])
    #addOverFlow=eval(config.get('Plot_general','addOverFlow'))
    addOverFlow = False

    if job.type != 'DATA':
    
        if type(options[7])==str:
            cutcut=config.get('Cuts',options[7])
        elif type(options[7])==list:
            cutcut=config.get('Cuts',options[7][0])
            cutcut=cutcut.replace(options[7][1],options[7][2])
            #print cutcut
        if subsample>-1:
            treeCut='%s & %s & EventForTraining == 0'%(cutcut,job.subcuts[subsample])        
        else:
            treeCut='%s & EventForTraining == 0'%(cutcut)

    elif job.type == 'DATA':
        cutcut=config.get('Cuts',options[8])
        treeCut='%s'%(cutcut)


    input = TFile.Open(path+'/'+job.getpath(),'read')

    Tree = input.Get(job.tree)
    #Tree=tmpTree.CloneTree()
    #Tree.SetDirectory(0)
    
    #Tree=tmpTree.Clone()
    weightF=config.get('Weights',which_weightF)
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
        ScaleFactor = getScale(job,path,config,rescale,subsample)
        if ScaleFactor != 0:
            hTree.Scale(ScaleFactor)
    
    if addOverFlow:
            print 'Adding overflow'
            uFlow = hTree.GetBinContent(0)+hTree.GetBinContent(1)
            oFlow = hTree.GetBinContent(hTree.GetNbinsX()+1)+hTree.GetBinContent(hTree.GetNbinsX())
            uFlowErr = ROOT.TMath.Sqrt(ROOT.TMath.Power(hTree.GetBinError(0),2)+ROOT.TMath.Power(hTree.GetBinError(1),2))
            oFlowErr = ROOT.TMath.Sqrt(ROOT.TMath.Power(hTree.GetBinError(hTree.GetNbinsX()),2)+ROOT.TMath.Power(hTree.GetBinError(hTree.GetNbinsX()+1),2))
            hTree.SetBinContent(1,uFlow)
            hTree.SetBinContent(hTree.GetNbinsX(),oFlow)
            hTree.SetBinError(1,uFlowErr)
            hTree.SetBinError(hTree.GetNbinsX(),oFlowErr)
              
            
    print '\t-->import %s\t Integral: %s'%(job.name,hTree.Integral())
            
    hTree.SetDirectory(0)
    input.Close()  
    
    return hTree, group
    

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

    print typs

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


