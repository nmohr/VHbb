#include "samples.h"


std::vector<Sample> Nov10Fall1160MTopIVFWSVHistos(){
  std::vector<Sample> s;
  //  from Andrea mail
/*   SingleMu,Run2011A_Aug05ReReco,0.373216 */
/*     SingleMu,Run2011A_PromptRecoV4,0.929748 */
/*     SingleMu,Run2011A_PromptRecoV6,0.658886 */
/*     SingleMu,Run2011B_PromptRecoV1,1.79 */
/*     SingleMu,Run2011B_PromptRecoV1_last,0.714626 */
/*     SingleMu,Run2011_May10ReReco,0.208621 */

  Double_t ZeeL;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi,Run2011B_PromptRecoV1Last700pb_Lumi;

  Run2011_May10Rereco_Lumi = 208.621;
  Run2011A_PromptRecoV4_Lumi = 929.748;
  Run2011A_Aug05ReReco_Lumi = 373.216;
  Run2011A_PromptRecoV6_Lumi = 658.886;
  //before 178078
  //  Run2011B_PromptRecoV1_Lumi = 1358;
  //  full range
  Run2011B_PromptRecoV1_Lumi = 1790;
  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  //    Run2011B_PromptRecoV1Last700pb_Lumi = 0.;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;
  std::string path("~/Physics/WSVAnalysis/HBB_EDMNtuple/V11/");
  std::string pathData("~/Physics/WSVAnalysis/HBB_EDMNtuple/V11/");
  std::string ZH("ZH"); 
  std::string DYL("DYL");
  std::string DYC("DYC");
  std::string DYB("DYB");
  std::string DYNoB("DYNoB");
  std::string TTbar("TTbar");
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJL("WJL");
  std::string WJC("WJC");
  std::string WJB("WJB");
  std::string WJNoB("WJNoB");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  std::string FullRun("FullRun");
  std::string FullRunEle("FullRunEle");
  std::string FullRunMu("FullRunMu");

  s.push_back(Sample(165,TTbar,path+"DiJetPt_HBB_EDMNtupleV11_TTJets_TuneZ2_7TeV-madgraph-tauola.root.histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYNoB,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root_histosNoB.root",kYellow-6 ,false ));
/*   s.push_back(Sample(3048,DYL,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(3048,DYC,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosC.root",kYellow-5 ,false )); */
  s.push_back(Sample(3048,DYB,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root_histosB.root",kYellow ,false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_tW-channel-DS_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_tW-channel-DS_7TeV-powheg-tauola.root.histos.root", kCyan , false ));
  s.push_back(Sample(31314,WJNoB,path+"DiJetPt_HBB_EDMNtupleV11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root_histosNoB.root", kGreen, false ));
  s.push_back(Sample(31314,WJB,path+"DiJetPt_HBB_EDMNtupleV11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root_histosB.root", kGreen+3, false ));
  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_HBB_EDMNtupleV11_SingleMu.root.histos.root",0 , true, ZeeL ));

  return s;
}


