#include "../../interface/samples.hpp"

std::vector<Sample> trees(){
  std::vector<Sample> s;

  Double_t Lumi=1;

  bool usePathLocal = false;

//from Storage
  std::string path;
  std::string pathRemote("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/HBB_EDMNtuple/V42/Oct5/env/sys/MVAout/");
  std::string pathLocal("./SideBandAnalysis-Pt50To100/histos/");
  //  std::string version("Oct1");


  if( usePathLocal )
    path = pathLocal;
  else
    path = pathRemote;

  std::string version("Oct5");


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
 


  //Background
  //  s.push_back(Sample(225.197,TTbar,path+"ZllH.DiJetPt."+version+".TTJets_TuneZ2star_8TeV-madgraph-tauola.root", kBlue , false ));
  s.push_back(Sample(234,TTbar,path+"ZllH.DiJetPt."+version+".TTJets_Merged.root", kBlue , false )); 
  
  //   s.push_back(Sample(2950.0 * 1.188,DY,path+"withHistosZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root",kYellow ,false ));
  
  s.push_back(Sample(2950.0 * 1.188,DY,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root",kYellow ,false ));

  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root",kYellow ,false ));
  s.push_back(Sample(1.,DY,path+"ZllH.DiJetPt."+version+".DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root",kYellow ,false ));

  s.push_back(Sample(5.9,VV,path+"ZllH.DiJetPt."+version+".ZZ_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  //  s.push_back(Sample(5.9,VV,path+"ZllH.DiJetPt."+version+".ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,VV,path+"ZllH.DiJetPt."+version+".WZ_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(43,VV,path+"ZllH.DiJetPt."+version+".WW_TuneZ2star_8TeV_pythia6_tauola.root",kOrange+2 , false ));
  s.push_back(Sample(3.19,ST,path+"ZllH.DiJetPt."+version+".T_s-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(41.92,ST,path+"ZllH.DiJetPt."+version+".T_t-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.DiJetPt."+version+".T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(1.44,ST,path+"ZllH.DiJetPt."+version+".Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(22.65,ST,path+"ZllH.DiJetPt."+version+".Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,ST,path+"ZllH.DiJetPt."+version+".Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root", kBlue , false ));

  s.push_back(Sample(1000,FullRun,path+"ZllH.DiJetPt."+version+".DataZ.root",0 , true, Lumi ));
  //  s.push_back(Sample(1000,FullRun,path+"ZllH.DiJetPt."+version+".DataZee.root",0 , true, Lumi ));
  //  s.push_back(Sample(1000,FullRun,path+"ZllH.DiJetPt."+version+".DataZmm.root",0 , true, Lumi ));

  return s;
}

std::vector<Sample> histos(){
  std::vector<Sample> s;

  //  Double_t Lumi = 2880.+700.+1500.;///692.972+2825.; //2.88+0.7
  //ichep 5353.45
  //  Double_t Lumi = 5353.45;

  //  Double_t Lumi = 670.444+0.+3742.0+4751.0+379.447+490.881; // with wrong json (Michele/Prompt)
  //  Double_t Lumi = 943.378+97.078+3742.0+4751.0+379.447+490.881; // without json before run 190949, otherwise Michele/Prompt json applied
  //  Double_t Lumi = 12020;///olny muons


  Double_t Lumi = 12100;  //for Oct5

  //for fit the scale factor:
/*   std::string path("./SideBandAnalysis-Pt50To100/noBTagReshape/"); */
/*   std::string pathData("./SideBandAnalysis-Pt50To100/noBTagReshape/"); */



  std::string version("Oct5");

  std::string path("./SideBandAnalysis-Pt50To100/histos/");
  std::string pathData("./SideBandAnalysis-Pt50To100/histos/");
/*   std::string path("./SideBandAnalysis-Pt50To100/histos_hcp/"); */
/*   std::string pathData("./SideBandAnalysis-Pt50To100/histos_hcp/"); */
/*   std::string path("./SideBandAnalysis-Pt50To100/noRegHistos/"); */
/*   std::string pathData("./SideBandAnalysis-Pt50To100/noRegHistos/"); */
/*   std::string path("./SideBandAnalysis-Pt50To100/histos_ichep12/"); */
/*   std::string pathData("./SideBandAnalysis-Pt50To100/histos_ichep12/"); */

//for plotting:
/*   std::string path("./histos/"); */
/*   std::string pathData("./histos/"); */
/*   std::string path("./noRegHistos/"); */
/*   std::string pathData("./noRegHistos/"); */

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
  //std::string appendix("SideBand-Pt50To100");
  //  std::string appendix("SideBand-Pt50To100_noTriggerWeights");
  std::string appendix("SideBand-Pt50To100_pt30GeV");
  //  std::string appendix("SideBand-Pt50To100_lowBtag");

  double xSec_ZZ_MCFM = 8.25561;
  double BR_ZToLL = 0.03658*3;
  double BR_ZToQQ = 0.6991;

/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"ZllH.DiJetPt."+version+".ZH_ZToLL_HToBB_M-115_8TeV-powheg-herwigpp.root"+appendix+".histos.root", kRed , false )); */
  s.push_back(Sample(xSec_ZZ_MCFM,VV,path+"ZllH.DiJetPt."+version+".ZZ_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(32.3161,VV,path+"ZllH.DiJetPt."+version+".WZ_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(57.1097,VV,path+"ZllH.DiJetPt."+version+".WW_TuneZ2star_8TeV_pythia6_tauola.root"+appendix+".histos.root", 17 , false ));
  s.push_back(Sample(1.76,ST,path+"ZllH.DiJetPt."+version+".T_s-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(30.7,ST,path+"ZllH.DiJetPt."+version+".T_t-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false )); 
  s.push_back(Sample(11.1,ST,path+"ZllH.DiJetPt."+version+".T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(3.79,ST,path+"ZllH.DiJetPt."+version+".Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(56.4,ST,path+"ZllH.DiJetPt."+version+".Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  s.push_back(Sample(11.1,ST,path+"ZllH.DiJetPt."+version+".Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root"+appendix+".histos.root", kTeal , false ));
  //  s.push_back(Sample(234,TTbar,path+"ZllH.DiJetPt."+version+".TTJets_TuneZ2star_8TeV-madgraph-tauola.root"+appendix+".histos.root", kBlue , false ));
  s.push_back(Sample(234,TTbar,path+"ZllH.DiJetPt."+version+".TTJets_Merged.root"+appendix+".histos.root", kBlue , false ));

  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false ));
  s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false ));

  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false ));

  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false ));
  s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false ));


  //without lheWeight
