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
parser.add_option("-S", "--subtructed", dest="sub", default="False",
                      help="subtruction plot")
parser.add_option("-L", "--rescale", dest="rescale", default="False",
                      help="rescale by 1/max_weight")

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
        for i in range(7,9):
            if 'VH' in histo.GetName():
                s+=histo.GetBinContent(i)
            else:
                b+=histo.GetBinContent(i)
    return s/b

def get_s_over_sb(fName):
    #using bin 9, 10, 11
    s=0
    b=0
    histos = get_th1(fName)
    for histo in histos:
        if 'data' in histo.GetName(): continue
        for i in range(7,9):
            if 'VH' in histo.GetName():
                s+=histo.GetBinContent(i)
            else:
                b+=histo.GetBinContent(i)
    return s/(s+b)


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


    fileList = []

    #MedPt
    fileList += [ '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZmmMedPt_PostFit_s.root',
                 '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZeeMedPt_PostFit_s.root',
                 '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Znn_MedPt_ZnunuMedPt_8TeV_PostFit_s.root',
                 '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wln_ch2_Wmunu2_PostFit_s.root']
    #LowPt    
    fileList += [ '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Znn_LowPt_ZnunuLowPt_8TeV_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZmmLowPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZeeLowPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wln_ch1_Wenu_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wln_ch2_Wmunu_PostFit_s.root']
    #highPt    
    fileList += [ '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wln_ch1_WenuHighPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZeeHighPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Znn_HighPt_ZnunuHighPt_8TeV_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wln_ch2_WmunuHighPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Zll_ZmmHighPt_PostFit_s.root',
                  '/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_v0.1/MJJ_Wtn_Wtn_PostFit_s.root']
        
    # 7tev
    fileList += ['ZeeLowPt_7TeV.root','ZmmLowPt_7TeV.root','WmnLowPt_7TeV.root','ZnnLowPt_7TeV.root']
    fileList += ['ZeeHighPt_7TeV.root','ZmmHighPt_7TeV.root','WmnHighPt_7TeV.root','ZnnHighPt_7TeV.root']


    histosL = []

    max_sb = 0
    max_ssb = 0
    for file in fileList:
        if max_sb < get_s_over_b(file):
            max_sb = get_s_over_b(file)
        if max_ssb < get_s_over_sb(file):
            max_ssb = get_s_over_sb(file)
                        
    print max_ssb
    print max_sb

    for file in fileList:
        print file
        print get_s_over_b(file)
        if eval(opts.rescale) == False:
                max_sb = 1.
                max_ssb = 1.
        for th1 in get_th1(file):
            th1.Sumw2()
            if 's/b' in opts.fom:
                th1.Scale(get_s_over_b(file)/max_sb)
            elif 's/s+b' in opts.fom:
                th1.Scale(get_s_over_sb(file)/max_ssb)
            if 'VV' in th1.GetName():
                    th1.SetName('VV')
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

    appendix = ''
    if(eval(opts.rescale) == True):
            appendix = '_rescaled_'
    
    if 's/s+b' in opts.fom:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined78tev_postFit_s_over_sb'+appendix+'.pdf')
    elif 's/b' in opts.fom:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined78tev_postFit_s_over_b'+appendix+'.pdf')
    else:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_unweighted.pdf')            
    
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_highPt_7tev.pdf')
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined_postFit_s_over_b_Hpt_weight_1.pdf'
    stack.lumi = 19040
 
    
    mjj_sub = eval(opts.sub)

    if mjj_sub == False:
            stack.doPlot()
    elif mjj_sub == True:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_subtracted.pdf')
            stack.doSubPlot(['VH','VV'])
    print 'i am done!\n'


plot()
sys.exit(0)    





