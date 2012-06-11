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
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )


#usage: ./write_regression_systematic.py path

path=sys.argv[1]

#load info
infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()
#os.mkdir(path+'/sys')

def deltaPhi(phi1, phi2): 
    result = phi1 - phi2
    while (result > math.pi): result -= 2*math.pi
    while (result <= -math.pi): result += 2*math.pi
    return result

def corrCSV(btag,  csv, flav):
    if(csv < 0.): return csv
    if(csv > 1.): return csv;
    if(flav == 0): return csv;
    if(math.fabs(flav) == 5): return  btag.ib.Eval(csv)
    if(math.fabs(flav) == 4): return  btag.ic.Eval(csv)
    if(math.fabs(flav) != 4  and math.fabs(flav) != 5): return  btag.il.Eval(csv)
    return -10000


for job in info:
    #print job.name
    #if job.name != 'ZH125': continue
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
    ROOT.gROOT.LoadMacro('../interface/btagshape.h+')
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
    
    print '\t - %s' %(job.name)
    input = TFile.Open(job.getpath(),'read')
    output = TFile.Open(job.path+'/sys/'+job.prefix+job.identifier+'.root','recreate')

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
        
    regWeight = "../data/MVA_BDT_REG_May23.weights.xml"
    regDict = {"Jet_pt": "hJet_pt", "Jet_eta": "hJet_eta", "Jet_e": "hJet_e", "Jet_JECUnc": "hJet_JECUnc", "Jet_chf": "hJet_chf","Jet_nconstituents": "hJet_nconstituents", "Jet_vtxPt": "hJet_vtxPt", "Jet_vtx3dL": "hJet_vtx3dL", "Jet_vtx3deL": "hJet_vtx3deL"}
    regVars = ["Jet_pt","Jet_eta","Jet_e","Jet_JECUnc", "Jet_chf","Jet_nconstituents", "Jet_vtxPt", "Jet_vtx3dL", "Jet_vtx3deL"]
        
          
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
    hJet_MET_dPhi = array('f',[0]*2)
    hJet_regWeight = array('f',[0]*2)
    hJet_MET_dPhiArray = [array('f',[0]),array('f',[0])]
    newtree.Branch('hJet_MET_dPhi',hJet_MET_dPhi,'hJet_MET_dPhi[2]/F')
    newtree.Branch('hJet_regWeight',hJet_regWeight,'hJet_regWeight[2]/F')
    readerJet0 = ROOT.TMVA.Reader("!Color:!Silent" )
    readerJet1 = ROOT.TMVA.Reader("!Color:!Silent" )
        
    theForms = {}
    theVars0 = {}
    for var in regVars:
        theVars0[var] = array( 'f', [ 0 ] )
        readerJet0.AddVariable(var,theVars0[var])
        theForms['form_reg_%s_0'%(regDict[var])] = ROOT.TTreeFormula("form_reg_%s_0"%(regDict[var]),'%s[0]' %(regDict[var]),tree)
    readerJet0.AddVariable( "Jet_MET_dPhi", hJet_MET_dPhiArray[0] )
    readerJet0.AddVariable( "METet", METet )
    readerJet0.AddVariable( "rho25", rho25 )
        
    theVars1 = {}
    for var in regVars:
        theVars1[var] = array( 'f', [ 0 ] )
        readerJet1.AddVariable(var,theVars1[var])
        theForms['form_reg_%s_1'%(regDict[var])] = ROOT.TTreeFormula("form_reg_%s_1"%(regDict[var]),'%s[1]' %(regDict[var]),tree)
    readerJet1.AddVariable( "Jet_MET_dPhi", hJet_MET_dPhiArray[1] )
    readerJet1.AddVariable( "METet", METet )
    readerJet1.AddVariable( "rho25", rho25 )
    readerJet0.BookMVA( "jet0Regression",  regWeight );
    readerJet1.BookMVA( "jet1Regression", regWeight );
        
    #Add training Flag
    EventForTraining = array('f',[0])
    newtree.Branch('EventForTraining',EventForTraining,'EventForTraining/F')
    EventForTraining[0]=0

    lheWeight = array('f',[0])
    newtree.Branch('lheWeight',lheWeight,'lheWeight/F')
    lheWeight[0] = 1.

    #EventForTraining=0
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
        
        
        #iter=0
        
        
    for entry in range(0,nEntries):
            tree.GetEntry(entry)

            #fill training flag 
            #iter+=1
            #if (iter%2==0):
            #    EventForTraining[0]=1
            #else:
            #    EventForTraining[0]=0
            #iter+=1
            
