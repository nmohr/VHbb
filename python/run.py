#!/usr/bin/env python
import sys
import os
import ROOT 
import shutil
from ROOT import TFile
from array import array
from init import *
#from initMuMu import *
from math import sqrt
import random
from copy import copy
#suppres the EvalInstace conversion warning bug
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
from ConfigParser import SafeConfigParser
from samplesinfo import sample
from mvainfos import mvainfo
import pickle
from progbar import progbar


for i in range(0,len(backgroundFiles)): backgroundFiles[i] = prefix + backgroundFiles[i]
for i in range(0,len(signalFiles)): signalFiles[i] = prefix + signalFiles[i]
for i in range(0,len(dataFiles)): dataFiles[i] = prefix + dataFiles[i]
#for i in range(0,len(InFiles0)): InFiles0[i] = Preprefix + InFiles0[i]
#for i in range(0,len(InFiles1)): InFiles1[i] = Preprefix + InFiles1[i]
#for i in range(0,len(InFiles2)): InFiles2[i] = Preprefix + InFiles2[i]

#add ehm together
jobs = copy(backgroundFiles)
jobs.append(signalFiles[0])
legenden = backname
legenden.append(signame[0])
xsecs = xsec
xsecs.append(signal_xsec)
if sys.argv[1] == 'stack' or 'pie': treeCut = treeCutPlot
else: treeCut = treeCutMVA




#CONFIGURE

#load config
config = SafeConfigParser()
config.read('./config')

#get locations:
Wdir=config.get('Directories','Wdir')


#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

#TreeVar Array
MVA_Vars={}
for systematic in systematics:
    MVA_Vars[systematic]=config.get('treeVars',systematic)
    MVA_Vars[systematic]=MVA_Vars[systematic].split(' ')


    










    ##############################
    #                            #
    #    VHbb Analysis Stuff     #
    #    ETHZ, Philipp Eller     #
    #                            #
    ##############################


#*********************HELPERS*******************************
def getTree(path,job):
    Tree = ROOT.TChain(treeName)
    Tree.Add("%s/%s.root" %(path,job))
    Tree.SetDirectory(0)
    #nEntries = Tree.GetEntries()
    return Tree
    
#NEW
def getTree2(job):
    Tree = ROOT.TChain(job.tree)
    Tree.Add(job.getpath())
    Tree.SetDirectory(0)
    return Tree
        
def getScale2(job):
    input = TFile.Open(job.getpath())
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    #print lumi*xsecs[i]/hist.GetBinContent(1)
    return float(job.lumi)*float(job.xsec)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*1/float(job.split)

def getScale(path,job):
    input = TFile.Open("%s/%s.root" %(path,job))
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    i=jobs.index(job)
    return lumi*xsecs[i]/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))


#NEW
def AddSystematics(path):
    
    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()
    os.mkdir(path+'/sys')

    for job in info:
        
        if job.type != 'DATA':
            print '\t - %s' %(job.name)

            input = TFile.Open(job.getpath(),'read')
            Count = input.Get("Count")
            CountWithPU = input.Get("CountWithPU")
            CountWithPU2011B = input.Get("CountWithPU2011B")
            tree = input.Get(job.tree)
            nEntries = tree.GetEntries()
            
            job.addpath('/sys')
            output = ROOT.TFile(job.getpath(), 'RECREATE')
            newtree = tree.CloneTree(0)
            job.SYS = ['Nominal','JER_up','JER_down','JES_up','JES_down','beff_up','beff_down','bmis_up','bmis_down']

            
            hJ0 = ROOT.TLorentzVector()
            hJ1 = ROOT.TLorentzVector()
              
            #JER branches
            hJet_pt_JER_up = array('f',[0]*2)
            newtree.Branch('hJet_pt_JER_up',hJet_pt_JER_up,'hJet_pt_JER_up[2]/F')
            hJet_pt_JER_down = array('f',[0]*2)
            newtree.Branch('hJet_pt_JER_down',hJet_pt_JER_down,'hJet_pt_JER_down[2]/F')
            hJet_e_JER_up = array('f',[0]*2)
            newtree.Branch('hJet_e_JER_up',hJet_e_JER_up,'hJet_e_JER_up[2]/F')
            hJet_e_JER_down = array('f',[0]*2)
            newtree.Branch('hJet_e_JER_down',hJet_e_JER_down,'hJet_e_JER_down[2]/F')
            H_JER = array('f',[0]*4)
            newtree.Branch('H_JER',H_JER,'mass_up:mass_down:pt_up:pt_down/F')
            
            #JES branches
            hJet_pt_JES_up = array('f',[0]*2)
            newtree.Branch('hJet_pt_JES_up',hJet_pt_JES_up,'hJet_pt_JES_up[2]/F')
            hJet_pt_JES_down = array('f',[0]*2)
            newtree.Branch('hJet_pt_JES_down',hJet_pt_JES_down,'hJet_pt_JES_down[2]/F')
            hJet_e_JES_up = array('f',[0]*2)
            newtree.Branch('hJet_e_JES_up',hJet_e_JES_up,'hJet_e_JES_up[2]/F')
            hJet_e_JES_down = array('f',[0]*2)
            newtree.Branch('hJet_e_JES_down',hJet_e_JES_down,'hJet_e_JES_down[2]/F')
            H_JES = array('f',[0]*4)
            newtree.Branch('H_JES',H_JES,'mass_up:mass_down:pt_up:pt_down/F')
            
            #Add training Flag
            EventForTraining = array('f',[0])
            newtree.Branch('EventForTraining',EventForTraining,'EventForTraining/F')
            
            iter=0
            
            for entry in range(0,nEntries):
                tree.GetEntry(entry)

                #fill training flag 
                iter+=1
                if (iter%2==0):
                    EventForTraining=1
                else:
                    EventForTraining=0

                hJet_pt0 = tree.hJet_pt[0]
                hJet_pt1 = tree.hJet_pt[1]
                hJet_eta0 = tree.hJet_eta[0]
                hJet_eta1 = tree.hJet_eta[1]
                hJet_genPt0 = tree.hJet_genPt[0]
                hJet_genPt1 = tree.hJet_genPt[1]
                hJet_e0 = tree.hJet_e[0]
                hJet_e1 = tree.hJet_e[1]
                hJet_phi0 = tree.hJet_phi[0]
                hJet_phi1 = tree.hJet_phi[1]
                hJet_JECUnc0 = tree.hJet_JECUnc[0]
                hJet_JECUnc1 = tree.hJet_JECUnc[1]


                for updown in ['up','down']:
                    #JER
                    if updown == 'up':
                        inner = 0.06
                        outer = 0.1
                    if updown == 'down':
                        inner = -0.06
                        outer = -0.1
                    #Calculate
                    if abs(hJet_eta0)<1.1: res0 = inner
                    else: res0 = outer
                    if abs(hJet_eta1)<1.1: res1 = inner
                    else: res1 = outer
                    rPt0 = hJet_pt0 + (hJet_pt0-hJet_genPt0)*res0
                    rPt1 = hJet_pt1 + (hJet_pt1-hJet_genPt1)*res1
                    rE0 = hJet_e0*rPt0/hJet_pt0
                    rE1 = hJet_e1*rPt1/hJet_pt1
                    hJ0.SetPtEtaPhiE(rPt0,hJet_eta0,hJet_phi0,rE0)
                    hJ1.SetPtEtaPhiE(rPt1,hJet_eta1,hJet_phi1,rE1)
                    #Set
                    if updown == 'up':
                        hJet_pt_JER_up[0]=rPt0
                        hJet_pt_JER_up[1]=rPt1
                        hJet_e_JER_up[0]=rE0
                        hJet_e_JER_up[1]=rE1
                        H_JER[0]=(hJ0+hJ1).M()
                        H_JER[2]=(hJ0+hJ1).Pt()
                    if updown == 'down':
                        hJet_pt_JER_down[0]=rPt0
                        hJet_pt_JER_down[1]=rPt1
                        hJet_e_JER_down[0]=rE0
                        hJet_e_JER_down[1]=rE1
                        H_JER[1]=(hJ0+hJ1).M()
                        H_JER[3]=(hJ0+hJ1).Pt()
                    
                    #JES
                    if updown == 'up':
                        variation=1
                    if updown == 'down':
                        variation=-1
                    #calculate
                    rPt0 = hJet_pt0*(1+variation*hJet_JECUnc0)
                    rPt1 = hJet_pt1*(1+variation*hJet_JECUnc1)
                    rE0 = hJet_e0*(1+variation*hJet_JECUnc0)
                    rE1 = hJet_e1*(1+variation*hJet_JECUnc1)
                    hJ0.SetPtEtaPhiE(rPt0,hJet_eta0,hJet_phi0,rE0)
                    hJ1.SetPtEtaPhiE(rPt1,hJet_eta1,hJet_phi1,rE1)
                    #Fill
                    if updown == 'up':
                        hJet_pt_JES_up[0]=rPt0
                        hJet_pt_JES_up[1]=rPt1
                        hJet_e_JES_up[0]=rE0
                        hJet_e_JES_up[1]=rE1
                        H_JES[0]=(hJ0+hJ1).M()
                        H_JES[2]=(hJ0+hJ1).Pt()
                    if updown == 'down':
                        hJet_pt_JES_down[0]=rPt0
                        hJet_pt_JES_down[1]=rPt1
                        hJet_e_JES_down[0]=rE0
                        hJet_e_JES_down[1]=rE1
                        H_JES[1]=(hJ0+hJ1).M()
                        H_JES[3]=(hJ0+hJ1).Pt()
                
                newtree.Fill()
                            
            newtree.Write()            
            Count.Write()
            CountWithPU.Write()
            CountWithPU2011B.Write()
            output.Close()

        else: #(is data)
        
            shutil.copy(job.getpath(),path+'/sys')
            job.addpath('/sys')

    infofile = open(path+'/sys'+'/samples.info','w')
    pickle.dump(info,infofile)
    infofile.close()

