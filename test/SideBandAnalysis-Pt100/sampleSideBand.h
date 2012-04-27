#include "../samples.h"

std::vector<Sample> Nov10SideBand(){
  std::vector<Sample> s;

  Double_t ZeeL;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi,Run2011B_PromptRecoV1Last700pb_Lumi;
  Run2011_May10Rereco_Lumi = 216.607;
  Run2011A_PromptRecoV4_Lumi = 929.748;
  Run2011A_Aug05ReReco_Lumi = 373.216;
  Run2011A_PromptRecoV6_Lumi = 658.886;
  //before 178078
  //  Run2011B_PromptRecoV1_Lumi = 1358;
  //full range
  Run2011B_PromptRecoV1_Lumi = 1790;
  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10NtupleDataFix/");

  std::string ZH("ZH");
  std::string DY("DY");
  std::string DYBOOSTED("DYBOOSTED");  
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  std::string FullRun("FullRun");  
  std::string FullRunEle("FullRunEle");  
  std::string FullRunMu("FullRunMu");  
 
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false )); 
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updatedNewBTAGSF_skimmed", kRed , false ));
/* /\*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed",kYellow ,false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed", kBlue , false )); 
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DoubleElectronSingleMu_Skimmed.root",0 , true, ZeeL ));

  return s;
}

std::vector<Sample> Nov10SideBandHistos(){
  std::vector<Sample> s;
  Double_t ZeeL;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi,Run2011B_PromptRecoV1Last700pb_Lumi;
  Run2011_May10Rereco_Lumi = 216.607;
  Run2011A_PromptRecoV4_Lumi = 929.748;
  Run2011A_Aug05ReReco_Lumi = 373.216;
  Run2011A_PromptRecoV6_Lumi = 658.886;
  //before 178078
  //Run2011B_PromptRecoV1_Lumi = 1358;
  //  full range
  Run2011B_PromptRecoV1_Lumi = 1790;
  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10NtupleDataFix/");
  std::string ZH("ZH");
  std::string DYL("DYL");  
  std::string DYC("DYC");  
  std::string DYB("DYB");
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  std::string FullRun("FullRun");
  std::string FullRunEle("FullRunEle");
  std::string FullRunMu("FullRunMu");
  std::string appendix("sideband");

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+".histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updatedNewBTAGSF_skimmed"+appendix+"_histosB.root",kYellow ,false ));
  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_DiJetPt_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DoubleElectronSingleMu_Skimmed.root"+appendix+".histos.root",0 , true, ZeeL ));

  return s;
}


std::vector<Sample> Nov10Fall1160MTopSlimSideBandHistos(){
  std::vector<Sample> s;

  Double_t ZeeL;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi,Run2011B_PromptRecoV1Last700pb_Lumi;
  Run2011_May10Rereco_Lumi = 216.607;
  Run2011A_PromptRecoV4_Lumi = 929.748;
  Run2011A_Aug05ReReco_Lumi = 373.216;
  Run2011A_PromptRecoV6_Lumi = 658.886;
  //before 178078
  //Run2011B_PromptRecoV1_Lumi = 1358;
  //  full range
  Run2011B_PromptRecoV1_Lumi = 1790;
  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;
/*   std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim_EleIdBug/"); */
/*   std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim_EleIdBug/"); */
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  //  std::string pathData("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11/");
  std::string ZH("ZH");  
  std::string DYL("DYL");  
  std::string DYC("DYC");  
  std::string DYB("DYB");
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  std::string FullRun("FullRun");
  std::string FullRunEle("FullRunEle");
  std::string FullRunMu("FullRunMu");
  std::string appendix("sideband");

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root"+appendix+".histos.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root"+appendix+".histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_DiJetPt_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPU"+appendix+"_histosB.root",kYellow ,false ));

  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root"+appendix+".histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEleFull_V11Again_pt20.root"+appendix+".histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleElectron_full2011Dataset_2.root"+appendix+".histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));


  return s;
}
