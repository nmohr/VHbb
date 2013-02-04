import sys,os
import pickle
import ROOT 
from array import array
from printcolor import printc
from BetterConfigParser import BetterConfigParser
from TreeCache import TreeCache

class HistoMaker:
    def __init__(self, samples, path, config, optionsList):
        self.path = path
        self.config = config
        self.optionsList = optionsList
        self.lumi=0.
        self.cuts = []
        for options in optionsList:
            self.cuts.append(options['cut'])
        #self.tc = TreeCache(self.cuts,samples,path) 
        self.tc = TreeCache(self.cuts,samples,path,config)

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
            group=job.group
            treeVar=options['var']
            name=options['name']
            nBins=int(options['nBins'])
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
            gDict[group] = hTree
            hTreeList.append(gDict)
         
        return hTreeList
        

    @staticmethod
    def orderandadd(histo_dicts,setup):
        print histo_dicts
        ordered_histo_dict = {}
        for sample in setup:
            nSample = 0
            for histo_dict in histo_dicts:
                if histo_dict.has_key(sample):
                    if nSample == 0:
                        ordered_histo_dict[sample] = histo_dict[sample]
                    else:
                        printc('magenta','','\t--> added %s to %s'%(sample,sample))
                        ordered_histo_dict[sample].Add(histo_dict[sample])
                    nSample += 1
        return ordered_histo_dict 