#NEW    
def Addcut(path,addpath,Samplecut,Datacut):

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()
    os.mkdir(path+addpath)
    addprefix=''

    Samplecut=config.get('Cuts',Samplecut)
    Datacut=config.get('Cuts',Datacut)


    for job in info:
        if job.type != 'DATA':    
            cut = Samplecut
            print '\t - %s' %(job.name)
            copytree2(job,addpath,addprefix,cut)
            job.addpath(addpath)
            job.addtreecut(cut)
            job.addprefix(addprefix)
            job.addcomment('added cut ' + cut)
            
        if job.type == 'DATA':
            cut = Datacut
            print '\t - %s' %(job.name)
            copytree2(job,addpath,addprefix,cut)
            job.addpath(addpath)
            job.addtreecut(cut)
            job.addprefix(addprefix)
            job.addcomment('added cut ' + cut)

    infofile = open(path+addpath+'/samples.info','w')
    pickle.dump(info,infofile)
    infofile.close()
    
def Addsinglecut(path,name,prefix,cut):

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()
    
    for job in info:
        if job.name == name:    
            print '\t - %s' %(job.name)
            copytree2(job,'',prefix,cut)
            job.addtreecut(cut)
            job.addcomment('added cut ' + cut)

    infofile = open(path+'/samples.info','w')
    pickle.dump(info,infofile)
    infofile.close()
    
def AddFile(path,name,newname,prefix,cut):

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()

    for job in info:
        if job.name == name:    
            print '\t - %s' %(job.name)
            copytree2(job,'',prefix,cut)
            job2 = copy(job)
            job2.addtreecut(cut)
            #job2.addprefix(prefix)
            job2.addcomment('added cut ' + cut)
            job2.name=newname
    
    info.append(job2)
    infofile = open(path+'/samples.info','w')
    pickle.dump(info,infofile)
    infofile.close()

def getHistoFromTree(path,job,scale):
    Tree = getTree(path,job)
    hTree = ROOT.TH1F(job,job,nBins,xMin,xMax)
    if scale !=0:
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,job,nBins,xMin,xMax),'%s*(%s)' %(weightF,treeCut), "goff")
    else:
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,job,nBins,xMin,xMax),'(%s)' %(treeCut), "goff")
    hTree = ROOT.gDirectory.Get(job)
    hTree.SetDirectory(0)
    if scale !=0:
        ScaleFactor = getScale(treePath,job)
        if ScaleFactor != 0:
            hTree.Scale(ScaleFactor)
    return hTree
    
def getHistoFromTree2(job,options):
    Tree = getTree2(job)
    treeVar=options[0]
    name=job.name
    title=job.plotname()
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])
    if job.type != 'DATA':
        treeCut=config.get('Cuts',options[7])
    elif job.type == 'DATA':
        treeCut=config.get('Cuts',options[8])    
    weightF=config.get('Weights','weightF')
    hTree = ROOT.TH1F('%s'%name,'%s'%title,nBins,xMin,xMax)
    hTree.Sumw2()
    if job.type != 'DATA':
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),'%s*(%s)' %(weightF,treeCut), "goff,e")
    else:
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),'(%s)' %(treeCut), "goff,e")
    hTree = ROOT.gDirectory.Get(name)
    hTree.SetDirectory(0)
    #print job.name + ' Sumw2', hTree.GetEntries()

    if job.type != 'DATA':
        ScaleFactor = getScale2(job)
        if ScaleFactor != 0:
            hTree.Scale(ScaleFactor)
            
        hTree.SetFillStyle(1001)
        hTree.SetFillColor(job.plotcolor())
        hTree.SetLineWidth(1)
        print '\t-->import %s\t Integral: %s'%(job.name,hTree.Integral())
            
            
    return hTree, job.plotname()
        
def copytreeetc(path,job,Nprefix,Acut):
    input = TFile.Open("%s/%s%s.root" %(skim_path,Preprefix,job))
    Count = input.Get("Count")
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    inputTree = input.Get(treeName)
    nEntries = inputTree.GetEntries()
    output = TFile.Open("%s/%s%s%s.root" %(path,Preprefix,Nprefix,job),'recreate')
    print 'copy file: ' + job
    outputTree = inputTree.CopyTree(Acut)
    kEntries = outputTree.GetEntries()
    #factor = kEntries/nEntries
    print "\t before cuts\t %s" %nEntries
    print "\t survived\t %s" %kEntries
    #print factor
    #print "\t Factor for Scaling is %s" %factor
    outputTree.AutoSave()
    #Count.Scale(factor)
    Count.Write()
    CountWithPU.Write()
    #CountWithPU.Scale(factor)
    CountWithPU2011B.Write()
    #CountWithPU2011B.Scale(factor)
    input.Close()
    output.Close()

#NEW
def copytree2(job,addpath,addprefix,addcut):
    input = TFile.Open(job.getpath(),'read')
    Count = input.Get("Count")
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    inputTree = input.Get(job.tree)
    nEntries = inputTree.GetEntries()
    output = TFile.Open("%s%s/%s%s%s.root" %(job.path,addpath,addprefix,job.prefix,job.identifier()),'recreate')
    print '\t\tcopy file: ' + job.name + ' with cut ' + addcut + ' to ' + addpath
    outputTree = inputTree.CopyTree(addcut)
    kEntries = outputTree.GetEntries()
    print "\t before cuts\t %s" %nEntries
    print "\t survived\t %s" %kEntries
    outputTree.AutoSave()
    Count.Write()
    CountWithPU.Write()
    CountWithPU2011B.Write()
    input.Close()
    output.Close()

    
def CutCopy(mode):

    if mode == 'all':
        path = treePath
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0])#+'&'+treeCutMVA)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i])#+'&'+treeCutMVA)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i])#+'&'+treeCutMVA)

    if mode == 'Zbb':
        path = treePath + '/Zbb'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutZbb)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+treeCutZbb)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+treeCutZbb)
        for job in dataFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutZbb)
    if mode == 'Zlight':
        path = treePath + '/Zlight'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutZlight)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+treeCutZlight)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+treeCutZlight)
        for job in dataFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutZlight)
    if mode == 'Top':
        path = treePath + '/Top'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutTop)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+treeCutTop)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+treeCutTop)
        for job in dataFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutTop)
    if mode == 'Signal':
        path = treePath + '/Signal'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutSignal)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+treeCutSignal)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+treeCutSignal)
        for job in dataFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+treeCutSignal)
    
    if mode == 'data':
        path = treePath #+ '/test'
        for job in dataFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+triggerFlags[0])#+'&'+treeCutMVA)
            
    if mode == 'test':
        path = treePath +'/test'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+cut_even+'&'+treeCutMVA)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+cut_even+'&'+treeCutMVA)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+cut_even+'&'+treeCutMVA)
            
    if mode == 'train':    
        path = treePath +'/train'
        for job in InFiles0:
            copytreeetc(path,job,prefix0[0],cut0[0]+'&'+cut_odd+'&'+treeCutMVA)
        for i in range(2):
            copytreeetc(path,InFiles1[0],prefix1[i],cut1[i]+'&'+cut_odd+'&'+treeCutMVA)
            copytreeetc(path,InFiles2[0],prefix2[i],cut2[i]+'&'+cut_odd+'&'+treeCutMVA)
            
def createComparison():
        ROOT.gROOT.SetStyle("Plain")
        c = ROOT.TCanvas(title,title, 800, 600)
        c.SetLogy()
        allStack = ROOT.THStack(title,title)
        histos = []
        for job in jobs:
            hTemp = getHistoFromTree(treePath,job)
            histos.append(hTemp)
        l = ROOT.TLegend(0.55, 0.82, 0.93, 0.93)
        for i in range(0,len(histos)):
            histos[i].SetFillStyle(0)
            histos[i].SetLineColor(i+2)
            histos[i].SetLineWidth(2)
            allStack.Add(histos[i])
            l.AddEntry(histos[i],legenden[i],'l')
        allStack.Draw("HISTNOSTACK")
        allStack.GetXaxis().SetTitle(xTitle)
        allStack.GetYaxis().SetTitle(yTitle)
        allStack.GetXaxis().SetRangeUser(xMin,xMax)
        l.Draw()
        name = '%s/Comparison/%s.png' %(plotPath,title)
        c.Print(name)
        
def plot():
    print 'ok, i make plots for you now...'
    histos = []
    for job in jobs:
        hTemp = getHistoFromTree(treePath,job,1)
        histos.append(hTemp)
    datas = []
    for job in dataFiles:
        hTemp = getHistoFromTree(treePath,job,0)
        datas.append(hTemp)
    createStack(histos,datas,plotPath,title,treeVar,xMin,xMax,nBins,xTitle,yTitle)

def allplots():
    print 'ok, i make all plots for you now...'
    for i in range(0,len(treeVars)-1):
        global treeVar
        treeVar = treeVars[i]
        xTitle = treeVar
        title = set + '_' + treeVar
        global xMin
        xMin = xMinS[i]
        global xMax
        xMax = xMaxS[i]
        global nBins
        nBins = nBinsS[i]
        histos = []
        for job in jobs:
            hTemp = getHistoFromTree(treePath,job,1)
            histos.append(hTemp)
        datas = []
        for job in dataFiles:
            hTemp = getHistoFromTree(treePath,job,0)
            datas.append(hTemp)
        createStack(histos,datas,plotPath,title,treeVar,xMin,xMax,nBins,xTitle,yTitle)

