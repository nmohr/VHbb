#ifndef CUTSBASIC_H
#define CUTSBASIC_H
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
  bool sampleCut = false;
  bool boost = false;
  bool isB = false;
  if(p.genZpt >= 120)
    boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    return ( sampleCut && p.EVENT_json == true && p.hbhe == true );
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


class BasicRegionHZcomb: public CutSample{
 public:
 BasicRegionHZcomb(int jec_= 0 , int btag_ = 0):
  jec(jec_),btag(btag_){ baseName = "BasicRegionHZcomb"; };
  Bool_t pass(ntupleReader &p){
    return ( p.hJet_PT(0,jec) > 20.  
	     && p.hJet_PT(1,jec) > 20. 
	     && p.V_mass > 50.
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


#endif
