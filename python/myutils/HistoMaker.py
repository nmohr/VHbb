import sys,os
import pickle
import ROOT 
from array import array
from printcolor import printc
from BetterConfigParser import BetterConfigParser
from TreeCache import TreeCache
from math import sqrt
from copy import copy

class HistoMaker:
    def __init__(self, samples, path, config, optionsList,GroupDict=None):
        self.path = path
        self.config = config
        self.optionsList = optionsList
        self.nBins = optionsList[0]['nBins']
        self.lumi=0.
        self.cuts = []
        for options in optionsList:
            self.cuts.append(options['cut'])
        #self.tc = TreeCache(self.cuts,samples,path) 
        self.tc = TreeCache(self.cuts,samples,path,config)
        self._rebin = False
        self.mybinning = None
        self.GroupDict=GroupDict

    def get_histos_from_tree(self,job):
        if self.lumi == 0: 
            raise Exception("You're trying to plot with no lumi")
         
        hTreeList=[]

        #get the conversion rate in case of BDT plots
        TrainFlag = eval(self.config.get('Analysis','TrainFlag'))
        BDT_add_cut='EventForTraining == 0'


        plot_path = self.config.get('Directories','plotpath')
        addOverFlow=eval(self.config.get('Plot_general','addOverFlow'))

        # get all Histos at once
        for options in self.optionsList:
            name=job.name
            if self.GroupDict is None:
                group=job.group
            else:
                group=self.GroupDict[job.name]
            treeVar=options['var']
            name=options['name']
            if self._rebin:
                nBins = self.nBins
            else:
                nBins = int(options['nBins'])
            xMin=float(options['xMin'])
            xMax=float(options['xMax'])
            weightF=options['weight']
            treeCut='%s'%(options['cut'])
            CuttedTree = self.tc.get_tree(job,treeCut)

            #options

            if job.type != 'DATA':
                if CuttedTree.GetEntries():
                    
                    if 'RTight' in treeVar or 'RMed' in treeVar: 
                        drawoption = '(%s)*(%s)'%(weightF,BDT_add_cut)
                    else: 
                        drawoption = '%s'%(weightF)
                    CuttedTree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax), drawoption, "goff,e")
                    full=True
                else:
                    full=False
            elif job.type == 'DATA':
                if options['blind']:
                    if treeVar == 'H.mass':
                        CuttedTree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),treeVar+'<90. || '+treeVar + '>150.' , "goff,e")
                    else:
                        CuttedTree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),treeVar+'<0', "goff,e")

                else:
                    CuttedTree.Draw('%s>>%s(%s,%s,%s)' %(treeVar,name,nBins,xMin,xMax),'1', "goff,e")
                full = True
            if full:
                hTree = ROOT.gDirectory.Get(name)
            else:
                hTree = ROOT.TH1F('%s'%name,'%s'%name,nBins,xMin,xMax)
                hTree.Sumw2()
            if job.type != 'DATA':
                if 'RTight' in treeVar or 'RMed' in treeVar:
                    if TrainFlag:
                        MC_rescale_factor=2.
                        print 'I RESCALE BY 2.0'
                    else: 
                        MC_rescale_factor = 1.
                    ScaleFactor = self.tc.get_scale(job,self.config,self.lumi)*MC_rescale_factor
                else: 
                    ScaleFactor = self.tc.get_scale(job,self.config,self.lumi)
                if ScaleFactor != 0:
                    hTree.Scale(ScaleFactor)
            #print '\t-->import %s\t Integral: %s'%(job.name,hTree.Integral())
            if addOverFlow:
            	uFlow = hTree.GetBinContent(0)+hTree.GetBinContent(1)
            	oFlow = hTree.GetBinContent(hTree.GetNbinsX()+1)+hTree.GetBinContent(hTree.GetNbinsX())
            	uFlowErr = ROOT.TMath.Sqrt(ROOT.TMath.Power(hTree.GetBinError(0),2)+ROOT.TMath.Power(hTree.GetBinError(1),2))
            	oFlowErr = ROOT.TMath.Sqrt(ROOT.TMath.Power(hTree.GetBinError(hTree.GetNbinsX()),2)+ROOT.TMath.Power(hTree.GetBinError(hTree.GetNbinsX()+1),2))
            	hTree.SetBinContent(1,uFlow)
            	hTree.SetBinContent(hTree.GetNbinsX(),oFlow)
            	hTree.SetBinError(1,uFlowErr)
            	hTree.SetBinError(hTree.GetNbinsX(),oFlowErr)
            hTree.SetDirectory(0)
            gDict = {}
            if self._rebin:
                gDict[group] = self.mybinning.rebin(hTree)
                del hTree
            else: 
                gDict[group] = hTree
            hTreeList.append(gDict)
            CuttedTree.IsA().Destructor(CuttedTree)
            del CuttedTree
        return hTreeList
       
    @property
    def rebin(self):
        return self._rebin

    @property
    def rebin(self, value):
        if self._rebin and value:
            return True
        elif self._rebin and not value:
            self.nBins = self.norebin_nBins
            self._rebin = False
        elif not self._rebin and value:
            if self.mybinning is None:
                raise Exception('define rebinning first')
            else:
                self.nBins = self.rebin_nBins
                self._rebin = True
                return True
        elif not self._rebin and not self.value:
            return False

    def calc_rebin(self, bg_list, nBins_start=1000, tolerance=0.35):
        self.norebin_nBins = self.nBins
        self.rebin_nBins = nBins_start
        self.nBins = nBins_start
        i=0
        #add all together:
        print '\n\t...calculating rebinning...'
        for job in bg_list:
            htree = self.get_histos_from_tree(job)[0].values()[0]
            if not i:
                totalBG = copy(htree)
            else:
                totalBG.Add(htree,1)
            del htree
            i+=1
        ErrorR=0
        ErrorL=0
        TotR=0
        TotL=0
        binR=self.rebin_nBins
        binL=1
        rel=1.0
        #---- from right
        while rel > tolerance:
            TotR+=totalBG.GetBinContent(binR)
            ErrorR=sqrt(ErrorR**2+totalBG.GetBinError(binR)**2)
            binR-=1
            if not TotR == 0 and not ErrorR == 0:
                rel=ErrorR/TotR
                #print rel
        #print 'upper bin is %s'%binR

        #---- from left
        rel=1.0
        while rel > tolerance:
            TotL+=totalBG.GetBinContent(binL)
            ErrorL=sqrt(ErrorL**2+totalBG.GetBinError(binL)**2)
            binL+=1
            if not TotL == 0 and not ErrorL == 0:
                rel=ErrorL/TotL
                #print rel
        #it's the lower edge
        binL+=1
        #print 'lower bin is %s'%binL

        inbetween=binR-binL
        stepsize=int(inbetween)/(int(self.norebin_nBins)-2)
        modulo = int(inbetween)%(int(self.norebin_nBins)-2)

        #print'stepsize %s'% stepsize
        #print 'modulo %s'%modulo
        binlist=[binL]
        for i in range(0,int(self.norebin_nBins)-3):
            binlist.append(binlist[-1]+stepsize)
        binlist[-1]+=modulo
        binlist.append(binR)
        binlist.append(self.rebin_nBins+1)

        self.mybinning = Rebinner(int(self.norebin_nBins),array('d',[-1.0]+[totalBG.GetBinLowEdge(i) for i in binlist]),True)
        self._rebin = True
        print '\t > rebinning is set <\n'

    @staticmethod
    def orderandadd(histo_dicts,setup):
        ordered_histo_dict = {}
        for sample in setup:
            nSample = 0
            for histo_dict in histo_dicts:
                if histo_dict.has_key(sample):
                    if nSample == 0:
                        ordered_histo_dict[sample] = histo_dict[sample].Clone()
                    else:
                        printc('magenta','','\t--> added %s to %s'%(sample,sample))
                        ordered_histo_dict[sample].Add(histo_dict[sample])
                    nSample += 1
        del histo_dicts
        return ordered_histo_dict 

class Rebinner:
    def __init__(self,nBins,lowedgearray,active=True):
        self.lowedgearray=lowedgearray
        self.nBins=nBins
        self.active=active
    def rebin(self, histo):
        if not self.active: return histo
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
        del histo
        del binhisto
        return copy(newhisto)