/*   s.push_back(Sample(2950*1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(93.8 * 1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(52.31 * 1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosL.root",kYellow-6 ,false )); */
/*   s.push_back(Sample(34.1 * 1.188,DYL,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosL.root",kYellow-6 ,false )); */

/*   s.push_back(Sample(2950*1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false )); */
/*   s.push_back(Sample(93.8 * 1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false )); */
/*   s.push_back(Sample(52.31 * 1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosC.root",kYellow-5 ,false )); */
/*   s.push_back(Sample(34.1 * 1.188,DYC,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosC.root",kYellow-5 ,false )); */

/*   s.push_back(Sample(2950*1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false )); */
/*   s.push_back(Sample(93.8 * 1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false )); */
/*   s.push_back(Sample(52.31 * 1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root"+appendix+"_histosB.root",kYellow ,false )); */
/*   s.push_back(Sample(34.1 * 1.188,DYB,path+"ZllH.DiJetPt."+version+".DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root"+appendix+"_histosB.root",kYellow ,false )); */


  //Zbb massive bs
  //  s.push_back(Sample(13.75,DYB,"~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov10Ntuple_PUFix_Fall11_2011AandB_OK/Updated_.ZbbToLL_M-50_TuneZ2Star_8TeV-madgraph-pythia6_tauola.root.updatedPU_histosB.root",kYellow ,false ));

  //Data
  s.push_back(Sample(1000,FullRun,pathData+"ZllH.DiJetPt."+version+".DataZ.root"+appendix+".histos.root",0 , true, Lumi ));
  //  s.push_back(Sample(1000,FullRun,pathData+"ZllH.DiJetPt."+version+".DataZee.root"+appendix+".histos.root",0 , true, Lumi ));
  //  s.push_back(Sample(1000,FullRun,pathData+"ZllH.DiJetPt."+version+".DataZmm.root"+appendix+".histos.root",0 , true, Lumi ));

  return s;
}
