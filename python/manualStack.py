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
parser.add_option("-M", "--figure_of_merit", dest="fom", default="",
                      help="figure of merit to be used to weight the plots. Possibilities: s/b, s/sqrt(b)")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
parser.add_option("-S", "--subtracted", dest="sub", default="False",
                      help="subtracted plot")
parser.add_option("-L", "--rescale", dest="rescale", default="True",
                      help="rescale by 1/max_weight")
parser.add_option("-T", "--type", dest="type", default="mjj",
                      help="type of plot you want to make: mjj, log10")
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


def get_s_or_b(fName,binmin,binmax,sb):
    s=0
    b=0
    if isinstance(fName,str):
            histos = get_th1(fName)
    else:
            histos = [fName]
    for histo in histos:
        if 'data' in histo.GetName(): continue
        for i in range(binmin,binmax+1):
            if 'VH' in histo.GetName():
                s+=histo.GetBinContent(i)
            else:
                b+=histo.GetBinContent(i)
    if 's' in sb:
        return s
    else:
        return b

def get_s_over_b(fName,binmin,binmax):
    s = get_s_or_b(fName,binmin,binmax,'s')
    b = get_s_or_b(fName,binmin,binmax,'b')
    return s/b

def get_s_over_sb(fName,binmin,binmax):
    s = get_s_or_b(fName,binmin,binmax,'s')
    b = get_s_or_b(fName,binmin,binmax,'b')
    return s/(s+b)

def get_th1(fName):
    infile = ROOT.TFile.Open(fName,'read')
    th1 = []
    for key in ROOT.gDirectory.GetListOfKeys():
        infile.cd()
        th1.append(key.ReadObj())
    return th1


def log_s_over_b(fileList):
    #--------------
    # log s  over b
    #--------------

    histosL={}
    s_b_d_histos = {}
    for file in fileList:
        print file
        name = '%s' %file
        histosL[name] = []
        for th1 in get_th1(file):
            #th1.Sumw2()
            if 'VVLF' in th1.GetName():
                    th1.SetName('VV')
            if 'Zj1b' in th1.GetName():
                    th1.SetName('Zj2b')
            if 'Wj1b' in th1.GetName():
                    th1.SetName('Wj2b')
            histosL[name].append(th1)
        i = 0
        for hist in histosL[name]:
            if 'VH' in hist.GetName() and not 'VVHF' in hist.GetName():
                hSignal = hist.Clone()
            elif 'data_obs' in hist.GetName():
                hData = hist.Clone()
            else:
                if i == 0:
                    hBkg = hist.Clone()
                else:
                    hBkg.Add(hist)
                i += 1
        s_b_d_histos[name] = {'b': hBkg, 's': hSignal, 'd': hData}


    bmin=-4
    bmax=0
    nbins=16

    log_s_over_b_b = ROOT.TH1F("log_s_over_b_b","log_s_over_b_b",nbins,bmin,bmax)
    log_s_over_b_b.SetFillColor(4)
    log_s_over_b_b.GetXaxis().SetTitle("log(S/B)")
    log_s_over_b_b.GetYaxis().SetTitle("Events")
    log_s_over_b_s = ROOT.TH1F("log_s_over_b_s","log_s_over_b_s",nbins,bmin,bmax)
    log_s_over_b_s.SetFillColor(2)
    log_s_over_b_d = ROOT.TH1F("log_s_over_b_d","log_s_over_b_d",nbins,bmin,bmax)
    log_s_over_b = ROOT.THStack("log_s_over_b","log_s_over_b")

    stack_log_s_over_b = ROOT.THStack("stack_log_s_over_b","stack_log_s_over_b")

    for key, s_b_d in s_b_d_histos.iteritems():
        for bin in range(0,s_b_d['b'].GetNbinsX()+1):
            s = s_b_d['s'].GetBinContent(bin)
            b = s_b_d['b'].GetBinContent(bin)
            d = s_b_d['d'].GetBinContent(bin)
            sErr = s_b_d['s'].GetBinError(bin)
            bErr = s_b_d['b'].GetBinError(bin)
            dErr = s_b_d['d'].GetBinError(bin)
            logsb = -3.9
            if b > 0. and s > 0.:
                logsb = log10(s/b)
            elif s > 0.:
                logsb = -0.
            #print logsb
            newBin = log_s_over_b_b.FindBin(logsb) 
            log_s_over_b_b.SetBinContent(newBin, b+log_s_over_b_b.GetBinContent(newBin))
            log_s_over_b_s.SetBinContent(newBin, s+log_s_over_b_s.GetBinContent(newBin))
            log_s_over_b_d.SetBinContent(newBin, d+log_s_over_b_d.GetBinContent(newBin))
            log_s_over_b_b.SetBinError(newBin, sqrt(bErr*bErr+log_s_over_b_b.GetBinError(newBin)*log_s_over_b_b.GetBinError(newBin)))
            log_s_over_b_s.SetBinError(newBin, sqrt(sErr*sErr+log_s_over_b_s.GetBinError(newBin)*log_s_over_b_s.GetBinError(newBin)))
            log_s_over_b_d.SetBinError(newBin, sqrt(dErr*dErr+log_s_over_b_d.GetBinError(newBin)*log_s_over_b_d.GetBinError(newBin)))

    stack = StackMaker(config,'logSB','plot1',False)
    stack.setup = ['VH','BKG']
    stack.typs = ['VH','BKG']
    stack.lumi = 19000.
    stack.histos = [log_s_over_b_s,log_s_over_b_b]
    stack.datas = [log_s_over_b_d]
    stack.datanames='data_obs'
    stack.overlay = log_s_over_b_s
    stack.doPlot()


