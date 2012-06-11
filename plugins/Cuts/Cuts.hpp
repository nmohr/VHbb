#ifndef CUTS_H
#define CUTS_H
#include "../../interface/CutsAndHistos.h"
#include "../../interface/ntupleReader.hpp"
#include <TH1F.h>
#include <sstream>
#include "../../interface/samples.hpp"
#include "TKey.h"

#define CSVM 0.679
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498


bool sampleCut(ntupleReader &p, Sample &sample){

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

    return sampleCut;
}


//I collect the weight and the sample information ONLY here in the SignalPreselection
class PreSelectionZee : public CutSample {
  std::string name() {return "PreSelZee";};  
  Bool_t pass(ntupleReader &p ){ return ( p.Vtype == 1 );  }
  Bool_t pass(ntupleReader &p, Sample &sample ){
    return ( sampleCut(p, sample) == true
	     && p.Vtype == 1
	     && p.EVENT_json == true
	     && p.hbhe == true 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );  }
  double weight(ntupleReader &p, Sample &sample){ 
    if( sample.data ) 
      return 1; 
    else 
      return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class EmptyCut : public PCut
{
 public:
 EmptyCut():PCut(){}
  bool pass(ntupleReader &p) {
    return true;
  }
  virtual std::string name()  {return "NoCut_Gt_"+cutValueString(); }
};

class HPtCut : public PCut
{
 public:
  HPtCut(double ptMin):PCut(ptMin){}
  bool pass(ntupleReader &p) {
    return (  p.H_pt > m_cut);
  }
  virtual std::string name()  {return "Higgs_Pt_Gt_"+cutValueString(); }
};

class HMassCut : public PCut
{
 public:
 HMassCut(double massMin):PCut(massMin){}
  bool pass(ntupleReader &p) {
    return (  p.H_mass > m_cut );
  }
  virtual std::string name()  {return "Higgs_Mass_Gt_"+cutValueString(); }
};

class HMassCutMax : public PCut
{
 public:
 HMassCutMax(double maxMass ):PCut(maxMass){}
  bool pass(ntupleReader &p) {
    return ( !(p.H_mass > m_cut) );
  }
  virtual std::string name()  {return "Higgs_Mass_Gt_"+cutValueString(); }
};


class VPtCut : public PCut
{
 public:
  VPtCut(double ptMin):PCut(ptMin){}
  bool pass(ntupleReader &p) {
    return (  p.V_pt > m_cut);
  }
  virtual std::string name()  {return "V_Pt_Gt_"+cutValueString(); }
};

class VMassCutMin : public PCut
{
 public:
 VMassCutMin(double massMin):PCut(massMin){}
  bool pass(ntupleReader &p) {
    return ( p.V_mass > m_cut );
  }
  virtual std::string name()  {return "V_Mass_Gt_"+cutValueString(); }
};

class VMassCutMax : public PCut
{
 public:
 VMassCutMax(double massMax):PCut(massMax){}
  bool pass(ntupleReader &p) {
    return ( p.V_mass < m_cut );
  }
  virtual std::string name()  {return "V_Mass_Gt_"+cutValueString(); }
};


class JetPtCut : public PCut
{
 public:
  JetPtCut(double ptMin):PCut(ptMin){}
  bool pass(ntupleReader &p) {
    return ( p.hJet_pt[0] > m_cut
	     && p.hJet_pt[1] > m_cut );
  }
  virtual std::string name()  {return "Jet_Pt_Gt_"+cutValueString(); }
};

class JetBtagCut : public PCut
{
 public:
 JetBtagCut(double btagMin, double btagMax):PCut(btagMin, btagMax){}
  bool pass(ntupleReader &p) {
    return ( p.hJet_csv[0] > m_cut
	     && p.hJet_csv[1] > m_cut
	     && ( p.hJet_csv[0] > M_cut
		  || p.hJet_csv[1] > M_cut )  );
  }
  virtual std::string name()  {return "Jet_Btag_Gt_"+cutValueString(); }
};

class HVdPhiCut : public PCut
{
 public:
 HVdPhiCut(double phiMin):PCut(phiMin){}
  bool pass(ntupleReader &p) {
    return (  TMath::Abs(p.HVdPhi) >  m_cut );
  }
  virtual std::string name()  {return "HV_dPhi_Gt_"+cutValueString(); }
};

class JetVeto : public PCut
{
 public:
 JetVeto(double nJetsMax):PCut(nJetsMax){}
  bool pass(ntupleReader &p) {
    return (  p.CountAddJets() < m_cut );
  }
  virtual std::string name()  {return "jetVeto_Gt_"+cutValueString(); }
};



#endif
