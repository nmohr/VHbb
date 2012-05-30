#include "../../interface/samples.hpp"

std::vector<Sample> trees(){
  std::vector<Sample> s;

  Double_t Lumi=4980;

  std::string path("./SideBandAnalysis-Pt50To100/histos/");
  std::string pathData("./SideBandAnalysis-Pt50To100/histos/");

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
 
  s.push_back(Sample(165,TTbar,path+"ZllH.May23.TTJets_TuneZ2_7TeV-madgraph-tauola.root", kBlue , false ));
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kRed , false ));
/* /\*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
 
  s.push_back(Sample(3048,DY,path+"ZllH.May23.DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(30,DYBOOSTED,path+"ZllH.May23.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(5.9,VV,path+"ZllH.May23.ZZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"ZllH.May23.WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  //  s.push_back(Sample(43,VV,path+"ZllH.May23.WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"ZllH.May23.T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"ZllH.May23.T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.May23.T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"ZllH.May23.Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"ZllH.May23.Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.May23.Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false )); 
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.May23.DataZ.root",0 , true, Lumi ));

  return s;
}

std::vector<Sample> histos(){
  std::vector<Sample> s;

  Double_t Lumi = 4980;

  std::string path("./SideBandAnalysis-Pt50To100/histos/");
  std::string pathData("./SideBandAnalysis-Pt50To100/histos/");
/*   std::string path("./histos/"); */
/*   std::string pathData("./histos/"); */
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
  std::string appendix("SideBand-Pt50To100");

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.May23.ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root"+appendix+".histos.root", kRed , false ));
  s.push_back(Sample(5.9,VV,path+"ZllH.May23.ZZ_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(18.3,VV,path+"ZllH.May23.WZ_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  //  s.push_back(Sample(43,VV,path+"ZllH.May23.WW_TuneZ2_7TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(3.19,ST,path+"ZllH.May23.T_TuneZ2_s-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(41.92,ST,path+"ZllH.May23.T_TuneZ2_t-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.May23.T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(1.44,ST,path+"ZllH.May23.Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(22.65,ST,path+"ZllH.May23.Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.May23.Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(165,TTbar,path+"ZllH.May23.TTJets_TuneZ2_7TeV-madgraph-tauola.root"+appendix+".histos.root", kBlue , false ));
  s.push_back(Sample(3048,DYL,path+"ZllH.May23.DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(30,DYL,path+"ZllH.May23.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(3048,DYC,path+"ZllH.May23.DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(30,DYC,path+"ZllH.May23.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,DYB,path+"ZllH.May23.DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(30,DYB,path+"ZllH.May23.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_ZllH.May23.ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.May23.DataZ.root"+appendix+".histos.root",0 , true, Lumi ));

  return s;
}
