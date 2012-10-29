#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <iostream>
#include "../interface/CutsAndHistos.h"
#include "../plugins/Histos.h"
#include "../plugins/Cuts/CutsMjj.h"
#include "../plugins/Cuts/CutsExtra.h"
#include "../interface/ntupleReader.hpp"
#include "../interface/samples.hpp"


std::vector<Sample> trees( std::string &sample_name, std::string & sample_type , bool &usePathLocal ){
  std::vector<Sample> s;

  Double_t Lumi=1;
//from Storage
  std::string path;
  std::string pathRemote("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/HBB_EDMNtuple/V42/Oct22/env/sys/MVAout/");
  std::string pathLocal("./histos/");

  if( usePathLocal )
    path = pathLocal;
  else
    path = pathRemote;

  std::string version("Oct22");
  std::string data("data");
  
  s.push_back(Sample(1,sample_type ,path+"ZllH.DiJetPt."+version+"."+sample_name, 0 , false ));
  if(sample_type == data)
    s.push_back(Sample(1,sample_type,path+"ZllH.DiJetPt."+version+"."+sample_name, 0 , true ));
 
  return s;
}




void prepareAllZHistos(std::vector<CutsAndHistos *> & allHistosZ,TFile *fout  )
{
  std::string Zee115("ZH115");
  std::cout << "Book Z" << std::endl;

  //  int channel = 1;
  int jec [] = { -2, -1, 1, 2 };
  int btag [] = { -2, -1, 0, 1, 2 };

  int channel = -1;

  allHistosZ.push_back(new CutsAndHistos(new SideBandRegion_Mjj( channel, 0, 0 ),new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new TTbarRegion_Mjj( channel, 0, 0 ),new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new SignalRegion_Mjj( channel, 0, 0 ),new StandardHistos));

  //run over all the channels
  //  for(int channel = -1; channel < 2; ++channel){
    //Btag histos
    //    allHistosZ.push_back(new CutsAndHistos(new BDTSideBandRegion_noBTag( channel, 0, 0 ),new BTagHistos));
    //Standard histos
//     allHistosZ.push_back(new CutsAndHistos(new BDTTTbarControlRegion_Pt100_lowBtag( channel, 0, 0 ),new StandardHistos));
//     //    allHistosZ.push_back(new CutsAndHistos(new BDTZlightControlRegion( channel, 0 , 0 ),new StandardHistos));
//     allHistosZ.push_back(new CutsAndHistos(new BDTSideBandRegion_Pt100_lowBtag( channel, 0, 0 ),new StandardHistos));
//     allHistosZ.push_back(new CutsAndHistos(new BDTSignalRegion_Pt100_lowBtag( channel, 0, 0 ),new StandardHistos));
    //allHistosZ.push_back(new CutsAndHistos(new BDTTrainingRegion( channel, 0, 0 ),new StandardHistos));
    //    allHistosZ.push_back(new CutsAndHistos(new BDTZbbControlRegion( channel, 0, 0 ),new StandardHistos));

    //Systematics histos
    //    allHistosZ.push_back(new CutsAndHistos(new BDTTTbarControlRegion( channel, 0, 0 ),new SystematicsHistos));
    //  allHistosZ.push_back(new CutsAndHistos(new BDTZlightControlRegion( channel, 0 , 0 ),new SystematicsHistos));
    //allHistosZ.push_back(new CutsAndHistos(new BDTSideBandRegion( channel, 0, 0 ),new SystematicsHistos));
    //    allHistosZ.push_back(new CutsAndHistos(new BDTTrainingRegion( channel, 0, 0 ),new SystematicsHistos));
    //  allHistosZ.push_back(new CutsAndHistos(new BDTZbbControlRegion( channel, 0, 0 ),new SystematicsHistos));        

//     for(int j=0; j<4; ++j){ // jec systematics
//       //Standard histos
//       allHistosZ.push_back(new CutsAndHistos(new BDTSignalRegion( channel, jec[j], 0 ),new StandardHistos));
//       //Systematics histos
//       allHistosZ.push_back(new CutsAndHistos(new BDTSignalRegion( channel, jec[j], 0 ),new SystematicsHistos));
//       allHistosZ.push_back(new CutsAndHistos(new BDTSideBandRegion( channel, jec[j], 0 ),new SystematicsHistos));
//     }
//     for( int b=0; b<5; ++b){ //btag systematics + no systematics ( [0,0] bin )  
//       //Standard histos
//       allHistosZ.push_back(new CutsAndHistos(new BDTSignalRegion( channel, 0, btag[b] ),new StandardHistos));
//       //Systematics histos
//       allHistosZ.push_back(new CutsAndHistos(new BDTSignalRegion( channel, 0, btag[b] ),new SystematicsHistos));
//     }
    
//  }

  for(size_t a=0;a < allHistosZ.size(); a++)
    {
      allHistosZ[a]->book(*fout);
    }
}


