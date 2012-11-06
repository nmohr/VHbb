#!/usr/bin/env python
import pickle
import ROOT 
from BetterConfigParser import BetterConfigParser
import sys, os
from optparse import OptionParser
from copy import copy,deepcopy
from StackMaker import StackMaker
from math import sqrt
import math
from HiggsAnalysis.CombinedLimit.DatacardParser import *
from HiggsAnalysis.CombinedLimit.ShapeTools     import *

ROOT.gROOT.SetBatch(True)
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so")

#CONFIGURE
argv = sys.argv
parser = OptionParser()
parser.add_option("-D", "--datacard", dest="dc", default="",
                      help="Datacard to be plotted")
parser.add_option("-B", "--bin", dest="bin", default="",
                      help="DC bin to plot")
parser.add_option("-M", "--mlfit", dest="mlfit", default="",
                      help="mlfit file for nuisances")
parser.add_option("-F", "--fitresult", dest="fit", default="s",
                      help="Fit result to be used, 's' (signal+background)  or 'b' (background only), default is 's'")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration file")
(opts, args) = parser.parse_args(argv)


def readBestFit(theFile):
    file = ROOT.TFile(theFile)
    if file == None: raise RuntimeError, "Cannot open file %s" % args[0]
    fit_s  = file.Get("fit_s")
    fit_b  = file.Get("fit_b")
    prefit = file.Get("nuisances_prefit")
    if fit_s == None or fit_s.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the signal fit 'fit_s'"     % args[0]
    if fit_b == None or fit_b.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the background fit 'fit_b'" % args[0]
    if prefit == None or prefit.ClassName() != "RooArgSet":    raise RuntimeError, "File %s does not contain the prefit nuisances 'nuisances_prefit'"  % args[0]

    isFlagged = {}
    table = {}
    fpf_b = fit_b.floatParsFinal()
    fpf_s = fit_s.floatParsFinal()
    nuiVariation = {}
    for i in range(fpf_s.getSize()):
        nuis_s = fpf_s.at(i)
        name   = nuis_s.GetName();
        nuis_b = fpf_b.find(name)
        nuis_p = prefit.find(name)
        if nuis_p != None:
            mean_p, sigma_p = (nuis_p.getVal(), nuis_p.getError())
        for fit_name, nuis_x in [('b', nuis_b), ('s',nuis_s)]:
            if nuis_p != None:
                valShift = (nuis_x.getVal() - mean_p)/sigma_p
                #sigShift = nuis_x.getError()/sigma_p
                print fit_name, name
                print valShift
                nuiVariation['%s_%s'%(fit_name,name)] = valShift
                #print valShift
    return nuiVariation