std::vector<Sample> Nov10Fall1160MTopIVFWSV(){
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
  //  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  Run2011B_PromptRecoV1Last700pb_Lumi = 0.;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;

  std::string path("~/Physics/WSVAnalysis/HBB_EDMNtuple/V11/");
  std::string pathData("~/Physics/WSVAnalysis/HBB_EDMNtuple/V11/");

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

  //  s.push_back(Sample(1,QCD,path+"DiJetPt_HBB_EDMNtupleV11_QCD_Pt-120to170_TuneZ2_7TeV_pythia6.root",kPink,false);
  s.push_back(Sample(3048,DY,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_HBB_EDMNtupleV11_TTJets_TuneZ2_7TeV-madgraph-tauola.root", kBlue , false ));
  s.push_back(Sample(31314,WJ,path+"DiJetPt_HBB_EDMNtupleV11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root", kGreen+3, false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_HBB_EDMNtupleV11_T_TuneZ2_tW-channel-DS_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_HBB_EDMNtupleV11_Tbar_TuneZ2_tW-channel-DS_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_HBB_EDMNtupleV11_SingleMu.root",0 , true, ZeeL ));

  return s;
}


std::vector<Sample> Nov10Fall1160MTopSlimZbbXsecHistos(){
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
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  std::string ZH("ZH");  
  std::string DYL("DYL");  
  std::string DYC("DYC");  
  std::string DYNoB("DYNoB");  
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

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.rootZbbXsec.histos.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.rootZbbXsec.histos.root", 17 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.rootZbbXsec.histos.root", 17 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.rootZbbXsec.histos.root", 17 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.rootZbbXsec.histos.root", kTeal , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.rootZbbXsec.histos.root", kBlue , false ));
  //  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.rootZbbXsec_histosL.root",kYellow-6 ,false ));
  //  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.rootZbbXsec_histosL.root",kYellow-6 ,false ));
  //  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.rootZbbXsec_histosC.root",kYellow-5 ,false ));
  //  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.rootZbbXsec_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYNoB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.rootZbbXsec_histosNoB.root",kYellow-5 ,false ));
  //  s.push_back(Sample(30,DYNoB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.rootZbbXsec_histosNoB.root",kYellow ,false ));
  //  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.rootZbbXsec_histosB.root",kYellow ,false ));
  //  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.rootZbbXsec_histosB.root",kYellow ,false ));
  //Zbb massive bs //13.75 cross section LO, 1.231515 K factor LO->NNLO
  //  s.push_back(Sample(16.93,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_DiJetPt_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPUZbbXsec_histosB.root",kYellow ,false ));
  s.push_back(Sample(16.93,DYB,"~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/DiJetPt_HBB_EDMNtupleV11_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_V5.rootZbbXsec_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.rootZbbXsec.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEleFull_V11Again_pt20.rootZbbXsec.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleElectron_full2011Dataset_2.rootZbbXsec.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}

std::vector<Sample> Nov10Fall1160MTopIVF_forEff(){
  std::vector<Sample> s;

  std::string path("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");
  std::string pathData("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");

  std::string DY("DY");  
  std::string TTbar("TTbar");  
  
  //  s.push_back(Sample(5.9,VV,path+"DiJetPt_HBB_EDMNtupleV11_ZZ_TuneZ2_7TeV_pythia6_tauola.root",kGray , false ));
  s.push_back(Sample(3048,DY,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root",kYellow ,false ));
  //s.push_back(Sample(165,TTbar,path+"DiJetPt_HBB_EDMNtupleV11_TTJets.root", kBlue , false ));

  return s;
}


std::vector<Sample> Nov10Fall1160MTopIVFHistos(){
  std::vector<Sample> s;
  //  from Andrea mail
/*     DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */
  Double_t ZeeL;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi,Run2011B_PromptRecoV1Last700pb_Lumi;
  Run2011_May10Rereco_Lumi = 216.607;
  Run2011A_PromptRecoV4_Lumi = 929.748;
  Run2011A_Aug05ReReco_Lumi = 373.216;
  Run2011A_PromptRecoV6_Lumi = 658.886;
  //before 178078
  //  Run2011B_PromptRecoV1_Lumi = 1358;
  //  full range
  Run2011B_PromptRecoV1_Lumi = 1790;
  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  // Run2011B_PromptRecoV1Last700pb_Lumi = 0.;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;
  std::string path("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");
  std::string pathData("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");
  std::string ZH("ZH");  
  std::string DYL("DYL");  
  std::string DYC("DYC");  
  std::string DYB("DYB");  
  std::string DYNoB("DYNoB");  
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  std::string FullRun("FullRun");
  std::string FullRunEle("FullRunEle");
  std::string FullRunMu("FullRunMu");

  //  s.push_back(Sample(0.3158*0.577*0.03365*3,ZH,path+"DiJetPt_HBB_EDMNtupleV11_ZH_ZToLL_HToBB_M-125.root.histos.root", kRed , false )); 
  s.push_back(Sample(165,TTbar,path+"DiJetPt_HBB_EDMNtupleV11_TTJets.root.histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYNoB,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosNoB.root",kYellow-6 ,false ));
/*   s.push_back(Sample(3048,DYL,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(3048,DYC,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosC.root",kYellow-5 ,false )); */
//  s.push_back(Sample(3048,DYB,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root_histosB.root",kYellow ,false ));
  s.push_back(Sample(16.93,DYB,path+"DiJetPt_HBB_EDMNtupleV11_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_V5.root_histosB.root",kYellow,false));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleEle.root.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleMu.root.histos.root",0 , true, ZeeL ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleMuDoubleEle.root.histos.root",0 , true, ZeeL ));

  return s;
}


std::vector<Sample> Nov10Fall1160MTopIVF(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

/*   DoubleMu,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleMu,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleMu,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleMu,Run2011B_PromptRecoV1,1.79 */
/*     DoubleMu,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleMu,Run2011_May10ReReco,0.216122 */

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
  //  Run2011B_PromptRecoV1Last700pb_Lumi = 715.584;
  Run2011B_PromptRecoV1Last700pb_Lumi = 0.;
  ZeeL=Run2011_May10Rereco_Lumi+Run2011A_PromptRecoV4_Lumi+Run2011A_Aug05ReReco_Lumi+Run2011A_PromptRecoV6_Lumi+Run2011B_PromptRecoV1_Lumi+Run2011B_PromptRecoV1Last700pb_Lumi;

  std::string path("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");
  std::string pathData("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false )); */
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
  
//  s.push_back(Sample(0.3158*0.577*0.03365*3,ZH,path+"DiJetPt_HBB_EDMNtupleV11_ZH_ZToLL_HToBB_M-125.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_HBB_EDMNtupleV11_ZZ_TuneZ2_7TeV_pythia6_tauola.root",kGray , false ));
  s.push_back(Sample(3048,DY,path+"DiJetPt_HBB_EDMNtupleV11_DYJetsToLL.root",kYellow ,false ));
  s.push_back(Sample(13.76,DY,path+"DiJetPt_HBB_EDMNtupleV11_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_V5.root",kYellow,false));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_HBB_EDMNtupleV11_TTJets.root", kBlue , false ));
  //  s.push_back(Sample(31314,WJ,path+"DiJetPt_HBB_EDMNtupleV11_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root", kGreen+3, false ));
  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleEle.root",0 , true, ZeeL ));
  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleMu.root",0 , true, ZeeL ));
  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_HBB_EDMNtupleV11_DoubleMuDoubleEle.root",0 , true, ZeeL ));

/*   s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false )); */

/* /\*   s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false )); *\/ */
/* /\*   s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false )); *\/ */
/*   s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false )); */
/*   s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false )); */
/*   s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false )); */
/*   s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false )); */
/*   s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false )); */
/*   s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false )); */

//  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEleIVF_pt20_ProdV11Again.root",0 , true, ZeeL ));
//  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_DoubleElectron_Run2011_FULL.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleElectron_full2011Dataset_2.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunMu,pathData+"DiJetPt_Data_DoubleMu_full2011Dataset.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root",0 , true, ZeeL ));



  return s;
}


std::vector<Sample> Nov10Fall1160MTopSlimHistos(){
  std::vector<Sample> s;
  //  from Andrea mail
/*     DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */
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

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.histos.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.histos.root", 17 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.histos.root", 17 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.histos.root", 17 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.histos.root", kTeal , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root_histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root_histosB.root",kYellow ,false ));
  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_DiJetPt_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));

  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEleFull_V11Again_pt20.root.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleElectron_full2011Dataset_2.root.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));


  return s;
}

std::vector<Sample> Nov10Fall1160MTopSlim(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  //  std::string pathData("~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false ));
/* /\*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(13.76,DY,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_DiJetPt_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPU",kYellow,false));
  s.push_back(Sample(13.76,DY,"~/Physics/ZSVAnalysis/HBB_EDMNtuple/V11b/DiJetPt_HBB_EDMNtupleV11_ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_V5.root",kYellow,false));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root", kBlue , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root",0 , true, ZeeL ));
//  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEleFull_V11Again_pt20.root",0 , true, ZeeL ));
  //  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleEle_full2011Dataset_pt20.root",0 , true, ZeeL ));
//  s.push_back(Sample(1000,FullRunEle,pathData+"DiJetPt_Data_DoubleElectron_full2011Dataset_2.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root", kGreen+3, false ));

  return s;
}

std::vector<Sample> Nov10thDiJetPtUpdatedFall11Slim_EleIdBug(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim_EleIdBug/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim_EleIdBug/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false ));
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root", kBlue , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdatedFall11OKSlim(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Fall1160MTopSlim/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false ));
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root", kBlue , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdatedFall11OK(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updated", kBlue , false ));
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.updated",0 , true, ZeeL ));
  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdatedFall11Histos(){
  std::vector<Sample> s;
  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */
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
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thFall11Fixed/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");
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
  //  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kGray , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kGray , false ));
/*   s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kOrange+2 , false )); */
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  //  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  //  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated.histos.root", kAzure , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated_histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.updated.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdatedFall11(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thFall11Fixed/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));

  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));

  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  //  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));

  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  //  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  //  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.updated",0 , true, ZeeL ));

  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}



std::vector<Sample> testSample(){
  std::vector<Sample> s;

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

  std::string ZH("ZH");  
  std::string DY("DY");  
  std::string DYBOOSTED("DYBOOSTED");  
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10th/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10th/DiJetPt/");

  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));


  return s;
}