def createStack(histos,datas,plotPath,title,treeVar,xMin,xMax,nBins,xTitle,yTitle):
    #*********************STACK*******************************
    print '*******************'
    print 'now i am working on ' + title
    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(title,title, 800, 600)
    allStack = ROOT.THStack(title,title)     
    l = ROOT.TLegend(0.68, 0.63, 0.88, 0.88)
    MC_integral=0
    for i in range(0,len(histos)):
        histos[i].SetFillStyle(1001)
        histos[i].SetFillColor(color[i])
        histos[i].SetLineWidth(1)
        #histos[i].SetLineColor(color[i])
        print "\t%s integral:" %legenden[i]
        print histos[i].Integral()
        MC_integral=MC_integral+histos[i].Integral()
    print "MC integral:"
    print MC_integral
    histos[0].Add(histos[1],1)
    del histos[1]
    histos[1].Add(histos[2],1)
    del histos[2]
    for i in range(2):
        histos[2].Add(histos[3],1)
        del histos[3]
    for i in range(5):
        histos[4].Add(histos[5],1)
        del histos[5]
    k=len(histos)
    for j in range(0,k):
        #print histos[j].GetBinContent(1)
        i=k-j-1
        allStack.Add(histos[i])
        l.AddEntry(histos[j],legende[j],'F')
    d1 = ROOT.TH1F('d1','d1',nBins,xMin,xMax)

    for i in range(0,len(datas)):
        d1.Add(datas[i],1)
    print "data integral:"
    print d1.Integral()
    print d1.GetEntries()
    l.AddEntry(d1,datalegend,'PL')
    allStack.SetTitle()
    allStack.Draw("")
    allStack.GetXaxis().SetTitle(xTitle)
    allStack.GetYaxis().SetTitle(yTitle)
    allStack.GetXaxis().SetRangeUser(xMin,xMax)
    allStack.GetYaxis().SetRangeUser(0,20000)
    Ymax = max(allStack.GetMaximum(),d1.GetMaximum())*1.2
    allStack.SetMaximum(Ymax)
    allStack.SetMinimum(0.01)
    c.Update()
    ROOT.gPad.SetLogy()
    ROOT.gPad.SetTicks(1,1)
    allStack.Draw("")
    d1.SetMarkerStyle(21)
    d1.Draw("P0,E1,X0,same")
    l.SetFillColor(0)
    l.SetBorderSize(0)
    l.Draw()
    name = '%s/Stack/%s.png' %(plotPath,title)
    c.Print(name)
    
    
def treeStack(path,var,data):
    #*********************STACK*******************************

    plot=config.get('Plot',var)

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()

    options = plot.split(',')
    name=options[1]
    title = options[2]
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])

    setup=config.get('Plot','setup')
    setup=setup.split(',')


    print '\nProducing Plot of %s\n'%title


    histos = []
    typs = []
    datas = []
    datatyps =[]

    for job in info:
        if job.name != 'DATA':
            hTemp, typ = getHistoFromTree2(job,options)
            histos.append(hTemp)
            typs.append(typ)
        elif job.name in data:
            hTemp, typ = getHistoFromTree2(job,options)
            datas.append(hTemp)
            datatyps.append(typ)




    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(name,title, 800, 600)
    allStack = ROOT.THStack(name,title)     
    l = ROOT.TLegend(0.68, 0.63, 0.88, 0.88)
    MC_integral=0
    MC_entries=0

    for histo in histos:
        MC_integral+=histo.Integral()
        #MC_entries+=histo.GetEntries()
    print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral
    #flow = MC_entries-MC_integral
    #if flow > 0:
    #    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow    
    
    #ORDER AND ADD TOGETHER
    
    ordnung=[]
    ordnungtyp=[]
    num=[0]*len(setup)
    for i in range(0,len(setup)):
        for j in range(0,len(histos)):
            if typs[j] == setup[i]:
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
                histos[k].Add(histos[k+1],1)
                del histos[k+1]
                del typs[k+1]

    k=len(histos)
    for j in range(0,k):
        #print histos[j].GetBinContent(1)
        i=k-j-1
        allStack.Add(histos[i])
        l.AddEntry(histos[j],typs[j],'F')
        
    
    d1 = ROOT.TH1F('d1','d1',nBins,xMin,xMax)

    datatitle=''
    for i in range(0,len(datas)):
        d1.Add(datas[i],1)
        datatitle=datatitle+ ' + '+datatyps[i]
    print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
    flow = d1.GetEntries()-d1.Integral()
    if flow > 0:
        print "\033[1;31m\tU/O flow: %s\033[1;m"%flow
    l.AddEntry(d1,datatitle,'PL')
    allStack.SetTitle()
    allStack.Draw("")
    allStack.GetXaxis().SetTitle(title)
    allStack.GetYaxis().SetTitle('Counts')
    allStack.GetXaxis().SetRangeUser(xMin,xMax)
    allStack.GetYaxis().SetRangeUser(0,20000)
    Ymax = max(allStack.GetMaximum(),d1.GetMaximum())*1.2
    allStack.SetMaximum(Ymax)
    allStack.SetMinimum(0.1)
    c.Update()
    if config.get('Plot','logy') == '1':
        ROOT.gPad.SetLogy()
    ROOT.gPad.SetTicks(1,1)
    allStack.Draw("")
    d1.SetMarkerStyle(21)
    d1.Draw("P0,E1,X0,same")
    l.SetFillColor(0)
    l.SetBorderSize(0)
    l.Draw()
    
    name = '%s/%s' %(config.get('Directories','plotpath'),options[6])
    c.Print(name)

def treeCompare(path,var):
    #*********************STACK*******************************


    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()

    plot=config.get('Compare',var)
    options = plot.split(',')
    name=options[1]
    title = options[2]
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])


    bkgs=config.get('Compare','BKG')
    bkgs=bkgs.split(' ')

    sigs=config.get('Compare','SIG')
    sigs=sigs.split(' ')


    bkgsA = []
    bkgsB = []
    sigsA = []
    sigsB = []

    optionsA=copy(options)
    optionsB=copy(options)
    
    optionsA[7]=config.get('Compare','cutA')
    optionsB[7]=config.get('Compare','cutB')




    for job in info:
        if job.name in bkgs:
            hTemp, typ = getHistoFromTree2(job,optionsA)
            bkgsA.append(hTemp)
            hTemp, typ = getHistoFromTree2(job,optionsB)
            bkgsB.append(hTemp)
        if job.name in sigs:
            hTemp, typ = getHistoFromTree2(job,optionsA)
            sigsA.append(hTemp)
            hTemp, typ = getHistoFromTree2(job,optionsB)
            sigsB.append(hTemp)
        

    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(name,title, 800, 600)
    l = ROOT.TLegend(0.68, 0.7, 0.88, 0.88)

    ROOT.gStyle.SetOptStat(0)
    ROOT.gROOT.ForceStyle

    for i in range(1,len(sigsA)):
        sigsA[0].Add(sigsA[i])
        sigsB[0].Add(sigsB[i])


    for i in range(1,len(bkgsA)):
        bkgsA[0].Add(bkgsA[i])
        bkgsB[0].Add(bkgsB[i])
    
    ScaleFactor=1/sigsA[0].Integral()
    sigsA[0].Scale(ScaleFactor)
    ScaleFactor=1/sigsB[0].Integral()
    sigsB[0].Scale(ScaleFactor)
    ScaleFactor=1/bkgsA[0].Integral()
    bkgsA[0].Scale(ScaleFactor)
    ScaleFactor=1/bkgsB[0].Integral()
    bkgsB[0].Scale(ScaleFactor)
    

    sigsA[0].SetLineColor(2)
    sigsB[0].SetLineColor(1)
    bkgsA[0].SetLineColor(4)
    bkgsB[0].SetLineColor(1)
    
    sigsA[0].SetFillColor(0)
    sigsB[0].SetMarkerColor(2)
    bkgsA[0].SetFillColor(0)
    bkgsB[0].SetMarkerColor(4)


    sigsA[0].SetLineWidth(2)
    sigsB[0].SetLineWidth(1)
    bkgsA[0].SetLineWidth(2)
    bkgsB[0].SetLineWidth(1)


    sigsA[0].SetFillStyle(3000)
    sigsB[0].SetFillStyle(3345)
    bkgsA[0].SetFillStyle(3000)
    bkgsB[0].SetFillStyle(3354)

    l.AddEntry(sigsA[0],'SIG %s'%optionsA[7],'L')
    l.AddEntry(sigsB[0],'SIG %s'%optionsB[7],'PL')
    l.AddEntry(bkgsA[0],'BKG %s'%optionsA[7],'L')
    l.AddEntry(bkgsB[0],'BKG %s'%optionsB[7],'PL')


    maximum=max(sigsA[0].GetMaximum(),sigsB[0].GetMaximum(),bkgsA[0].GetMaximum(),bkgsB[0].GetMaximum())


    sigsA[0].SetTitle("Comparison EE/MM")
    sigsA[0].Draw("hist")
    sigsA[0].GetXaxis().SetTitle(title)
    sigsA[0].GetYaxis().SetTitle('Normalized Scale')
    sigsA[0].GetXaxis().SetRangeUser(xMin,xMax)
    sigsA[0].GetYaxis().SetRangeUser(0,maximum*1.1)
    #c.Update()
    #if config.get('Plot','logy') == '1':
    #    ROOT.gPad.SetLogy()
    ROOT.gPad.SetTicks(1,1)
    
    
    l.SetFillColor(0)
    l.SetBorderSize(0)
    l.Draw()
    print sigsA[0].GetEntries()
    print sigsB[0].GetEntries()
    print bkgsA[0].GetEntries()
    print bkgsB[0].GetEntries()
    

    sigsA[0].Draw("hist,same")
    sigsB[0].SetMarkerStyle(21)
    #sigsB[0].Sumw2()
    sigsB[0].Draw("P0,same")
    bkgsA[0].Draw("hist,same")
    bkgsB[0].SetMarkerStyle(21)
    #bkgsB[0].Sumw2()
    bkgsB[0].Draw("P0,same")
    


    
    name = '%s/%s' %(config.get('Directories','plotpath'),options[6])
    c.Print(name)

