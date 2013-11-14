import ROOT
from copy import copy

class Rebinner:
    def __init__(self,nBins,lowedgearray,active=True):
        self.lowedgearray=lowedgearray
        self.nBins=nBins
        self.active=active
    def rebin(self, histo):
        if not self.active: return histo
        #print 'rebinning'
        #print histo.Integral()
        ROOT.gDirectory.Delete('hnew')
        histo.Rebin(self.nBins,'hnew',self.lowedgearray)
        binhisto=ROOT.gDirectory.Get('hnew')
        #print binhisto.Integral()
        newhisto=ROOT.TH1F('new','new',self.nBins,self.lowedgearray[0],self.lowedgearray[-1])
        newhisto.Sumw2()
        for bin in range(1,self.nBins+1):
            newhisto.SetBinContent(bin,binhisto.GetBinContent(bin))
            newhisto.SetBinError(bin,binhisto.GetBinError(bin))
        newhisto.SetName(binhisto.GetName())
        newhisto.SetTitle(binhisto.GetTitle())
        #print newhisto.Integral()
        return copy(newhisto)

    @staticmethod
    def calculate_binning(hDummyRB,max_rel):
        ErrorR=0
        ErrorL=0
        TotR=0
        TotL=0
        binR=nBinsRB
        binL=1
        rel=1.0
        #---- from right
        while rel > max_rel:
            TotR+=hDummyRB.GetBinContent(binR)
            ErrorR=sqrt(ErrorR**2+hDummyRB.GetBinError(binR)**2)
            binR-=1
            if not TotR == 0 and not ErrorR == 0:
                rel=ErrorR/TotR
                #print rel
        #print 'upper bin is %s'%binR

        #---- from left
        rel=1.0
        while rel > max_rel:
            TotL+=hDummyRB.GetBinContent(binL)
            ErrorL=sqrt(ErrorL**2+hDummyRB.GetBinError(binL)**2)
            binL+=1
            if not TotL == 0 and not ErrorL == 0:
                rel=ErrorL/TotL
                #print rel
        #it's the lower edge
        binL+=1
        #print 'lower bin is %s'%binL

        inbetween=binR-binL
        stepsize=int(inbetween)/(int(nBins)-2)
        modulo = int(inbetween)%(int(nBins)-2)

        #print'stepsize %s'% stepsize
        #print 'modulo %s'%modulo

        binlist=[binL]
        for i in range(0,int(nBins)-3):
            binlist.append(binlist[-1]+stepsize)
        binlist[-1]+=modulo
        binlist.append(binR)
        binlist.append(nBinsRB+1)
        return binlist

