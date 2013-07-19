import ROOT 
ROOT.gROOT.SetBatch(True)
import sys,os
from BetterConfigParser import BetterConfigParser
import TdrStyles
from Ratio import getRatio
from HistoMaker import HistoMaker

class StackMaker:
    def __init__(self, config, var,region,SignalRegion,setup=None):
        section='Plot:%s'%region
        self.var = var
        self.SignalRegion=SignalRegion
        self.region = region
        self.normalize = eval(config.get(section,'Normalize'))
        self.log = eval(config.get(section,'log'))
        if config.has_option('plotDef:%s'%var,'log') and not self.log:
            self.log = eval(config.get('plotDef:%s'%var,'log'))
        self.blind = eval(config.get(section,'blind'))
        if setup is None:
            self.setup=config.get('Plot_general','setup')
            if self.log:
                self.setup=config.get('Plot_general','setupLog')
            self.setup=self.setup.split(',')
        else:
            self.setup=setup
        if not SignalRegion: 
            if 'ZH' in self.setup:
                self.setup.remove('ZH')
            if 'WH' in self.setup:
                self.setup.remove('WH')
        self.rebin = 1
        if config.has_option(section,'rebin'):
            self.rebin = eval(config.get(section,'rebin'))
        if config.has_option(section,'nBins'):
            self.nBins = int(eval(config.get(section,'nBins'))/self.rebin)
        else:
            self.nBins = int(eval(config.get('plotDef:%s'%var,'nBins'))/self.rebin)
        print self.nBins
        if config.has_option(section,'min'):
            self.xMin = eval(config.get(section,'min'))
        else:
            self.xMin = eval(config.get('plotDef:%s'%var,'min'))
        if config.has_option(section,'max'):
            self.xMax = eval(config.get(section,'max'))
        else:
            self.xMax = eval(config.get('plotDef:%s'%var,'max'))
        self.name = config.get('plotDef:%s'%var,'relPath')
        self.mass = config.get(section,'Signal')
        data = config.get(section,'Datas')
        if '<mass>' in self.name:
            self.name = self.name.replace('<mass>',self.mass)
            print self.name
        if config.has_option('Cuts',region):
            cut = config.get('Cuts',region)
        else:
            cut = None
        if config.has_option(section, 'Datacut'):
            cut=config.get(section, 'Datacut')
        if config.has_option(section, 'doFit'):
            self.doFit=eval(config.get(section, 'doFit'))
        else:
            self.doFit = False

        self.colorDict=eval(config.get('Plot_general','colorDict'))
        self.typLegendDict=eval(config.get('Plot_general','typLegendDict'))
        self.anaTag = config.get("Analysis","tag")
        self.xAxis = config.get('plotDef:%s'%var,'xAxis')
        self.options = {'var': self.name,'name':'','xAxis': self.xAxis, 'nBins': self.nBins, 'xMin': self.xMin, 'xMax': self.xMax,'pdfName': '%s_%s_%s.pdf'%(region,var,self.mass),'cut':cut,'mass': self.mass, 'data': data, 'blind': self.blind}
        if config.has_option('Weights','weightF'):
            self.options['weight'] = config.get('Weights','weightF')
        else:
            self.options['weight'] = None
        self.plotDir = config.get('Directories','plotpath')
        self.maxRatioUncert = 0.5
        if self.SignalRegion:
            self.maxRatioUncert = 1000.
        self.config = config
        self.datas = None
        self.datatyps = None
        self.overlay = None
        self.lumi = None
        self.histos = None
        self.typs = None
        self.AddErrors = None
        print self.setup

    @staticmethod
    def myText(txt="CMS Preliminary",ndcX=0,ndcY=0,size=0.8):
        ROOT.gPad.Update()
        text = ROOT.TLatex()
        text.SetNDC()
        text.SetTextColor(ROOT.kBlack)
        text.SetTextSize(text.GetTextSize()*size)
        text.DrawLatex(ndcX,ndcY,txt)
        return text

    def doCompPlot(self,aStack,l):
        c = ROOT.TCanvas(self.var+'Comp','',600,600)
        c.SetFillStyle(4000)
        c.SetFrameFillStyle(1000)
        c.SetFrameFillColor(0)
        k=len(self.histos)
        l.Clear()
        maximum = 0.
        for j in range(0,k):
            #print histos[j].GetBinContent(1)
            i=k-j-1
            self.histos[i].SetLineColor(int(self.colorDict[self.typs[i]]))
            self.histos[i].SetFillColor(0)
            self.histos[i].SetLineWidth(3)
            if self.histos[i].Integral() > 0.:
                self.histos[i].Scale(1./self.histos[i].Integral())
            if self.histos[i].GetMaximum() > maximum:
                maximum = self.histos[i].GetMaximum()
            l.AddEntry(self.histos[j],self.typLegendDict[self.typs[j]],'l')
        aStack.SetMinimum(0.)
        aStack.SetMaximum(maximum*1.5)
        aStack.GetXaxis().SetTitle(self.xAxis)
        aStack.Draw('HISTNOSTACK')
        if self.overlay:
            if self.overlay.Integral() > 0.:
                self.overlay.Scale(1./self.overlay.Integral())
            self.overlay.Draw('hist,same')
            l.AddEntry(self.overlay,self.typLegendDict['Overlay'],'L')
        l.Draw()
        name = '%s/comp_%s' %(self.plotDir,self.options['pdfName'])
        c.Print(name)

    def doPlot(self):
        TdrStyles.tdrStyle()
        histo_dict = HistoMaker.orderandadd([{self.typs[i]:self.histos[i]} for i in range(len(self.histos))],self.setup)
        #sort
        print histo_dict
        self.histos=[histo_dict[key] for key in self.setup]
        self.typs=self.setup
    
        c = ROOT.TCanvas(self.var,'', 600, 600)
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
        allStack = ROOT.THStack(self.var,'')     
        l = ROOT.TLegend(0.45, 0.6,0.75,0.92)
        l.SetLineWidth(2)
        l.SetBorderSize(0)
        l.SetFillColor(0)
        l.SetFillStyle(4000)
        l.SetTextFont(62)
        l.SetTextSize(0.035)
        l_2 = ROOT.TLegend(0.68, 0.6,0.92,0.92)
        l_2.SetLineWidth(2)
        l_2.SetBorderSize(0)
        l_2.SetFillColor(0)
        l_2.SetFillStyle(4000)
        l_2.SetTextFont(62)
        l_2.SetTextSize(0.035)
        MC_integral=0
        MC_entries=0

        for histo in self.histos:
            MC_integral+=histo.Integral()
        print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral

        #ORDER AND ADD TOGETHER

        if not 'DYc' in self.typs: self.typLegendDict.update({'DYlight':self.typLegendDict['DYlc']})
        print self.typLegendDict

        k=len(self.histos)
    
        for j in range(0,k):
            #print histos[j].GetBinContent(1)
            i=k-j-1
            self.histos[i].SetFillColor(int(self.colorDict[self.typs[i]]))
            self.histos[i].SetLineColor(1)
            allStack.Add(self.histos[i])

        d1 = ROOT.TH1F('noData','noData',self.nBins,self.xMin,self.xMax)
        datatitle='Data'
        addFlag = ''
        if 'Zee' in self.datanames and 'Zmm' in self.datanames:
	        addFlag = 'Z(l^{-}l^{+})H(b#bar{b})'
        elif 'Zee' in self.datanames:
	        addFlag = 'Z(e^{-}e^{+})H(b#bar{b})'
        elif 'Zmm' in self.datanames:
	        addFlag = 'Z(#mu^{-}#mu^{+})H(b#bar{b})'
        elif 'Znn' in self.datanames:
	        addFlag = 'Z(#nu#nu)H(b#bar{b})'
        elif 'Wmn' in self.datanames:
	        addFlag = 'W(#mu#nu)H(b#bar{b})'
        elif 'Wen' in self.datanames:
	        addFlag = 'W(e#nu)H(b#bar{b})'
        elif 'Wtn' in self.datanames:
	        addFlag = 'W(#tau#nu)H(b#bar{b})'
        addFlag2 = ''
        if 'TTbar' in self.region:
	        addFlag2 = 't#bar{t} enriched region'
        elif 'ZLight' in self.region:
	        addFlag2 = 'Z+udscg enriched region'
        elif 'Zbb' in self.region:
	        addFlag2 = 'Z+b#bar{b} enriched region'
        else:
            addFlag2 = 'pp #rightarrow VH; H #rightarrow b#bar{b}'

        for i in range(0,len(self.datas)):
            print self.datas[i]
            d1.Add(self.datas[i],1)
        print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
        flow = d1.GetEntries()-d1.Integral()
        if flow > 0:
            print "\033[1;31m\tU/O flow: %s\033[1;m"%flow

        if self.overlay and not isinstance(self.overlay,list):
            self.overlay = [self.overlay]
        if self.overlay:
            for _overlay in self.overlay:
                _overlay.SetLineColor(int(self.colorDict[_overlay.GetName()]))
                _overlay.SetLineWidth(2)
                _overlay.SetFillColor(0)
                _overlay.SetFillStyle(4000)

        numLegend = 2+k
        if self.overlay:
            numLegend += len(self.overlay)
        l.AddEntry(d1,datatitle,'P')
        for j in range(0,k):
            if j < numLegend/2.-1:
                l.AddEntry(self.histos[j],self.typLegendDict[self.typs[j]],'F')
            else:
                l_2.AddEntry(self.histos[j],self.typLegendDict[self.typs[j]],'F')
        if self.overlay:
            for _overlay in self.overlay:
                l_2.AddEntry(_overlay,self.typLegendDict[_overlay.GetName()],'L')
    
        if self.normalize:
            if MC_integral != 0:	stackscale=d1.Integral()/MC_integral
            if self.overlay:
                for _overlay in self.overlay:
                    _overlay.Scale(stackscale)
            stackhists=allStack.GetHists()
            for blabla in stackhists:
        	    if MC_integral != 0: blabla.Scale(stackscale)
   
        allMC=allStack.GetStack().Last().Clone()

        allStack.SetTitle()
        allStack.Draw("hist")
        allStack.GetXaxis().SetTitle('')
        #yTitle = 's/(s+b) weighted entries'
        if not d1.GetSumOfWeights() % 1 == 0.0:
            yTitle = 's/(s+b) weighted entries'
        else:
            yTitle = 'Entries'
        if not '/' in yTitle:
            yAppend = '%.0f' %(allStack.GetXaxis().GetBinWidth(1)) 
            yTitle = '%s / %s' %(yTitle, yAppend)
        allStack.GetYaxis().SetTitle(yTitle)
        allStack.GetXaxis().SetRangeUser(self.xMin,self.xMax)
        allStack.GetYaxis().SetRangeUser(0,20000)
        theErrorGraph = ROOT.TGraphErrors(allMC)
        theErrorGraph.SetFillColor(ROOT.kGray+3)
        theErrorGraph.SetFillStyle(3013)
        theErrorGraph.Draw('SAME2')
        l_2.AddEntry(theErrorGraph,"MC uncert. (stat.)","fl")
        Ymax = max(allStack.GetMaximum(),d1.GetMaximum())*1.7
        if self.log:
            allStack.SetMinimum(0.1)
            Ymax = Ymax*ROOT.TMath.Power(10,1.2*(ROOT.TMath.Log(1.2*(Ymax/0.1))/ROOT.TMath.Log(10)))*(0.2*0.1)
            #Ymax = Ymax*ROOT.TMath.Power(10,1.3*(ROOT.TMath.Log(1.3*(Ymax/0.1))/ROOT.TMath.Log(10)))*(0.3*0.1)
            ROOT.gPad.SetLogy()
        allStack.SetMaximum(Ymax)
        c.Update()
        ROOT.gPad.SetTicks(1,1)
        l.SetFillColor(0)
        l.SetBorderSize(0)
        l_2.SetFillColor(0)
        l_2.SetBorderSize(0)
        
        if self.overlay:
            for _overlay in self.overlay:
                _overlay.Draw('hist,same')
        d1.Draw("E,same")
        l.Draw()
        l_2.Draw()

        tPrel = self.myText("CMS",0.17,0.88,1.04)
        tLumi = self.myText("#sqrt{s} =  %s, L = %.1f fb^{-1}"%('7TeV',(float(5000.)/1000.)),0.17,0.83)
        tLumi1 = self.myText("#sqrt{s} =  %s, L = %.1f fb^{-1}"%(self.anaTag,(float(self.lumi)/1000.)),0.17,0.78)
        tAddFlag = self.myText(addFlag,0.17,0.78)
        if addFlag2:
            tAddFlag2 = self.myText(addFlag2,0.17,0.73)

        unten.cd()
        ROOT.gPad.SetTicks(1,1)

        l2 = ROOT.TLegend(0.50, 0.82,0.92,0.95)
        l2.SetLineWidth(2)
        l2.SetBorderSize(0)
        l2.SetFillColor(0)
        l2.SetFillStyle(4000)
        l2.SetTextFont(62)
        l2.SetNColumns(2)


        ratio, error = getRatio(d1,allMC,self.xMin,self.xMax,"",self.maxRatioUncert)
        ksScore = d1.KolmogorovTest( allMC )
        chiScore = d1.Chi2Test( allMC , "UWCHI2/NDF")
        print ksScore
        print chiScore
        ratio.SetStats(0)
        ratio.GetXaxis().SetTitle(self.xAxis)
        ratioError = ROOT.TGraphErrors(error)
        ratioError.SetFillColor(ROOT.kGray+3)
        ratioError.SetFillStyle(3013)
        ratio.Draw("E1")
        if self.doFit:
            fitData = ROOT.TF1("fData", "gaus",0.7, 1.3)
            fitMC = ROOT.TF1("fMC", "gaus",0.7, 1.3)
            print 'Fit on data'
            d1.Fit(fitData,"R")
            print 'Fit on simulation'
            allMC.Fit(fitMC,"R")


        if not self.AddErrors == None:
            self.AddErrors.SetFillColor(5)
            self.AddErrors.SetFillStyle(1001)
            self.AddErrors.Draw('SAME2')

            l2.AddEntry(self.AddErrors,"MC uncert. (stat. + syst.)","f")


        l2.AddEntry(ratioError,"MC total uncert.","f")

        l2.Draw()

        ratioError.Draw('SAME2')
        ratio.Draw("E1SAME")
        ratio.SetTitle("")
        m_one_line = ROOT.TLine(self.xMin,1,self.xMax,1)
        m_one_line.SetLineStyle(ROOT.kDashed)
        m_one_line.Draw("Same")

        if not self.blind:
            #tKsChi = self.myText("#chi_{#nu}^{2} = %.3f K_{s} = %.3f"%(chiScore,ksScore),0.17,0.9,1.5)
            tKsChi = self.myText("#chi_{#nu}^{2} = %.3f"%(chiScore),0.17,0.9,1.5)
        t0 = ROOT.TText()
        t0.SetTextSize(ROOT.gStyle.GetLabelSize()*2.4)
        t0.SetTextFont(ROOT.gStyle.GetLabelFont())
        if not self.log:
    	    t0.DrawTextNDC(0.1059,0.96, "0")
        if not os.path.exists(self.plotDir):
            os.makedirs(os.path.dirname(self.plotDir))
        name = '%s/%s' %(self.plotDir,self.options['pdfName'])
        c.Print(name)
        fOut = ROOT.TFile.Open(name.replace('.pdf','.root'),'RECREATE')
        for theHist in allStack.GetHists():
            if not self.AddErrors == None and not theHist.GetName() in ['ZH','WH','VH']:
                #print theHist.GetNbinsX()
                #print self.AddErrors.GetN()
                #print error.GetNbinsX()
                for bin in range(0,theHist.GetNbinsX()):
                    theRelativeTotalError = self.AddErrors.GetErrorY(bin)
                    if error.GetBinError(bin+1) > 0.:
                        theRelativeIncrease = theRelativeTotalError/error.GetBinError(bin+1)
                    else:
                        theRelativeIncrease = 1.
                    #print 'TheTotalRelativeIncrease is: %.2f' %theRelativeIncrease
                    #print 'TheTotalStatError is: %.2f' %error.GetBinError(bin+1)
                    #print 'TheTotalError is: %.2f' %theRelativeTotalError
                    theHist.SetBinError(bin,theHist.GetBinError(bin)*theRelativeIncrease)
            theHist.SetDirectory(fOut)
            if theHist.GetName() == 'ZH' or theHist.GetName() == 'WH':
                theHist.SetName('VH')
            theHist.Write()
        d1.SetName('data_obs')
        d1.SetDirectory(fOut)
        d1.Write()
        fOut.Close()
        #self.doCompPlot(allStack,l)

    def doSubPlot(self,signal):
        
        TdrStyles.tdrStyle()
        histo_dict = HistoMaker.orderandadd([{self.typs[i]:self.histos[i]} for i in range(len(self.histos))],self.setup)
        #sort
        print histo_dict
        sig_histos=[]
        sub_histos=[histo_dict[key] for key in self.setup]
        self.typs=self.setup
        for key in self.setup:
            if key in signal:
                sig_histos.append(histo_dict[key])
        
        c = ROOT.TCanvas(self.var,'', 600, 600)
        c.SetFillStyle(4000)
        c.SetFrameFillStyle(1000)
        c.SetFrameFillColor(0)

        main_pad = ROOT.TPad('main_pad','main_pad',0,0.1 ,1.0,1.0)
