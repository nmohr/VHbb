#!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import os
import ROOT


files = [ 'vhbb_TH_BDT_M125_ZeeLowPt_8TeV.root' ]
histos=[ 'TT','ZjLF','ZjHF', 'VV','VH','s_Top' ]

def dc_tex_converter(rootFile):
    infile = ROOT.TFile(rootFile,"READ")
    print infile.GetName()
    for histo in histos:
       th1 = infile.Get(histo)
       error = ROOT.Double()
       integral = th1.IntegralAndError(0,1000,error)
       print th1.GetName() + '  ' + '%.2f' %(integral) + ' \pm ' + '%.2f' %(error)



if __name__ == "__main__":
    dc_tex_converter(files[0])
