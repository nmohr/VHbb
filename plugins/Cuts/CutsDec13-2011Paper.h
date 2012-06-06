#ifndef CUTSPAPER1211_H
#define CUTSPAPER1211_H
#include "../../interface/CutsAndHistos.h"
#include "../../interface/ntupleReader.hpp"
#include "../../interface/samples.hpp"
#include <TH1F.h>
#include <sstream>
#include "TKey.h"

#define CSVM 0.679
#define CSVC 0.5 //custom btag
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498


bool sCut( ntupleReader & p , Sample & sample ){
  return ( p.EVENT_json == true && p.hbhe == true );
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

class CnCVlightControlRegionHZcomb: public CutSample {
 public:
 CnCVlightControlRegionHZcomb(int jec_=0, int btag_=0 ):
  jec(jec_),btag(btag_){baseName="CnCVlightControlRegionHZcomb"; };
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1 
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     && p.V_pt > 100.
	     && p.Higgs(jec).M() < 250
	     && p.Higgs(jec).Pt() > 100.
	     && p.hJet_PT(0,jec) > 20.
	     && p.hJet_PT(1,jec) > 20.
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && TMath::Abs( p.HVdPhi ) > 2.9
	     && p.CountAddJets() < 2
	     && !(p.hJet_CSV(0,btag) > CSVT || p.hJet_CSV(1,btag) > CSVT ) 
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )  );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return (sCut ( p, sample ) == true && pass(p) );   
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};


class CnCTTbarControlRegionHZcomb: public CutSample {
 public: 
 CnCTTbarControlRegionHZcomb(int jec_=0, int btag_=0):
  jec(jec_),btag(btag_){ baseName = "CnCTTbarControlRegionHZcomb";};
  Bool_t pass(ntupleReader &p){
    return( ( p.V_mass > 105.
		 || p.V_mass < 75. )
	    && p.Higgs(jec).Pt() > 100.
	    //&& p.Higgs(jec).M() < 250
	    && p.hJet_PT(0,jec) > 20.
	    && p.hJet_PT(1,jec) > 20.
	    && (p.hJet_CSV(0,btag) > 0.5 && p.hJet_CSV(1,btag) > 0.5)
	    && (p.hJet_CSV(0,btag) > 0.898 || p.hJet_CSV(1,btag) > 0.898)
	    && p.EVENT_json == true
	    && p.hbhe == true
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) )  );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) == true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};

class CnCVbbControlRegionHZcomb: public CutSample {

 public:
 CnCVbbControlRegionHZcomb(int jec_=0,int btag_=0):
  jec(jec_),btag(btag_){ baseName = "CnCVbbControlRegionHZcomb";};
  Bool_t pass(ntupleReader &p){
    return( p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.V_pt > 0.
	    && p.Higgs(jec).Pt() > 0.
	    && p.hJet_PT(0,jec) > 20.
	    && p.hJet_PT(1,jec) > 20.
	    && ( p.hJet_CSV(0,btag) > CSVT
		 || p.hJet_CSV(1,btag) > CSVT )
	    && p.hJet_CSV(0,btag) > 0.5
	    && p.hJet_CSV(1,btag) > 0.5
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && p.CountAddJets() < 2
	    //      && p. MET_et < 30
	    && ( p.Higgs(jec).M() < 90
		 || p.Higgs(jec).M() > 145 )
	    && p.Higgs(jec).M() < 250
	    && TMath::Abs(p.HVdPhi) > 2.9
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) );    
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    return ( sCut( p, sample ) ==  true && pass( p ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;

};

class CnCSignalRegionHZcomb: public CutSample{
 public:
 CnCSignalRegionHZcomb(int jec_=0,int btag_=0):
  jec(jec_), btag(btag_){ baseName = "CnCSignalRegionHZcomb";};
  Bool_t pass(ntupleReader &p){
    return ( p.V_mass > 75.
	     && p.V_mass < 105.
	     // this cut depends on the H mass here for 115
	     //	     && p.Higgs(jec).M() > 95.
	     //	     && p.Higgs(jec).M() < 125.
	     //////////
	     && p.V_pt > 100.
	     && p.Higgs(jec).Pt() > 100.
	     && ( p.hJet_CSV(0,btag) > 0.898
		  || p.hJet_CSV(1,btag) > 0.898 )
	     && p.hJet_CSV(0,btag) > 0.5
	     && p.hJet_CSV(1,btag) > 0.5
	     && p.hJet_PT(0,jec) > 20.
	     && p.hJet_PT(1,jec) > 20.
	     && TMath::Abs(p.HVdPhi) > 2.9
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && p.CountAddJets() < 2
	     && ( (  p.Vtype == 1 && ( p.triggerFlags[5] || p.triggerFlags[6] ) )
		  || ( p.Vtype == 0 && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) );    
  }
  Bool_t pass(ntupleReader &p, Sample & sample){
    return ( sCut(p, sample)==true && pass(p) ); }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }      

 private:
  std::string name(){ return( generateName(baseName, btag, jec) ) ;};
  std::string baseName;
  int btag;
  int jec;
};

#endif
