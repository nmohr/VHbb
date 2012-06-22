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
 



//  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kRed , false ));
/* /\*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */
/* /\*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root", kBlue , false )); *\/ */

//fromhere
  s.push_back(Sample(1.*1.*0.03365*3,ZH,path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-110_8TeV-powheg-herwigpp.root", kBlue , false ));
  s.push_back(Sample(1.*0.648*0.03365*3,ZH,path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-120_8TeV-powheg-herwigpp.root", kBlue , false ));
  s.push_back(Sample(225.197,TTbar,path+"ZllH.Jun18.TTJets_TuneZ2star_8TeV-madgraph-tauola.root", kBlue , false ));

  s.push_back(Sample(2950.0 * 1.188,DY,path+"withHistosZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root",kYellow ,false ));

/*   s.push_back(Sample(2950.0 * 1.188,DY,path+"withHistosZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root",kYellow ,false )); */
  s.push_back(Sample(1.,DY,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root",kYellow ,false ));
  s.push_back(Sample(5.9,VV,path+"ZllH.Jun18.ZZ_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  //  s.push_back(Sample(5.9,VV,path+"ZllH.Jun18.ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"ZllH.Jun18.WZ_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"ZllH.Jun18.WW_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"ZllH.Jun18.T_s-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
/*   s.push_back(Sample(41.92,ST,path+"ZllH.Jun18.T_TuneZ2star_t-channel_8TeV-powheg-tauola.root", kBlue , false )); */
  s.push_back(Sample(7.87,ST,path+"ZllH.Jun18.T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"ZllH.Jun18.Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"ZllH.Jun18.Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.Jun18.Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.Jun18.DataZ.root",0 , true, Lumi ));

  return s;
}

std::vector<Sample> histos(){
  std::vector<Sample> s;

  Double_t Lumi = 692.972+2825.; //2.88+0.7
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

  double xSec_ZZ_MCFM = 8.25561;
  double BR_ZToLL = 0.03658*3;
  double BR_ZToQQ = 0.6991;

/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.Jun18.ZH_ZToLL_HToBB_M-115_8TeV-powheg-herwigpp.root"+appendix+".histos.root", kRed , false )); */
  s.push_back(Sample(xSec_ZZ_MCFM,VV,path+"ZllH.Jun18.ZZ_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(32.3161,VV,path+"ZllH.Jun18.WZ_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(57.1097,VV,path+"ZllH.Jun18.WW_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(1.76,ST,path+"ZllH.Jun18.T_s-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); 
  /*   s.push_back(Sample(30.7,ST,path+"ZllH.Jun18.T_t-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); */
  s.push_back(Sample(11.1,ST,path+"ZllH.Jun18.T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); 
  s.push_back(Sample(3.79,ST,path+"ZllH.Jun18.Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); 
  s.push_back(Sample(56.4,ST,path+"ZllH.Jun18.Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(11.1,ST,path+"ZllH.Jun18.Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(225.197,TTbar,path+"ZllH.Jun18.TTJets_TuneZ2star_8TeV-madgraph-tauola.root"+appendix+".histos.root", kBlue , false ));

/*   s.push_back(Sample(2950*1.188,DYL,path+"ZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(2950*1.188,DYC,path+"ZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false )); */
/*   s.push_back(Sample(2950*1.188,DYB,path+"ZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false )); */

  s.push_back(Sample(2950*1.188,DYL,path+"withHistosZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(93.8 * 1.188,DYL,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(52.31 * 1.188,DYL,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(34.1 * 1.188,DYL,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false ));

  s.push_back(Sample(2950*1.188,DYC,path+"withHistosZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(93.8 * 1.188,DYC,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(52.31 * 1.188,DYC,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(34.1 * 1.188,DYC,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false ));

  s.push_back(Sample(2950*1.188,DYB,path+"withHistosZllH.Jun18.DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(93.8 * 1.188,DYB,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(52.31 * 1.188,DYB,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(34.1 * 1.188,DYB,path+"withHistosZllH.Jun18.DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false ));


  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_.ZbbToLL_M-50_TuneZ2Star_8TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.Jun18.DataZ.root"+appendix+".histos.root",0 , true, Lumi ));

  return s;
}
