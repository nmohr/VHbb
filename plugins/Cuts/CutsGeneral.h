#ifndef CUTSGENERAL_H
#define CUTSGENERAL_H
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

//cuts that has to be applied globally
bool qualityCuts( ntupleReader & p ){
  return ( p. hJet_puJetIdL[0] > 0. 
	   && p. hJet_puJetIdL[1] > 0.
	   && TMath::Abs(p.hJet_eta[0]) < 2.4
	   && TMath::Abs(p.hJet_eta[1]) < 2.4
	   && p.hbhe == true );
};

//if you want to do a sample-dependent cut.
bool sCut( ntupleReader & p , Sample & sample ){
/*   if( sample.data ) */
/*     return ( p.EVENT_json == true ); */
/*   else */
    return 1;
};

//channel dependent cuts
Bool_t channel(ntupleReader & p, int ch , Sample & sample){
  bool trigger[2];
  
  if(sample.data){
    //muons
    trigger[0] = ( ( p.triggerFlags[14] || p.triggerFlags[21] || p.triggerFlags[22] || p.triggerFlags[23] ) );
    //electrons
    trigger[1] = ( ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  else{
    trigger[0] = 1;
    trigger[1] = 1;
  }

  if(ch == -1) return (( p.Vtype == 0 && trigger[0] ) || ( p.Vtype == 1 && trigger[1] )); 
  else return ( p.Vtype == ch && trigger[ch] );
};

//here if you want to apply a sample depepndent weight.
double w(ntupleReader &p, Sample &sample){
  //  return 1;
  std::string DY("DY");
  if(sample.name == DY) return (p.lheWeight);
  else return 1;
};

//naming conventions
std::string generateName( std::string & baseName, int ch = -1, int btag = 0, int jec = 0 ) {
  std::string channel; 
  if(ch == -1)
    channel = "HZcomb";
  else if(ch == 0)
    channel = "HZmm";
  else if(ch == 1)
    channel = "HZee";
  if( jec == 1 )
    return ( "SystJecUP"+baseName+channel );
  else if( jec == -1 )
    return ( "SystJecDOWN"+baseName+channel );
  else if( jec == 2 )
    return ( "SystJerUP"+baseName+channel );
  else if( jec == -2 )
    return ( "SystJerDOWN"+baseName+channel );
  if( btag == 1)
    return ( "SystBtagUP"+baseName+channel );
  else if( btag == -1 )
    return ( "SystBtagDOWN"+baseName+channel );
  else if( btag == 2 )
    return ( "SystBtagFUP"+baseName+channel );
  else if( btag == -2 )
    return ( "SystBtagFDOWN"+baseName+channel );
  else if( btag == 0 && jec == 0)
    return baseName+channel;
};


#endif
