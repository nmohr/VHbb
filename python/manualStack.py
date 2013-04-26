#!/usr/bin/env python
import pickle
import ROOT 
from array import array
import sys, os
from optparse import OptionParser
from copy import copy,deepcopy
from math import sqrt
ROOT.gROOT.SetBatch(True)

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-R", "--region", dest="region", default="",
                      help="region to plot")
parser.add_option("-M", "--figure_of_merit", dest="fom", default="",
                      help="figure of merit to be used to weight the plots. Possibilities: s/b, s/sqrt(b)")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
        
from myutils import BetterConfigParser, printc, ParseInfo, mvainfo, StackMaker, HistoMaker

print opts.config
opts.config.append('8TeVconfig/vhbbPlotDef.ini')
config = BetterConfigParser()
config.read(opts.config)

def get_s_over_b(fName):
    #using bin 9, 10, 11
    s=0
    b=0
    histos = get_th1(fName)
    for histo in histos:
        if 'data' in histo.GetName(): continue
        for i in range(9,11):
            if 'VH' in histo.GetName():
                s+=histo.GetBinContent(i)
            else:
                b+=histo.GetBinContent(i)
    return s/b

def get_th1(fName):
    infile = ROOT.TFile.Open(fName,'read')
    th1 = []
    for key in ROOT.gDirectory.GetListOfKeys():
        infile.cd()
        th1.append(key.ReadObj())
    return th1

def plot():
    signalRegion = True
    region = 'plot'
    var = 'Hmass'

    stack = StackMaker(config,var,region,signalRegion)

#     fileList = [
#         '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch1_Wenu3_PreFit.root',
#         '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeHighPt_PreFit.root',
#         '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_HighPt_ZnunuHighPt_8TeV_PreFit.root',
#         '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_Wmunu3_PreFit.root',
#         '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmHighPt_PreFit.root']


    fileList = [
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmMedPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeMedPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_MedPt_ZnunuMedPt_8TeV_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_Wmunu2_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_LowPt_ZnunuLowPt_8TeV_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmLowPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeLowPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch1_Wenu_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_Wmunu_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch1_WenuHighPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeHighPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_HighPt_ZnunuHighPt_8TeV_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_WmunuHighPt_PostFit_s.root',
        '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmHighPt_PostFit_s.root']


# #tau
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wtn_Wtn_PostFit_s.root


# #Med
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmMedPt_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeMedPt_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_MedPt_ZnunuMedPt_8TeV_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_Wmunu2_PostFit_s.root

# #Low

# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Znn_LowPt_ZnunuLowPt_8TeV_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZmmLowPt_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Zll_ZeeLowPt_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch1_Wenu_PostFit_s.root
# /shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit/MJJ_Wln_ch2_Wmunu_PostFit_s.root

    fileList += ['ZeeLowPt_7TeV.root','ZmmLowPt_7TeV.root','WmnLowPt_7TeV.root','ZnnLowPt_7TeV.root']
    fileList += ['ZeeHighPt_7TeV.root','ZmmHighPt_7TeV.root','WmnHighPt_7TeV.root','ZnnHighPt_7TeV.root']

    histosL = []
    for file in fileList:
        print file
        print get_s_over_b(file)
        for th1 in get_th1(file):
            if opts.fom == 's/b':
                th1.Scale(10*get_s_over_b(file))
            histosL.append(th1)

    print 'histoL'
    print histosL
    typs = []
    typsL = []
    datas = []
    datasL = []

    #append the name just once
    for histo in histosL:
        typsL.append(histo.GetName())
        if 'data' in histo.GetName():
            datasL.append(histo)    

    #datasL.append(datas)
    #typsL.append(typs)
    print typsL
        
    stack.histos = histosL
    stack.typs = typsL
    stack.datas = datasL
#    stack.datatyps = Ldatatyps[v]
    stack.datanames='data_obs'
    #if signalRegion:
    #    stack.overlay = ['VH','VVHF','VVLF']
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_preFit.pdf')
    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined78tev_postFit_s_over_b.C')
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_highPt_7tev.pdf')
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined_postFit_s_over_b_Hpt_weight_1.pdf')
    stack.lumi = 19040
    stack.doPlot()
    
    print 'i am done!\n'


plot()
sys.exit(0)    





