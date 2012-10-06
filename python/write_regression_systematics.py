#!/usr/bin/env python
from samplesclass import sample
from printcolor import printc
import pickle
import sys
import os
import ROOT 
import math
import shutil
from ROOT import TFile
import ROOT
from array import array
import warnings
from optparse import OptionParser
from BetterConfigParser import BetterConfigParser
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#usage: ./write_regression_systematic.py path


#os.mkdir(path+'/sys')
argv = sys.argv
parser = OptionParser()
parser.add_option("-P", "--path", dest="path", default="", 
                      help="path to samples")
parser.add_option("-S", "--samples", dest="names", default="", 
                      help="samples you want to run on")
parser.add_option("-C", "--config", dest="config", default=[], action="append",
                      help="configuration defining the plots to make")
(opts, args) = parser.parse_args(argv)
if opts.config =="":
        opts.config = "config"
print opts.config
config = BetterConfigParser()
config.read(opts.config)
anaTag = config.get("Analysis","tag")
TrainFlag = eval(config.get('Analysis','TrainFlag'))
btagLibrary = config.get('BTagReshaping','library')
path=opts.path
namelist=opts.names.split(',')
#load info
infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()

def deltaPhi(phi1, phi2): 
    result = phi1 - phi2
    while (result > math.pi): result -= 2*math.pi
    while (result <= -math.pi): result += 2*math.pi
    return result

def resolutionBias(eta):
    if(eta< 1.1): return 0.05
    if(eta< 2.5): return 0.10
    if(eta< 5): return 0.30
    return 0

def corrPt(pt,eta,mcPt):
    return (pt+resolutionBias(math.fabs(eta))*(pt-mcPt))/pt

def corrCSV(btag,  csv, flav):
    if(csv < 0.): return csv
    if(csv > 1.): return csv;
    if(flav == 0): return csv;
    if(math.fabs(flav) == 5): return  btag.ib.Eval(csv)
    if(math.fabs(flav) == 4): return  btag.ic.Eval(csv)
    if(math.fabs(flav) != 4  and math.fabs(flav) != 5): return  btag.il.Eval(csv)
    return -10000


def csvReshape(sh, pt, eta, csv, flav):
	return sh.reshape(float(eta), float(pt), float(csv), int(flav))


