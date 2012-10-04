#ifndef CUTSEXTRAS_H
#define CUTSEXTRAS_H
#include "../../interface/CutsAndHistos.h"
#include "../../interface/ntupleReader.hpp"
#include <TH1F.h>
#include <sstream>
#include "../../interface/samples.hpp"
#include "TKey.h"
#include "CutsSideBand-Pt50To100.h"

#define CSVM 0.679
#define CSVC 0.5 //custom btag
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498

// New implementations of the control region
// The signal regions must be implemented incrementally since cutflow is needed


class BDTSideBandRegion_noBTag: public CutSample{
 public:
  BDTSideBandRegion_noBTag(int ch_= -1, int jec_= 0 , int btag_ = 0):
    ch(ch_),jec(jec_),btag(btag_){ baseName = "BDTSideBandRegion_noBTag"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20.  
	     && p.hJet_PT(1,jec) > 20. 
	     //Loose-Custom : ONLY FOR THE FIT for Scale Factors 
/* 	     && ( p.hJet_CSV(0,btag) > CSVC  */
/* 		  || p.hJet_CSV(1,btag) > CSVC ) */
	     //	     && p.Higgs(jec).Pt() > 100. 
	     && p.V_pt < 100. 
	     && p.V_pt > 50. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && ( p.Higgs(jec).M() < 80.
		  || p.Higgs(jec).M() > 150. )
	     //sanity check
	     //	     && p.Higgs(jec).M() > 50.
	     && p.Higgs(jec).M() < 250.
	     //	     && p.CountAddJets() < 2 
	     && qualityCuts( p ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) == true && channel( p, ch, sample) );
  }
  double weight(ntupleReader &p, Sample &sample) { return w( p, sample); }

 private:
  std::string name(){ return( generateName(baseName, ch, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;
  int ch;

};


#endif