#NEW TRAINING
def newTraining(run,gui):

    #CONFIG
    #factory
    factoryname=config.get('factory','factoryname')
    factorysettings=config.get('factory','factorysettings')
    #MVA
    MVAtype=config.get(run,'MVAtype')
    MVAname=config.get(run,'MVAname')
    MVAsettings=config.get(run,'MVAsettings')
    fnameOutput = Wdir +'/weights/'+factoryname+'_'+MVAname+'.root'
    #locations
    Tpath=config.get(run,'Tpath')
    Epath=config.get(run,'Epath')
    
    #signals
    signals=config.get(run,'signals')
    signals=signals.split(' ')
    #backgrounds
    backgrounds=config.get(run,'backgrounds')
    backgrounds=backgrounds.split(' ')
    
    treeVarSet=config.get(run,'treeVarSet')
            
    #variables
    #TreeVar Array
    MVA_Vars={}
    MVA_Vars['Nominal']=config.get(treeVarSet,'Nominal')
    MVA_Vars['Nominal']=MVA_Vars['Nominal'].split(' ')    
    #Spectators:
    spectators=config.get(treeVarSet,'spectators')
    spectators=spectators.split(' ')
    
    #TRAINING samples
    infofile = open(Tpath+'/samples.info','r')
    Tinfo = pickle.load(infofile)
    infofile.close()

    #Evaluate samples
    infofile = open(Epath+'/samples.info','r')
    Einfo = pickle.load(infofile)
    infofile.close()    
    
    #Workdir
    workdir=ROOT.gDirectory.GetPath()
    
    
    #load TRAIN trees
    Tbackgrounds = []
    TbScales = []
    Tsignals = []
    TsScales = []
    
    for job in Tinfo:
        if job.name in signals:
            Tsignal = getTree2(job)
            ROOT.gDirectory.Cd(workdir)
            TsScale = getScale2(job)
            Tsignals.append(Tsignal)
            TsScales.append(TsScale)
            
        if job.name in backgrounds:
            Tbackground = getTree2(job)
            ROOT.gDirectory.Cd(workdir)
            TbScale = getScale2(job)
            Tbackgrounds.append(Tbackground)
            TbScales.append(TbScale)
            
    #load EVALUATE trees
    Ebackgrounds = []
    EbScales = []
    Esignals = []
    EsScales = []
    
    for job in Einfo:
        if job.name in signals:
            Esignal = getTree2(job)
            ROOT.gDirectory.Cd(workdir)
            EsScale = getScale2(job)
            Esignals.append(Esignal)
            EsScales.append(EsScale)
            
        if job.name in backgrounds:
            Ebackground = getTree2(job)
            ROOT.gDirectory.Cd(workdir)
            EbScale = getScale2(job)
            Ebackgrounds.append(Ebackground)
            EbScales.append(EbScale)

    output = ROOT.TFile.Open(fnameOutput, "RECREATE")
    factory = ROOT.TMVA.Factory(factoryname, output, factorysettings)
    
    #set input trees
    for i in range(len(Tsignals)):

        factory.AddSignalTree(Tsignals[i], TsScales[i], ROOT.TMVA.Types.kTraining)
        factory.AddSignalTree(Esignals[i], EsScales[i], ROOT.TMVA.Types.kTesting)
    
    for i in range(len(Tbackgrounds)):
        if (Tbackgrounds[i].GetEntries()>0):
            factory.AddBackgroundTree(Tbackgrounds[i], TbScales[i], ROOT.TMVA.Types.kTraining)

        if (Ebackgrounds[i].GetEntries()>0):
            factory.AddBackgroundTree(Ebackgrounds[i], EbScales[i], ROOT.TMVA.Types.kTesting)
            
            
    for var in MVA_Vars['Nominal']:
        factory.AddVariable(var,'D') # add the variables
    for var in spectators:
        factory.AddSpectator(var,'D') #add specators

    #Execute TMVA
    factory.SetSignalWeightExpression(weightF)
    factory.Verbose()
    factory.BookMethod(MVAtype,MVAname,MVAsettings)
    factory.TrainAllMethods()
    factory.TestAllMethods()
    factory.EvaluateAllMethods()
    output.Write()
    
    #WRITE INFOFILE
    infofile = open(Wdir+'/weights/'+factoryname+'_'+MVAname+'.info','w')
    info=mvainfo(MVAname)
    info.factoryname=factoryname
    info.factorysettings=factorysettings
    info.MVAtype=MVAtype
    info.MVAsettings=MVAsettings
    info.weightfilepath=Wdir+'/weights'
    info.Tpath=Tpath
    info.Epath=Epath
    info.varset=treeVarSet
    info.vars=MVA_Vars['Nominal']
    info.spectators=spectators
    pickle.dump(info,infofile)
    infofile.close()
    
    # open the TMVA Gui 
    if gui == 'gui': 
        ROOT.gROOT.ProcessLine( ".L TMVAGui.C")
        ROOT.gROOT.ProcessLine( "TMVAGui(\"%s\")" % fnameOutput )
        ROOT.gApplication.Run() 


#*********************EVALUATE*******************************
def evaluate(run,Apath): #fnameOutput='training.root', split=0.5

    #CONFIG
    #factory
    factoryname=config.get('factory','factoryname')
    #MVA
    MVAname=config.get(run,'MVAname')
    #print Wdir+'/weights/'+factoryname+'_'+MVAname+'.info'
    MVAinfofile = open(Wdir+'/weights/'+factoryname+'_'+MVAname+'.info','r')
    MVAinfo = pickle.load(MVAinfofile)
    treeVarSet=MVAinfo.varset
    #variables
    #TreeVar Array
    MVA_Vars={}
    for systematic in systematics:
        MVA_Vars[systematic]=config.get(treeVarSet,systematic)
        MVA_Vars[systematic]=MVA_Vars[systematic].split(' ')
    #Spectators:
    spectators=config.get(treeVarSet,'spectators')
    spectators=spectators.split(' ')
    #progbar quatsch
    longe=40
    #Workdir
    workdir=ROOT.gDirectory.GetPath()

    os.mkdir(Apath+'/'+run)


    #Book TMVA readers: MVAlist=["MMCC_bla","CC5050_bla"]
    reader=ROOT.TMVA.Reader("!Color:!Silent" )
    
    #define variables and specatators
    MVA_var_buffer = []
    for i in range(len( MVA_Vars['Nominal'])):
        MVA_var_buffer.append(array( 'f', [ 0 ] ))
        reader.AddVariable( MVA_Vars['Nominal'][i],MVA_var_buffer[i])
    MVA_spectator_buffer = []
    for i in range(len(spectators)):
        MVA_spectator_buffer.append(array( 'f', [ 0 ] ))
        reader.AddSpectator(spectators[i],MVA_spectator_buffer[i])
    #Load raeder
    reader.BookMVA(MVAinfo.MVAname,MVAinfo.getweightfile())
    #--> Now the MVA is booked
    
    #Apply samples
    infofile = open(Apath+'/samples.info','r')
    Ainfo = pickle.load(infofile)
    infofile.close()
    
    #eval
    for job in Ainfo:
        job.addcomment('Added MVA %s'%MVAinfo.MVAname)
        #MCs
        
        
        
    
        input = TFile.Open(job.getpath(),'read')
        Count = input.Get("Count")
        CountWithPU = input.Get("CountWithPU")
        CountWithPU2011B = input.Get("CountWithPU2011B")
        tree = input.Get(job.tree)
        nEntries = tree.GetEntries()
    
    
    
    
        #tree = getTree2(job)
        ROOT.gDirectory.Cd(workdir)
        #nEntries=tree.GetEntries()
        
    
        
        
        if job.type != 'DATA':
        

            MVA_formulas={}
            for systematic in systematics: 
                #print '\t\t - ' + systematic
                MVA_formulas[systematic]=[]
                #create TTreeFormulas
                for j in range(len( MVA_Vars['Nominal'])):
                    MVA_formulas[systematic].append(ROOT.TTreeFormula("MVA_formula%s_%s"%(j,systematic),MVA_Vars[systematic][j],tree))
            job.addpath('/%s'%run)
            outfile = ROOT.TFile(job.getpath(), 'RECREATE')
            newtree = tree.CloneTree(0)
            #Setup Branches
            MVA = array('f',[0]*9)
            newtree.Branch(MVAinfo.MVAname,MVA,'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down/F')
            print '\n--> ' + job.name +':'
            #progbar setup
            if nEntries >= longe:
                step=int(nEntries/longe)
                long=longe
            else:
                long=nEntries
                step = 1
            bar=progbar(long)                

            #Fill event by event:
            for entry in range(0,nEntries):
                if entry % step == 0:
                    bar.move()
                #load entry
                tree.GetEntry(entry)
                for systematic in systematics:
                    for j in range(len( MVA_Vars['Nominal'])):
                        MVA_var_buffer[j][0] = MVA_formulas[systematic][j].EvalInstance()
                    MVA[systematics.index(systematic)] = reader.EvaluateMVA(MVAinfo.MVAname)
                #Fill:
                newtree.Fill()
                
            newtree.Write()
            newtree.Write()            
            Count.Write()
            CountWithPU.Write()
            CountWithPU2011B.Write()
            outfile.Close()
            
        #DATA
        if job.type == 'DATA':
        
            #MVA Formulas
            MVA_formulas_Nominal = []
            #create TTreeFormulas
            for j in range(len( MVA_Vars['Nominal'])):
                MVA_formulas_Nominal.append(ROOT.TTreeFormula("MVA_formula%s_Nominal"%j, MVA_Vars['Nominal'][j],tree))
            job.addpath('/%s'%run)
            outfile = ROOT.TFile(job.getpath(), 'RECREATE')
            newtree = tree.CloneTree(0)
            #Setup Branches
            MVA = array('f',[0])
            newtree.Branch(MVAinfo.MVAname,MVA,'nominal/F') 
            #progbar           
            print '\n--> ' + job.name +':'
            if nEntries >= longe:
                step=int(nEntries/longe)
                long=longe
            else:
                long=nEntries
                step = 1
            bar=progbar(long)

            #Fill event by event:
            for entry in range(0,nEntries):
                if entry % step == 0:
                    bar.move()
                #load entry
                tree.GetEntry(entry)
                #nominal:
                for j in range(len( MVA_Vars['Nominal'])):
                        MVA_var_buffer[j][0] = MVA_formulas_Nominal[j].EvalInstance()
                MVA[0]= discr = reader.EvaluateMVA(MVAinfo.MVAname)                
                newtree.Fill()
            newtree.Write()
            newtree.Write()            
            Count.Write()
            CountWithPU.Write()
            CountWithPU2011B.Write()
            outfile.Close()
                
    print '\n'                
    infofile = open(Apath+'/'+run+'/samples.info','w')
    pickle.dump(Ainfo,infofile)
    infofile.close()

