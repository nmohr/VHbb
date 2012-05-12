#!/usr/bin/env python



import sys
import os

import ROOT 
from ROOT import TFile

from array import array

from math import sqrt
from copy import copy
#suppres the EvalInstace conversion warning bug

import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='Error in <TTree::Fill>:*' )
from ConfigParser import SafeConfigParser



from samplesclass import sample
from mvainfos import mvainfo
import pickle
from progbar import progbar
from printcolor import printc


class DevNull:
    def write(self, msg):
        pass

sys.stderr = DevNull()




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







weightF=config.get('Weights','weightF')


def getTree(job,cut):
    Tree = ROOT.TChain(job.tree)
    Tree.Add(job.getpath())
    #Tree.SetDirectory(0)
    CuttedTree=Tree.CopyTree(cut)
    #CuttedTree.SetDirectory(0)
    print '\t--> read in %s'%job.name
    return CuttedTree
       

def getScale(job):
    input = TFile.Open(job.getpath())
    CountWithPU = input.Get("CountWithPU")
    CountWithPU2011B = input.Get("CountWithPU2011B")
    #print lumi*xsecs[i]/hist.GetBinContent(1)
    return float(job.lumi)*float(job.xsec)*float(job.sf)/(0.46502*CountWithPU.GetBinContent(1)+0.53498*CountWithPU2011B.GetBinContent(1))*2/float(job.split)


def getHistoFromTree(job,options):
    treeVar=options[0]
    name=job.name
    #title=job.plotname()
    nBins=int(options[3])
    xMin=float(options[4])
    xMax=float(options[5])
    if job.type != 'DATA':
        cutcut=config.get('Cuts',options[7])
        treeCut='%s & EventForTraining == 0'%cutcut

    elif job.type == 'DATA':
        treeCut=config.get('Cuts',options[8])

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
        Tree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),treeCut, "goff,e")
        full = True
    if full:
        hTree = ROOT.gDirectory.Get(name)
    else:
        hTree = ROOT.TH1F('%s'%name,'%s'%name,nBins,xMin,xMax)
        hTree.Sumw2()
    #print job.name + ' Sumw2', hTree.GetEntries()

    if job.type != 'DATA':
        ScaleFactor = getScale(job)
        if ScaleFactor != 0:
            hTree.Scale(ScaleFactor)
            
    print '\t-->import %s\t Integral: %s'%(job.name,hTree.Integral())
            
    return hTree, job.group
    

######################

path=sys.argv[1]
var=sys.argv[2]


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


mass=options[9]
data=options[10]


setup=config.get('Limit','setup')
setup=setup.split(',')

ROOToutname = options[6]
outpath=config.get('Directories','limits')
outfile = ROOT.TFile(outpath+'vhbb_TH_'+ROOToutname+'.root', 'RECREATE')
discr_names = ['ZjLF','ZjCF','ZjHF', 'TT','VV', 's_Top', 'VH', 'WjLF', 'WjHF', 'QCD']
data_name = ['data_obs']
WS = ROOT.RooWorkspace('%s'%options[10],'%s'%options[10]) #Zee
print 'WS initialized'
disc= ROOT.RooRealVar('BDT','BDT',-1,1)
obs = ROOT.RooArgList(disc)

ROOT.gROOT.SetStyle("Plain")
#c = ROOT.TCanvas(name,title, 800, 600)


datas = []
datatyps =[]
histos = []
typs = []
statUps=[]
statDowns=[]


for job in info:
    if job.type == 'BKG':
        #print 'MC'
        hTemp, typ = getHistoFromTree(job,options)
        histos.append(hTemp)
        typs.append(typ)
    elif job.type == 'SIG' and job.name == mass:
        hTemp, typ = getHistoFromTree(job,options)
        histos.append(hTemp)
        typs.append(typ)    
    elif job.name in data:
        #print 'DATA'
        hTemp, typ = getHistoFromTree(job,options)
        datas.append(hTemp)
        datatyps.append(typ)

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
        
            #add
            histos[k].Add(histos[k+1],1)
            printc('red','','\t--> added %s to %s'%(typs[k],typs[k+1]))
            del histos[k+1]
            del typs[k+1]

del histos[len(num):]
del typs[len(num):]