def plot(fileList):
    signalRegion = True
    region = 'plot'
    var = 'Hmass'

    stack = StackMaker(config,var,region,signalRegion)

    histosL = []
    overlayL = []

    #7-9 for the higgs
    #5-6 for the VV
    binmin=7
    binmax=9
    
    max_sb = 0
    max_ssb = 0
    for file in fileList:
        if max_sb < get_s_over_b(file,binmin,binmax):
            max_sb = get_s_over_b(file,binmin,binmax)
        if max_ssb < get_s_over_sb(file,binmin,binmax):
            max_ssb = get_s_over_sb(file,binmin,binmax)
                        
    print max_ssb
    print max_sb

    for file in fileList:
        print file
        print get_s_over_b(file,binmin,binmax)
        if eval(opts.rescale) == False:
                max_sb = 1.
                max_ssb = 1.
        for th1 in get_th1(file):
            #th1.Sumw2()
            if 's/b' in opts.fom:
                th1.Scale(get_s_over_b(file,binmin,binmax)/max_sb)
            if 's/s+b' in opts.fom:
                th1.Scale(get_s_over_sb(file,binmin,binmax)/max_ssb)
            if 'VV' in th1.GetName():
                    th1.SetName('VV')
            if 'Zj1b' in th1.GetName():
                    th1.SetName('Zj2b')
            if 'Wj1b' in th1.GetName():
                    th1.SetName('Wj2b')
            # new stack for the overlay plot
            if 'VH' in th1.GetName() or 'VV' in th1.GetName():
                    overlayL.append(th1)
            histosL.append(th1)

    print 'histoL'
    print histosL
    typs = []
    typsL = []
    datas = []
    datasL = []

    overlay_typs=[]

    #append the name just once
    for histo in histosL:
        typsL.append(histo.GetName())
        if 'data' in histo.GetName():
            datasL.append(histo)
        if 'VH' in histo.GetName() or 'VV' in histo.GetName():
            overlay_typs.append(histo.GetName())

    #datasL.append(datas)
    #typsL.append(typs)
    print typsL
    print 'Overlay list'
    print overlayL

    overlay_histo_dict = HistoMaker.orderandadd([{overlay_typs[i]:overlayL[i]} for i in range(len(overlayL))],['VH','VV'])

    overlayL2=[]
    stack.histos = histosL
    stack.typs = typsL
    stack.datas = datasL
#    stack.datatyps = Ldatatyps[v]
    stack.datanames='data_obs'
    for key in overlay_histo_dict:
         overlayL2.append(overlay_histo_dict[key])

    mjj_sub = eval(opts.sub)
    if not mjj_sub:
         stack.overlay = overlayL2
         
    appendix = ''
    if(eval(opts.rescale) == True):
            appendix = '_rescaled_'
    
    if 's/s+b' in opts.fom:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined78tev_postFit_s_over_sb'+appendix+'.'+opts.format)
    elif 's/b' in opts.fom:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined78tev_postFit_s_over_b'+appendix+'.'+opts.format)
    else:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_unweighted.'+opts.format)            
    
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_highPt_7tev.pdf')
#    stack.options['pdfName'] = stack.options['pdfName'].replace('.pdf','_combined_postFit_s_over_b_Hpt_weight_1.pdf'
    stack.lumi = 19040

    if mjj_sub == False:
            stack.doPlot()
    elif mjj_sub == True:
            stack.options['pdfName'] = stack.options['pdfName'].replace('.'+opts.format,'_subtracted.'+opts.format)
            stack.doSubPlot(['VH','VV'])
    print 'i am done!\n'