######################
#Evaluate multi: Must Have same treeVars!!!
def evalMulti(Apath,arglist): #fnameOutput='training.root', split=0.5
    MVAlist=arglist.split(',')

    #CONFIG
    #factory
    factoryname=config.get('factory','factoryname')
    #MVA
    MVAnames=[]
    for MVA in MVAlist:
        print MVA
        MVAnames.append(config.get(MVA,'MVAname'))
    #print Wdir+'/weights/'+factoryname+'_'+MVAname+'.info'
    #MVAinfofiles=[]
    MVAinfos=[]
    for MVAname in MVAnames:
        MVAinfofile = open(Wdir+'/weights/'+factoryname+'_'+MVAname+'.info','r')
        MVAinfos.append(pickle.load(MVAinfofile))
        MVAinfofile.close()
        
    treeVarSet=MVAinfos[0].varset
    #variables
    #TreeVar Array
    MVA_Vars={}
    for systematic in systematics:
        MVA_Vars[systematic]=config.get(treeVarSet,systematic)
        MVA_Vars[systematic]=MVA_Vars[systematic].split(' ')
    #Spectators:
    spectators=config.get(treeVarSet,'spectators')
    spectators=spectators.split(' ')
    #progbar quatsch
    longe=40
    #Workdir
    workdir=ROOT.gDirectory.GetPath()
    os.mkdir(Apath+'/MVAout')

    #Book TMVA readers: MVAlist=["MMCC_bla","CC5050_bla"]
    readers=[]
    for MVA in MVAlist:
        readers.append(ROOT.TMVA.Reader("!Color:!Silent"))
    
    #define variables and specatators
    MVA_var_buffer = []
    for i in range(len( MVA_Vars['Nominal'])):
        MVA_var_buffer.append(array( 'f', [ 0 ] ))
        for reader in readers:
            reader.AddVariable( MVA_Vars['Nominal'][i],MVA_var_buffer[i])
    MVA_spectator_buffer = []
    for i in range(len(spectators)):
        MVA_spectator_buffer.append(array( 'f', [ 0 ] ))
        for reader in readers:
            reader.AddSpectator(spectators[i],MVA_spectator_buffer[i])
    #Load raeder
    for i in range(0,len(readers)):
        readers[i].BookMVA(MVAinfos[i].MVAname,MVAinfos[i].getweightfile())
    #--> Now the MVA is booked
    
    #Apply samples
    infofile = open(Apath+'/samples.info','r')
    Ainfo = pickle.load(infofile)
    infofile.close()
    
    #eval
    for job in Ainfo:
        for MVAinfo in MVAinfos:
            job.addcomment('Added MVA %s'%MVAinfo.MVAname)
        #MCs
    
        input = TFile.Open(job.getpath(),'read')
        Count = input.Get("Count")
        CountWithPU = input.Get("CountWithPU")
        CountWithPU2011B = input.Get("CountWithPU2011B")
        tree = input.Get(job.tree)
        nEntries = tree.GetEntries()
    
        #tree = getTree2(job)
        ROOT.gDirectory.Cd(workdir)
        #nEntries=tree.GetEntries()
        
        if job.type != 'DATA':
        
            MVA_formulas={}
            for systematic in systematics: 
                #print '\t\t - ' + systematic
                MVA_formulas[systematic]=[]
                #create TTreeFormulas
                for j in range(len( MVA_Vars['Nominal'])):
                    MVA_formulas[systematic].append(ROOT.TTreeFormula("MVA_formula%s_%s"%(j,systematic),MVA_Vars[systematic][j],tree))
            job.addpath('/MVAout')
            outfile = ROOT.TFile(job.getpath(), 'RECREATE')
            newtree = tree.CloneTree(0)
            #Setup Branches
            MVAbranches=[]
            for i in range(0,len(readers)):
                MVAbranches.append(array('f',[0]*9))
                newtree.Branch(MVAinfos[i].MVAname,MVAbranches[i],'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down/F')
            print '\n--> ' + job.name +':'
            #progbar setup
            if nEntries >= longe:
                step=int(nEntries/longe)
                long=longe
            else:
                long=nEntries
                step = 1
            bar=progbar(long)                

            #Fill event by event:
            for entry in range(0,nEntries):
                if entry % step == 0:
                    bar.move()
                #load entry
                tree.GetEntry(entry)
                for systematic in systematics:
                    for j in range(len( MVA_Vars['Nominal'])):
                        MVA_var_buffer[j][0] = MVA_formulas[systematic][j].EvalInstance()
                        
                    for j in range(0,len(readers)):
                        MVAbranches[j][systematics.index(systematic)] = readers[j].EvaluateMVA(MVAinfos[j].MVAname)
                #Fill:
                newtree.Fill()
                
            newtree.Write()
            newtree.Write()            
            Count.Write()
            CountWithPU.Write()
            CountWithPU2011B.Write()
            outfile.Close()
            
        #DATA
        if job.type == 'DATA':
        
            #MVA Formulas
            MVA_formulas_Nominal = []
            #create TTreeFormulas
            for j in range(len( MVA_Vars['Nominal'])):
                MVA_formulas_Nominal.append(ROOT.TTreeFormula("MVA_formula%s_Nominal"%j, MVA_Vars['Nominal'][j],tree))
            job.addpath('/MVAout')
            outfile = ROOT.TFile(job.getpath(), 'RECREATE')
            newtree = tree.CloneTree(0)
            #Setup Branches
            MVAbranches=[]
            for i in range(0,len(readers)):

                MVAbranches.append(array('f',[0]))
                newtree.Branch(MVAinfos[i].MVAname,MVAbranches[i],'nominal/F') 
            #progbar           
            print '\n--> ' + job.name +':'
            if nEntries >= longe:
                step=int(nEntries/longe)
                long=longe
            else:
                long=nEntries
                step = 1
            bar=progbar(long)

            #Fill event by event:
            for entry in range(0,nEntries):
                if entry % step == 0:
                    bar.move()
                #load entry
                tree.GetEntry(entry)
                #nominal:
                for j in range(len( MVA_Vars['Nominal'])):
                        MVA_var_buffer[j][0] = MVA_formulas_Nominal[j].EvalInstance()
                        
                for j in range(0,len(readers)):
                    MVAbranches[j][0]= readers[j].EvaluateMVA(MVAinfos[j].MVAname)
                    
                                        
                newtree.Fill()
            newtree.Write()
            newtree.Write()            
            Count.Write()
            CountWithPU.Write()
            CountWithPU2011B.Write()
            outfile.Close()
                
    print '\n'                
    infofile = open(Apath+'/MVAout/samples.info','w')
    pickle.dump(Ainfo,infofile)
    infofile.close()