std::vector<Sample> Nov10thDiJetPtUpdatedSlimHistos(){
  std::vector<Sample> s;
  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */
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
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");
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
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated.histos.root", kBlue , false ));
/*   s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kOrange+2 , false )); */
/*   s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kOrange+2 , false )); */
/*   s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated.histos.root",kOrange+2 , false )); */
  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated.histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated.histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated.histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated.histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated.histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated.histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated.histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.updated.histos.root",0 , true, ZeeL ));
  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdatedSlim(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10thSlim/DiJetPt/");

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
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root.updated", kBlue , false ));
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));

  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));

  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));

  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  

  s.push_back(Sample(1000,FullRun,pathData+"DiJetPt_DataZee.root.updated",0 , true, ZeeL ));


  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> Nov10thDiJetPtUpdated(){
  std::vector<Sample> s;

  //from Andrea mail
  /*   DoubleElectron,Run2011A_Aug05ReReco,0.373216 */
/*     DoubleElectron,Run2011A_PromptRecoV4,0.929748 */
/*     DoubleElectron,Run2011A_PromptRecoV6,0.658886 */
/*     DoubleElectron,Run2011B_PromptRecoV1,1.79 */
/*     DoubleElectron,Run2011B_PromptRecoV1_last,0.715584 */
/*     DoubleElectron,Run2011_May10ReReco,0.21607 */

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

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10th/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10th/DiJetPt/");

  std::string ZH("ZH");  
  std::string DY("DY");  
  std::string DYBOOSTED("DYBOOSTED");  
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false ));
/*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));

  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));

  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));

  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV4.root",0 , true, Run2011A_PromptRecoV4_Lumi));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_Aug05ReReco.root",0 , true, Run2011A_Aug05ReReco_Lumi ));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV6.root",0 , true, Run2011A_PromptRecoV6_Lumi ));

  s.push_back(Sample(1000,Run2011B,pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1.root",0 , true, Run2011B_PromptRecoV1_Lumi ));
  s.push_back(Sample(1000,Run2011B,pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1_Last700pb.root",0 , true, Run2011B_PromptRecoV1Last700pb_Lumi ));

  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}



std::vector<Sample> Nov1stDiJetPt(){
  std::vector<Sample> s;
  Double_t ZeeL=215.094+930.228+370.915+662.967;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi;
  Run2011_May10Rereco_Lumi = 215.094;
  Run2011A_PromptRecoV4_Lumi = 925.660;
  Run2011A_Aug05ReReco_Lumi = 370.915;
  Run2011A_PromptRecoV6_Lumi = 653.973;
  //before 178078
  Run2011B_PromptRecoV1_Lumi = 1358;
  //full range
  //Run2011B_PromptRecoV1_Lumi = 1755;

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct30th/DiJetPt/");

  std::string DY("DY");  
  std::string DYBOOSTED("DYBOOSTED");  
  std::string TTbar("TTbar");  
  std::string VV("VV");  
  std::string ST("ST");
  std::string WJ("WJ");
  std::string Run2011A("Run2011A");  
  std::string Run2011B("Run2011B");  

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false ));
 
  s.push_back(Sample(3048,DY,path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_Fall11.root",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_Fall11.root",kYellow ,false ));

  s.push_back(Sample(165,TTbar,path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola_Fall11.root", kBlue , false ));

  s.push_back(Sample(5.9,VV,path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola_Fall11.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));

  s.push_back(Sample(3.19,ST,path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  
  s.push_back(Sample(1.44,ST,path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  
  //  s.push_back(Sample(31314,WJ,path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_Fall11.root", kGreen+3, false ));

  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV4.root",0 , true, Run2011A_PromptRecoV4_Lumi));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_Aug05ReReco.root",0 , true, Run2011A_Aug05ReReco_Lumi ));
  s.push_back(Sample(1000,Run2011A,pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV6.root",0 , true, Run2011A_PromptRecoV6_Lumi ));

  s.push_back(Sample(1000,Run2011B,pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1.root",0 , true, Run2011B_PromptRecoV1_Lumi ));


  return s;
}

std::vector<Sample> Nov1stDiJetPtUpdated(){
  std::vector<Sample> s;
  Double_t ZeeL=215.094+930.228+370.915+662.967;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi;
  Run2011_May10Rereco_Lumi = 215.094;
  Run2011A_PromptRecoV4_Lumi = 925.660;
  Run2011A_Aug05ReReco_Lumi = 370.915;
  Run2011A_PromptRecoV6_Lumi = 653.973;
  //before 178078
  Run2011B_PromptRecoV1_Lumi = 1358;
  //full range
  //Run2011B_PromptRecoV1_Lumi = 1755;

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct30th/DiJetPt/");
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
  s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false ));
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,"DY",path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,"DYBOOSTED",path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));

  s.push_back(Sample(165,"TTbar",path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));

  s.push_back(Sample(5.9,"VV",path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,"VV",path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(43,"VV",path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));

  s.push_back(Sample(3.19,"ST",path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(41.92,"ST",path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1.44,"ST",path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,"ST",path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV4.root",0 , true, Run2011A_PromptRecoV4_Lumi));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_Aug05ReReco.root",0 , true, Run2011A_Aug05ReReco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV6.root",0 , true, Run2011A_PromptRecoV6_Lumi ));

  s.push_back(Sample(1000,"Run2011B",pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1.root",0 , true, Run2011B_PromptRecoV1_Lumi ));

  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> samples()
{
  std::vector<Sample> s;

  Double_t ZeeL=215.094+930.228+370.915+662.967;
  //  ZeeL=1143;

  std::string path("/data1/VHbbAnalysis/EDMNtuple_step2/V9/oct9Ntuple/histos/");
  std::string pathData("/data1/VHbbAnalysis/EDMNtuple_step2/V9/oct7Ntuple/histos/");
  // s.push_back(Sample(1000,"data","SingleMu_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root",0 , true,219));
  // s.push_back(Sample(1000,"data","SingleMu_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root",0 , true,789));
  s.push_back(Sample(1000,"data",pathData+"TestDoubleElectron_Run2010-2011A_merged_histos.root",0 , true,ZeeL ));
  // s.push_back(Sample(1000,"data",pathData+"TestDoubleElectron_Run2011A_PromptRecoV4_histos.root",0 , true,930.228 ));

  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root", 0, true ,235.22));
  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root",1 , true,814.5 ));
  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_merge_histos.root",1 , true,235.22 + 814.8));

  // s.push_back(Sample(1000,"data","DoubleMu_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root", 1, true, 500.159));

  // s.push_back(Sample(1000,"data","METBTag_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root", 1, true,235));
  // s.push_back(Sample(1000,"data","MET_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root", 1, true,784.12));


  s.push_back(Sample(165,"TTbar",path+"TestTTJets_TuneZ2_7TeV-madgraph-tauola_histos.root", kBlue , false ));

  int stcolor=kTeal;

  /* // s.push_back(Sample(1.44,"Single Top","Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_HBB_EDMNtupleV1_ProcV2_CandV1_histos.root", stcolor, false )); */
  /*  s.push_back(Sample(22.65,"Single Top",path+"TestTbar_TuneZ2_t-channel_7TeV-powheg-tauola_histos.root", stcolor, false )); */
  /*  s.push_back(Sample(7.87,"Single Top",path+"TestTbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_histos.root", stcolor, false)); */
  /* //s.push_back(Sample(7.87,"Single Top",path+"TestTbar_TuneZ2_tW-channel-DS_7TeV-powheg-tauola_HBB_EDMNtupleV1_ProcV2_CandV1_histos.root", stcolor, false)); */
  /*  s.push_back(Sample(7.87,"Single Top",path+"TestT_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_histos.root", stcolor, false)); */

  float wxsec= 31314.;
  float wxsec100= 31314./27770.*194.6;
  //TOT: 18904365 b: 363441 c: 6264682 l: 12276242
  float t=18904365;
  float b=363441;
  float c=6264682;
  float l=12276242;
 
  s.push_back(Sample(wxsec,"Wb",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosB.root", kGreen+3, false ));
  s.push_back(Sample(wxsec,"Wc",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosC.root", kGreen+3, false ));
  s.push_back(Sample(wxsec,"Wl",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosL.root", kGreen+3, false ));


  float zxsecMG=2045;
  s.push_back(Sample(3048,"Zb",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosB.root",kYellow ,false ));
  s.push_back(Sample(3048,"Zc",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,"Zl",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosL.root",kYellow-6 ,false ));

  /*  s.push_back(Sample(24,"Zb",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosB.root",kYellow ,false )); */
  /*  s.push_back(Sample(24,"Zc",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosC.root",kYellow-5 ,false )); */
  /*  s.push_back(Sample(24,"Zl",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosL.root",kYellow-6 ,false )); */
 
  s.push_back(Sample(42.9,"VV",path+"TestWW_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,"VV",path+"TestWZ_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));
  s.push_back(Sample(5.9,"VV",path+"TestZZ_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));

  // s.push_back(Sample((0.4107*0.704*0.03365*3),"ZH","TestZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_histos.root",kAzure,false ));

  return s;
}
