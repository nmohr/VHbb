#ifndef CUTSSIDEBAND_MJJ_H
#define CUTSSIDEBAND_MJJ_H
#include "../../interface/CutsAndHistos.h"
#include "../../interface/ntupleReader.hpp"
#include <TH1F.h>
#include <sstream>
#include "../../interface/samples.hpp"
//to change: put qualityCuts, etc... in some more general header file
#include "CutsSideBand-Pt50To100.h"
#include "TKey.h"

#define CSVM 0.679
#define CSVC 0.5 //custom btag
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498


bool mjj_preselection( ntupleReader & p, int jec,int  btag){
  return(  p.hJet_PT(0,jec) > 20.  
	   && p.hJet_PT(1,jec) > 20. 
	   && TMath::Max( p.hJet_CSV(0,btag) , p.hJet_CSV(1,btag) ) > CSVT
	   && TMath::Min( p.hJet_CSV(0,btag) , p.hJet_CSV(1,btag) ) > CSVC
	   && p.V_pt > 100. 
	   && p.Higgs(jec).M() < 250.
	   && TMath::Abs(p.Higgs(jec).DeltaPhi(p.VectorBoson())) > 2.9
	   && p.CountAddJets() < 2 
	   && qualityCuts( p ) );

};

class SideBandRegion_Mjj: public CutSample{
 public:
  SideBandRegion_Mjj(int ch_= -1, int jec_= 0 , int btag_ = 0):
    ch(ch_),jec(jec_),btag(btag_){ baseName = "SideBandRegion_Mjj"; };
  Bool_t pass(ntupleReader &p){
    return ( mjj_preselection(p,jec,btag)   
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && ( p.Higgs(jec).M() < 80.
		  || p.Higgs(jec).M() > 150. ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) == true && channel( p, ch, sample ) );
  }
  double weight(ntupleReader &p, Sample &sample) { return w( p, sample); }

 private:
  std::string name(){ return( generateName(baseName, ch, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;
  int ch;

};

class SignalRegion_Mjj: public CutSample{
 public:
  SignalRegion_Mjj( int ch_= -1,int jec_= 0 , int btag_ = 0):
    ch(ch_),jec(jec_),btag(btag_){ baseName = "SignalRegion_Mjj"; };
  Bool_t pass(ntupleReader &p){
    return ( mjj_preselection(p,jec,btag)   
	     && p.V_mass > 75. 
	     && p.V_mass < 105 );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) == true && channel( p, ch, sample ) );
  }
  double weight(ntupleReader &p, Sample &sample) { return w( p, sample); }

 private:
  std::string name(){ return( generateName(baseName, ch, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;
  int ch;
};

class TTbarRegion_Mjj: public CutSample{
 public:
  TTbarRegion_Mjj(int ch_= -1, int jec_ = 0, int btag_ = 0):
    ch(ch_),jec(jec_), btag(btag_) { baseName = "TTbarRegion_Mjj"; };
  Bool_t pass(ntupleReader &p){
    return ( mjj_preselection(p,jec,btag)   
	     && p.V_mass > 50. 
	     && ( p.V_mass > 105.
		  || p.V_mass < 75. ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) == true && pass( p ) == true && channel( p, ch, sample ) );
  }
  double weight(ntupleReader &p, Sample &sample) { return w( p, sample); }

 private:
  std::string name() {return generateName(baseName, ch, btag, jec);};
  std::string baseName;
  int btag;
  int jec;
  int ch;
};

#endif