for i in range(0,len(histos)):
    histos[i].SetName(discr_names[i])
    #histos[i].SetDirectory(outfile)
    outfile.cd()
    histos[i].Write()


    statUps.append(histos[i].Clone())
    statDowns.append(histos[i].Clone())
    statUps[i].SetName('%sCMS_vhbb_stats_%s_%sUp'%(discr_names[i],discr_names[i],options[10]))
    statDowns[i].SetName('%sCMS_vhbb_stats_%s_%sDown'%(discr_names[i],discr_names[i],options[10]))
    statUps[i].Sumw2()
    statDowns[i].Sumw2()
    
    #shift up and down with statistical error
    for j in range(histos[i].GetNbinsX()):
        #print '\t\t Up  : %s'%(statUps[i].GetBinContent(j)+statUps[i].GetBinError(j))
        #print '\t\t Nominal: %s'%histos[i].GetBinContent(j)
        statUps[i].SetBinContent(j,statUps[i].GetBinContent(j)+statUps[i].GetBinError(j))
        #print '\t\t Down: %s'%(statDowns[i].GetBinContent(j)-statDowns[i].GetBinError(j))
        statDowns[i].SetBinContent(j,statDowns[i].GetBinContent(j)-statDowns[i].GetBinError(j))



    #statUps[i].SetDirectory(outfile)
    #statDowns[i].SetDirectory(outfile)
    #statUps[i].Draw("goff")
    #outfile.cd()
    statUps[i].Write()
    #statUp.Write()
    statDowns[i].Write()
    #statDowns[i].Draw("goff")
    #statDown.Write()

    histPdf = ROOT.RooDataHist(discr_names[i],discr_names[i],obs,histos[i])

    #UP stats of MCs
    RooStatsUp = ROOT.RooDataHist('%sCMS_vhbb_stats_%s_%sUp'%(discr_names[i],discr_names[i],options[10]),'%sCMS_vhbb_stats_%s_%sUp'%(discr_names[i],discr_names[i],options[10]),obs, statUps[i])
    #DOWN stats of MCs
    RooStatsDown = ROOT.RooDataHist('%sCMS_vhbb_stats_%s_%sDown'%(discr_names[i],discr_names[i],options[10]),'%sCMS_vhbb_stats_%s_%sDown'%(discr_names[i],discr_names[i],options[10]),obs, statDowns[i])
    
    

    
    getattr(WS,'import')(histPdf)
    getattr(WS,'import')(RooStatsUp)
    getattr(WS,'import')(RooStatsDown)

#dunnmies
#Wlight,Wbb,QCD
for i in range(7,10):
    dummy = ROOT.TH1F(discr_names[i], "discriminator", nBins, xMin, xMax)
    #dummy.SetDirectory(outfile)
    outfile.cd()
    dummy.Write()
    #dummy.Draw("goff")
    
    #nominal
    histPdf = ROOT.RooDataHist(discr_names[i],discr_names[i],obs,dummy)
    #UP stats of MCs
    RooStatsUp = ROOT.RooDataHist('%sCMS_vhbb_stats_%s_%sUp'%(discr_names[i],discr_names[i],options[10]),'%sCMS_vhbb_stats_%s_%sUp'%(discr_names[i],discr_names[i],options[10]),obs, dummy)
    #DOWN stats of MCs
    RooStatsDown = ROOT.RooDataHist('%sCMS_vhbb_stats_%s_%sDown'%(discr_names[i],discr_names[i],options[10]),'%sCMS_vhbb_stats_%s_%sDown'%(discr_names[i],discr_names[i],options[10]),obs, dummy)
    
    getattr(WS,'import')(histPdf)
    getattr(WS,'import')(RooStatsUp)
    getattr(WS,'import')(RooStatsDown)





#HISTOGRAMM of DATA    
d1 = ROOT.TH1F('d1','d1',nBins,xMin,xMax)
for i in range(0,len(datas)):
    d1.Add(datas[i],1)
print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
flow = d1.GetEntries()-d1.Integral()
if flow > 0:
    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow
    
#datas[0]: data_obs
d1.SetName(data_name[0])
#d1.SetDirectory(outfile)
outfile.cd()
d1.Write()
#d1.Draw("goff")

#ROOT.RooDataHist('data_obsHist','',RooArgList,??)
histPdf = ROOT.RooDataHist('data_obs','data_obs',obs,d1)
#ROOT.RooAbsData.plotOn(histPdf,frame)
#frame.Draw()

#c.Print('~/Hbb/WStest/d1.png')
#IMPORT
getattr(WS,'import')(histPdf)