for job in info:
    if not job.name in namelist: continue
    #print job.name
    #if job.name != 'ZH120': continue
    ROOT.gROOT.ProcessLine(
        "struct H {\
        int         HiggsFlag;\
        float         mass;\
        float         pt;\
        float         eta;\
        float         phi;\
        float         dR;\
        float         dPhi;\
        float         dEta;\
        } ;"
    )
    if anaTag == '7TeV':
    	ROOT.gSystem.Load(btagLibrary)
    	from ROOT import BTagShape
    	btagNom = BTagShape("../data/csvdiscr.root")
    	btagNom.computeFunctions()
    	btagUp = BTagShape("../data/csvdiscr.root")
    	btagUp.computeFunctions(+1.,0.)
    	btagDown = BTagShape("../data/csvdiscr.root")
    	btagDown.computeFunctions(-1.,0.)
    	btagFUp = BTagShape("../data/csvdiscr.root")
    	btagFUp.computeFunctions(0.,+1.)
    	btagFDown = BTagShape("../data/csvdiscr.root")
    	btagFDown.computeFunctions(0.,-1.)
    elif anaTag == '8TeV':
    	ROOT.gSystem.Load(btagLibrary)
    	from ROOT import BTagShapeInterface
    	btagNom = BTagShapeInterface("../data/csvdiscr.root",0,0)
    	btagUp = BTagShapeInterface("../data/csvdiscr.root",+1,0)
    	btagDown = BTagShapeInterface("../data/csvdiscr.root",-1,0)
    	btagFUp = BTagShapeInterface("../data/csvdiscr.root",0,+1.)
    	btagFDown = BTagShapeInterface("../data/csvdiscr.root",0,-1.)
    
    print '\t - %s' %(job.name)
    input = TFile.Open(path+'/'+job.getpath(),'read')
    output = TFile.Open(path+'/sys/'+job.prefix+job.identifier+'.root','recreate')

    input.cd()
    obj = ROOT.TObject
    for key in ROOT.gDirectory.GetListOfKeys():
        input.cd()
        obj = key.ReadObj()
        #print obj.GetName()
        if obj.GetName() == job.tree:
            continue
        output.cd()
        #print key.GetName()
        obj.Write(key.GetName())
        
    input.cd()
    tree = input.Get(job.tree)
    nEntries = tree.GetEntries()
        
    job.addpath('/sys')
    if job.type != 'DATA':
        job.SYS = ['Nominal','JER_up','JER_down','JES_up','JES_down','beff_up','beff_down','bmis_up','bmis_down']
        
    H = ROOT.H()
    HNoReg = ROOT.H()
    tree.SetBranchStatus('H',0)
    output.cd()
    newtree = tree.CloneTree(0)
        
    hJ0 = ROOT.TLorentzVector()
    hJ1 = ROOT.TLorentzVector()
        
    regWeight = config.get("Regression","regWeight")
    regDict = eval(config.get("Regression","regDict"))
    regVars = eval(config.get("Regression","regVars"))
    useMET = eval(config.get("Regression","useMET"))
    usePtRaw = eval(config.get("Regression","usePtRaw"))
    useMt = eval(config.get("Regression","useMt"))
    useRho25 = eval(config.get("Regression","useRho25"))
          
    #Regression branches
    applyRegression = True
    hJet_pt = array('f',[0]*2)
    hJet_e = array('f',[0]*2)
    newtree.Branch( 'H', H , 'HiggsFlag/I:mass/F:pt/F:eta:phi/F:dR/F:dPhi/F:dEta/F' )
    newtree.Branch( 'HNoReg', HNoReg , 'HiggsFlag/I:mass/F:pt/F:eta:phi/F:dR/F:dPhi/F:dEta/F' )
    Event = array('f',[0])
    METet = array('f',[0])
    rho25 = array('f',[0])
    METphi = array('f',[0])
    fRho25 = ROOT.TTreeFormula("rho25",'rho25',tree)
    fEvent = ROOT.TTreeFormula("Event",'EVENT.event',tree)
    fMETet = ROOT.TTreeFormula("METet",'METnoPU.et',tree)
    fMETphi = ROOT.TTreeFormula("METphi",'METnoPU.phi',tree)
    hJet_MtArray = [array('f',[0]),array('f',[0])]
    hJet_EtArray = [array('f',[0]),array('f',[0])]
    hJet_ptRawArray = [array('f',[0]),array('f',[0])]
    hJet_MET_dPhi = array('f',[0]*2)
    hJet_regWeight = array('f',[0]*2)
    hJet_MET_dPhiArray = [array('f',[0]),array('f',[0])]
    newtree.Branch('hJet_MET_dPhi',hJet_MET_dPhi,'hJet_MET_dPhi[2]/F')
    newtree.Branch('hJet_regWeight',hJet_regWeight,'hJet_regWeight[2]/F')
    readerJet0 = ROOT.TMVA.Reader("!Color:!Silent" )
    readerJet1 = ROOT.TMVA.Reader("!Color:!Silent" )
        
    theForms = {}
    theVars0 = {}
    theVars1 = {}
    def addVarsToReader(reader,theVars,theForms,i,hJet_MET_dPhiArray,METet,rho25,hJet_MtArray,hJet_EtArray,hJet_ptRawArray):
        for key in regVars:
            var = regDict[key]
            theVars[key] = array( 'f', [ 0 ] )
            if var == 'Jet_MET_dPhi':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, hJet_MET_dPhiArray[i] )
            elif var == 'METet':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, METet )
            elif var == 'rho25':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, rho25 )
            elif var == 'Jet_mt':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, hJet_MtArray[i] )
            elif var == 'Jet_et':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, hJet_EtArray[i] )
            elif var == 'Jet_ptRaw':
                print 'Adding var: %s with %s to readerJet%.0f' %(key,var,i)
                reader.AddVariable( key, hJet_ptRawArray[i] )
            else:
                reader.AddVariable(key,theVars[key])
                formula = regDict[key].replace("[0]","[%.0f]" %i)
                print 'Adding var: %s with %s to readerJet%.0f' %(key,formula,i)
                theForms['form_reg_%s_%.0f'%(key,i)] = ROOT.TTreeFormula("form_reg_%s_%.0f"%(key,i),'%s' %(formula),tree)
        return 
    addVarsToReader(readerJet0,theVars0,theForms,0,hJet_MET_dPhiArray,METet,rho25,hJet_MtArray,hJet_EtArray,hJet_ptRawArray)    
    addVarsToReader(readerJet1,theVars1,theForms,1,hJet_MET_dPhiArray,METet,rho25,hJet_MtArray,hJet_EtArray,hJet_ptRawArray)    
    readerJet0.BookMVA( "jet0Regression", regWeight )
    readerJet1.BookMVA( "jet1Regression", regWeight )
    
    
        
    #Add training Flag
    EventForTraining = array('i',[0])
    newtree.Branch('EventForTraining',EventForTraining,'EventForTraining/I')
    EventForTraining[0]=0

    TFlag=ROOT.TTreeFormula("EventForTraining","EVENT.event%2",tree)
        
    if job.type != 'DATA':
        #CSV branches
        hJet_flavour = array('f',[0]*2)
        hJet_csv = array('f',[0]*2)
        hJet_csvOld = array('f',[0]*2)
        hJet_csvUp = array('f',[0]*2)
        hJet_csvDown = array('f',[0]*2)
        hJet_csvFUp = array('f',[0]*2)
        hJet_csvFDown = array('f',[0]*2)
        newtree.Branch('hJet_csvOld',hJet_csvOld,'hJet_csvOld[2]/F')
        newtree.Branch('hJet_csvUp',hJet_csvUp,'hJet_csvUp[2]/F')
        newtree.Branch('hJet_csvDown',hJet_csvDown,'hJet_csvDown[2]/F')
        newtree.Branch('hJet_csvFUp',hJet_csvFUp,'hJet_csvFUp[2]/F')
        newtree.Branch('hJet_csvFDown',hJet_csvFDown,'hJet_csvFDown[2]/F')
        
        #JER branches
        hJet_pt_JER_up = array('f',[0]*2)
        newtree.Branch('hJet_pt_JER_up',hJet_pt_JER_up,'hJet_pt_JER_up[2]/F')
        hJet_pt_JER_down = array('f',[0]*2)
        newtree.Branch('hJet_pt_JER_down',hJet_pt_JER_down,'hJet_pt_JER_down[2]/F')
        hJet_e_JER_up = array('f',[0]*2)
        newtree.Branch('hJet_e_JER_up',hJet_e_JER_up,'hJet_e_JER_up[2]/F')
        hJet_e_JER_down = array('f',[0]*2)
        newtree.Branch('hJet_e_JER_down',hJet_e_JER_down,'hJet_e_JER_down[2]/F')
        H_JER = array('f',[0]*4)
        newtree.Branch('H_JER',H_JER,'mass_up:mass_down:pt_up:pt_down/F')
        
        #JES branches
        hJet_pt_JES_up = array('f',[0]*2)
        newtree.Branch('hJet_pt_JES_up',hJet_pt_JES_up,'hJet_pt_JES_up[2]/F')
        hJet_pt_JES_down = array('f',[0]*2)
        newtree.Branch('hJet_pt_JES_down',hJet_pt_JES_down,'hJet_pt_JES_down[2]/F')
        hJet_e_JES_up = array('f',[0]*2)
        newtree.Branch('hJet_e_JES_up',hJet_e_JES_up,'hJet_e_JES_up[2]/F')
        hJet_e_JES_down = array('f',[0]*2)
        newtree.Branch('hJet_e_JES_down',hJet_e_JES_down,'hJet_e_JES_down[2]/F')
        H_JES = array('f',[0]*4)
        newtree.Branch('H_JES',H_JES,'mass_up:mass_down:pt_up:pt_down/F')
	lheWeight = array('f',[0])
        if job.type != 'DY':
            newtree.Branch('lheWeight',lheWeight,'lheWeight/F')
            lheWeight[0] = 1.
        
        
        #iter=0
        
        
    for entry in range(0,nEntries):
            tree.GetEntry(entry)

            if job.type != 'DATA' and TrainFlag:
                EventForTraining[0]=int(not TFlag.EvalInstance())


            #get
            hJet_pt = tree.hJet_pt
            hJet_e = tree.hJet_e
            hJet_pt0 = tree.hJet_pt[0]
            hJet_pt1 = tree.hJet_pt[1]
            hJet_eta0 = tree.hJet_eta[0]
            hJet_eta1 = tree.hJet_eta[1]
            hJet_genPt0 = tree.hJet_genPt[0]
            hJet_genPt1 = tree.hJet_genPt[1]
            hJet_e0 = tree.hJet_e[0]
            hJet_e1 = tree.hJet_e[1]
            hJet_phi0 = tree.hJet_phi[0]
            hJet_phi1 = tree.hJet_phi[1]
            hJet_JECUnc0 = tree.hJet_JECUnc[0]
            hJet_JECUnc1 = tree.hJet_JECUnc[1]

            Event[0]=fEvent.EvalInstance()
            METet[0]=fMETet.EvalInstance()
            rho25[0]=fRho25.EvalInstance()
            METphi[0]=fMETphi.EvalInstance()
            for key, value in regDict.items():
                if not (value == 'Jet_MET_dPhi' or value == 'METet' or value == "rho25" or value == "Jet_et" or value == 'Jet_mt' or value == 'Jet_ptRaw'):
                    theVars0[key][0] = theForms["form_reg_%s_0" %(key)].EvalInstance()
                    theVars1[key][0] = theForms["form_reg_%s_1" %(key)].EvalInstance()
            for i in range(2):
                hJet_MET_dPhi[i] = deltaPhi(METphi[0],tree.hJet_phi[i])
                hJet_MET_dPhiArray[i][0] = deltaPhi(METphi[0],tree.hJet_phi[i])
                corrRes = 1.
                if not job.type == 'Data':
                   corrRes = corrPt(tree.hJet_pt[i],tree.hJet_eta[i],tree.hJet_genPt[i])
                hJet_ptRawArray[i][0] = tree.hJet_ptRaw[i]*corrRes
            
            
            if applyRegression:
                hJ0.SetPtEtaPhiE(hJet_pt0,hJet_eta0,hJet_phi0,hJet_e0)
                hJ1.SetPtEtaPhiE(hJet_pt1,hJet_eta1,hJet_phi1,hJet_e1)
                HNoReg.HiggsFlag = 1
                HNoReg.mass = (hJ0+hJ1).M()
                HNoReg.pt = (hJ0+hJ1).Pt()
                HNoReg.eta = (hJ0+hJ1).Eta()
                HNoReg.phi = (hJ0+hJ1).Phi()
                HNoReg.dR = hJ0.DeltaR(hJ1)
                HNoReg.dPhi = hJ0.DeltaPhi(hJ1)
                HNoReg.dEta = abs(hJ0.Eta()-hJ1.Eta())
                hJet_MtArray[0][0] = hJ0.Mt()
                hJet_MtArray[1][0] = hJ1.Mt()
                hJet_EtArray[0][0] = hJ0.Et()
                hJet_EtArray[1][0] = hJ1.Et()
                rPt0 = max(0.0001,readerJet0.EvaluateRegression( "jet0Regression" )[0])
                rPt1 = max(0.0001,readerJet1.EvaluateRegression( "jet1Regression" )[0])
                hJet_regWeight[0] = rPt0/hJet_pt0
                hJet_regWeight[1] = rPt1/hJet_pt1
                rE0 = hJet_e0*hJet_regWeight[0]
                rE1 = hJet_e1*hJet_regWeight[1]
                hJ0.SetPtEtaPhiE(rPt0,hJet_eta0,hJet_phi0,rE0)
                hJ1.SetPtEtaPhiE(rPt1,hJet_eta1,hJet_phi1,rE1)
                tree.hJet_pt[0] = rPt0
                tree.hJet_pt[1] = rPt1
                tree.hJet_e[0] = rE0
                tree.hJet_e[1] = rE1
                H.HiggsFlag = 1
                H.mass = (hJ0+hJ1).M()
                H.pt = (hJ0+hJ1).Pt()
                H.eta = (hJ0+hJ1).Eta()
                H.phi = (hJ0+hJ1).Phi()
                H.dR = hJ0.DeltaR(hJ1)
                H.dPhi = hJ0.DeltaPhi(hJ1)
                H.dEta = abs(hJ0.Eta()-hJ1.Eta())
                if hJet_regWeight[0] > 5. or hJet_regWeight[1] > 5.:
                    print 'Event %.0f' %(Event[0])
                    print 'MET %.2f' %(METet[0])
                    print 'rho25 %.2f' %(rho25[0])
                    for key, value in regDict.items():
                        if not (value == 'Jet_MET_dPhi' or value == 'METet' or value == "rho25" or value == "Jet_et" or value == 'Jet_mt' or value == 'Jet_ptRaw'):
                            print '%s 0: %.2f'%(key, theVars0[key][0])
                            print '%s 1: %.2f'%(key, theVars1[key][0])
                    for i in range(2):
                        print 'dPhi %.0f %.2f' %(i,hJet_MET_dPhiArray[i][0])
                    for i in range(2):
                        print 'ptRaw %.0f %.2f' %(i,hJet_ptRawArray[i][0])
                    for i in range(2):
                        print 'Mt %.0f %.2f' %(i,hJet_MtArray[i][0])
                    for i in range(2):
                        print 'Et %.0f %.2f' %(i,hJet_EtArray[i][0])
                    print 'corr 0 %.2f' %(hJet_regWeight[0])
                    print 'corr 1 %.2f' %(hJet_regWeight[1])
                    print 'rPt0 %.2f' %(rPt0)
                    print 'rPt1 %.2f' %(rPt1)
                    print 'rE0 %.2f' %(rE0)
                    print 'rE1 %.2f' %(rE1)
                    print 'Mass %.2f' %(H.mass)
                
            if job.type == 'DATA':
                newtree.Fill()
                continue

            for i in range(2):
                flavour = int(tree.hJet_flavour[i])
                pt = float(tree.hJet_pt[i])
                eta = float(tree.hJet_eta[i])
                csv = float(tree.hJet_csv[i])
                hJet_csvOld[i] = csv 
                if anaTag == '7TeV':
                    tree.hJet_csv[i] = corrCSV(btagNom,csv,flavour)
                    hJet_csvDown[i] = corrCSV(btagDown,csv,flavour)
                    hJet_csvUp[i] = corrCSV(btagUp,csv,flavour) 
                    hJet_csvFDown[i] = corrCSV(btagFDown,csv,flavour)
                    hJet_csvFUp[i] = corrCSV(btagFUp,csv,flavour)
                elif anaTag == '8TeV':
                    tree.hJet_csv[i] = btagNom.reshape(eta,pt,csv,flavour)
                    hJet_csvDown[i] = btagDown.reshape(eta,pt,csv,flavour)
                    hJet_csvUp[i] = btagUp.reshape(eta,pt,csv,flavour) 
                    hJet_csvFDown[i] = btagFDown.reshape(eta,pt,csv,flavour)
                    hJet_csvFUp[i] = btagFUp.reshape(eta,pt,csv,flavour)

            for updown in ['up','down']:
                #JER
                if updown == 'up':
                    inner = 0.06
                    outer = 0.1
                if updown == 'down':
                    inner = -0.06
                    outer = -0.1
                #Calculate
                if abs(hJet_eta0)<1.1: res0 = inner
                else: res0 = outer
                if abs(hJet_eta1)<1.1: res1 = inner
                else: res1 = outer
                rPt0 = hJet_pt0 + (hJet_pt0-hJet_genPt0)*res0
                rPt1 = hJet_pt1 + (hJet_pt1-hJet_genPt1)*res1
                rE0 = hJet_e0*rPt0/hJet_pt0
                rE1 = hJet_e1*rPt1/hJet_pt1
                #if applyRegression:
                #    theVars0['Jet_pt'][0] = rPt0
                #    theVars1['Jet_pt'][0] = rPt1
                #    theVars0['Jet_e'][0] = rE0
                #    theVars1['Jet_e'][0] = rE1
                #    rPt0 = max(0.0001,readerJet0.EvaluateRegression( "jet0Regression" )[0])
                #    rPt1 = max(0.0001,readerJet1.EvaluateRegression( "jet1Regression" )[0])
                #    rE0 = hJet_e0*rPt0/hJet_pt0
                #    rE1 = hJet_e1*rPt1/hJet_pt1
                hJ0.SetPtEtaPhiE(rPt0,hJet_eta0,hJet_phi0,rE0)
                hJ1.SetPtEtaPhiE(rPt1,hJet_eta1,hJet_phi1,rE1)
                #Set
                if updown == 'up':
                    hJet_pt_JER_up[0]=rPt0
                    hJet_pt_JER_up[1]=rPt1
                    hJet_e_JER_up[0]=rE0
                    hJet_e_JER_up[1]=rE1
                    H_JER[0]=(hJ0+hJ1).M()
                    H_JER[2]=(hJ0+hJ1).Pt()
                if updown == 'down':
                    hJet_pt_JER_down[0]=rPt0
                    hJet_pt_JER_down[1]=rPt1
                    hJet_e_JER_down[0]=rE0
                    hJet_e_JER_down[1]=rE1
                    H_JER[1]=(hJ0+hJ1).M()
                    H_JER[3]=(hJ0+hJ1).Pt()
                
                #JES
                if updown == 'up':
                    variation=1
                if updown == 'down':
                    variation=-1
                #calculate
                rPt0 = hJet_pt0*(1+variation*hJet_JECUnc0)
                rPt1 = hJet_pt1*(1+variation*hJet_JECUnc1)
                rE0 = hJet_e0*(1+variation*hJet_JECUnc0)
                rE1 = hJet_e1*(1+variation*hJet_JECUnc1)
                #if applyRegression:
                #    theVars0['Jet_pt'][0] = rPt0
                #    theVars1['Jet_pt'][0] = rPt1
                #    theVars0['Jet_e'][0] = rE0
                #    theVars1['Jet_e'][0] = rE1
                #    rPt0 = max(0.0001,readerJet0.EvaluateRegression( "jet0Regression" )[0])
                #    rPt1 = max(0.0001,readerJet1.EvaluateRegression( "jet1Regression" )[0])
                #    rE0 = hJet_e0*rPt0/hJet_pt0
                #    rE1 = hJet_e1*rPt1/hJet_pt1
                hJ0.SetPtEtaPhiE(rPt0,hJet_eta0,hJet_phi0,rE0)
                hJ1.SetPtEtaPhiE(rPt1,hJet_eta1,hJet_phi1,rE1)
                #Fill
                if updown == 'up':
                    hJet_pt_JES_up[0]=rPt0
                    hJet_pt_JES_up[1]=rPt1
                    hJet_e_JES_up[0]=rE0
                    hJet_e_JES_up[1]=rE1
                    H_JES[0]=(hJ0+hJ1).M()
                    H_JES[2]=(hJ0+hJ1).Pt()
                if updown == 'down':
                    hJet_pt_JES_down[0]=rPt0
                    hJet_pt_JES_down[1]=rPt1
                    hJet_e_JES_down[0]=rE0
                    hJet_e_JES_down[1]=rE1
                    H_JES[1]=(hJ0+hJ1).M()
                    H_JES[3]=(hJ0+hJ1).Pt()
            
            newtree.Fill()
                   
    newtree.AutoSave()
    output.Close()
        
#dump info
#infofile = open(path+'/sys'+'/samples.info','w')
#pickle.dump(info,infofile)
#infofile.close()
