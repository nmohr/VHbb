#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <iostream>
#include "CutsAndHistos.h"
#include "Histos.h"
#include "Cuts.h"
#include "TF1.h"
#include "TH1.h"
#include "samples.h"
#include "ntupleReader.h"
#include "sampleCollection.h"
#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "setTDRStyle.C"
#include "controlRegions.h"

#define ZeeL 4683.5
#define fA 0.46502
#define fB 0.53498

int main(int argc, char **argv)
{
  
  typedef std::vector<Sample> samplesCollection;
  setTDRStyle();
  bool verbose_ = true;
  TCanvas * c1 = new TCanvas("c1","c1", 600,600);
  TH1D * h = new TH1D("h","h",30,0,300);
  CutSample *PreSelZee = new PreSelectionZee;
  PCutSet signalRegionCutFlow;

  signalRegionCutFlow.add( new EmptyCut );
  signalRegionCutFlow.add( new VMassCutMin(75.) );
  signalRegionCutFlow.add( new VMassCutMax(105.) );
  signalRegionCutFlow.add( new JetPtCut(20.) );
  signalRegionCutFlow.add( new HPtCut(100.) );
  signalRegionCutFlow.add( new VPtCut(100.) );
  signalRegionCutFlow.add( new JetBtagCut(0.5, 0.898) );
  signalRegionCutFlow.add( new HVdPhiCut(2.9) );
  signalRegionCutFlow.add( new JetVeto(2) );
  signalRegionCutFlow.add( new HMassCut(100.) );
  signalRegionCutFlow.add( new HMassCutMax(130.) );

  samplesCollection samples = Nov10thDiJetPtUpdatedFall11OKSlim();
  std::vector< controlRegion > cutFlowCR;

  for(int i=0; i<signalRegionCutFlow.size(); ++i){
    cutFlowCR.push_back( controlRegion(ZeeL,fA,fB) );
    cutFlowCR.at(i).init();
  }

  for(size_t iS = 0; iS < samples.size(); ++iS ){
    
    samples.at(iS).dump(1);
    
    TFile* f = samples.at(iS).file();
    if(f==0){
      std::cerr << "File not found " << std::endl;
      std::cerr << "Please check the path of this file " << samples.at(iS).filename << std::endl;
      return -1;
    }
    
    ntupleReader event(samples.at(iS).filename.c_str());
    bool trigger = true;
    Long64_t  entries  = event.fChain->GetEntriesFast();
    //Loop on all events of this file
    for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
      event.GetEntry(iEvent);

      //to speed up the loop
      if( event.Vtype != 1 )
	continue;      

      //cut flow loop
      for(int i=0; i<signalRegionCutFlow.size(); ++i){
	cutFlowCR.at(i).fill( samples.at(iS), *PreSelZee, signalRegionCutFlow , i+1 , event );
      }

    }
        
  }

  for(int i=0; i<signalRegionCutFlow.size(); ++i){
    std::string cutFlowName = "";
    cutFlowName += signalRegionCutFlow.getCut(i)->name() + " " ;
    std::cout << " ---  Cut Flow " << cutFlowName << " --- " << std::endl;
    std::cout << "DYL = " << cutFlowCR.at(i).cDYL() << " +- " << cutFlowCR.at(i).eDYL() << std::endl;
    std::cout << "DYB = " << cutFlowCR.at(i).cDYB() << " +- " << cutFlowCR.at(i).eDYB() << std::endl;
    std::cout << "TTbar = " << cutFlowCR.at(i).cTTbar() << " +- " << cutFlowCR.at(i).eTTbar() << std::endl;
    std::cout << "VV = " << cutFlowCR.at(i).cVV() << " +- " << cutFlowCR.at(i).eVV() << std::endl;
    std::cout << "ST = " << cutFlowCR.at(i).cST() << " +- " << cutFlowCR.at(i).eST() << std::endl;
    std::cout << "WJETS = " << cutFlowCR.at(i).cWJETS() << " +- " << cutFlowCR.at(i).eWJETS() << std::endl;
    std::cout << "Others = " << cutFlowCR.at(i).cOthers() << " +- " << cutFlowCR.at(i).eOthers() << std::endl;
    std::cout << "Signal = " << cutFlowCR.at(i).cSignal() << " +- " << cutFlowCR.at(i).eSignal() << std::endl;
    std::cout << "Total = " << cutFlowCR.at(i).cTotal() << " +- " << cutFlowCR.at(i).eTotal() << std::endl;
    std::cout << "Data = " << cutFlowCR.at(i).cData() << " +- " << cutFlowCR.at(i).eData() << std::endl;
    
  }
  

  return 0;
}
