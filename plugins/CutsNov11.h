#ifndef CUTSLP_H
#define CUTSLP_H
#include "CutsAndHistos.h"
#include "ntupleReader.h"
#include <TH1F.h>
#include <sstream>
#include "samples.h"
#include "TKey.h"

#define CSVM 0.679
#define CSVC 0.5 //custom btag
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498

// New implementations of the control region
// The signal regions must be implemented incrementally since cutflow is needed

class VlightRegionHZee: public CutSample {

  std::string name() {return "VlightRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    iType = (VType)p.Vtype;
    return (  p.Vtype == 1 
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     && p.V_pt > 100.
	     && p.H_mass < 250
	     && p.H_pt > 100.
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && TMath::Abs( p.HVdPhi ) > 2.9
	     && p.CountAddJets() < 2
	     && !(p.hJet_csv[0] > CSVT || p.hJet_csv[1] > CSVT ) 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    iType = (VType)p.Vtype;
    return ( sampleCut == true
	     && p.Vtype == 1 
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     && p.V_pt > 100.
	     && p.H_mass < 250
	     && p.H_pt > 100.
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && TMath::Abs( p.HVdPhi ) > 2.9
	     && p.CountAddJets() < 2
	     && !(p.hJet_csv[0] > CSVT || p.hJet_csv[1] > CSVT ) 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class TTbarRegionHZee: public CutSample {
  std::string name() {return "TTbarRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1 
	    && ( p.V_mass > 105.
		 || p.V_mass < 75. )
	    && p.H_pt > 100.
	    && p.H_mass < 250
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && (p.hJet_csv[0] > 0.5 && p.hJet_csv[1] > 0.5)
	    && (p.hJet_csv[0] > 0.898 || p.hJet_csv[1] > 0.898)
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    else sampleCut = false;
    return( sampleCut == true 
	    && p.Vtype == 1 
	    && ( p.V_mass > 105.
		 || p.V_mass < 75. )
	    && p.H_pt > 100.
	    //&& p.H_mass < 250
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && (p.hJet_csv[0] > 0.5 && p.hJet_csv[1] > 0.5)
	    && (p.hJet_csv[0] > 0.898 || p.hJet_csv[1] > 0.898)
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
  double weight(ntupleReader &p, Sample &sample) {if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};



class oldTTbarRegionHZee: public CutSample {
  std::string name() {return "oldTTbarRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1 
	    && p.V_mass > 120
	    && p.MET_et > 50.
	    && p.H_mass < 250
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    else sampleCut = false;
    return( sampleCut == true 
	    && p.Vtype == 1 
	    && p.V_mass > 120.
	    && p.MET_et > 50.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
  double weight(ntupleReader &p, Sample &sample) {if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class VbbRegionHZee: public CutSample {
  std::string name() {return "VbbRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.V_pt > 0.
	    && p.H_pt > 0.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && ( p.hJet_csv[0] > CSVT
		 || p.hJet_csv[1] > CSVT )
	    && p.hJet_csv[0] > 0.5
	    && p.hJet_csv[1] > 0.5
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && p.CountAddJets() < 2
	    //      && p. MET_et < 30
	    && ( p.H_mass < 90
		 || p.H_mass > 145 )
	    && p.H_mass < 250
	    && TMath::Abs(p.HVdPhi) > 2.9  
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    else
      sampleCut=false;
    return( sampleCut == true 
	    && p.Vtype == 1
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.V_pt > 0.
	    && p.H_pt > 0.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && ( p.hJet_csv[0] > CSVT
		 || p.hJet_csv[1] > CSVT )
	    && p.hJet_csv[0] > 0.5
	    && p.hJet_csv[1] > 0.5
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && p.CountAddJets() < 2
	    //      && p. MET_et < 30
	    && ( p.H_mass < 90
		 || p.H_mass > 145 )
	    && p.H_mass < 250
	    && TMath::Abs(p.HVdPhi) > 2.9  
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};

class SignalRegionHZee: public CutSample{
  std::string name() {return "SignalRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     // this cut depends on the H mass here for 115
	     //	     && p.H_mass > 95.
	     //	     && p.H_mass < 125.
	     //////////
	     && p.V_pt > 100.
	     && p.H_pt > 100.
	     && ( p.hJet_csv[0] > 0.898
		  || p.hJet_csv[1] > 0.898 )
	     && p.hJet_csv[0] > 0.5
	     && p.hJet_csv[1] > 0.5
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && TMath::Abs(p.HVdPhi) > 2.9
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample & sample){
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
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     // this cut depends on the H mass here for 115
	     //	     && p.H_mass > 95.
	     //	     && p.H_mass < 125.
	     //////////
	     && p.V_pt > 100.
	     && p.H_pt > 100.
	     && ( p.hJet_csv[0] > 0.898
		  || p.hJet_csv[1] > 0.898 )
	     && p.hJet_csv[0] > 0.5
	     && p.hJet_csv[1] > 0.5
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && TMath::Abs(p.HVdPhi) > 2.9
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }      
};

class BDTRegionHZee: public CutSample{
  std::string name() {return "BDTRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > 0.244 
	     && p.hJet_csv[1] > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > 0.244 
	     && p.hJet_csv[1] > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


class BDTZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > CSVL 
	     && p.hJet_csv[1] > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.hJet_csv[0] > CSVL
	     && p.hJet_csv[1] > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] < CSVL
	     && p.hJet_csv[1] < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] < CSVL
	     && p.hJet_csv[1] < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && p.H_mass < 250.
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return ( p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > CSVL 
	     && p.hJet_csv[1] > CSVL
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50. 
	     //&& p.H_mass < 250.
	     && ( p.V_mass > 105.
		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > CSVL 
	     && p.hJet_csv[1] > CSVL 
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
	     //&& p.H_mass < 250.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


class WbbRegionHWmnu: public CutSample {

  std::string name() {return "WbbRegionHWmnu";};
 public:
  Bool_t pass(ntupleReader &p){
    iType = (VType)p.Vtype;
    return (  p.Vtype == 2
	      && p.vLepton_pt[0] > 30.
	      && p.CountAddLeptons() == 0
	      && p.MET_et > 30
	      && p.hJet_pt[0] > 30.
	      && p.hJet_pt[1] > 30.
	      && p.hJet_csv[0] > CSVC
	      && p.hJet_csv[1] > CSVC
	      && ( p.hJet_csv[0] > CSVT
		   || p.hJet_csv[1] > CSVT )
	      && p.CountAddJets() < 2
	      && p.EVENT_json == true
	      && p.hbhe == true
	      && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    if(p.genZpt >= 120)
      boost = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    iType = (VType)p.Vtype;
    return ( sampleCut == true
	     && p.Vtype == 2
	     && p.vLepton_pt[0] > 30.
	     && p.CountAddLeptons() == 0
	     && p.MET_et > 30
	     && p.hJet_pt[0] > 30.
	     && p.hJet_pt[1] > 30.
	     && p.hJet_pt[0] > CSVC
	     && p.hJet_pt[1] > CSVC
	     && ( p.hJet_pt[0] > CSVT
		  || p.hJet_pt[1] > CSVT )
	     && p.CountAddJets() < 2
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) );
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};

class SingleTopRegionHWmnu: public CutSample {

  std::string name() {return "SingleTopRegionHWmnu";};
 public:
  Bool_t pass(ntupleReader &p){
    iType = (VType)p.Vtype;
    return (  p.Vtype == 2
	      && p.vLepton_pt[0] > 30.
	      && p.CountAddLeptons() == 0
	      && p.MET_et > 30
	      && p.hJet_pt[0] > 30.
	      && p.hJet_pt[1] > 30.
	      && p.hJet_csv[0] > CSVC
	      && p.hJet_csv[1] > CSVC
	      && ( p.hJet_csv[0] > CSVT
		   || p.hJet_csv[1] > CSVT )
	      && p.CountAddJets() < 2
	      && p.CountAddForwardJets() == 1
	      && p.EVENT_json == true
	      && p.hbhe == true
	      && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) );
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    if(p.genZpt >= 120)
      boost = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    iType = (VType)p.Vtype;
    return ( sampleCut == true
	     && p.Vtype == 2
	     && p.vLepton_pt[0] > 30.
	     && p.CountAddLeptons() == 0
	     && p.MET_et > 30
	     && p.hJet_pt[0] > 30.
	     && p.hJet_pt[1] > 30.
	     && p.hJet_pt[0] > CSVC
	     && p.hJet_pt[1] > CSVC
	     && ( p.hJet_pt[0] > CSVT
		  || p.hJet_pt[1] > CSVT )
	     && p.CountAddForwardJets() == 1
	     && p.CountAddJets() < 2
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) );
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class ZZRegionZee: public CutSample {
  std::string name() {return "ZZRegionZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.EVENT_json == true
	    && p.hbhe == true
	    //&& p.CountAddJets() < 2
	    && p. MET_et < 30
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  Bool_t pass(ntupleReader &p, Sample &sample){
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
    else
      sampleCut=false;
    return( sampleCut == true 
	    && p.Vtype == 1
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.EVENT_json == true
	    && p.hbhe == true
	    // && p.CountAddJets() < 2
	    && p. MET_et < 30
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};




/* class ZSVRegionHZee: public CutSample { */

/*   std::string name() {return "ZSVRegionHZee";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return (  p.Vtype == 1  */
/* 	      && p.V_mass > 75. */
/* 	      && p.V_mass < 105. */
/* 	      && p.nSvs == 2 */
/* 	      && p.EVENT_json == true */
/* 	      && p.hbhe == true */
/* 	      && ( p.triggerFlags[5] || p.triggerFlags[6] ) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && p.Vtype == 1  */
/* 	     && p.V_mass > 75. */
/* 	     && p.V_mass < 105. */
/* 	     && p.nSvs == 2 */
/* 	     && p.EVENT_json == true */
/* 	     && p.hbhe == true */
/* 	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */


/* class ZSVRegionHZmm: public CutSample { */

/*   std::string name() {return "ZSVRegionHZmm";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return (  p.Vtype == 0 */
/* 	      && p.V_mass > 75. */
/* 	      && p.V_mass < 105. */
/* 	      && p.nSvs == 2 */
/* 	      && p.EVENT_json == true */
/* 	      && p.hbhe == true */
/* 	      && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && p.Vtype == 0 */
/* 	     && p.V_mass > 75. */
/* 	     && p.V_mass < 105. */
/* 	     && p.nSvs == 2 */
/* 	     && p.EVENT_json == true */
/* 	     && p.hbhe == true */
/* 	     && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */



/* class ZSVRegionHZcomb: public CutSample { */

/*   std::string name() {return "ZSVRegionHZcomb";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return ( ( p.Vtype == 1  */
/* 	       && p.V_mass > 75. */
/* 	       && p.V_mass < 105. */
/* 	       && p.nSvs == 2 */
/* 	       && p.EVENT_json == true */
/* 	       && p.hbhe == true */
/* 	       && ( p.triggerFlags[5] || p.triggerFlags[6] ) )  */
/* 	     || ( p.Vtype == 0 */
/* 		  && p.V_mass > 75. */
/* 		  && p.V_mass < 105. */
/* 		  && p.nSvs == 2 */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && ( p.Vtype == 1  */
/* 		  && p.V_mass > 75. */
/* 		  && p.V_mass < 105. */
/* 		  && p.nSvs == 2 */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && ( p.triggerFlags[5] || p.triggerFlags[6] ) */
/* 		  || ( p.Vtype == 0 */
/* 		       && p.V_mass > 75. */
/* 		       && p.V_mass < 105. */
/* 		       && p.nSvs == 2 */
/* 		       && p.EVENT_json == true */
/* 		       && p.hbhe == true */
/* 		       && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */




/* class ZSVPureRegionHZee: public CutSample { */

/*   std::string name() {return "ZSVPureRegionHZee";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return (  p.Vtype == 1  */
/* 	      && p.V_mass > 75. */
/* 	      && p.V_mass < 105. */
/* 	      && p.nSvs == 2 */
/* 	      && p.MET_et < 40. */
/* 	      && p.EVENT_json == true */
/* 	      && p.hbhe == true */
/* 	      && ( p.triggerFlags[5] || p.triggerFlags[6] ) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && p.Vtype == 1  */
/* 	     && p.V_mass > 75. */
/* 	     && p.V_mass < 105. */
/* 	     && p.nSvs == 2 */
/* 	     && p.MET_et < 40. */
/* 	     && p.EVENT_json == true */
/* 	     && p.hbhe == true */
/* 	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */


/* class ZSVPureRegionHZmm: public CutSample { */

/*   std::string name() {return "ZSVPureRegionHZmm";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return (  p.Vtype == 0 */
/* 	      && p.V_mass > 75. */
/* 	      && p.V_mass < 105. */
/* 	      && p.nSvs == 2 */
/* 	      && p.MET_et < 40. */
/* 	      && p.EVENT_json == true */
/* 	      && p.hbhe == true */
/* 	      && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && p.Vtype == 0 */
/* 	     && p.V_mass > 75. */
/* 	     && p.V_mass < 105. */
/* 	     && p.nSvs == 2 */
/* 	     && p.MET_et < 40. */
/* 	     && p.EVENT_json == true */
/* 	     && p.hbhe == true */
/* 	     && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */



/* class ZSVPureRegionHZcomb: public CutSample { */

/*   std::string name() {return "ZSVPureRegionHZcomb";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return ( ( p.Vtype == 1  */
/* 	       && p.V_mass > 75. */
/* 	       && p.V_mass < 105. */
/* 	       && p.MET_et < 40. */
/* 	       && p.nSvs == 2 */
/* 	       && p.EVENT_json == true */
/* 	       && p.hbhe == true */
/* 	       && ( p.triggerFlags[5] || p.triggerFlags[6] ) )  */
/* 	     || ( p.Vtype == 0 */
/* 		  && p.V_mass > 75. */
/* 		  && p.V_mass < 105. */
/* 		  && p.MET_et < 40. */
/* 		  && p.nSvs == 2 */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && ( p.Vtype == 1  */
/* 		  && p.V_mass > 75. */
/* 		  && p.V_mass < 105. */
/* 		  && p.nSvs == 2 */
/* 		  && p.MET_et < 40. */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && ( p.triggerFlags[5] || p.triggerFlags[6] ) */
/* 		  || ( p.Vtype == 0 */
/* 		       && p.V_mass > 75. */
/* 		       && p.V_mass < 105. */
/* 		       && p.nSvs == 2 */
/* 		       && p.MET_et < 40. */
/* 		       && p.EVENT_json == true */
/* 		       && p.hbhe == true */
/* 		       && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */


/* class ZSVTTbarPureRegionHZcomb: public CutSample { */

/*   std::string name() {return "ZSVTTbarPureRegionHZcomb";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return ( ( p.Vtype == 1  */
/* 	       && p.V_mass > 120. */
/* 	       && p.nSvs == 2 */
/* 	       && p.EVENT_json == true */
/* 	       && p.hbhe == true */
/* 	       && ( p.triggerFlags[5] || p.triggerFlags[6] ) )  */
/* 	     || ( p.Vtype == 0 */
/* 		  && p.V_mass > 120. */
/* 		  && p.nSvs == 2 */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && ( p.Vtype == 1  */
/* 		  && p.V_mass > 120. */
/* 		  && p.nSvs == 2 */
/* 		  && p.EVENT_json == true */
/* 		  && p.hbhe == true */
/* 		  && ( p.triggerFlags[5] || p.triggerFlags[6] ) */
/* 		  || ( p.Vtype == 0 */
/* 		       && p.V_mass > 120. */
/* 		       && p.nSvs == 2 */
/* 		       && p.EVENT_json == true */
/* 		       && p.hbhe == true */
/* 		       && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ) ) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */



/* class WSVRegionHWmnu: public CutSample { */

/*   std::string name() {return "WSVRegionHWmnu";}; */
/*  public: */
/*   Bool_t pass(ntupleReader &p){ */
/*     iType = (VType)p.Vtype; */
/*     return (  p.Vtype == 2 */
/* 	      && p.vLepton_pt[0] > 30. */
/* 	      && p.CountAddLeptons() == 0 */
/* 	      && p.MET_et > 30 */
/* 	      && p.nSvs == 2 */
/* 	      && p.EVENT_json == true */
/* 	      && p.hbhe == true */
/* 	      && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   Bool_t pass(ntupleReader &p, Sample &sample){ */
/*     bool sampleCut = false; */
/*     bool boost = false; */
/*     if(p.genZpt >= 120) */
/*       boost = true; */
/*     std::string DY("DY"); */
/*     std::string DYBOOSTED("DYBOOSTED"); */
/*     if( sample.name == DY && !boost ) */
/*       sampleCut = true; */
/*     else if( sample.name == DYBOOSTED && boost ) */
/*       sampleCut = true; */
/*     else if( sample.name != DY && sample.name != DYBOOSTED ) */
/*       sampleCut = true; */
/*     else sampleCut=false; */
/*     iType = (VType)p.Vtype; */
/*     return ( sampleCut == true */
/* 	     && p.Vtype == 2 */
/* 	     && p.vLepton_pt[0] > 30. */
/* 	     && p.CountAddLeptons() == 0 */
/* 	     && p.MET_et > 30 */
/* 	     && p.nSvs == 2 */
/* 	     && p.EVENT_json == true */
/* 	     && p.hbhe == true */
/* 	     && (((p.EVENT_run<173198 && (p.triggerFlags[0]>0 || p.triggerFlags[13]>0 || p.triggerFlags[14]>0 || p.triggerFlags[20]>0 || p.triggerFlags[21]>0)) || (p.EVENT_run>=173198 && p.EVENT_run<175832  && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0))|| (p.EVENT_run>=175832 && p.EVENT_run<178390 && (p.triggerFlags[13]>0 ||p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0)) || (p.EVENT_run>=178390 && (p.triggerFlags[14]>0 ||p.triggerFlags[15]>0 || p.triggerFlags[21]>0 || p.triggerFlags[22]>0 || p.triggerFlags[23]>0 || p.triggerFlags[24]>0 || p.triggerFlags[25]>0 || p.triggerFlags[26]>0 || p.triggerFlags[27]>0)))) ); */
/*   } */
/*   double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } */
/* }; */


#endif
