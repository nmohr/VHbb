#ifndef CUTSSIDEBANDPT100_H
#define CUTSSIDEBANDPT100_H
#include "../../interface/CutsAndHistos.h"
#include "../../interface/ntupleReader.hpp"
#include <TH1F.h>
#include <sstream>
#include "../../interface/samples.hpp"
#include "TKey.h"

#define CSVM 0.679
#define CSVC 0.5 //custom btag
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498

// New implementations of the control region
// The signal regions must be implemented incrementally since cutflow is needed

bool sCut( ntupleReader & p , Sample & sample ){
  return (  p.EVENT_json == true && p.hbhe == true );
};


std::string generateName( std::string & baseName, int btag = 0, int jec = 0 ) {
  if( jec == 1 )
    return ( "SystJecUP"+baseName );
  else if( jec == -1 )
    return ( "SystJecDOWN"+baseName );
  else if( jec == 2 )
    return ( "SystJerUP"+baseName );
  else if( jec == -2 )
    return ( "SystJerDOWN"+baseName );
  if( btag == 1)
    return ( "SystBtagUP"+baseName );
  else if( btag == -1 )
    return ( "SystBtagDOWN"+baseName );
  else if( btag == 2 )
    return ( "SystBtagFUP"+baseName );
  else if( btag == -2 )
    return ( "SystBtagFDOWN"+baseName );
  else if( btag == 0 && jec == 0)
    return baseName;
};

class BDTTrainingRegionHZcombSB: public CutSample{
 public:
 BDTTrainingRegionHZcombSB(int jec_= 0 , int btag_ = 0):
  jec(jec_),btag(btag_){ baseName = "BDTTrainingRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20.  
	     && p.hJet_PT(1,jec) > 20. 
	     && p.hJet_CSV(0,btag) > CSVL 
	     && p.hJet_CSV(1,btag) > CSVL 
	     && p.Higgs(jec).Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.Higgs(jec).M() < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};

class BDTSideBandRegionHZcombSB: public CutSample{
 public:
 BDTSideBandRegionHZcombSB(int jec_= 0 , int btag_ = 0):
  jec(jec_),btag(btag_){ baseName = "BDTSideBandRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20.  
	     && p.hJet_PT(1,jec) > 20. 
	     && p.hJet_CSV(0,btag) > CSVL 
	     && p.hJet_CSV(1,btag) > CSVL 
	     //	     && p.Higgs(jec).Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && ( p.Higgs(jec).M() < 80.
		  || p.Higgs(jec).M() > 150. )
	     && p.Higgs(jec).M() < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};

class BDTSignalRegionHZcombSB: public CutSample{
 public:
 BDTSignalRegionHZcombSB(int jec_= 0 , int btag_ = 0):
  jec(jec_),btag(btag_){ baseName = "BDTSignalRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20.  
	     && p.hJet_PT(1,jec) > 20. 
	     && p.hJet_CSV(0,btag) > CSVL 
	     && p.hJet_CSV(1,btag) > CSVL 
	     //	     && p.Higgs(jec).Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.Higgs(jec).M() > 80.
	     && p.Higgs(jec).M() < 150.
	     //	     && p.CountAddJets() < 2 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p , sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};


class BDTZbbControlRegionHZcombSB: public CutSample{
 public:
 BDTZbbControlRegionHZcombSB(int jec_ = 0, int btag_ = 0):
  jec(jec_), btag(btag_) { baseName = "BDTZbbControlRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20. 
	     && p.hJet_PT(1,jec) > 20. 
	     && p.hJet_CSV(0,btag) > CSVL 
	     && p.hJet_CSV(1,btag) > CSVL
/* 	     && p.hJet_vtxMass[0] > 0. */
/* 	     && p.hJet_vtxMass[1] > 0. */
  	     && p.V_pt > 100. 
	     //   	     && p.Higgs(jec).Pt() > 100.  
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && ( p.Higgs(jec).M() < 80.
		  || p.Higgs(jec).M() > 150. )
	     && p.Higgs(jec).M() < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
 private:
  std::string name() {return generateName(baseName, btag, jec);};
  std::string baseName;
  int btag;
  int jec;
};

class BDTZlightControlRegionHZcombSB: public CutSample{
 public:
 BDTZlightControlRegionHZcombSB( int jec_ = 0, int btag_ = 0 ):
  jec(jec_), btag(btag_) { baseName = "BDTZlightControlRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20. 
	     && p.hJet_PT(1,jec) > 20. 
 	     && p.hJet_CSV(0,btag) < CSVL
 	     && p.hJet_CSV(1,btag) < CSVL 
/* 	     && ( p.hJet_CSV(0,btag) > CSVC  */
/* 		  || p.hJet_CSV(1,btag) > CSVC ) */
// 	     && p.hJet_vtxMass[0] < 0.
// 	     && p.hJet_vtxMass[1] < 0. 
 	     && p.V_pt > 100.
	     // 	     && p.Higgs(jec).Pt() > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
 	     && ( p.Higgs(jec).M() < 80.
 		  || p.Higgs(jec).M() > 150. )
	     && p.Higgs(jec).M() < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) 
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) == true && pass ( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
 private:
  std::string name() {return generateName(baseName, btag, jec);};
  std::string baseName;
  int btag;
  int jec;
};

class BDTTTbarControlRegionHZcombSB: public CutSample{
 public:
 BDTTTbarControlRegionHZcombSB(int jec_ = 0, int btag_ = 0):
  jec(jec_), btag(btag_) { baseName = "BDTTTbarControlRegionHZcombSB"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20. 
	     && p.hJet_PT(1,jec) > 20. 
	     && p.hJet_CSV(0,btag) > CSVL 
	     && p.hJet_CSV(1,btag) > CSVL
	     //	     && p.CountAddJets() > 0
	     // 	     && p.Higgs(jec).Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 50. 
	     && ( p.V_mass > 105.
		  || p.V_mass < 75. )
/* 	     && ( p.Higgs(jec).M() < 80. */
/* 		  || p.Higgs(jec).M() > 150. ) */
	     && p.Higgs(jec).M() < 250.
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) 
	     );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
 private:
  std::string name() {return generateName(baseName, btag, jec);};
  std::string baseName;
  int btag;
  int jec;
};

#endif
