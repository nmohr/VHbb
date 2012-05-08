#!/usr/bin/env python
from samplesinfo import sample
from printcolor import printc
import pickle
import sys
import os
import ROOT 
import shutil
from ROOT import TFile
import ROOT
from array import array


#usage: ./write_systematic.py path


path=sys.argv[1]

#load info
infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()
os.mkdir(path+'/sys')

for job in info:
    if job.type != 'DATA':
        print '\t - %s' %(job.name)

        input = TFile.Open(job.getpath(),'read')
        output = TFile.Open(job.path+'/sys/'+job.prefix+job.identifier+'.root','recreate')

        input.cd()
        obj = ROOT.TObject
        for key in ROOT.gDirectory.GetListOfKeys():
            input.cd()
            obj = key.ReadObj()
            print obj.GetName()
            if obj.GetName() == job.tree:
                continue
            output.cd()
            print key.GetName()
            obj.Write(key.GetName())

        tree = input.Get(job.tree)
        nEntries = tree.GetEntries()
        job.addpath('/sys')
        output.cd()
        newtree = tree.CloneTree(0)


        '''
        input = TFile.Open(job.getpath(),'read')
        Count = input.Get("Count")
        CountWithPU = input.Get("CountWithPU")
        CountWithPU2011B = input.Get("CountWithPU2011B")
        tree = input.Get(job.tree)
        nEntries = tree.GetEntries()
        
        job.addpath('/sys')
        output = ROOT.TFile(job.getpath(), 'RECREATE')
        newtree = tree.CloneTree(0)
        '''
        job.SYS = ['Nominal','JER_up','JER_down','JES_up','JES_down','beff_up','beff_down','bmis_up','bmis_down']
        
        hJ0 = ROOT.TLorentzVector()
        hJ1 = ROOT.TLorentzVector()
          
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
        
        #Add training Flag
        EventForTraining = array('f',[0])
        newtree.Branch('EventForTraining',EventForTraining,'EventForTraining/F')
        
        iter=0
        
        for entry in range(0,nEntries):
            tree.GetEntry(entry)

            #fill training flag 
            iter+=1
            if (iter%2==0):
                EventForTraining[0]=1
            else:
                EventForTraining[0]=0

            #get
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
        #newtree.Write()            
        #Count.Write()
        #CountWithPU.Write()
        #CountWithPU2011B.Write()
        output.Close()

    else: #(is data)
    
        shutil.copy(job.getpath(),path+'/sys')
        job.addpath('/sys')

#dump info
infofile = open(path+'/sys'+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()