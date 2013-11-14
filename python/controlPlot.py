#!/usr/bin/env python
import pickle
import ROOT 
from array import array
import sys, os
from optparse import OptionParser
from copy import copy,deepcopy
from math import sqrt, log10
ROOT.gROOT.SetBatch(True)
from myutils import TdrStyles

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-R", "--region", dest="region", default="",
                      help="region to plot")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
parser.add_option("-F", "--format", dest="format", default="pdf",
                      help="outut format for the plot: pdf, root, png, C, jpg, etc.")

(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
        
from myutils import BetterConfigParser, printc, ParseInfo, mvainfo, StackMaker, HistoMaker

print opts.config
opts.config.append('8TeVconfig/vhbbPlotDef.ini')
config = BetterConfigParser()
config.read(opts.config)
TdrStyles.tdrStyle()


def get_th1(fName):
    infile = ROOT.TFile.Open(fName,'read')
    th1 = []
    for key in ROOT.gDirectory.GetListOfKeys():
        infile.cd()
        th1.append(key.ReadObj())
    return th1



def plot(file,var,region):
    signalRegion = False

    stack = StackMaker(config,var,region,signalRegion)

    histosL = []
    overlayL = []


    print file
    datas = []
    datasL = []
    for th1 in get_th1(file):
        print th1.GetBinLowEdge(0)
        if 'VH' in th1.GetName(): 
            overlayL.append(th1)
            th1.SetLineWidth(1)
        if 'data_obs' in th1.GetName():
            datasL.append(th1)
        else:
            histosL.append(th1)

    print 'histoL'
    print histosL
    typs = []
    typsL = []

    overlay_typs=[]

    #append the name just once
    for histo in histosL:
        typsL.append(histo.GetName())
        print histo.GetName()
        if 'VH' in histo.GetName():
            overlay_typs.append(histo.GetName())

    print typsL
    print 'Overlay list'
    print overlayL

    overlay_histo_dict = HistoMaker.orderandadd([{overlay_typs[i]:overlayL[i]} for i in range(len(overlayL))],['VH','VV'])

    overlayL2=[]
    stack.histos = histosL
    stack.typs = typsL
    stack.datas = datasL
    stack.datanames=region
    for key in overlay_histo_dict:
         overlayL2.append(overlay_histo_dict[key])

    appendix = ''
    
    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_unweighted.'+opts.format)            
    
    stack.lumi = 18940

    stack.doPlot()
    print 'i am done!\n'



file = '/shome/nmohr/VHbb/lhcp/Control/ZnunuHighPt_WjHF_CSVmin.root'
region = 'WbbCSVZnn'
var = 'minCSVZnn'
plot(file,var,region)
file = '/shome/nmohr/VHbb/lhcp/Control/ZnunuHighPt_ZjHF_pfMET.root'
region = 'ZbbMETZnn'
var = 'METZnn'
plot(file,var,region)
file = '/shome/nmohr/VHbb/lhcp/Control/Wmnu-TTbar-ptjj-lin.root'
region = 'TTbarHptWmn'
var = 'HptWmn'
plot(file,var,region)
file = '/shome/nmohr/VHbb/lhcp/Control/ZnunuHighPt_WjHF_BDTregular.root'
region = 'WbbBDTZnn'
var = 'BDTZnn'
plot(file,var,region)
file = '/shome/nmohr/VHbb/lhcp/Control/ZnunuHighPt_ZjHF_BDTregular.root'
region = 'ZbbBDTZnn'
var = 'BDTZnn'
plot(file,var,region)
file = '/shome/nmohr/VHbb/lhcp/Control/WenuHighPt_Wudscg_BDT.root'
region = 'WudscgBDTWen'
var = 'BDTWen'
plot(file,var,region)
##########################
#### ____ main _____ #####
##########################
plot(file,var,region)

sys.exit(0)    





