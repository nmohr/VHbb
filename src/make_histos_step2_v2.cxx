#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <iostream>
#include "CutsAndHistos.h"
#include "Histos.h"
//#include "Cuts200X.h"
#include "CutsNov11.h"
#include "CutsForIVF.h"
#include "CutsForZbbXsec.h"
#include "CutsForSystematics.h"
#include "ntupleReader.h"
#include "sampleCollection.h"

void prepareAllZHistos(std::vector<CutsAndHistos *> & allHistosZ,TFile *fout  )
{
  std::string Zee115("ZH115");
  std::cout << "Book Z" << std::endl;
  allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZee,new StandardHistos));
  // //  allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZee,new StandardHistos));
  //   //  allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZee,new StandardHistos));
  //   //  allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new SignalRegionHZee,new StandardHistos));
  //   //  allHistosZ.push_back(new CutsAndHistos(new SignalRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new BDTRegionHZee,new StandardHistos));
  //   //  allHistosZ.push_back(new CutsAndHistos(new BDTRegionHZee,new MVAHistos(Zee115)));
  allHistosZ.push_back(new CutsAndHistos(new BDTZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTZlightControlRegionHZee,new StandardHistos));
  //systematics jec
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPZlightControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNZlightControlRegionHZee,new StandardHistos));
  //systematics btag
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPZlightControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNZlightControlRegionHZee,new StandardHistos));
  //mistag
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPZlightControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNZbbControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNTTbarControlRegionHZee,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNZlightControlRegionHZee,new StandardHistos));

  //systematics jec
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecUPZlightControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystJecDOWNZlightControlRegionHZee,new SystematicsHistos));
  //systematics btag
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagUPZlightControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagDOWNZlightControlRegionHZee,new SystematicsHistos));
  //mistag
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFUPZlightControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNZbbControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNTTbarControlRegionHZee,new SystematicsHistos));
  allHistosZ.push_back(new CutsAndHistos(new BDTSystBtagFDOWNZlightControlRegionHZee,new SystematicsHistos));


  //ZSV
//   allHistosZ.push_back(new CutsAndHistos(new ZSVRegionZeeSV,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new ZSVRegionZmmSV,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new ZSVRegionZcombSV,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new ZSVTTbarPureRegionZcombSV,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new ZSVPureRegionZcombSV,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new TTbarRegionZeeSVJets,new IVFHistos));

//WSV
//   allHistosZ.push_back(new CutsAndHistos(new WSVRegionHWmnu,new IVFHistos));
//   allHistosZ.push_back(new CutsAndHistos(new WbbRegionHWmnu,new StandardHistos));
//   allHistosZ.push_back(new CutsAndHistos(new SingleTopRegionHWmnu,new StandardHistos));

//for the Zbb cross section measurement
//   allHistosZ.push_back(new CutsAndHistos(new ZbbXsecRegionHZee,new StandardHistos));
//   allHistosZ.push_back(new CutsAndHistos(new ZbbXsecLightRegionHZee,new StandardHistos));

//ZZ dileptons
//  allHistosZ.push_back(new CutsAndHistos(new ZZRegionZee,new ZZHistos));


  for(size_t a=0;a < allHistosZ.size(); a++)
    {
      allHistosZ[a]->book(*fout);
    }
}