##########################
#### ____ main _____ #####
##########################
fileList = []
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


bdt_fileList = []
# 7tev
#bdt_fileList += ['ZeeLowPt_7TeV.root','ZmmLowPt_7TeV.root','WmnLowPt_7TeV.root','ZnnLowPt_7TeV.root']
#bdt_fileList += ['ZeeHighPt_7TeV.root','ZmmHighPt_7TeV.root','WmnHighPt_7TeV.root','ZnnHighPt_7TeV.root']

bdt_fileList+=[
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch1_Wenu2_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch1_Wenu3_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch1_Wenu_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch2_Wmunu2_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch2_Wmunu3_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wln_ch2_Wmunu_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Wtn_Wtn_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Zll_ZeeHighPt_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Zll_ZeeLowPt_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Zll_ZmmHighPt_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Zll_ZmmLowPt_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Znn_HighPt_ZnunuHighPt_8TeV_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Znn_LowPt_ZnunuLowPt_8TeV_PostFit_s.root',
		'/shome/bortigno/VHbbAnalysis/postPreApp//LHCP_PostFit_BDT_v0.0/BDT_Znn_MedPt_ZnunuMedPt_8TeV_PostFit_s.root',
		]
bdt_fileList_7TeV=[
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Wln_VH_7TeV_Wln_7TeV_ch1_Wenu2_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Wln_VH_7TeV_Wln_7TeV_ch1_Wenu_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Wln_VH_7TeV_Wln_7TeV_ch2_Wmunu2_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Wln_VH_7TeV_Wln_7TeV_ch2_Wmunu_PostFit_s.root',
         '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Zll_VH_7TeV_Zll_7TeV_card1_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Zll_VH_7TeV_Zll_7TeV_card2_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Zll_VH_7TeV_Zll_7TeV_card3_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Zll_VH_7TeV_Zll_7TeV_card4_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Znn_VH_7TeV_Znn_7TeV_ch1_PostFit_s.root',
        '/shome/bortigno//VHbbAnalysis/postPreApp/stack_from_dc_7TeV/BDT_Znn_VH_7TeV_Znn_7TeV_ch2_PostFit_s.root'
         ]

bdt_fileList+=bdt_fileList_7TeV

bdt_fileList1 = []
bdt_fileList1+=[
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch1_Wenu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch1_Wenu3_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch1_Wenu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch2_Wmunu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch2_Wmunu3_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wln_VV_ch2_Wmunu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Wtn_VV_Wtn_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Zll_VV_ZeeHighPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Zll_VV_ZeeLowPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Zll_VV_ZmmHighPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Zll_VV_ZmmLowPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Znn_VV_HighPt_ZnunuHighPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Znn_VV_LowPt_ZnunuLowPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDTVV/BDT_Znn_VV_MedPt_ZnunuMedPt_PostFit_s.root'
]
bdt_fileList2 = []
bdt_fileList2+=[
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch1_Wenu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch1_Wenu3_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch1_Wenu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch2_Wmunu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch2_Wmunu3_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wln_ch2_Wmunu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Wtn_Wtn_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Zll_ZeeHighPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Zll_ZeeLowPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Zll_ZmmHighPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Zll_ZmmLowPt_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Znn_HighPt_ZnunuHighPt_8TeV_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Znn_LowPt_ZnunuLowPt_8TeV_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/mBDT/BDT_Znn_MedPt_ZnunuMedPt_8TeV_PostFit_s.root'
]

bdt_fix = [
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Wln_ch1_Wenu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Wln_ch1_Wenu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Wln_ch2_Wmunu2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Wln_ch2_Wmunu_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Zll_card1_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Zll_card2_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Zll_card3_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Zll_card4_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Znn_ch1_PostFit_s.root',
'/shome/nmohr/VHbb/lhcp/PrePost/BDT7TeV/BDT_Znn_ch2_PostFit_s.root' ]

bdt_fileList2+=bdt_fix



if('mjj' in opts.type):
        plot(fileList)
else:
        log_s_over_b(bdt_fileList2)

sys.exit(0)    





