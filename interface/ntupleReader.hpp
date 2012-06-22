#ifndef ntupleReader_h
#define ntupleReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include "ntupleLoader.hpp"


class ntupleReader : public ntupleLoader {
public :

  ntupleReader(const char * infile) : ntupleLoader( infile ){};
  //  virtual ~ntupleReader();
  virtual int GetSign(int v);
  virtual std::vector<TLorentzVector> SimBs();
  virtual std::vector<TLorentzVector> SVs();
  virtual double typeIcorrMET( double sign );
  virtual int CountJets();
  virtual int CountAddJets();
  virtual int CountAddForwardJets();
  virtual int CountAddJets_jec( double sign );
  virtual int CountAddLeptons();
  virtual bool TriggerBit();
  virtual TLorentzVector VectorBoson(); //vector boson TLorentz vector
  virtual double resolution(double eta); //smearing for the jet energy resolution
  virtual TLorentzVector hJet_jer( int idx, double sign );
  virtual TLorentzVector H_jer( double sing );
  virtual double hJet_PT( int idx, int sign ); //higgs jet energy correction
  virtual double aJet_PT( int idx, int sign ); //addtional jet energy correction
  virtual double hJet_E( int idx, int sign ); //higgs jet energy correction
  virtual double aJet_E( int idx, int sign ); //addtional jet energy correction
  virtual TLorentzVector Higgs( int sign ); //higgs candidate jet energy correction
  virtual double hJet_CSV( int idx, int sign ); //higgs jet energy correction
  virtual double hJet_pt_jec( int idx, double sign ); //higgs jet energy correction
  virtual double aJet_pt_jec( int idx, double sign ); //addtional jet energy correction
  virtual double hJet_e_jec( int idx, double sign );
  virtual double aJet_e_jec( int idx, double sign );
  virtual TLorentzVector H_jec( double sign ); //higgs candidate jet energy correction
  virtual double hJet_csv_cUP( int idx );
  virtual double hJet_csv_cDOWN( int idx );
  virtual double hJet_csv_cFUP( int idx );
  virtual double hJet_csv_cFDOWN( int idx );
  virtual double hJet_pt_jecUP( int idx );
  virtual double hJet_pt_jecDOWN( int idx );
  virtual double aJet_pt_jecUP( int idx );
  virtual double aJet_pt_jecDOWN( int idx );
  virtual TLorentzVector H_jecUP();
  virtual TLorentzVector H_jecDOWN();
  
};

int ntupleReader::GetSign(int v){
  return v > 0 ? 1 : (v < 0 ? -1 : 0);
}

std::vector<TLorentzVector> ntupleReader::SimBs(){
  TLorentzVector simB;
  std::vector<TLorentzVector> iSimBs;
  for(int j=0; j<nSimBs; ++j){
    simB.SetPtEtaPhiM( SimBs_pt[j], SimBs_eta[j], SimBs_phi[j], SimBs_mass[j]);
    iSimBs.push_back( simB );
  }
  return iSimBs;
}

std::vector<TLorentzVector> ntupleReader::SVs(){
  TLorentzVector sv;
  std::vector<TLorentzVector> iSVs;
  for(int j=0; j<nSvs; ++j){
    sv.SetPtEtaPhiM( Sv_pt[j], Sv_eta[j], Sv_phi[j], Sv_massBCand[j]);
    iSVs.push_back( sv );
  }
  return iSVs;
}

double ntupleReader::typeIcorrMET( double sign = 0 ){ 
  double met_et;
  TLorentzVector sumPt;
  TLorentzVector sumPtRaw;
  TLorentzVector rawMet, jet, rawJet;
  for(int i=0; i<nhJets; ++i){
    jet.SetPtEtaPhiE( hJet_PT(i, sign) , hJet_eta[i], hJet_phi[i], hJet_E(i, sign));
    rawJet.SetPtEtaPhiE( hJet_ptRaw[i] , hJet_eta[i], hJet_phi[i], (hJet_ptRaw[i]/hJet_PT(i,sign)) * hJet_E(i,sign));
    sumPt += jet;
    sumPtRaw += rawJet;
  }
  rawMet.SetPtEtaPhiE(MET_et, 0., MET_phi, MET_et);
  met_et = (rawMet - (sumPt - sumPtRaw)).Pt();
  return met_et;
} 
TLorentzVector ntupleReader::VectorBoson(){
  TLorentzVector l1, l2;
  l1.SetPtEtaPhiM(vLepton_pt[0],vLepton_eta[0],vLepton_phi[0],vLepton_mass[0] );
  l2.SetPtEtaPhiM(vLepton_pt[1],vLepton_eta[1],vLepton_phi[1],vLepton_mass[1] );
  return (l1+l2);
}

