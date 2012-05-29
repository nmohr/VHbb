#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from ConfigParser import SafeConfigParser
import sys
from mvainfos import mvainfo
from gethistofromtree import getHistoFromTree, orderandadd
from Ratio import getRatio

#warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#load config
config = SafeConfigParser()
config.read('./config')

#get locations:
Wdir=config.get('Directories','Wdir')


Normalize=True

path = sys.argv[1]
var = sys.argv[2]

if 'bb' in var or 'Light' in var or 'Top' in var:
    Normalize=True

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

mass=options[9]
data=options[10]

blind=options[11]

setup=config.get('Plot','setup')
setup=setup.split(',')

color=config.get('Plot','color')
color=color.split(',')


weightF=config.get('Weights','weightF')


print '\nProducing Plot of %s\n'%title


histos = []
typs = []
datas = []
datatyps =[]
datanames=[]

for job in info:
    if job.type == 'BKG':
        #print 'MC'
        hTemp, typ = getHistoFromTree(job,options,2)
        histos.append(hTemp)
        typs.append(typ)
    elif job.type == 'SIG' and job.name == mass:
        hTemp, typ = getHistoFromTree(job,options,2)
        histos.append(hTemp)
        typs.append(typ)    
    elif job.name in data:
        #print 'DATA'
        hTemp, typ = getHistoFromTree(job,options)
        datas.append(hTemp)
        datatyps.append(typ)
        datanames.append(job.name)



ROOT.gROOT.SetStyle("Plain")
c = ROOT.TCanvas(name,title, 800, 700)

oben = ROOT.TPad('oben','oben',0,0.2 ,1.0,1.0,10)
unten = ROOT.TPad('unten','unten',0,0.05,1.0,0.2,10)

oben.Draw()
unten.Draw()
#c.Divide(1,2)

#c.cd(1)
oben.cd()

allStack = ROOT.THStack(name,title)     
l = ROOT.TLegend(0.75, 0.63, 0.88, 0.88)
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

histos, typs = orderandadd(histos,typs,setup)


k=len(histos)
for j in range(0,k):
    #print histos[j].GetBinContent(1)
    i=k-j-1
    histos[i].SetFillColor(int(color[i]))
    allStack.Add(histos[i])
    l.AddEntry(histos[j],typs[j],'F')
    

d1 = ROOT.TH1F('noData','noData',nBins,xMin,xMax)
datatitle=''
for i in range(0,len(datas)):
    d1.Add(datas[i],1)
    if i ==0:
        datatitle=datanames[i]
    else:
        datatitle=datatitle+ ' + '+datanames[i]
print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
flow = d1.GetEntries()-d1.Integral()
if flow > 0:
    print "\033[1;31m\tU/O flow: %s\033[1;m"%flow
l.AddEntry(d1,datatitle,'PL')

if Normalize:
    stackscale=d1.Integral()/MC_integral
    stackhists=allStack.GetHists()
    for blabla in stackhists:
        blabla.Scale(stackscale)



allStack.SetTitle()
allStack.Draw("hist")
allStack.GetXaxis().SetTitle(title)
allStack.GetYaxis().SetTitle('Counts')
allStack.GetXaxis().SetRangeUser(xMin,xMax)
allStack.GetYaxis().SetRangeUser(0,20000)
Ymax = max(allStack.GetMaximum(),d1.GetMaximum())*1.3
allStack.SetMaximum(Ymax)
allStack.SetMinimum(0.1)
c.Update()
if config.get('Plot','logy') == '1':
    ROOT.gPad.SetLogy()
ROOT.gPad.SetTicks(1,1)
allStack.Draw("hist")
d1.SetMarkerStyle(21)
d1.Draw("P,E1,X0,same")
l.SetFillColor(0)
l.SetBorderSize(0)
l.Draw()


allMC=ROOT.TH1F('allMC','allMC',nBins,xMin,xMax)
allMC.Sumw2()
for bin in range(0,nBins):
    allMC.SetBinContent(bin,allStack.GetStack().Last().GetBinContent(bin))




t = ROOT.TLatex()
t.SetNDC()
t.SetTextAlign(12)
t.SetTextSize(0.04)
t.DrawLatex(0.13,0.85,"CMS Preliminary")#, BDT Shape")
t.SetTextSize(0.03)
t.DrawLatex(0.13,0.79,"#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}")
#t.DrawLatex(0.13,0.74,"Z(ll)H(b#bar{b})")


unten.cd()
ROOT.gPad.SetTicks(1,1)

ratio, error, ksScore, chiScore = getRatio(d1,allMC,xMin,xMax)
print ksScore
print chiScore
ratio.SetStats(0)
ratio.GetYaxis().SetRangeUser(0.5,1.5)
ratio.GetYaxis().SetNdivisions(502,0)
ratio.GetYaxis().SetLabelSize(0.2)
ratio.GetYaxis().SetTitleSize(0.2)
ratio.GetYaxis().SetTitleOffset(0.2)
ratio.GetXaxis().SetLabelColor(10)
ratio.Draw("E1")
ratio.SetTitle("")
m_one_line = ROOT.TLine(xMin,1,xMax,1)
m_one_line.SetLineStyle(7)
m_one_line.SetLineColor(4)
m_one_line.Draw("Same")

t = ROOT.TLatex()
t.SetNDC()
t.SetTextAlign(12)
t.SetTextSize(0.15)
t.DrawLatex(0.12,0.8,"KS: %s"%(ksScore))
t.DrawLatex(0.12,0.25,"x2: %s"%(chiScore))

name = '%s/%s' %(config.get('Directories','plotpath'),options[6])
c.Print(name)