#        main_pad.SetBottomMargin(0)
        main_pad.SetFillStyle(4000)
        main_pad.SetFrameFillStyle(1000)
        main_pad.SetFrameFillColor(0)

        main_pad.Draw()

        main_pad.cd()
        allStack = ROOT.THStack(self.var,'')
        bkgStack = ROOT.THStack(self.var,'')     
        sigStack = ROOT.THStack(self.var,'')     

        l = ROOT.TLegend(0.59, 0.55,0.88,0.92)
        l.SetLineWidth(2)
        l.SetBorderSize(0)
        l.SetFillColor(0)
        l.SetFillStyle(4000)
        l.SetTextFont(62)
        l.SetTextSize(0.035)
        MC_integral=0
        MC_entries=0

        for histo in sub_histos:
            MC_integral+=histo.Integral()
        print "\033[1;32m\n\tMC integral = %s\033[1;m"%MC_integral



        if not 'DYc' in self.typs: self.typLegendDict.update({'DYlight':self.typLegendDict['DYlc']})
        print self.typLegendDict

        k=len(sub_histos)

        # debug
        print sub_histos
        print sig_histos
    
        for j in range(0,k):
            #print histos[j].GetBinContent(1)
            i=k-j-1
            sub_histos[i].SetFillColor(int(self.colorDict[self.typs[i]]))
            sub_histos[i].SetLineColor(1)
            allStack.Add(sub_histos[i])
            print sub_histos[i].GetName()
            print sub_histos[i].Integral()
            if not sub_histos[i] in sig_histos:
                bkgStack.Add(sub_histos[i])
            if sub_histos[i] in sig_histos:
                sigStack.Add(sub_histos[i])


        sub_d1 = ROOT.TH1F('subData','subData',self.nBins,self.xMin,self.xMax)
        sub_mc = ROOT.TH1F('subMC','subMC',self.nBins,self.xMin,self.xMax)

        d1 = ROOT.TH1F('noData','noData',self.nBins,self.xMin,self.xMax)
        datatitle='Data'
        addFlag = ''
        if 'Zee' in self.datanames and 'Zmm' in self.datanames:
	        addFlag = 'Z(l^{-}l^{+})H(b#bar{b})'
        elif 'Zee' in self.datanames:
	        addFlag = 'Z(e^{-}e^{+})H(b#bar{b})'
        elif 'Zmm' in self.datanames:
	        addFlag = 'Z(#mu^{-}#mu^{+})H(b#bar{b})'
        elif 'Znn' in self.datanames:
	        addFlag = 'Z(#nu#nu)H(b#bar{b})'
        elif 'Wmn' in self.datanames:
	        addFlag = 'W(#mu#nu)H(b#bar{b})'
        elif 'Wen' in self.datanames:
                addFlag = 'W(e#nu)H(b#bar{b})'
        else:
                addFlag = 'pp #rightarrow VH; H #rightarrow b#bar{b}'
        for i in range(0,len(self.datas)):
            print self.datas[i]
            d1.Add(self.datas[i],1)
        print "\033[1;32m\n\tDATA integral = %s\033[1;m"%d1.Integral()
        flow = d1.GetEntries()-d1.Integral()
        if flow > 0:
            print "\033[1;31m\tU/O flow: %s\033[1;m"%flow
        

        numLegend = 1+k
        if self.overlay:
            numLegend += len(self.overlay)
        l.AddEntry(d1,datatitle,'P')
