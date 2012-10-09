#!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import os,sys
import ROOT
from optparse import OptionParser

argv = sys.argv
parser = OptionParser()
parser.add_option("-F", "--file", dest="file", default="",
                      help="File with TH to create the .row from, must contain M125, eg vhbb_TH_BDT_M125_ZeeLowPt_8TeV.root")
(opts, args) = parser.parse_args(argv)
files = opts.file
histos=[ 'TT','ZjLF','ZjHF', 'VV','s_Top' ]
masses = [110,115,120,125,130,135]
dictNr = {'QCD': '--','WjHF': '--','WjLF': '--','WH110':'--','WH115':'--','WH120':'--','WH125':'--','WH130':'--','WH135':'--'}

def dc_tex_converter(rootFile):
    def getNr(th1):
        error = ROOT.Double()
        integral = th1.IntegralAndError(0,1000,error)
        return integral,error
    if 'Zee' in rootFile: dictNr['mode'] = 'ZeeH'
    if 'Zmm' in rootFile: dictNr['mode'] = 'ZmmH'

    for mass in masses:
        infile = ROOT.TFile(rootFile.replace('M125','M%.0f'%mass),"READ")
        th1 = infile.Get('VH')
        integral,error = getNr(th1)
        dictNr['ZH%.0f'%mass] = '  ' + '$%.2f' %(integral) + ' \pm ' + '%.2f$' %(error)
        
    infile = ROOT.TFile(rootFile,"READ")
    for histo in histos:
        th1 = infile.Get(histo)
        integral,error = getNr(th1)
        dictNr[histo] = '  ' + '$%.2f' %(integral) + ' \pm ' + '%.2f$' %(error)

    theString = '$\\%(mode)s$ & %(ZjLF)s & %(ZjHF)s & %(WjLF)s & %(WjLF)s & %(TT)s & %(s_Top)s & %(VV)s & %(ZH110)s & %(WH110)s & %(ZH115)s & %(WH115)s & %(ZH120)s & %(WH120)s & %(ZH125)s & %(WH125)s & %(ZH130)s & %(WH130)s & %(ZH135)s & %(WH135)s \\\\'%dictNr
    outname = rootFile.replace('.root','.row')
    f = open(outname,'w')
    f.write(theString)
    print outname 
    f.close()

if __name__ == "__main__":
    dc_tex_converter(files)