#Number of Obs?
#nObs = int(d1.Integral())

#SYSTEMATICS:

#systematics=config.get('systematics','systematics')
#for sys in systematics[1:]

ud = ['up','down']
UD = ['Up','Down']

systhistosarray=[]
Coco=0

for sys in ['JER','JES','beff','bmis']:

    for Q in range(0,2):
    
        ff=options[0].split('.')
        ff[1]='%s_%s'%(sys,ud[Q])
        options[0]='.'.join(ff)


        printc('blue','','\t\t--> doing systematic %s %s'%(sys,ud[Q])) 

        systhistosarray.append([])
        #histosX = []
        typsX = []

        for job in info:
            #print job.name
            if job.type == 'BKG':
                #print 'MC'
                hTemp, typ = getHistoFromTree(job,options)
                systhistosarray[Coco].append(hTemp)
                typsX.append(typ)
                
            elif job.type == 'SIG' and job.name == mass:
                #print 'MC'
                hTemp, typ = getHistoFromTree(job,options)
                systhistosarray[Coco].append(hTemp)
                typsX.append(typ)


        MC_integral=0
        MC_entries=0

        for histoX in systhistosarray[Coco]:
            MC_integral+=histoX.Integral()
            #MC_entries+=histo.GetEntries()
        print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral
        #flow = MC_entries-MC_integral
        #if flow > 0:
        #    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow    
        
        #ORDER AND ADD TOGETHER
        ordnungX=[]
        ordnungtypX=[]
        num=[0]*len(setup)
        #printc('red','','num=%s'%num)
        for i in range(0,len(setup)):
            #printc('blue','','i am in %s'%setup[i])
            for j in range(0,len(systhistosarray[Coco])):
                #printc('blue','','i compare %s'%typsX[j])
                if typsX[j] == setup[i]:
                    #print 'yes'
                    num[i]+=1
                    ordnungX.append(systhistosarray[Coco][j])

                    ordnungtypX.append(typsX[j])
        #printc('red','','num=%s'%num)

        #del systhistosarray[Coco]
        del typsX
        systhistosarray[Coco]=ordnungX
        typsX=ordnungtypX
        for k in range(0,len(num)):
            for m in range(0,num[k]):
                if m > 0:
                    systhistosarray[Coco][k].Add(systhistosarray[Coco][k+1],1)
                    #printc('red','','added %s to %s'%(typsX[k],typsX[k+1]))
                    del systhistosarray[Coco][k+1]
                    del typsX[k+1]
        for i in range(0,len(systhistosarray[Coco])):
            systhistosarray[Coco][i].SetName('%sCMS_%s%s'%(discr_names[i],sys,UD[Q]))
            #systhistosarray[Coco][i].SetDirectory(outfile)
            outfile.cd()
            systhistosarray[Coco][i].Write()
            #systhistosarray[Coco][i].Draw("goff")
            #histosX[i].Write()
            
            histPdf = ROOT.RooDataHist('%sCMS_%s%s'%(discr_names[i],sys,UD[Q]),'%sCMS_%s%s'%(discr_names[i],sys,UD[Q]),obs,systhistosarray[Coco][i])
            getattr(WS,'import')(histPdf)


        Coco+=1
        #print Coco

WS.writeToFile(outpath+'vhbb_WS_'+ROOToutname+'.root')
   #WS.writeToFile("testWS.root")


#write DATAcard:
pier = open (Wdir+'/pier.txt','r')
scalefactors=pier.readlines()
pier.close()