#        l.AddEntry(sub_d1,datatitle,'P')
        for j in range(0,k):
            if self.typs[j] in signal:
                if j < numLegend/2.:
                    l.AddEntry(sub_histos[j],self.typLegendDict[self.typs[j]],'F')
                else:
                    l_2.AddEntry(sub_histos[j],self.typLegendDict[self.typs[j]],'F')
        if self.overlay:
            for _overlay in self.overlay:
                l_2.AddEntry(_overlay,self.typLegendDict['Overlay'+_overlay.GetName()],'L')
    
        if self.normalize:
            if MC_integral != 0:	stackscale=d1.Integral()/MC_integral
            if self.overlay:
                for _overlay in self.overlay:
                    _overlay.Scale(stackscale)
            stackhists=allStack.GetHists()
            for blabla in stackhists:
        	    if MC_integral != 0: blabla.Scale(stackscale)
   
        allMC=allStack.GetStack().Last().Clone()
        bkgMC=bkgStack.GetStack().Last().Clone()

        bkgMC_noError = bkgMC.Clone()
        for bin in range(0,bkgMC_noError.GetNbinsX()):
            bkgMC_noError.SetBinError(bin,0.)
        sub_d1 = d1.Clone()
        sub_d1.Sumw2()
        sub_d1.Add(bkgMC_noError,-1)
        sub_mc = allMC.Clone()
        sub_mc.Sumw2()
        sub_mc.Add(bkgMC_noError,-1)

        sigStack.SetTitle()
        sigStack.Draw("hist")
        sigStack.GetXaxis().SetTitle('')
        yTitle = 's/(s+b) weighted entries'
        if not '/' in yTitle:
            yAppend = '%.0f' %(sigStack.GetXaxis().GetBinWidth(1)) 
            yTitle = '%s / %s' %(yTitle, yAppend)
        sigStack.GetYaxis().SetTitle(yTitle)
        sigStack.GetYaxis().SetTitleOffset(1.3)
        sigStack.GetXaxis().SetRangeUser(self.xMin,self.xMax)
        sigStack.GetYaxis().SetRangeUser(-2000,20000)
        sigStack.GetXaxis().SetTitle(self.xAxis)

        theMCOutline = bkgMC.Clone()
        for i in range(1,theMCOutline.GetNbinsX()+1):
            theMCOutline.SetBinContent(i,theMCOutline.GetBinError(i))
        theNegativeOutline = theMCOutline.Clone()
        theNegativeOutline.Add(theNegativeOutline,-2.)

        theMCOutline.SetLineColor(4)
        theNegativeOutline.SetLineColor(4)
        theMCOutline.SetLineWidth(2)
        theNegativeOutline.SetLineWidth(2)
        theMCOutline.SetFillColor(0)
        theNegativeOutline.SetFillColor(0)
        theMCOutline.Draw("hist same")
        theNegativeOutline.Draw("hist same")
        l.AddEntry(theMCOutline,"Sub. MC uncert.","fl")
        
        theErrorGraph = ROOT.TGraphErrors(sigStack.GetStack().Last().Clone())
        theErrorGraph.SetFillColor(ROOT.kGray+3)
        theErrorGraph.SetFillStyle(3013)
        theErrorGraph.Draw('SAME2')
        l.AddEntry(theErrorGraph,"VH + VV MC uncert.","fl")

        Ymax = max(sigStack.GetMaximum(),sub_d1.GetMaximum())*1.7
        Ymin = max(-sub_mc.GetMinimum(),-sub_d1.GetMinimum())*2.7
        if self.log:
            sigStack.SetMinimum(0.1)
            Ymax = Ymax*ROOT.TMath.Power(10,1.2*(ROOT.TMath.Log(1.2*(Ymax/0.1))/ROOT.TMath.Log(10)))*(0.2*0.1)
            ROOT.gPad.SetLogy()
        sigStack.SetMaximum(Ymax)
        sigStack.SetMinimum(-Ymin)
        c.Update()
        ROOT.gPad.SetTicks(1,1)
        #sigStack.Draw("hist")
        l.SetFillColor(0)
        l.SetBorderSize(0)
        
        if self.overlay:
            for _overlay in self.overlay:
                _overlay.Draw('hist,same')
        sub_d1.Draw("E,same")
        l.Draw()

        tPrel = self.myText("CMS",0.17,0.88,1.04)
        tLumi = self.myText("#sqrt{s} =  %s, L = %.1f fb^{-1}"%(self.anaTag,(float(self.lumi)/1000.)),0.17,0.83)
        tLumi = self.myText("#sqrt{s} =  7TeV, L = 5.0 fb^{-1}",0.17,0.78)
        tAddFlag = self.myText(addFlag,0.17,0.73)

        ROOT.gPad.SetTicks(1,1)

        l2 = ROOT.TLegend(0.5, 0.82,0.92,0.95)
        l2.SetLineWidth(2)
        l2.SetBorderSize(0)
        l2.SetFillColor(0)
        l2.SetFillStyle(4000)
        l2.SetTextFont(62)
        #l2.SetTextSize(0.035)
        l2.SetNColumns(2)



        if not self.AddErrors == None:
            self.AddErrors.SetFillColor(5)
            self.AddErrors.SetFillStyle(1001)
            self.AddErrors.Draw('SAME2')

            l2.AddEntry(self.AddErrors,"MC uncert. (stat. + syst.)","f")


        if not os.path.exists(self.plotDir):
            os.makedirs(os.path.dirname(self.plotDir))
        name = '%s/%s' %(self.plotDir,self.options['pdfName'])
        c.Print(name)