def Limit(path,var,data):
    print data


    plot=config.get('Limit',var)

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()

    options = plot.split(',')


    name=options[1]
    title = options[2]
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])

    setup=config.get('Plot','setup')
    setup=setup.split(',')


    ROOToutname = options[6]


    outpath=config.get('Directories','limits')


    outfile = ROOT.TFile(outpath+ROOToutname+'.root', 'RECREATE')
    #Spuck out se Histograms for se Comination tool
    discr_names = ['Zudscg', 'Zbb', 'TTbar','VV', 'ST', 'Sig115', 'Wudscg', 'Wbb', 'QCD']
    data_name = ['data_obs']




    histos = []
    typs = []
    datas = []
    datatyps =[]

    for job in info:
        print job.name
        if job.type != 'DATA':
            print 'MC'
            hTemp, typ = getHistoFromTree2(job,options)
            histos.append(hTemp)
            typs.append(typ)
        elif job.name in data:
            print 'DATA'
            hTemp, typ = getHistoFromTree2(job,options)
            datas.append(hTemp)
            datatyps.append(typ)




    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(name,title, 800, 600)
    MC_integral=0
    MC_entries=0

    for histo in histos:
        MC_integral+=histo.Integral()
        #MC_entries+=histo.GetEntries()
    print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral
    #flow = MC_entries-MC_integral
    #if flow > 0:
    #    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow    
    
    #ORDER AND ADD TOGETHER
    
    ordnung=[]
    ordnungtyp=[]
    num=[0]*len(setup)
    for i in range(0,len(setup)):
        for j in range(0,len(histos)):
            if typs[j] == setup[i]:
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
                histos[k].Add(histos[k+1],1)
                del histos[k+1]
                del typs[k+1]

        
    
    d1 = ROOT.TH1F('d1','d1',nBins,xMin,xMax)

    for i in range(0,len(datas)):
        d1.Add(datas[i],1)
    print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
    flow = d1.GetEntries()-d1.Integral()
    if flow > 0:
        print "\033[1;31m\tU/O flow: %s\033[1;m"%flow



    for i in range(0,len(histos)):
        histos[i].SetName(discr_names[i])
        histos[i].SetDirectory(outfile)
        histos[i].Draw()
        print discr_names[i]
        print histos[i].Integral(0,nBins)

        
    #datas[0]: data_obs
    d1.SetName(data_name[0])
    d1.SetDirectory(outfile)
    print data_name[0]
    print d1.Integral(0,nBins)
    print d1.Integral()
    print d1.GetEntries()
    
    #write DATAcard
    f = open(outpath+'/vhbb_%s.txt'%ROOToutname,'w')
    f.write('imax\t1\tnumber of channels\njmax\t8\tnumber of backgrounds (\'*\' = automatic)\nkmax\t*\tnumber of nuisance parameters (sources of systematical uncertainties)\n\n')
    f.write('shapes * * %s.root $PROCESS $PROCESS$SYSTEMATIC\n\nbin\tZee\n\n'%ROOToutname)
    f.write('observation\t%s\n\n\n' %(d1.Integral()))
    f.write('bin\tZee\tZee\tZee\tZee\tZee\tZee\tZee\tZee\tZee\n')
    f.write('process\tSig115\tWudscg\tWbb\tZudscg\tZbb\tTTbar\tST\tVV\tQCD\n')
    f.write('process\t0\t1\t2\t3\t4\t5\t6\t7\t8\n')
    f.write('rate\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n' %(histos[5].Integral(),0,0,histos[0].Integral(),histos[1].Integral(),histos[2].Integral(),histos[4].Integral(),histos[3].Integral(),0)) #\t1.918\t0.000 0.000\t135.831  117.86  18.718 1.508\t7.015\t0.000
    f.write('lumi\tlnN\t1.045\t-\t-\t-\t-\t-\t1.045\t1.045\t1.045\npdf_qqbar\tlnN\t1.01\t-\t-\t-\t-\t-\t-\t1.01\t-\npdf_gg\tlnN\t-\t-\t-\t-\t-\t-\t1.01\t-\t1.01\nQCDscale_VH\tlnN\t1.04\t-\t-\t-\t-\t-\t-\t-\t-\nQCDscale_ttbar\tlnN\t-\t-\t-\t-\t-\t-\t1.06\t-\t-\nQCDscale_VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.04\t-\nQCDscale_QCD\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t1.30\nCMS_vhbb_boost_EWK\tlnN\t1.05\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_boost_QCD\tlnN\t1.10\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_ST\tlnN\t-\t-\t-\t-\t-\t-\t1.29\t-\t-\nCMS_vhbb__VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.30\t-\nCMS_vhbb_WjLF_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_WjHF_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_ZjLF_SF\tlnN\t-\t-\t-\t1.06\t-\t-\t-\t-\t-\nCMS_vhbb_ZjHF_SF\tlnN\t-\t-\t-\t-\t1.17\t-\t-\t-\t-\nCMS_vhbb_TT_SF\tlnN\t-\t-\t-\t-\t-\t1.14\t-\t-\t-\nCMS_vhbb_QCD_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_trigger_m\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_trigger_e\tlnN\t1.02\t-\t-\t-\t-\t-\t1.02\t1.02\t-\n')
    f.write('CMS_vhbb_trigger_MET\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_eff_m\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_eff_e\tlnN\t1.04\t-\t-\t-\t-\t-\t1.04\t1.04\t1.04\nCMS_toteff_b\tlnN\t1.10\t1.10\t1.00\t1.10\t1.00\t1.10\t1.10\t1.10\t1.10\nCMS_totscale_j\tlnN\t1.02\t-\t-\t-\t-\t-\t1.02\t1.02\t-\nCMS_totres_j\tlnN\t1.05\t1.03\t1.03\t1.03\t1.03\t1.03\t1.03\t1.05\t-\nCMS_vhbb_MET_nojets\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VH_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjLF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjHF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhb_stats_ZjLF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_ZjHF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_TT_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_sT_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VV_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_QCD_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjHF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhb_stats_ZjLF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_ZjHF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_TT_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_sT_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VV_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_QCD_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VH_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjLF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjHF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhb_stats_ZjLF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_ZjHF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_TT_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_sT_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VV_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_QCD_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VH_Zee\tlnN\t1.03\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjLF_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjHF_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhb_stats_ZjLF_Zee\tlnN\t-\t-\t-\t1.05\t-\t-\t-\t-\t-\nCMS_vhbb_stats_ZjHF_Zee\tlnN\t-\t-\t-\t-\t1.07\t-\t-\t-\t-\nCMS_vhbb_stats_TT_Zee\tlnN\t-\t-\t-\t-\t-\t1.06\t-\t-\t-\nCMS_vhbb_stats_sT_Zee\tlnN\t-\t-\t-\t-\t-\t-\t1.30\t-\t-\nCMS_vhbb_stats_Diboson_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.06\t-\nCMS_vhbb_stats_QCD_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VH_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjLF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_WjHF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhb_stats_ZjLF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_ZjHF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_TT_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_sT_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_VV_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\nCMS_vhbb_stats_QCD_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.close()
    
    #dunnmies
    dummies=[]
    #Wlight,Wbb,QCD
    for i in range(6,9):
        dummy = ROOT.TH1F(discr_names[i], "discriminator", nBins, xMin, xMax)
        dummy.SetDirectory(outfile)
        dummy.Draw()
        dummies.append(dummy)
        print discr_names[i]
    #Wbb
    #dummy = ROOT.TH1F(discr_names[7], "discriminator", div, discrMin, discrMax)
    #dummies.append(dummy)
    #QCD
    #dummy = ROOT.TH1F(discr_names[8], "discriminator", div, discrMin, discrMax)
    #dummies.append(dummy)
        
    #Write to file
    outfile.Write()
    outfile.Close()
    
    
def writeWorkspace(path,var,data):


    plot=config.get('Limit',var)

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()

    options = plot.split(',')


    name=options[1]
    title = options[2]
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])

    setup=config.get('Plot','setup')
    setup=setup.split(',')


    ROOToutname = options[6]


    outpath=config.get('Directories','limits')


    outfile = ROOT.TFile(outpath+ROOToutname+'_WS.root', 'RECREATE')
    discr_names = ['Zudscg', 'Zbb', 'TTbar','VV', 'ST', 'Sig115', 'Wudscg', 'Wbb', 'QCD']
    data_name = ['data_obs']

    WS = ROOT.RooWorkspace('Zee','Zee')
    print 'WS initialized'

    disc= ROOT.RooRealVar('BDT','BDT',-1,1)
    obs = ROOT.RooArgList(disc)


    histos = []
    typs = []
    datas = []
    datatyps =[]

    for job in info:
        #print job.name
        if job.type != 'DATA':
            #print 'MC'
            hTemp, typ = getHistoFromTree2(job,options)
            histos.append(hTemp)
            typs.append(typ)
        elif job.name in data:
            #print 'DATA'
            hTemp, typ = getHistoFromTree2(job,options)
            datas.append(hTemp)
            datatyps.append(typ)




    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(name,title, 800, 600)
    MC_integral=0
    MC_entries=0

    for histo in histos:
        MC_integral+=histo.Integral()
        #MC_entries+=histo.GetEntries()
    print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral
    #flow = MC_entries-MC_integral
    #if flow > 0:
    #    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow    
    
    #ORDER AND ADD TOGETHER
    
    ordnung=[]
    ordnungtyp=[]
    num=[0]*len(setup)
    for i in range(0,len(setup)):
        for j in range(0,len(histos)):
            if typs[j] == setup[i]:
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
                histos[k].Add(histos[k+1],1)
                del histos[k+1]
                del typs[k+1]

        
    
    d1 = ROOT.TH1F('d1','d1',nBins,xMin,xMax)

    for i in range(0,len(datas)):
        d1.Add(datas[i],1)
    print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
    flow = d1.GetEntries()-d1.Integral()
    if flow > 0:
        print "\033[1;31m\tU/O flow: %s\033[1;m"%flow






    for i in range(0,len(histos)):
        histos[i].SetName(discr_names[i])
        histos[i].SetDirectory(outfile)
        histos[i].Draw()
        




        statUp = histos[i].Clone()
        statDown = histos[i].Clone()
        #shift up and down with statistical error
        for j in range(histos[i].GetNbinsX()):
            statUp.SetBinContent(j,statUp.GetBinContent(j)+statUp.GetBinError(j))
            statDown.SetBinContent(j,statDown.GetBinContent(j)-statDown.GetBinError(j))
        statUp.SetName('%sStatsUp'%discr_names[i])
        statDown.SetName('%sStatsDown'%discr_names[i])


        histPdf = ROOT.RooDataHist(discr_names[i],discr_names[i],obs,histos[i])

        #UP stats of MCs
        RooStatsUp = ROOT.RooDataHist('%sStatsUp'%discr_names[i],'%sStatsUp'%discr_names[i],obs, statUp)
        #DOWN stats of MCs
        RooStatsDown = ROOT.RooDataHist('%sStatsDown'%discr_names[i],'%sStatsDown'%discr_names[i],obs, statDown)
        
        
        getattr(WS,'import')(histPdf)
        getattr(WS,'import')(RooStatsUp)
        getattr(WS,'import')(RooStatsDown)



        frame=disc.frame()


        ROOT.RooAbsData.plotOn(histPdf,frame)
        frame.Draw()
        
        c.Print('~/Hbb/WStest/%s.png'%discr_names[i])




        #print discr_names[i]
        #print histos[i].Integral(0,nBins)

        
    #datas[0]: data_obs
    d1.SetName(data_name[0])
    d1.SetDirectory(outfile)
    #print data_name[0]
    #print d1.Integral(0,nBins)
    #print d1.Integral()
    #print d1.GetEntries()
    
    #write DATAcard
    f = open(outpath+'/vhbb_%s_WS.txt'%ROOToutname,'w')
    f.write('imax\t1\tnumber of channels\n')
    f.write('jmax\t8\tnumber of backgrounds (\'*\' = automatic)\n')
    f.write('kmax\t*\tnumber of nuisance parameters (sources of systematical uncertainties)\n\n')

    f.write('shapes * * %s_WS.root $CHANNEL:$PROCESS $CHANNEL:$PROCESS$SYSTEMATIC\n\n'%ROOToutname)
    f.write('bin\tZee\n\n')
    f.write('observation\t%s\n\n'%d1.Integral())
    f.write('bin\tZee\tZee\tZee\tZee\tZee\tZee\tZee\tZee\tZee\n')
    f.write('process\tSig115\tWudscg\tWbb\tZudscg\tZbb\tTTbar\tST\tVV\tQCD\n')
    f.write('process\t0\t1\t2\t3\t4\t5\t6\t7\t8\n')
    f.write('rate\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n'%(histos[5].Integral(),0,0,histos[0].Integral(),histos[1].Integral(),histos[2].Integral(),histos[4].Integral(),histos[3].Integral(),0)) #\t1.918\t0.000 0.000\t135.831  117.86  18.718 1.508\t7.015\t0.000
    f.write('lumi\tlnN\t1.045\t-\t-\t-\t-\t-\t1.045\t1.045\t1.045\n\n')
    f.write('pdf_qqbar\tlnN\t1.01\t-\t-\t-\t-\t-\t-\t1.01\t-\n')
    f.write('pdf_gg\tlnN\t-\t-\t-\t-\t-\t-\t1.01\t-\t1.01\n')
    f.write('QCDscale_VH\tlnN\t1.04\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('QCDscale_ttbar\tlnN\t-\t-\t-\t-\t-\t-\t1.06\t-\t-\n')
    f.write('QCDscale_VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.04\t-\n')
    f.write('QCDscale_QCD\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t1.30\n')
    f.write('CMS_vhbb_boost_EWK\tlnN\t1.05\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_boost_QCD\tlnN\t1.10\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_ST\tlnN\t-\t-\t-\t-\t-\t-\t1.29\t-\t-\n')
    f.write('CMS_vhbb__VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.30\t-\n')
    f.write('CMS_vhbb_WjLF_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_WjHF_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_ZjLF_SF\tlnN\t-\t-\t-\t1.06\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_ZjHF_SF\tlnN\t-\t-\t-\t-\t1.17\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_TT_SF\tlnN\t-\t-\t-\t-\t-\t1.14\t-\t-\t-\n')
    f.write('CMS_vhbb_QCD_SF\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_trigger_m\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_trigger_e\tlnN\t1.02\t-\t-\t-\t-\t-\t1.02\t1.02\t-\n')
    f.write('CMS_vhbb_trigger_MET\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_eff_m\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_eff_e\tlnN\t1.04\t-\t-\t-\t-\t-\t1.04\t1.04\t1.04\n')
    f.write('CMS_toteff_b\tlnN\t1.10\t1.10\t1.00\t1.10\t1.00\t1.10\t1.10\t1.10\t1.10\n')
    f.write('CMS_totscale_j\tlnN\t1.02\t-\t-\t-\t-\t-\t1.02\t1.02\t-\n')
    f.write('CMS_totres_j\tlnN\t1.05\t1.03\t1.03\t1.03\t1.03\t1.03\t1.03\t1.05\t-\n')
    f.write('CMS_vhbb_MET_nojets\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VH_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjHF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhb_stats_ZjLF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_ZjHF_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_TT_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_sT_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VV_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_QCD_Wmn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjHF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhb_stats_ZjLF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_ZjHF_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_TT_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_sT_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VV_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_QCD_Wen\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VH_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjHF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhb_stats_ZjLF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_ZjHF_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_TT_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_sT_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VV_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_QCD_Zmm\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VH_Zee\tlnN\t1.03\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjHF_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhb_stats_ZjLF_Zee\tlnN\t-\t-\t-\t1.05\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_ZjHF_Zee\tlnN\t-\t-\t-\t-\t1.07\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_TT_Zee\tlnN\t-\t-\t-\t-\t-\t1.06\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_sT_Zee\tlnN\t-\t-\t-\t-\t-\t-\t1.30\t-\t-\n')
    f.write('CMS_vhbb_stats_Diboson_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.06\t-\n')
    f.write('CMS_vhbb_stats_QCD_Zee\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VH_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjLF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_WjHF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhb_stats_ZjLF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_ZjHF_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_TT_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_sT_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_VV_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_vhbb_stats_QCD_Znn\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')

    f.write('Stats\tshape\t1.0\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t1.0\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t1.0\t-\t-\t-\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t1.0\t-\t-\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t-\t1.0\t-\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t-\t-\t1.0\t-\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t-\t-\t-\t1.0\t-\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t-\t-\t-\t-\t1.0\t-\n')
    f.write('Stats\tshape\t-\t-\t-\t-\t-\t-\t-\t-\t1.0\n')

    
    f.close()
    
    #dunnmies
    #Wlight,Wbb,QCD
    for i in range(6,9):
        dummy = ROOT.TH1F(discr_names[i], "discriminator", nBins, xMin, xMax)
        dummy.SetDirectory(outfile)
        dummy.Draw()
        
        #nominal
        histPdf = ROOT.RooDataHist(discr_names[i],discr_names[i],obs,dummy)
        #UP stats of MCs
        RooStatsUp = ROOT.RooDataHist('%sStatsUp'%discr_names[i],'%sStatsUp'%discr_names[i],obs, dummy)
        #DOWN stats of MCs
        RooStatsDown = ROOT.RooDataHist('%sStatsDown'%discr_names[i],'%sStatsDown'%discr_names[i],obs, dummy)
        
        
        getattr(WS,'import')(histPdf)
        getattr(WS,'import')(RooStatsUp)
        getattr(WS,'import')(RooStatsDown)
        #print discr_names[i]
    #Wbb
    #dummy = ROOT.TH1F(discr_names[7], "discriminator", div, discrMin, discrMax)
    #dummies.append(dummy)
    #QCD
    #dummy = ROOT.TH1F(discr_names[8], "discriminator", div, discrMin, discrMax)
    #dummies.append(dummy)
        
    #Write to file



               
    #HISTOGRAMM of DATA
    #ROOT.RooDataHist('data_obsHist','',RooArgList,??)
    histPdf = ROOT.RooDataHist('data_obs','data_obs',obs,d1)
    ROOT.RooAbsData.plotOn(histPdf,frame)
    frame.Draw()
    
    c.Print('~/Hbb/WStest/d1.png')
    #IMPORT
    getattr(WS,'import')(histPdf)

    #Number of Obs?
    nObs = int(d1.Integral())
    

    

    '''
               
       theStatsUp = []
       theStatsDown = []
       
       #LOOP over MCsamples BKG
       for i in range(0,len(self.__theStacks)):
           #name = 'ZjLF'
           name = '%s%s' %(self.__dcRepMap[self.__datasets[i]],self.__writeCombination) #what is self writeCombination??, assume ''
           print name
           self.__theStacks[i].SetName(name)
           
           #HISTOGRAMM of MCs
           #ROOT.RooDataHist('ZjLF','',RooArgList,??)
           histPdf = ROOT.RooDataHist(name,'',obs,self.__theStacks[i])
           #IMPORT
           getattr(self.__w,'import')(histPdf)
           
           
           if self.__writeCombination == '':
               self.__dcRepMap['n%s'%(self.__datasets[i])] = self.__theStacks[i].Integral()
               name = '%s%s%s%s' %(self.__dcRepMap[self.__datasets[i]],'_CMS_vhbb_stats_',self.__dcRepMap[self.__datasets[i]],'_%(bin)s'%self.__dcRepMap)
               statUp = self.__theStacks[i].Clone()
               statDown = self.__theStacks[i].Clone()
               #shift up and down with statistical error
               for j in range(self.__theStacks[i].GetNbinsX()):
                   statUp.SetBinContent(j,statUp.GetBinContent(j)+statUp.GetBinError(j))
                   statDown.SetBinContent(j,statDown.GetBinContent(j)-statDown.GetBinError(j))
               theStatsUp.append(statUp)
               theStatsDown.append(statDown)
               theStatsUp[i].SetName('%s%s' %(name,'Up'))
               theStatsDown[i].SetName('%s%s' %(name,'Down'))
               #UP stats of MCs
               theRooStatsUp = ROOT.RooDataHist('%s%s' %(name,'Up'),'',obs, theStatsUp[i])
               #DOWN stats of MCs
               theRooStatsDown = ROOT.RooDataHist('%s%s' %(name,'Down'),'',obs, theStatsDown[i])
               getattr(self.__w,'import')(theRooStatsUp)
               getattr(self.__w,'import')(theRooStatsDown)
               
               
       #overlays=signal SIG
       #OVERLAYS??
       theOStatsUp = []
       theOStatsDown = []
       for i in range(0,len(self.__theOverlays)):
           name = '%s%s' %(self.__dcRepMap[self.__overlays[i]],self.__writeCombination)
           self.__theOverlays[i].SetName(name)
           histPdf = ROOT.RooDataHist(name,'',obs,self.__theOverlays[i])
           getattr(self.__w,'import')(histPdf)
           if self.__writeCombination == '':
               self.__dcRepMap['nSig'] = self.__theOverlays[i].Integral()
               #e.g. name=TTbar_CMS_vhbb_stats_TTbar_ZeeUp
               name = '%s%s%s%s' %(self.__dcRepMap[self.__overlays[i]],'_CMS_vhbb_stats_',self.__dcRepMap[self.__overlays[i]],'_%(bin)s'%self.__dcRepMap)
               statUp = self.__theOverlays[i].Clone()
               statDown = self.__theOverlays[i].Clone()
               for j in range(self.__theOverlays[i].GetNbinsX()):
                   statUp.SetBinContent(j,statUp.GetBinContent(j)+statUp.GetBinError(j))
                   statDown.SetBinContent(j,statDown.GetBinContent(j)-statDown.GetBinError(j))
               theOStatsUp.append(statUp)
               theOStatsDown.append(statDown)
               theOStatsUp[i].SetName('%s%s' %(name,'Up'))
               theOStatsDown[i].SetName('%s%s' %(name,'Down'))
               theRooStatsUp = ROOT.RooDataHist('%s%s' %(name,'Up'),'',obs, theOStatsUp[i])
               theRooStatsDown = ROOT.RooDataHist('%s%s' %(name,'Down'),'',obs, theOStatsDown[i])
               getattr(self.__w,'import')(theRooStatsUp)
               getattr(self.__w,'import')(theRooStatsDown)
       
      '''         
               
    WS.writeToFile(outpath+ROOToutname+'_WS.root')
       #WS.writeToFile("testWS.root")







        
def SysPlot(mode,systematic):

    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas('title','title', 800, 600)
    ROOT.gPad.SetTicks(1,1)


    #systematic='JER'
    
    #if mode == 'test':
    #    type = 'TMVAClassification_nov10BDTCatnaJet3_shuffled'

    #if mode == 'test2':
    #    type = 'TMVAClassification_nov10BDT_shuffled'

    print 'ok, i plot the MVA output for you...'
    #namehisto = 'taskTMVAClassification_BDTCatnaJet3loose'
    namehisto = task+type
    rebin = 100
    if mode == 'test': path=treePath+'/test'
    if mode == 'Top': path=treePath+'/Top'
    if mode == 'Zlight': path=treePath+'/Zlight'
    if mode == 'Zbb': path=treePath+'/Zbb'
    if mode == 'Signal': path=treePath+'/Signal'

    MVAtitle=mode
    nBins=div/rebin

    Ntotal = ROOT.TH1F(systematic,systematic,nBins,discrMin,discrMax)     
    Utotal = ROOT.TH1F('Utotal','Utotal',nBins,discrMin,discrMax)     
    Dtotal = ROOT.TH1F('Dtotal','Dtotal',nBins,discrMin,discrMax)     
    
    for job in jobs: #jobs:
        jobN= path +'/MVA_'+training+'_'+MVAtitle+'.' + job +'.root'
        jobU= path +'/MVA_'+training+'_'+MVAtitle+'.' + job +'.'+systematic+'_up.root'
        jobD= path +'/MVA_'+training+'_'+MVAtitle+'.' + job +'.'+systematic+'_down.root'
        print jobN
        l = ROOT.TLegend(0.28, 0.73, 0.38, 0.88)
        #hTemp = getHistoFromTree(path,job2,0)
        
        N = ROOT.TFile(jobN, 'OPEN')
        NHist = N.Get(namehisto)
        NHist.Rebin(rebin)
        NHist.SetDirectory(0)
        NHist.SetLineColor(1)
        NHist.SetMarkerStyle(8)
        NHist.SetStats(0)
        NHist.SetTitle('MVA '+systematic+' '+ legenden[jobs.index(job)])
        Ntotal.Add(NHist)
        l.AddEntry(NHist,'nominal','PL')
        
        U = ROOT.TFile(jobU, 'OPEN')
        UHist = U.Get(namehisto)
        UHist.Rebin(rebin)
        UHist.SetDirectory(0)
        UHist.SetLineColor(4)
        UHist.SetLineStyle(4)
        UHist.SetLineWidth(2)
        l.AddEntry(UHist,'up','PL')
        Utotal.Add(UHist)
        
        D = ROOT.TFile(jobD, 'OPEN')
        DHist = D.Get(namehisto)
        DHist.Rebin(rebin)
        DHist.SetDirectory(0)
        DHist.SetLineColor(2)
        DHist.SetLineStyle(3)
        DHist.SetLineWidth(2)
        l.AddEntry(DHist,'down','PL')
        Dtotal.Add(DHist)        
        
        NHist.Draw("P0")
        NHist.Draw("same")
        UHist.Draw("same")
        DHist.Draw("same")
        l.SetFillColor(0)
        l.SetBorderSize(0)
        l.Draw()
        title= mode + type + legenden[jobs.index(job)] +systematic
        name = '%s/Stack/%s.png' %(plotPath,title)
        c.Print(name)
        N.Close()
        U.Close()
        D.Close()
     
    Ntotal.SetMarkerStyle(8)
    Ntotal.SetLineColor(1)
    Ntotal.SetStats(0)
    Ntotal.Draw("P0")
    Ntotal.Draw("same")
    Utotal.SetLineColor(4)    
    Utotal.SetLineStyle(4)
    Utotal.SetLineWidth(2)        
    Utotal.Draw("same")
    Dtotal.SetLineColor(2)
    Dtotal.SetLineStyle(3)
    Dtotal.Draw("same")
    Dtotal.SetLineWidth(2)        
    l.Draw()

    title= mode + type +systematic
    name = '%s/Stack/%s.png' %(plotPath,title)
    c.Print(name)

def newFoM(path,var):





    plot=config.get('FoM',var)

    infofile = open(path+'/samples.info','r')
    info = pickle.load(infofile)
    infofile.close()



    options = plot.split(',')
    name=options[1]
    title = options[2]
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])

    bkgs=config.get('FoM','BKG')
    bkgs=bkgs.split(' ')

    sigs=config.get('FoM','SIG')
    sigs=sigs.split(' ')


    ROOT.gROOT.SetStyle("Plain")
    c = ROOT.TCanvas(title,title, 800, 600)
    ROOT.gPad.SetTicks(1,1)




    print '\nProducing Plot of %s\n'%title


    histos = []

    for job in info:
        if job.name in bkgs:
            hTemp, typ = getHistoFromTree2(job,options)
            histos.append(hTemp)
    
    for job in info:
        if job.name in sigs:
            hTemp, typ = getHistoFromTree2(job,options)
            histos.append(hTemp)
    
    for i in range(1,len(bkgs)):
        histos[0].Add(histos[1],1)
        del histos[1]

    
    for i in range(1,len(sigs)):
        histos[1].Add(histos[2],1)
        del histos[2]



    fig = []
    C=[]
    print '\n\t--> Info:'
    B=histos[0].Integral()
    print '\t Background count is %s' %B
    S=histos[1].Integral()
    print '\t Signal count is %s\n' %S
    F=[]
    print 'nbins %s' %nBins
    print 'size %s' %histos[0].GetSize()
    for i in range(0,nBins):
        #print S
        #print B
        if B >= 0:
            FOM = S/(1.5+sqrt(B)+0.2*B)
            F.append(FOM)
            #print (S/(1.5+sqrt(B)+0.2*B))
            print 'S = %s, B = %s, FoM = %s' %(S,B,FOM)
            C.append(histos[0].GetBinCenter(i+1))
        else: print 'S %s, B %s' %(S,B)
        B=B-histos[0].GetBinContent(i+1)
        S=S-histos[1].GetBinContent(i+1)

    x = array('f', C)
    y = array('f', F)
    gr1 = ROOT.TGraph(len(x), x,y)
    gr1.SetTitle(title)
    gr1.Draw('APL')
    gr1.GetXaxis().SetTitle('BDT Cut')
    gr1.GetYaxis().SetTitle('FoM')
    gr1.GetXaxis().SetRangeUser(xMin,xMax)
    name = '%s/%s' %(config.get('Directories','plotpath'),options[6])
    c.Print(name)