//JER
double ntupleReader::resolution(double eta){
  double inner = 0.06;
  double outer = 0.1;
  double eta_tracker = 1.1;
  if(abs(eta) < eta_tracker) return inner; else return outer;
}

TLorentzVector ntupleReader::hJet_jer( int idx, double sign ){
  TLorentzVector tmp;
  double hJet_pt_jer = hJet_pt[idx] + sign * resolution(hJet_eta[idx])*TMath::Abs(hJet_pt[idx]-hJet_genPt[idx]);
  tmp.SetPtEtaPhiE(  hJet_pt_jer,
		     hJet_eta[idx],
		     hJet_phi[idx],
		     hJet_e[idx]*(hJet_pt_jer/hJet_pt[idx]) );
 return tmp;
}

TLorentzVector ntupleReader::H_jer( double sign ){
  TLorentzVector h;
  h = hJet_jer( 0, sign ) + hJet_jer( 1, sign );
  return h;
}

double ntupleReader::hJet_PT( int idx, int sign ){ 
  if( TMath::Abs(sign) < 2 )
    return  hJet_pt[idx]*(1 + (sign)*hJet_JECUnc[idx]); 
  else // +- 2 are for jet energy corrections 
    return (hJet_jer( idx, sign - GetSign(sign)*1 )).Pt() ;
}
double ntupleReader::aJet_PT( int idx, int sign ){ return  aJet_pt[idx]*(1 + (sign)*aJet_JECUnc[idx]); }
double ntupleReader::hJet_E( int idx, int sign ){  return  hJet_e[idx] * hJet_PT(idx, sign)/hJet_pt[idx]; }
double ntupleReader::aJet_E( int idx, int sign ){ return aJet_e[idx] * aJet_PT(idx, sign)/aJet_pt[idx]; }
TLorentzVector ntupleReader::Higgs( int sign ){ 
  TLorentzVector j1,j2,H;
  j1.SetPtEtaPhiE( hJet_PT(0,sign), hJet_eta[0], hJet_phi[0], hJet_E(0,sign) );
  j2.SetPtEtaPhiE( hJet_PT(1,sign), hJet_eta[1], hJet_phi[1], hJet_E(1,sign) );
  return  H=j1+j2;
}
double ntupleReader::hJet_CSV( int idx, int sign ){ 
  //this is not reshaped
  //else return (hJet_csv[idx]); 
  //this is reshaped using my framework
  //  else return (sh.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csv[idx], hJet_flavour[idx] )); 
  //using Niklas framework the csv not reshaped is called csvOld
  if( hJet_flavour[0] < 1 ) // stupid check if it is data. In niklas framework there is no csvOld for data. reshaping knows about data for flavour 0
    return (reshape.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csv[idx], hJet_flavour[idx] )); 
  else{ //MC
    if(sign == 1) return (reshape_bTagUp.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csvOld[idx], hJet_flavour[idx] )); 
    else if(sign == -1) return (reshape_bTagDown.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csvOld[idx], hJet_flavour[idx] )); 
    else if( sign == 2 ) return (reshape_misTagUp.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csvOld[idx], hJet_flavour[idx] ));  
    else if( sign == -2 ) return (reshape_misTagDown.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csvOld[idx], hJet_flavour[idx] ));  
    else return (reshape.reshape( hJet_eta[idx], hJet_pt[idx], hJet_csvOld[idx], hJet_flavour[idx] )); 
  }
}


