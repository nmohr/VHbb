#include "../../interface/samples.hpp"

std::vector<Sample> trees(){
  std::vector<Sample> s;

  Double_t Lumi=530;

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
 
  //  s.push_back(Sample(225.197,TTbar,path+"ZllH.Jun01.TTJets_TuneZ2Star_8TeV-madgraph-tauola.root", kBlue , false ));
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); */
//  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kRed , false ));
/* /\*   s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
 
  s.push_back(Sample(2950.0 * 1.188,DY,path+"ZllH.Jun01.DYJetsToLL_TuneZ2Star_M-50_8TeV-madgraph-tauola.root",kYellow ,false ));
  s.push_back(Sample(52.31 * 1.188,DYBOOSTED,path+"ZllH.May30.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tauola.root",kYellow ,false ));
  //  s.push_back(Sample(30,DYBOOSTED,path+"ZllH.Jun01.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root",kYellow ,false ));
  //  s.push_back(Sample(5.9,VV,path+"ZllH.Jun01.ZZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(5.9,VV,path+"ZllH.Jun01.ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"ZllH.Jun01.WZ_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"ZllH.Jun01.WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));
/*   s.push_back(Sample(3.19,ST,path+"ZllH.Jun01.T_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false )); */
  s.push_back(Sample(41.92,ST,path+"ZllH.Jun01.T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.Jun01.T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"ZllH.Jun01.Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root", kBlue , false ));
  /*   s.push_back(Sample(22.65,ST,path+"ZllH.Jun01.Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false )); */
  s.push_back(Sample(7.87,ST,path+"ZllH.Jun01.Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));  
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.Jun01.DataZ.root",0 , true, Lumi ));

  return s;
}

std::vector<Sample> histos(){
  std::vector<Sample> s;

  Double_t Lumi = 530;

/*   std::string path("./SideBandAnalysis-Pt50To100/histos/"); */
/*   std::string pathData("./SideBandAnalysis-Pt50To100/histos/"); */
  std::string path("./histos/");
  std::string pathData("./histos/");
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

/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.Jun01.ZH_ZToLL_HToBB_M-115_8TeV-powheg-herwigpp.root"+appendix+".histos.root", kRed , false )); */
/*   s.push_back(Sample(5.9,VV,path+"ZllH.Jun01.ZZ_TuneZ2Star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false )); */
/*   s.push_back(Sample(18.3,VV,path+"ZllH.Jun01.WZ_TuneZ2Star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false )); */
/*   //  s.push_back(Sample(43,VV,path+"ZllH.Jun01.WW_TuneZ2Star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false )); */
/*   s.push_back(Sample(3.19,ST,path+"ZllH.Jun01.T_TuneZ2Star_s-channel_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
/*   s.push_back(Sample(41.92,ST,path+"ZllH.Jun01.T_TuneZ2Star_t-channel_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
/*   s.push_back(Sample(7.87,ST,path+"ZllH.Jun01.T_TuneZ2Star_tW-channel-DR_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
/*   s.push_back(Sample(1.44,ST,path+"ZllH.Jun01.Tbar_TuneZ2Star_s-channel_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
/*   s.push_back(Sample(22.65,ST,path+"ZllH.Jun01.Tbar_TuneZ2Star_t-channel_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
/*   s.push_back(Sample(7.87,ST,path+"ZllH.Jun01.Tbar_TuneZ2Star_tW-channel-DR_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
  s.push_back(Sample(225.197,TTbar,path+"ZllH.Jun01.TTJets_TuneZ2Star_8TeV-madgraph-tauola.root"+appendix+".histos.root", kBlue , false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.Jun01.DYJetsToLL_TuneZ2Star_M-50_8TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  //  s.push_back(Sample(30,DYL,path+"ZllH.Jun01.DYJetsToLL_PtZ-100_TuneZ2Star_8TeV-madgraph-tauola.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.Jun01.DYJetsToLL_TuneZ2Star_M-50_8TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  //  s.push_back(Sample(30,DYC,path+"ZllH.Jun01.DYJetsToLL_PtZ-100_TuneZ2Star_8TeV-madgraph-tauola.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.Jun01.DYJetsToLL_TuneZ2Star_M-50_8TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  //  s.push_back(Sample(30,DYB,path+"ZllH.Jun01.DYJetsToLL_PtZ-100_TuneZ2Star_8TeV-madgraph-tauola.root"+appendix+"_histosB.root",kYellow ,false ));
  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_ZllH.Jun01.ZbbToLL_M-50_TuneZ2Star_8TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.Jun01.DataZ.root"+appendix+".histos.root",0 , true, Lumi ));

  return s;
}