def drawFromDC():
    config = BetterConfigParser()
    config.read(opts.config)
    print config.sections()
    region = 'BDT'
    var = 'BDT'
    ws_var = config.get('plotDef:%s'%var,'relPath')
    blind = eval(config.get('Plot:%s'%region,'blind'))
    Stack=StackMaker(config,var,region,True)

    dataname = ''
    if 'Zmm' in opts.bin: dataname = 'Zmm'
    elif 'Zee' in opts.bin: dataname = 'Zee'
    elif 'Wmn' in opts.bin: dataname = 'Wmn'
    elif 'Wen' in opts.bin: dataname = 'Wen'
    elif 'Znn' in opts.bin: dataname = 'Znn'

    log = eval(config.get('Plot:%s'%region,'log'))

    setup = config.get('Plot_general','setup').split(',')
    Dict = eval(config.get('LimitGeneral','Dict'))
    lumi = eval(config.get('Plot_general','lumi'))
    
    options = copy(opts)
    options.dataname = "data_obs"
    options.mass = 0
    options.format = "%8.3f +/- %6.3f"
    options.channel = opts.bin
    options.excludeSyst = []
    options.norm = False
    options.stat = False
    options.bin = True # fake that is a binary output, so that we parse shape lines
    options.out = "tmp.root"
    options.fileName = args[0]
    options.cexpr = False
    options.fixpars = False
    options.libs = []
    options.verbose = 0
    options.poisson = 0
    options.nuisancesToExclude = []
    options.noJMax = None

    file = open(opts.dc, "r")
    os.chdir(os.path.dirname(opts.dc))
    DC = parseCard(file, options)
    if not DC.hasShapes: DC.hasShapes = True
    MB = ShapeBuilder(DC, options)
    theShapes = {}
    theSyst = {}
    if opts.mlfit:
        nuiVar = readBestFit(opts.mlfit)
    for b in DC.bins:
        if options.channel != None and (options.channel != b): continue
        exps = {}
        expNui = {}
        shapeNui = {}
        for (p,e) in DC.exp[b].items(): # so that we get only self.DC.processes contributing to this bin
            exps[p] = [ e, [] ]
            expNui[p] = [ e, [] ]
        for (lsyst,nofloat,pdf,pdfargs,errline) in DC.systs:
            if pdf in ('param', 'flatParam'): continue
            # begin skip systematics
            skipme = False
            for xs in options.excludeSyst:
                if re.search(xs, lsyst): 
                    skipme = True
            if skipme: continue
            # end skip systematics
            counter = 0
            for p in DC.exp[b].keys(): # so that we get only self.DC.processes contributing to this bin
                if errline[b][p] == 0: continue
                if pdf == 'gmN':
                    exps[p][1].append(1/sqrt(pdfargs[0]+1));
                elif pdf == 'gmM':
                    exps[p][1].append(errline[b][p]);
                elif type(errline[b][p]) == list: 
                    kmax = max(errline[b][p][0], errline[b][p][1], 1.0/errline[b][p][0], 1.0/errline[b][p][1]);
                    exps[p][1].append(kmax-1.);
                elif pdf == 'lnN':
                     exps[p][1].append(max(errline[b][p], 1.0/errline[b][p])-1.);
                     if not nuiVar.has_key('%s_%s'%(opts.fit,lsyst)):
                         nui = 0.
                     else:
                        nui= nuiVar['%s_%s'%(opts.fit,lsyst)]
                     expNui[p][1].append(abs(1-errline[b][p])*nui);
                elif ("shape" in pdf) and not 'CMS_vhbb_stats_' in lsyst:
                    s0 = MB.getShape(b,p)
                    sUp   = MB.getShape(b,p,lsyst+"Up")
                    sDown = MB.getShape(b,p,lsyst+"Down")
                    if (s0.InheritsFrom("RooDataHist")):
                        s0 = ROOT.RooAbsData.createHistogram(s0,ws_var)
                        s0.SetName(p)
                        sUp = ROOT.RooAbsData.createHistogram(sUp,ws_var)
                        sUp.SetName(p+lsyst+'Up')
                        sDown = ROOT.RooAbsData.createHistogram(sDown,ws_var)
                        sDown.SetName(p+lsyst+'Down')
                    theShapes[p] = s0.Clone()
                    theShapes[p+lsyst+'Up'] = sUp.Clone()
                    theShapes[p+lsyst+'Down'] = sDown.Clone()
                    if not nuiVar.has_key('%s_%s'%(opts.fit,lsyst)):
                        nui = 0.
                    else:
                        nui= nuiVar['%s_%s'%(opts.fit,lsyst)]
                    shapeNui[p] = nui
                    if counter == 0:
                        theSyst[lsyst] = s0.Clone() 
                        theSyst[lsyst+'Up'] = sUp.Clone() 
                        theSyst[lsyst+'Down'] = sDown.Clone() 
                    else:
                        theSyst[lsyst].Add(s0)
                        theSyst[lsyst+'Up'].Add(sUp.Clone())
                        theSyst[lsyst+'Down'].Add(sDown.Clone()) 
                    counter += 1
    procs = DC.exp[b].keys(); procs.sort()
    fmt = ("%%-%ds " % max([len(p) for p in procs]))+"  "+options.format;
    #Compute norm uncertainty and best fit
    theNormUncert = {}
    theBestFit = {}
    for p in procs:
        relunc = sqrt(sum([x*x for x in exps[p][1]]))
        print fmt % (p, exps[p][0], exps[p][0]*relunc)
        theNormUncert[p] = relunc
        absBestFit = sum([x for x in expNui[p][1]])
        theBestFit[p] = 1.+absBestFit
    
    histos = []
    typs = []

    setup2=copy(setup)

    shapesUp = [[] for _ in range(0,len(setup2))]
    shapesDown = [[] for _ in range(0,len(setup2))]
    
    for p in procs:
        b = opts.bin
        for s in setup:
            if not Dict[s] == p: continue
            if 'ZH' == s:
                Overlay=copy(theShapes[Dict[s]])
            else:
                histos.append(theShapes[Dict[s]])
                typs.append(s)
                print s
            for (lsyst,nofloat,pdf,pdfargs,errline) in DC.systs:
                if errline[b][p] == 0: continue
                if ("shape" in pdf) and not 'CMS_vhbb_stats_' in lsyst:
                    print 'syst %s'%lsyst
                    shapesUp[setup2.index(s)].append(theShapes[Dict[s]+lsyst+'Up'])
                    shapesDown[setup2.index(s)].append(theShapes[Dict[s]+lsyst+'Down'])

    #-------------
    #Compute absolute uncertainty from shapes
    counter = 0
    for (lsyst,nofloat,pdf,pdfargs,errline) in DC.systs:
        if ("shape" in pdf) and not 'CMS_vhbb_stats_' in lsyst:
            theSystUp = theSyst[lsyst+'Up'].Clone()
            theSystUp.Add(theSyst[lsyst].Clone(),-1.)
            theSystUp.Multiply(theSystUp)
            theSystDown = theSyst[lsyst+'Down'].Clone()
            theSystDown.Add(theSyst[lsyst].Clone(),-1.)
            theSystDown.Multiply(theSystDown)
            if counter == 0:
                theAbsSystUp = theSystUp.Clone()
                theAbsSystDown = theSystDown.Clone()
            else:
                theAbsSystUp.Add(theSystUp.Clone())
                theAbsSystDown.Add(theSystDown.Clone())
            counter +=1
    
    #-------------
    #Best fit for shapes
    for p in procs:
        counter = 0
        nom = theShapes[p].Clone()
        for (lsyst,nofloat,pdf,pdfargs,errline) in DC.systs:
            if errline[b][p] == 0: continue
            if ("shape" in pdf) and not 'CMS_vhbb_stats_' in lsyst and not 'CMS_vhbb_model_VV' in lsyst:
                if shapeNui > 0.:
                    theVari = 'Up'
                else:
                    theVari = 'Down'
                bestNuiVar = theShapes[p+lsyst+theVari].Clone()
                bestNuiVar.Add(nom,-1.)
                bestNuiVar.Scale(abs(shapeNui[p]))
                if counter == 0:
                    bestNui = bestNuiVar.Clone()
                else:
                    bestNui.Add(bestNuiVar)
                counter +=1
                nom.Add(bestNui)
        nom.Scale(theShapes[p].Integral()/nom.Integral())
        nBins = nom.GetNbinsX()
        for bin in range(1,nBins+1):
            nom.SetBinError(bin,theShapes[p].GetBinError(bin))
        theShapes['%s_%s'%(opts.fit,p)] = nom.Clone()
    histos = []
    typs = []
    for s in setup:
        if 'ZH' == s:
            Overlay=copy(theShapes[Dict[s]])
        else:
            histos.append(theShapes['%s_%s'%(opts.fit,Dict[s])])
            typs.append(s)
    
    counter = 0
    errUp=[]
    total=[]
    errDown=[]
    nBins = histos[0].GetNbinsX()
    print 'total bins %s'%nBins
    Error = ROOT.TGraphAsymmErrors(histos[0])
    theTotalMC = histos[0].Clone()
    for h in range(1,len(histos)):
        theTotalMC.Add(histos[h])
    
    total = [[]]*nBins
    errUp = [[]]*nBins
    errDown = [[]]*nBins
    for bin in range(1,nBins+1):
        binError = theTotalMC.GetBinError(bin)
        if math.isnan(binError):
            binError = 0.
        total[bin-1]=theTotalMC.GetBinContent(bin)
        #Stat uncertainty of the MC outline
        errUp[bin-1] = [binError]
        errDown[bin-1] = [binError]
        #Relative norm uncertainty of the individual MC
        for h in range(0,len(histos)):
            errUp[bin-1].append(histos[h].GetBinContent(bin)*theNormUncert[histos[h].GetName()])
            errDown[bin-1].append(histos[h].GetBinContent(bin)*theNormUncert[histos[h].GetName()])
    #Shape uncertainty of the MC
    for bin in range(1,nBins+1):
        #print sqrt(theSystUp.GetBinContent(bin))
        errUp[bin-1].append(sqrt(theAbsSystUp.GetBinContent(bin)))
        errDown[bin-1].append(sqrt(theAbsSystDown.GetBinContent(bin)))
    

    #Add all in quadrature
    totErrUp=[sqrt(sum([x**2 for x in bin])) for bin in errUp]
    totErrDown=[sqrt(sum([x**2 for x in bin])) for bin in errDown]

    #Make TGraph with errors
    for bin in range(1,nBins+1):
        if not total[bin-1] == 0:
            point=histos[0].GetXaxis().GetBinCenter(bin)
            Error.SetPoint(bin-1,point,1)
            Error.SetPointEYlow(bin-1,totErrDown[bin-1]/total[bin-1])
            print 'down %s'%(totErrDown[bin-1]/total[bin-1])
            Error.SetPointEYhigh(bin-1,totErrUp[bin-1]/total[bin-1])
            print 'up   %s'%(totErrUp[bin-1]/total[bin-1])

    #-----------------------
    #Read data
    data0 = MB.getShape(opts.bin,'data_obs')
    if (data0.InheritsFrom("RooDataHist")):
        data0 = ROOT.RooAbsData.createHistogram(data0,ws_var)
        data0.SetName('data_obs')
    datas=[data0]
    datatyps = [None]
    datanames=[dataname] 


    if blind:
        for bin in range(10,datas[0].GetNbinsX()+1):
            datas[0].SetBinContent(bin,0)

    histos.append(copy(Overlay))
    typs.append('ZH')

    Stack.histos = histos
    Stack.typs = typs
    Stack.datas = datas
    Stack.datatyps = datatyps
    Stack.datanames= datanames
    Stack.overlay = Overlay
    Stack.AddErrors=Error
    Stack.lumi = lumi
    Stack.doPlot()

    print 'i am done!\n'
#-------------------------------------------------


if __name__ == "__main__":
    drawFromDC()
    sys.exit(0)