int main(int argc, char **argv)
{
  std::cout << "Hello word" << std::endl;

  bool verbose_ = true;
  bool stitching = true;
  //  std::string file_appendix = "ZbbXsec";
  std::string file_appendix = "";

  double fa = 0.46502;
  double fb = 0.53498;
  Double_t eventWeight=0;
  int event_all=0;
  int event_all_b=0;
  int event_all_nob=0;
  int event_all_c=0;
  int event_all_l=0;

  std::vector<Sample> samples =  Nov10Fall1160MTopSlim();
  //  std::vector<Sample> samples =  Nov10Fall1160MTopIVF();
  //std::vector<Sample> samples =  Nov10Fall1160MTopIVFWSV();
  //std::vector<Sample> samples =  Nov10Fall1160MTopIVFUpdated();

  //loop over all the samples
  for(unsigned int iS=0; iS<samples.size(); ++iS){

    std::string name = samples.at(iS).filename;
    samples.at(iS).dump(1,fa,fb);

    std::cout << "is data = " << samples.at(iS).data << std::endl; 
    //if appendix is needed
    name+=file_appendix;

    bool splitBCLIGHT=true;
    bool data=true;

    if(samples.at(iS).data) { data=true; splitBCLIGHT=false;}
    else{ data=false; splitBCLIGHT=true;}
  
    //  mkdir("./Histograms",755);

    if(verbose_)
      std::cout << "opening the output file" << std::endl;
    TFile *fout = new TFile((name+".histos.root").c_str(),"RECREATE");
    if(verbose_)
      std::cout << "Creating the histograms" << std::endl;
    TH1F * countAll = new TH1F("Count","Count",1,0,2);
    TH1F * countAllWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
    TH1F * countAllWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);

    if(verbose_)
      std::cout << "Preparing the Z histos" << std::endl;
    std::vector<CutsAndHistos *> allHistosZ;
    prepareAllZHistos(allHistosZ,fout);

    if(verbose_)
      std::cout << "Preparing the plitted histos" << std::endl;
    std::vector<CutsAndHistos *> allHistosBZ;
    std::vector<CutsAndHistos *> allHistosNoBZ;
    std::vector<CutsAndHistos *> allHistosCZ;
    std::vector<CutsAndHistos *> allHistosLZ;
    TFile *foutB,*foutNoB,*foutC,*foutL;
    TH1F *countB, *countBWithPU,*countNoB, *countNoBWithPU,*countC, *countCWithPU,*countL, *countLWithPU;
    TH1F *countBWithPU2011B,*countNoBWithPU2011B, *countCWithPU2011B, *countLWithPU2011B;

    if(splitBCLIGHT)
      {
	std::cout << "Enabling split" << std::endl;
	foutB = new TFile((name+"_histosB.root").c_str(),"RECREATE");
	countB = new TH1F("Count","Count",1,0,2);
	countBWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countBWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutNoB = new TFile((name+"_histosNoB.root").c_str(),"RECREATE");
	countNoB = new TH1F("Count","Count",1,0,2);
	countNoBWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countNoBWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutC = new TFile((name+"_histosC.root").c_str(),"RECREATE");
	countC = new TH1F("Count","Count",1,0,2);
	countCWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countCWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutL = new TFile((name+"_histosL.root").c_str(),"RECREATE");
	countL = new TH1F("Count","Count",1,0,2);
	countLWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countLWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	prepareAllZHistos(allHistosBZ,foutB);
	prepareAllZHistos(allHistosNoBZ,foutNoB);
	prepareAllZHistos(allHistosCZ,foutC);
	prepareAllZHistos(allHistosLZ,foutL);

      }

    std::string inputFile = samples.at(iS).filename;
    std::cout << "Start processing " << inputFile  << " files" << std::endl;

    // open input file (can be located on castor)
    TFile* f = TFile::Open(inputFile.c_str());
    if(f==0){
      std::cerr << "File not found " << std::endl;
      std::cerr << "Please check the path of this file " << inputFile << std::endl;
      return -1;
    }

    std::cout << "File succesfully opened" << std::endl;

    if(!data){
      if(verbose_)
	std::cout << "Adding coutn histograms" << std::endl;
      countAll->Add((TH1F*)f->Get("Count"));
      countAllWithPU->Add((TH1F*)f->Get("CountWithPU"));
      countAllWithPU2011B->Add((TH1F*)f->Get("CountWithPU2011B"));
      countB->Add((TH1F*)f->Get("Count"));
      countBWithPU->Add((TH1F*)f->Get("CountWithPU"));
      countBWithPU2011B->Add((TH1F*)f->Get("CountWithPU2011B"));
      countNoB->Add((TH1F*)f->Get("Count"));
      countNoBWithPU->Add((TH1F*)f->Get("CountWithPU"));
      countNoBWithPU2011B->Add((TH1F*)f->Get("CountWithPU2011B"));
      countC->Add((TH1F*)f->Get("Count"));
      countCWithPU->Add((TH1F*)f->Get("CountWithPU"));
      countCWithPU2011B->Add((TH1F*)f->Get("CountWithPU2011B"));
      countL->Add((TH1F*)f->Get("Count"));
      countLWithPU->Add((TH1F*)f->Get("CountWithPU"));
      countLWithPU2011B->Add((TH1F*)f->Get("CountWithPU2011B"));
    }
    if(verbose_){
      std::cout << "Count: " << countAll->GetBinContent(1) <<  std::endl;
      std::cout << "Count: " << countAll->GetEffectiveEntries() <<  std::endl;
      std::cout << "CountWithPU: " << countAllWithPU->GetEntries() <<  std::endl;
      std::cout << "CountWithPU: " << countAllWithPU->GetEffectiveEntries() <<  std::endl;
      std::cout << "CountWithPU2011B: " << countAllWithPU2011B->GetEffectiveEntries() <<  std::endl;
    }

    ntupleReader event(inputFile.c_str());
    Long64_t  entries  = event.fChain->GetEntriesFast();
    //Loop on all events of this file
    if(verbose_)
      std::cout << "Start looping" << std::endl;
    for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
      event.GetEntry(iEvent);
      event_all++;
      if(data == false)
	eventWeight = (fa*event.PUweight+fb*event.PUweight2011B)*event.weightTrig;
      else
	eventWeight = 1;

      if(splitBCLIGHT){
	if( TMath::Abs(event.eventFlav) != 5 ){
	  event_all_b++;
	  for(size_t a=0;a < allHistosNoBZ.size(); a++) 
	    if(stitching)
	      allHistosNoBZ[a]->process(event,eventWeight,samples.at(iS));
	    else
	      allHistosNoBZ[a]->process(event,eventWeight);
	}
	if( TMath::Abs(event.eventFlav) == 5 ){
	  event_all_nob++;
	  for(size_t a=0;a < allHistosBZ.size(); a++) 
	    if(stitching)
	      allHistosBZ[a]->process(event,eventWeight,samples.at(iS));
	    else
	      allHistosBZ[a]->process(event,eventWeight);
	}
	else if( TMath::Abs(event.eventFlav) == 4 ){
	  event_all_c++;
	  for(size_t a=0;a < allHistosCZ.size(); a++)   
	    if(stitching)
	      allHistosCZ[a]->process(event,eventWeight,samples.at(iS));
	    else
	      allHistosCZ[a]->process(event,eventWeight);
	} else {
	  event_all_l++;
	  for(size_t a=0;a < allHistosLZ.size(); a++)
	    if(stitching)
	      allHistosLZ[a]->process(event,eventWeight,samples.at(iS));	  
	    else
	      allHistosLZ[a]->process(event,eventWeight);
	}
      }
    
      for(size_t a=0;a < allHistosZ.size(); a++)
	{
	  if(stitching)
	    allHistosZ[a]->process(event,eventWeight,samples.at(iS));
	  else
	    allHistosZ[a]->process(event,eventWeight);
	}
    
    }
    
    fout->Write();
    fout->Close();
  
    if(splitBCLIGHT){
      foutNoB->Write();
      foutNoB->Close();

      foutB->Write();
      foutB->Close();
    
      foutC->Write();
      foutC->Close();
    
      foutL->Write();
      foutL->Close();   
    }

    f->Close();

    std::cout << "TOT: " << event_all << " b: " << event_all_b << " c: "<<  event_all_c <<" l: " << event_all_l <<" noB : " << event_all_nob  <<  std::endl;

  }  
  return 0;
}
