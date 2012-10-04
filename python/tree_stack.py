#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import ROOT 
from ROOT import TFile, TTree
import ROOT
from array import array
from BetterConfigParser import BetterConfigParser
import sys, os
from mvainfos import mvainfo
#from gethistofromtree import getHistoFromTree, orderandadd
from Ratio import getRatio
from optparse import OptionParser
from HistoMaker import HistoMaker, orderandadd
import TdrStyles

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-P", "--path", dest="path", default="",
                      help="path to samples")
parser.add_option("-R", "--reg", dest="region", default="",
                      help="region to plot")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
print opts.config
config = BetterConfigParser()
config.read(opts.config)
anaTag = config.get("Analysis","tag")

TrainFlag = eval(config.get('Analysis','TrainFlag'))

if TrainFlag:
    MC_rescale_factor=2.
    print 'I RESCALE BY 2.0'
else: MC_rescale_factor = 1.

path = opts.path
region = opts.region

plotConfig = BetterConfigParser()
plotConfig.read('vhbbPlotDef.ini')

#get locations:
Wdir=config.get('Directories','Wdir')

section='Plot:%s'%region

Normalize = eval(config.get(section,'Normalize'))
log = eval(config.get(section,'log'))
blind = eval(config.get(section,'blind'))

infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()

#options = plot.split(',')

mass = config.get(section,'Signal')

vars = (config.get(section, 'vars')).split(',')

names = [plotConfig.get('plotDef:%s'%x,'relPath') for x in vars]
nBins = [eval(plotConfig.get('plotDef:%s'%x,'nBins')) for x in vars]
xMin = [eval(plotConfig.get('plotDef:%s'%x,'min')) for x in vars]
xMax = [eval(plotConfig.get('plotDef:%s'%x,'max')) for x in vars]
xAxis = [plotConfig.get('plotDef:%s'%x,'xAxis') for x in vars]

for p in range(0,len(names)):
    if '<mass>' in names[p]:
        newp= names[p].replace('<mass>',mass)
        names[p]=newp
    print names[p]

data = config.get(section,'Datas')
if config.has_option(section, 'Datacut'):
    datacut=config.get(section, 'Datacut')
else:
    datacut = region

options=[]

if blind: blindopt='blind'
else: blindopt = 'noblind'

for i in range(0,len(vars)):
    options.append([names[i],'',xAxis[i],nBins[i],xMin[i],xMax[i],'%s_%s.pdf'%(region,vars[i]),region,datacut,mass,data,blindopt])


setup=config.get('Plot_general','setup')
setup=setup.split(',')

samples=config.get('Plot_general','samples')
samples=samples.split(',')

colorDict=eval(config.get('Plot_general','colorDict'))
#color=color.split(',')


weightF=config.get('Weights','weightF')
Group = eval(config.get('Plot_general','Group'))


#GETALL AT ONCE

Plotter=HistoMaker(path,config,region,options,MC_rescale_factor)

#print '\nProducing Plot of %s\n'%vars[v]
Lhistos = [[] for _ in range(0,len(vars))]
Ltyps = [[] for _ in range(0,len(vars))]
Ldatas = [[] for _ in range(0,len(vars))]
Ldatatyps = [[] for _ in range(0,len(vars))]
Ldatanames = [[] for _ in range(0,len(vars))]

def myText(txt="CMS Preliminary",ndcX=0,ndcY=0,size=0.8):
    ROOT.gPad.Update()
    text = ROOT.TLatex()
    text.SetNDC()
    text.SetTextColor(ROOT.kBlack)
    text.SetTextSize(text.GetTextSize()*size)
    text.DrawLatex(ndcX,ndcY,txt)
    return text


#Find out Lumi:
for job in info:
    if job.name in data: lumi_data=float(job.lumi)

Plotter.lumi=lumi_data

for job in info:
    if eval(job.active):
        if job.subsamples:
            for subsample in range(0,len(job.subnames)):
                
                if job.subnames[subsample] in samples:
                    hTempList, typList = Plotter.getHistoFromTree(job,subsample)
                    for v in range(0,len(vars)):
                        Lhistos[v].append(hTempList[v])
                        Ltyps[v].append(Group[job.subnames[subsample]])

        else:
            if job.name in samples:
                #print job.getpath()
                hTempList, typList = Plotter.getHistoFromTree(job)
                for v in range(0,len(vars)):
                    Lhistos[v].append(hTempList[v])
                    Ltyps[v].append(Group[job.name])

            elif job.name in data:
                #print 'DATA'
                hTemp, typ = Plotter.getHistoFromTree(job)
                for v in range(0,len(vars)):
                    Ldatas[v].append(hTemp[v])
                    Ldatatyps[v].append(typ[v])
                    Ldatanames[v].append(job.name)


