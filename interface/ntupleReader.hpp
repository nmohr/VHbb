#ifndef ntupleReader_h
#define ntupleReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include "ntupleLoader.h"

class ntupleReader : public ntupleLoader {
public :

  ntupleReader(const char * infile) : ntupleLoader ( infile );
  virtual ~ntupleReader();
   virtual std::vector<TLorentzVector> SimBs();
   virtual std::vector<TLorentzVector> SVs();
   virtual int CountJets();
   virtual int CountAddJets();
   virtual int CountAddForwardJets();
   virtual int CountAddJets_jec( double sign );
   virtual int CountAddLeptons();
   virtual bool TriggerBit();
   virtual TLorentzVector VectorBoson(); //vector boson TLorentz vector
   virtual double hJet_PT( int idx, int sign ); //higgs jet energy correction
   virtual double aJet_PT( int idx, int sign ); //addtional jet energy correction
   virtual TLorentzVector Higgs( int sign ); //higgs candidate jet energy correction
   virtual double hJet_CSV( int idx, int sign ); //higgs jet energy correction
   virtual double hJet_pt_jec( int idx, double sign ); //higgs jet energy correction
   virtual double aJet_pt_jec( int idx, double sign ); //addtional jet energy correction
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

TLorentzVector ntupleReader::VectorBoson(){
  TLorentzVector l1, l2;
  l1.SetPtEtaPhiM(vLepton_pt[0],vLepton_eta[0],vLepton_phi[0],vLepton_mass[0] );
  l2.SetPtEtaPhiM(vLepton_pt[1],vLepton_eta[1],vLepton_phi[1],vLepton_mass[1] );
  return (l1+l2);
}

double ntupleReader::hJet_PT( int idx, int sign ){ return  hJet_pt[idx]*(1 + (sign)*hJet_JECUnc[idx]); }
double ntupleReader::aJet_PT( int idx, int sign ){ return  aJet_pt[idx]*(1 + (sign)*aJet_JECUnc[idx]); }
TLorentzVector ntupleReader::Higgs( int sign ){ 
  TLorentzVector j1,j2,H;
  j1.SetPtEtaPhiE( hJet_pt_jec(0,sign), hJet_eta[0], hJet_phi[0], hJet_e[0] );
  j2.SetPtEtaPhiE( hJet_pt_jec(1,sign), hJet_eta[1], hJet_phi[1], hJet_e[1] );
  return  H=j1+j2;
}
double ntupleReader::hJet_CSV( int idx, int sign ){ 
  if(sign == 1) return (hJet_csvUp[idx]); 
  else if(sign == -1) return (hJet_csvDown[idx]); 
  else if( sign == 2 ) return (hJet_csvFUp[idx]); 
  else if( sign == -2 ) return (hJet_csvFDown[idx]) ; 
  else return (hJet_csv[idx]); 
}


//for jet energy correction variation
double ntupleReader::hJet_pt_jec( int idx, double sign ){ return  hJet_pt[idx]*(1 + (sign)*hJet_JECUnc[idx]); }
double ntupleReader::aJet_pt_jec( int idx, double sign ){ return  aJet_pt[idx]*(1 + (sign)*aJet_JECUnc[idx]); }
TLorentzVector ntupleReader::H_jec( double sign ){ 
  TLorentzVector j1,j2,H;
  j1.SetPtEtaPhiE( hJet_pt_jec(0,sign), hJet_eta[0], hJet_phi[0], hJet_e[0] );
  j2.SetPtEtaPhiE( hJet_pt_jec(1,sign), hJet_eta[1], hJet_phi[1], hJet_e[1] );
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