#*********************Actually DO STH*******************************
#getList(signalFiles)
if sys.argv[1] == 'limitWS': writeWorkspace(sys.argv[2],sys.argv[3],sys.argv[4])
if sys.argv[1] == 'newtrain': newTraining(sys.argv[2],sys.argv[3])
if sys.argv[1] == 'eval': evaluate(sys.argv[2],sys.argv[3])#,sys.argv[4])
if sys.argv[1] == 'evalMulti': evalMulti(sys.argv[2],sys.argv[3])
if sys.argv[1] == 'limit': Limit(sys.argv[2],sys.argv[3],sys.argv[4])
if sys.argv[1] == 'plot': plot()
if sys.argv[1] == 'allplots': allplots()
if sys.argv[1] == 'comp': createComparison()
if sys.argv[1] == 'compare': treeCompare(sys.argv[2],sys.argv[3])

if sys.argv[1] == 'MVAplot': MVAstack(sys.argv[2])
if sys.argv[1] == 'SysPlot': SysPlot(sys.argv[2],sys.argv[3])
if sys.argv[1] == 'copy': CutCopy(sys.argv[2])
if sys.argv[1] == 'FoM': newFoM(sys.argv[2],sys.argv[3])
if sys.argv[1] == 'shuffle': shuffle()
if sys.argv[1] == 'SuperShuffle': SuperShuffle()
if sys.argv[1] == 'addsys': AddSystematics(sys.argv[2])
if sys.argv[1] == 'addcut': Addcut(sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])
if sys.argv[1] == 'addsinglecut': Addsinglecut(sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])
if sys.argv[1] == 'addfile': AddFile(sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6])
if sys.argv[1] == 'stack': treeStack(sys.argv[2],sys.argv[3],sys.argv[4])