for v in range(0,len(vars)):

    histos = Lhistos[v]
    typs = Ltyps[v]
    datas = Ldatas[v]
    datatyps = Ldatatyps[v]
    datanames= Ldatanames[v]

    TdrStyles.tdrStyle()
    
    c = ROOT.TCanvas(vars[v],'', 600, 600)
    c.SetFillStyle(4000)
    c.SetFrameFillStyle(1000)
    c.SetFrameFillColor(0)

    oben = ROOT.TPad('oben','oben',0,0.3 ,1.0,1.0)
    oben.SetBottomMargin(0)
    oben.SetFillStyle(4000)
    oben.SetFrameFillStyle(1000)
    oben.SetFrameFillColor(0)
    unten = ROOT.TPad('unten','unten',0,0.0,1.0,0.3)
    unten.SetTopMargin(0.)
    unten.SetBottomMargin(0.35)
    unten.SetFillStyle(4000)
    unten.SetFrameFillStyle(1000)
    unten.SetFrameFillColor(0)

    oben.Draw()
    unten.Draw()

    oben.cd()

    allStack = ROOT.THStack(vars[v],'')     
    l = ROOT.TLegend(0.75, 0.63, 0.88, 0.88)
    MC_integral=0
    MC_entries=0

    for histo in histos:
        MC_integral+=histo.Integral()
        #MC_entries+=histo.GetEntries()
    print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral

    #ORDER AND ADD TOGETHER
    #print typs
    #print setup
    histos, typs = orderandadd(histos,typs,setup)


    k=len(histos)
    
    for j in range(0,k):
        #print histos[j].GetBinContent(1)
        i=k-j-1
        histos[i].SetFillColor(int(colorDict[setup[i]]))
        histos[i].SetLineColor(1)
        allStack.Add(histos[i])
        l.AddEntry(histos[j],typs[j],'F')

    d1 = ROOT.TH1F('noData','noData',nBins[v],xMin[v],xMax[v])
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
        if MC_integral != 0:	stackscale=d1.Integral()/MC_integral
        stackhists=allStack.GetHists()
        for blabla in stackhists:
        	if MC_integral != 0: blabla.Scale(stackscale)
    
    allMC=ROOT.TH1F('allMC','allMC',nBins[v],xMin[v],xMax[v])
    allMC.Sumw2()
    for bin in range(0,nBins[v]):
        allMC.SetBinContent(bin,allStack.GetStack().Last().GetBinContent(bin))
        allMC.SetBinError(bin,allStack.GetStack().Last().GetBinError(bin))

    allStack.SetTitle()
    allStack.Draw("hist")
    allStack.GetXaxis().SetTitle('')
    yTitle = 'Entries'
    if not '/' in yTitle:
            yAppend = '%s' %(allStack.GetXaxis().GetBinWidth(1)) 
            yTitle = '%s / %s' %(yTitle, yAppend)
    allStack.GetYaxis().SetTitle(yTitle)
    allStack.GetXaxis().SetRangeUser(xMin[v],xMax[v])
    allStack.GetYaxis().SetRangeUser(0,20000)
    theErrorGraph = ROOT.TGraphErrors(allMC)
    theErrorGraph.SetFillColor(ROOT.kGray+3)
    theErrorGraph.SetFillStyle(3013)
    theErrorGraph.Draw('SAME2')
    Ymax = max(allStack.GetMaximum(),d1.GetMaximum())*1.3
    allStack.SetMaximum(Ymax)
    allStack.SetMinimum(0.1)
    c.Update()
    if log:
        ROOT.gPad.SetLogy()
    ROOT.gPad.SetTicks(1,1)
    #allStack.Draw("hist")
    d1.Draw("E0same")
    l.SetFillColor(0)
    l.SetBorderSize(0)
    l.Draw()



    tPrel = myText("CMS Preliminary",0.17,0.88,1.04)
    tLumi = myText("#sqrt{s} =  %s, L = %s fb^{-1}"%(anaTag,(float(lumi_data)/1000.)),0.17,0.83)

    unten.cd()
    ROOT.gPad.SetTicks(1,1)

    ratio, error, ksScore, chiScore = getRatio(d1,allMC,xMin[v],xMax[v])
    ksScore = allMC.KolmogorovTest( d1 )
    chiScore = allMC.Chi2Test( d1 , "UWCHI2/NDF")
    print ksScore
    print chiScore
    ratio.SetStats(0)
    ratio.GetYaxis().SetRangeUser(0,2)
    ratio.GetYaxis().SetNdivisions(502,0)
    ratio.GetXaxis().SetTitle(xAxis[v])
    ratioError = ROOT.TGraphErrors(error)
    ratioError.SetFillColor(ROOT.kGray+3)
    ratioError.SetFillStyle(3013)
    ratio.Draw("E1")
    ratioError.Draw('SAME2')
    ratio.Draw("E1SAME")
    ratio.SetTitle("")
    m_one_line = ROOT.TLine(xMin[v],1,xMax[v],1)
    m_one_line.SetLineStyle(7)
    m_one_line.SetLineColor(4)
    m_one_line.Draw("Same")

    tKsChi = myText("#chi_{#nu}^{2} = %.3f K_{s} = %.3f"%(chiScore,ksScore),0.17,0.9,1.5)

    name = '%s/%s' %(config.get('Directories','plotpath'),options[v][6])
    c.Print(name)

    os.system('rm %s/tmp_plotCache_%s*'%(config.get('Directories','plotpath'),region))
    print 'i am done!\n'

sys.exit(0)
