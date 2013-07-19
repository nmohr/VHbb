import os, subprocess

def runPlot(opts):
    command = './stack_from_dc.py -D %(dc)s -B %(bin)s -C %(config)s -V %(var)s' %(opts)
    print command
    subprocess.call([command], shell=True)
    command = './stack_from_dc.py -D %(dc)s -B %(bin)s -C %(config)s -V %(var)s -M %(mlfit)s' %opts
    print command
    subprocess.call([command], shell=True)


def runAll():
    path = '/shome/nmohr/VHbb/lhcp/DCs/VVBDTs/mBDT/'
    configuration = '8TeVconfig/configPlotVVmBDT'
    #path = '/shome/nmohr/VHbb/lhcp/DCs/VVBDTs/BDT/'
    #configuration = '8TeVconfig/configPlotVVBDT'
    modes = ['Wln','Wtn','Znn','Zll']
    cards = {'Wln': 'combined_vhbb_DC_BDT_VV_8TeV.txt', 'Wtn': 'Wtn_BDT_newBinning_125_UsingVVasSignal.txt', 'Znn': 'vhbb_Znn_J12_combo_bbb_8TeV.txt', 'Zll': 'vhbb_DC_BDT_ZZbb_Zll_8TeV.txt'}
    bins = {'Wln': [['ch1_Wenu','BDT_Wln_VV'],['ch1_Wenu2','BDT_Wln_VV'],['ch1_Wenu3','BDT_Wln_VV'],['ch2_Wmunu','BDT_Wln_VV'],['ch2_Wmunu2','BDT_Wln_VV'],['ch2_Wmunu3','BDT_Wln_VV']],'Wtn': [['Wtn','BDT_Wtn_VV']], 'Znn':[['ZnunuLowPt','BDT_Znn_VV_LowPt'],['ZnunuMedPt','BDT_Znn_VV_MedPt'], ['ZnunuHighPt','BDT_Znn_VV_HighPt']], 'Zll': [['ZmmLowPt','BDT_Zll_VV'],['ZmmHighPt','BDT_Zll_VV'],['ZeeLowPt','BDT_Zll_VV'],['ZeeHighPt','BDT_Zll_VV']]}
    
    
    ####mBDT VH#########
    path = '/shome/nmohr/VHbb/lhcp/DCs/Unblinding/Combo/mBDT/125/'
    #path = '/shome/nmohr/VHbb/lhcp/DCs/Unblinding/Combo/Fix7TeV'
    configuration = '8TeVconfig/configPlotmBDT'
    #path = '/shome/nmohr/VHbb/lhcp/DCs/Unblinding/Combo/BDT/125/'
    #configuration = '8TeVconfig/configPlotBDT'
    #FOr VH
    cards = {'Wln': 'vhbb_Wln_8TeV.txt', 'Wtn': 'vhbb_Wtn_8TeV.txt', 'Znn': 'vhbb_Znn_8TeV.txt', 'Zll': 'vhbb_Zll_8TeV.txt'}
    bins = {'Wln': [['ch1_Wenu','BDT_Wln'],['ch1_Wenu2','BDT_Wln'],['ch1_Wenu3','BDT_Wln'],['ch1_Wenu3','BDT_Wln_Last'],['ch2_Wmunu','BDT_Wln'],['ch2_Wmunu2','BDT_Wln'],['ch2_Wmunu3','BDT_Wln'],['ch2_Wmunu3','BDT_Wln_Last']],'Wtn': [['Wtn','BDT_Wtn']], 'Znn':[['ZnunuLowPt_8TeV','BDT_Znn_LowPt'],['ZnunuMedPt_8TeV','BDT_Znn_MedPt'], ['ZnunuHighPt_8TeV','BDT_Znn_HighPt'], ['ZnunuHighPt_8TeV','BDT_Znn_HighPt_Last']], 'Zll': [['ZmmLowPt','BDT_Zll'],['ZmmHighPt','BDT_Zll'],['ZeeLowPt','BDT_Zll'],['ZeeHighPt','BDT_Zll']]}
    ####MJJ VH#########
    #path = '/shome/nmohr/VHbb/lhcp/DCs/Unblinding/Combo/MJJ/125/'
    #configuration = '8TeVconfig/configPlotMJJ'
    #bins = {'Wln': [['ch1_Wenu','MJJ_Wln'],['ch1_Wenu3','MJJ_Wln'],['ch2_Wmunu','MJJ_Wln'],['ch2_Wmunu2','MJJ_Wln'],['ch2_Wmunu3','MJJ_Wln']],'Wtn': [['Wtn','MJJ_Wtn']], 'Znn':[['ZnunuLowPt_8TeV','MJJ_Znn_LowPt'],['ZnunuMedPt_8TeV','MJJ_Znn_MedPt'], ['ZnunuHighPt_8TeV','MJJ_Znn_HighPt']], 'Zll': [['ZmmLowPt','MJJ_Zll'],['ZmmMedPt','MJJ_Zll'],['ZmmHighPt','MJJ_Zll'],['ZeeLowPt','MJJ_Zll'],['ZeeMedPt','MJJ_Zll'],['ZeeHighPt','MJJ_Zll']]}

    ####7TeV#########
    #path = '/shome/nmohr/VHbb/lhcp/DCs/Unblinding/Combo/Fix7TeV/'
    #configuration = '8TeVconfig/configPlot7TeV'
    #modes = ['Wln','Znn','Zll']
    #modes = ['Wln']
    #cards = {'Wln': 'vhbb_Wln_7TeV.txt', 'Znn': 'vhbb_Znn_7TeV.txt', 'Zll': 'vhbb_Zll_7TeV.txt'}
    #bins = {'Wln': [['ch1_Wenu','BDT_Wln'],['ch1_Wenu2','BDT_Wln'],['ch2_Wmunu','BDT_Wln'],['ch2_Wmunu2','BDT_Wln']], 'Znn':[['ch1','BDT_Znn'], ['ch2','BDT_Znn']], 'Zll': [['card1','BDT_Zll'],['card2','BDT_Zll'],['card3','BDT_Zll'],['card4','BDT_Zll']]}
    for mode in modes:
        for bin in bins[mode]:
            opts = {}
            opts['bin'] = bin[0]
            opts['var'] = bin[1]
            opts['config'] = '%s' %configuration
            opts['dc'] = '%s%s' %(path,cards[mode])
            opts['mlfit'] = '%s/mlfit.root' %(path)
            runPlot(opts)

runAll()