//for jet energy correction variation
double ntupleReader::hJet_pt_jec( int idx, double sign ){ return  hJet_pt[idx]*(1 + (sign)*hJet_JECUnc[idx]); }
double ntupleReader::aJet_pt_jec( int idx, double sign ){ return  aJet_pt[idx]*(1 + (sign)*aJet_JECUnc[idx]); }

double ntupleReader::hJet_e_jec( int idx, double sign ){ return  hJet_e[idx]*(1 + (sign)*hJet_JECUnc[idx]); }
double ntupleReader::aJet_e_jec( int idx, double sign ){ return  aJet_e[idx]*(1 + (sign)*aJet_JECUnc[idx]); }

TLorentzVector ntupleReader::H_jec( double sign ){ 
  TLorentzVector j1,j2,H;
  j1.SetPtEtaPhiE( hJet_pt_jec(0,sign), hJet_eta[0], hJet_phi[0], hJet_e_jec(0,sign) );
  j2.SetPtEtaPhiE( hJet_pt_jec(1,sign), hJet_eta[1], hJet_phi[1], hJet_e_jec(1,sign) );
  return  H=j1+j2;
}
double ntupleReader::hJet_csv_cUP( int idx ){ return ( hJet_csvUp[idx] ); }
double ntupleReader::hJet_csv_cDOWN( int idx ){ return ( hJet_csvDown[idx] ); }
double ntupleReader::hJet_csv_cFUP( int idx ){ return ( hJet_csvFUp[idx] ); }
double ntupleReader::hJet_csv_cFDOWN( int idx ){ return ( hJet_csvFDown[idx] ); }
double ntupleReader::hJet_pt_jecUP( int idx ){ return hJet_pt_jec(idx,+1); }
double ntupleReader::hJet_pt_jecDOWN( int idx ){ return  hJet_pt_jec(idx,-1); }
double ntupleReader::aJet_pt_jecUP( int idx ){ return aJet_pt_jec(idx,+1); }
double ntupleReader::aJet_pt_jecDOWN( int idx ){ return  aJet_pt_jec(idx,-1); }
TLorentzVector ntupleReader::H_jecUP(){ return H_jec(+1); }
TLorentzVector ntupleReader::H_jecDOWN(){ return H_jec(-1); }


int ntupleReader::CountJets(){
  int sum=0;
  for(int i=0; i<nhJets; ++i)
    if( hJet_pt[i] > 20.
	&& TMath::Abs(hJet_eta[i]) < 2.4 )
      sum++;
  for(int i=0; i<naJets; ++i)
    if( aJet_pt[i] > 20.
	&& TMath::Abs(aJet_eta[i]) < 2.4 )
      sum++;
  return sum;
}
int ntupleReader::CountAddJets(){
  int sum=0;
  for(int i=0; i<naJets; ++i)
    if( aJet_pt[i] > 20.
	&& TMath::Abs(aJet_eta[i]) < 2.4 )
      sum++;
  return sum;
}
int ntupleReader::CountAddForwardJets(){
  int sum=0;
  for(int i=0; i<naJets; ++i)
    if( aJet_pt[i] > 30.
	&& TMath::Abs(aJet_eta[i]) > 2.4 
	&& TMath::Abs(aJet_eta[i]) < 4.5 )
      sum++;
  return sum;
}
int ntupleReader::CountAddJets_jec( double sign ){
  int sum=0;
  for(int i=0; i<naJets; ++i)
    if( aJet_pt[i]*(1+(sign)*aJet_JECUnc[i]) > 20.
	&& TMath::Abs(aJet_eta[i]) < 2.4 )
      sum++;
  return sum;
}

int ntupleReader::CountAddLeptons(){
  int sum=0;
  for(int i=0; i<nalep; ++i)
    if( aLepton_pt[i] > 15.
	&& abs(aLepton_eta[i]) < 2.5
	&& aLepton_pfCombRelIso[i] < 0.15 )
      sum++;
  return sum;
}
bool ntupleReader::TriggerBit()
{
  if(  triggerFlags[5] 
       || triggerFlags[6] )
   return false;
  else
    return true;
}

#endif // #ifdef ntupleReader_cxx