int main(int argc, char **argv)
{

  if(argc < 3)
    {
      std::cout << "Usage:\n  make_histo_parallel [sample_name] [sample_type]" << std::endl;
      exit(1);
    }


  std::cout << "Hello word" << std::endl;

  //////// CONFIGURATION - START   ///////

  bool verbose_ = false;
  bool usePathLocal = false;
  //switch on the sample-dependent cuts and weights
  bool stitching = true; // let it always on!
  //run range where to apply the json. Needed for V42_V4a
  float run_min = 196532;
  //  float run_min = 0;
  float run_max = 1e10;
  std::string file_appendix = "HightPt_Mjj";

  //////// CONFIGURATION - END     ///////



  Double_t eventWeight=0;
  int event_all=0;
  int event_all_b=0;
  int event_all_nob=0;
  int event_all_c=0;
  int event_all_l=0;


  std::string sample_name(argv[1]);
  std::string sample_type(argv[2]);
  std::vector<Sample> samples = trees( sample_name, sample_type, usePathLocal );

  //loop over all the samples
  for(unsigned int iS=0; iS<samples.size(); ++iS){

    std::string name = samples.at(iS).filename;
    samples.at(iS).dump(1);

    std::cout << "is data = " << samples.at(iS).data << std::endl; 
    //if appendix is needed
    name+=file_appendix;

    bool splitBCLIGHT=true;
    bool data=true;

    if(samples.at(iS).data) { data=true; splitBCLIGHT=false;}
    else{ data=false; splitBCLIGHT=true;}
 

    if(verbose_)
      std::cout << "opening the output file" << std::endl;

    //output file name. Check if come fin from storage. If so change the path to local
    std::string fout_name = name;
    if(!usePathLocal){
      size_t found = fout_name.find_last_of("/");
      fout_name = std::string("./histos/") + fout_name.substr(found+1);
    }
    
    std::cout << "Output file name : " << fout_name << std::endl;
    //create output file
    TFile *fout = new TFile((fout_name+".histos.root").c_str(),"RECREATE");
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
	foutB = new TFile((fout_name+"_histosB.root").c_str(),"RECREATE");
	countB = new TH1F("Count","Count",1,0,2);
	countBWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countBWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutNoB = new TFile((fout_name+"_histosNoB.root").c_str(),"RECREATE");
	countNoB = new TH1F("Count","Count",1,0,2);
	countNoBWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countNoBWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutC = new TFile((fout_name+"_histosC.root").c_str(),"RECREATE");
	countC = new TH1F("Count","Count",1,0,2);
	countCWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
	countCWithPU2011B =  new TH1F("CountWithPU2011B","CountWithPU2011B",1,0,2);
	foutL = new TFile((fout_name+"_histosL.root").c_str(),"RECREATE");
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
      if(data == false){
	eventWeight = (event.PUweight)*event.weightTrig2012;
	//	if( event.Vtype == 1 )
	  //	  eventWeight *= 1.01763; // from luminosity difference
	//	  eventWeight *= 1.; // from luminosity difference
      }
      else{
	eventWeight = 1;
	if( ( event.EVENT_run > run_min
	      && event.EVENT_run < run_max )
	    && event.EVENT_json == false )
	  continue;
      }


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