#            if job.type != 'DATA':
#                EventForTraining=int(not TFlag.EvalInstance())
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
                theVars0[key][0] = theForms["form_reg_%s_0" %(value)].EvalInstance()
                theVars1[key][0] = theForms["form_reg_%s_1" %(value)].EvalInstance()
            for i in range(2):
                hJet_MET_dPhi[i] = deltaPhi(METphi[0],tree.hJet_phi[i])
                hJet_MET_dPhiArray[i][0] = deltaPhi(METphi[0],tree.hJet_phi[i])
            
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
                rPt0 = readerJet0.EvaluateRegression( "jet0Regression" )[0]
                rPt1 = readerJet1.EvaluateRegression( "jet1Regression" )[0]
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
                    print 'MET %.2f' %(METet[0])
                    print 'rho25 %.2f' %(rho25[0])
                    for key, value in regDict.items():
                        print '%s 0: %.2f'%(key, theVars0[key][0])
                        print '%s 0: %.2f'%(key, theVars1[key][0])
                    for i in range(2):
                        print 'dPhi %.0f %.2f' %(i,hJet_MET_dPhiArray[i][0])
                    print 'corr 0 %.2f' %(hJet_regWeight[0])
                    print 'corr 1 %.2f' %(hJet_regWeight[1])
                    print 'Event %.0f' %(Event[0])
                    print 'rPt0 %.2f' %(rPt0)
                    print 'rPt1 %.2f' %(rPt1)
                    print 'rE0 %.2f' %(rE0)
                    print 'rE1 %.2f' %(rE1)
                    print 'Mass %.2f' %(H.mass)
                
            if job.type == 'DATA':
                newtree.Fill()
                continue

            for i in range(2):
                flavour = tree.hJet_flavour[i]
                csv = tree.hJet_csv[i]
                hJet_csvOld[i] = csv 
                tree.hJet_csv[i] = corrCSV(btagNom,csv,flavour)
                hJet_csvDown[i] = corrCSV(btagDown,csv,flavour)
                hJet_csvUp[i] = corrCSV(btagUp,csv,flavour) 
                hJet_csvFDown[i] = corrCSV(btagFDown,csv,flavour)
                hJet_csvFUp[i] = corrCSV(btagFUp,csv,flavour)

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
                if applyRegression:
                    theVars0['Jet_pt'][0] = rPt0
                    theVars1['Jet_pt'][0] = rPt1
                    theVars0['Jet_e'][0] = rE0
                    theVars1['Jet_e'][0] = rE1
                    rPt0 = readerJet0.EvaluateRegression( "jet0Regression" )[0]
                    rPt1 = readerJet1.EvaluateRegression( "jet1Regression" )[0]
                    rE0 = hJet_e0*rPt0/hJet_pt0
                    rE1 = hJet_e1*rPt1/hJet_pt1
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
                if applyRegression:
                    theVars0['Jet_pt'][0] = rPt0
                    theVars1['Jet_pt'][0] = rPt1
                    theVars0['Jet_e'][0] = rE0
                    theVars1['Jet_e'][0] = rE1
                    rPt0 = readerJet0.EvaluateRegression( "jet0Regression" )[0]
                    rPt1 = readerJet1.EvaluateRegression( "jet1Regression" )[0]
                    rE0 = hJet_e0*rPt0/hJet_pt0
                    rE1 = hJet_e1*rPt1/hJet_pt1
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
infofile = open(path+'/sys'+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()