f = open(outpath+'vhbb_DC_'+ROOToutname+'.txt','w')
f.write('imax\t1\tnumber of channels\n')
f.write('jmax\t9\tnumber of backgrounds (\'*\' = automatic)\n')
f.write('kmax\t*\tnumber of nuisance parameters (sources of systematical uncertainties)\n\n')
f.write('shapes * * vhbb_WS_%s.root $CHANNEL:$PROCESS $CHANNEL:$PROCESS$SYSTEMATIC\n\n'%ROOToutname)
f.write('bin\t%s\n\n'%options[10])
f.write('observation\t%s\n\n'%d1.Integral())
f.write('bin\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n'%(options[10],options[10],options[10],options[10],options[10],options[10],options[10],options[10],options[10],options[10]))
f.write('process\tVH\tWjLF\tWjHF\tZjLF\tZjCF\tZjHF\tTT\ts_Top\tVV\tQCD\n')
f.write('process\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n')
f.write('rate\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n'%(histos[6].Integral(),0,0,histos[0].Integral(),histos[1].Integral(),histos[2].Integral(),histos[3].Integral(),histos[5].Integral(),histos[4].Integral(),0)) #\t1.918\t0.000 0.000\t135.831  117.86  18.718 1.508\t7.015\t0.000
f.write('lumi\tlnN\t1.045\t-\t-\t-\t-\t-\t-\t1.045\t1.045\t1.045\n\n')
f.write('pdf_qqbar\tlnN\t1.01\t-\t-\t-\t-\t-\t-\t-\t1.01\t-\n')
f.write('pdf_gg\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.01\t-\t1.01\n')
f.write('QCDscale_VH\tlnN\t1.04\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
f.write('QCDscale_ttbar\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.06\t-\t-\n')
f.write('QCDscale_VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t1.04\t-\n')
f.write('QCDscale_QCD\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t1.30\n')
f.write('CMS_vhbb_boost_EWK\tlnN\t1.05\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
f.write('CMS_vhbb_boost_QCD\tlnN\t1.10\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
f.write('CMS_vhbb_ST\tlnN\t-\t-\t-\t-\t-\t-\t-\t1.29\t-\t-\n')
f.write('CMS_vhbb_VV\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t1.30\t-\n')
#for line in scalefactors:
#    f.write(line)

f.write('CMS_vhbb_ZjLF_SF\tlnN\t-\t-\t-\t1.206\t0.808\t1.081\t1.000\t-\t-\t-\t-\n')
f.write('CMS_vhbb_ZjCF_SF\tlnN\t-\t-\t-\t0.621\t1.406\t0.759\t1.001\t-\t-\t-\t-\n')
f.write('CMS_vhbb_ZjHF_SF\tlnN\t-\t-\t-\t1.079\t0.882\t1.199\t0.964\t-\t-\t-\t-\n')
f.write('CMS_vhbb_TT_SF\tlnN\t-\t-\t-\t1.000\t1.000\t0.969\t1.169\t-\t-\t-\t-\n')

if options[10]=='Zee':
    f.write('CMS_eff_m lnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_eff_e lnN\t1.04\t-\t-\t-\t-\t-\t-\t1.04\t1.04\t1.04\n')
    f.write('CMS_trigger_m\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_trigger_e\tlnN\t1.02\t-\t-\t-\t-\t-\t-\t1.02\t1.02\t-\n')

if options[10]=='Zmm':
    f.write('CMS_eff_e lnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_eff_m lnN\t1.04\t-\t-\t-\t-\t-\t-\t1.04\t1.04\t1.04\n')
    f.write('CMS_trigger_e\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
    f.write('CMS_trigger_m\tlnN\t1.02\t-\t-\t-\t-\t-\t-\t1.02\t1.02\t-\n')

f.write('CMS_vhbb_trigger_MET\tlnN\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n')
f.write('CMS_vhbb_stats_VH_%s\tshape\t1.0\t-\t-\t-\t-\t-\t-\t-\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_ZjLF_%s\tshape\t-\t-\t-\t1.0\t-\t-\t-\t-\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_ZjCF_%s\tshape\t-\t-\t-\t-\t1.0\t-\t-\t-\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_ZjHF_%s\tshape\t-\t-\t-\t-\t-\t1.0\t-\t-\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_TT_%s\tshape\t-\t-\t-\t-\t-\t-\t1.0\t-\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_s_Top_%s\tshape\t-\t-\t-\t-\t-\t-\t-\t1.0\t-\t-\n'%options[10])
f.write('CMS_vhbb_stats_VV_%s\tshape\t-\t-\t-\t-\t-\t-\t-\t-\t1.0\t-\n'%options[10])
#SYST
f.write('CMS_JER\tshape\t1.0\t-\t-\t1.0\t1.0\t1.0\t1.0\t1.0\t1.0\t-\n')
f.write('CMS_JES\tshape\t1.0\t-\t-\t1.0\t1.0\t1.0\t1.0\t1.0\t1.0\t-\n')
f.write('CMS_beff\tshape\t1.0\t-\t-\t1.0\t1.0\t1.0\t1.0\t1.0\t1.0\t-\n')
f.write('CMS_bmis\tshape\t1.0\t-\t-\t1.0\t1.0\t1.0\t1.0\t1.0\t1.0\t-\n')
f.close()

outfile.Write()
outfile.Close()