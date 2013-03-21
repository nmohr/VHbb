#include "TLorentzVector.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TMath.h"
/*#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#endif*/

namespace VHbb {
  

  double deltaPhi(double phi1,double phi2)
  {
    double result = phi1 - phi2;
    while (result > TMath::Pi()) result -= 2*TMath::Pi();
    while (result <= -TMath::Pi()) result += 2*TMath::Pi();
    return result;
  }

  inline double deltaR(double eta1,double phi1,double eta2,double phi2)
    {
      double deta = eta1 - eta2;
      double dphi = deltaPhi(phi1, phi2);
      return TMath::Sqrt(deta*deta + dphi*dphi);
    }


  double Hmass( double V_eta,double V_phi,double V_pt, 
		double hJet1_eta,double hJet1_phi,double hJet1_pt, 
		double hJet2_eta,double hJet2_phi,double hJet2_pt ){
    
    TVector3 V(1,1,1);
    V.SetPtEtaPhi(V_pt,V_eta,V_phi);
    
    TVector3 H1(1,1,1);
    H1.SetPtEtaPhi(hJet1_pt,hJet1_eta,hJet1_phi);
    H1.SetMag(1/sin(H1.Theta()));
    
    TVector3 H2(1,1,1);
    H2.SetPtEtaPhi(hJet2_pt,hJet2_eta,hJet2_phi);
    H2.SetMag(1/sin(H2.Theta()));
    
    TVector3 n1(H1);
    TVector3 n2(H2);
    
    double det= n1.Px() * n2.Py() - n2.Px() * n1.Py();
    
    H1.SetMag( (  - n2.Py() * V.Px() + n2.Px() * V.Py() )  / (sin(n1.Theta()) *det ) );
    H2.SetMag( ( + n1.Py() * V.Px() - n1.Px() * V.Py() )  / (sin(n2.Theta())  *det ) );
    
    double mass=TMath::Sqrt( TMath::Power( (H1.Mag()+H2.Mag()),2 ) - TMath::Power(( ( H1+H2 ).Mag()),2) );
    
    return mass;
    
  }
  
  double Hmass_comb(double hJet1_eta,double hJet1_phi,double hJet1_pt, double hJet1_mass,
		    double hJet2_eta,double hJet2_phi,double hJet2_pt, double hJet2_mass){

    TLorentzVector H1, H2;
    H1.SetPtEtaPhiM(hJet1_pt,hJet1_eta,hJet1_phi, hJet1_mass);;
    H2.SetPtEtaPhiM(hJet2_pt,hJet2_eta,hJet2_phi, hJet2_mass);

    return (H1 + H2).M();

  }

  double Hmass_3j(double h_eta,double h_phi,double h_pt, double h_mass,
		  double aJet_eta,double aJet_phi,double aJet_pt, double aJet_mass){

    TLorentzVector H, H3;
    H.SetPtEtaPhiM( h_pt,h_eta,h_phi, h_mass);;
    H3.SetPtEtaPhiM(aJet_pt,aJet_eta,aJet_phi, aJet_mass);

    return (H + H3).M();


  }
  
  double ANGLELZ(double pt, double eta, double phi, double mass, double pt2, double eta2, double phi2, double mass2){
  TLorentzVector m1, m2, msum;
  m1.SetPtEtaPhiM(pt, eta, phi, mass);
  m2.SetPtEtaPhiM(pt2, eta2, phi2, mass2);
  msum = m1 + m2;

  TVector3 bZ =  msum.BoostVector();

  m1.Boost(-bZ);  
  m2.Boost(-bZ);  

  TVector3 b1;


  if((int) (pt) % 2 == 0)
    b1 =  m1.BoostVector();
  else
    b1 =  m2.BoostVector();

 double cosTheta = b1.Dot(msum.BoostVector()) / (b1.Mag()*msum.BoostVector().Mag());
 return(cosTheta);
  }


   double ANGLEHB(double pt, double eta, double phi, double e, double pt2, double eta2, double phi2, double e2){
 TLorentzVector m1, m2, msum;
 m1.SetPtEtaPhiE(pt, eta, phi, e);
 m2.SetPtEtaPhiE(pt2, eta2, phi2, e2);
 msum = m1 + m2;

 TVector3 bZ =  msum.BoostVector();

 m1.Boost(-bZ);
 m2.Boost(-bZ);  

 TVector3 b1;

  if((int) (pt) % 2 == 0)
    b1 =  m1.BoostVector();
  else
    b1 =  m2.BoostVector();

 double cosTheta = b1.Dot(msum.BoostVector()) / (b1.Mag()*msum.BoostVector().Mag());
 return(cosTheta);
   }

   double metCorSysShift(double met, double metphi, int Nvtx, int EVENT_run)
{
    double metx = met * cos(metphi);
    double mety = met * sin(metphi);
    double px = 0.0, py = 0.0;
    if (EVENT_run!=1) {
        //pfMEtSysShiftCorrParameters_2012runAplusBvsNvtx_data
        px = +1.68804e-01 + 3.37139e-01*Nvtx;
        py = -1.72555e-01 - 1.79594e-01*Nvtx;
    } else {
        //pfMEtSysShiftCorrParameters_2012runAplusBvsNvtx_mc
        px = +2.22335e-02 - 6.59183e-02*Nvtx;
        py = +1.52720e-01 - 1.28052e-01*Nvtx;
    }
    metx -= px;
    mety -= py;
    return std::sqrt(metx*metx + mety*mety);
}

    double metphiCorSysShift(double met, double metphi, int Nvtx, int EVENT_run)
{
    double metx = met * cos(metphi);
    double mety = met * sin(metphi);
    double px = 0.0, py = 0.0;
    if (EVENT_run!=1) {

        //pfMEtSysShiftCorrParameters_2012runAplusBvsNvtx_data
        px = +1.68804e-01 + 3.37139e-01*Nvtx;
        py = -1.72555e-01 - 1.79594e-01*Nvtx;
    } else {
        //pfMEtSysShiftCorrParameters_2012runAplusBvsNvtx_mc
        px = +2.22335e-02 - 6.59183e-02*Nvtx;
        py = +1.52720e-01 - 1.28052e-01*Nvtx;
    }
    metx -= px;
    mety -= py;
    if (metx == 0.0 && mety == 0.0)
        return 0.0;

    double phi1 = std::atan2(mety,metx);
    double phi2 = std::atan2(mety,metx)-2.0*M_PI;
    if (std::abs(phi1-metphi) < std::abs(phi2-metphi)+0.5*M_PI)
        return phi1;
    else
        return phi2;
}

TVector2 metType1Reg(double met, double metphi, double corr1, double corr2, double pt1, double eta1, double phi1, double e1, double pt2, double eta2, double phi2, double e2)
{
    double metx = met * cos(metphi);
    double mety = met * sin(metphi);
    TLorentzVector j1;
    TLorentzVector j2;
    j1.SetPtEtaPhiE(pt1,eta1,phi1, e1 );
    j2.SetPtEtaPhiE(pt2,eta2,phi2, e2 );
    metx += j1.Px()*(1-corr1);
    metx += j2.Px()*(1-corr2);
    mety += j1.Py()*(1-corr1);
    mety += j2.Py()*(1-corr2);
    TVector2 corrMET(metx, mety);
     return corrMET;
}

double metType1Phi(double met, double metphi, double corr1, double corr2, double pt1, double eta1, double phi1, double e1, double pt2, double eta2, double phi2, double e2){
    return metType1Reg(met, metphi, corr1, corr2, pt1, eta1, phi1, e1, pt2, eta2, phi2, e2).Phi();

}
double metType1Et(double met, double metphi, double corr1, double corr2, double pt1, double eta1, double phi1, double e1, double pt2, double eta2, double phi2, double e2){
    return metType1Reg(met, metphi, corr1, corr2, pt1, eta1, phi1, e1, pt2, eta2, phi2, e2).Mod();

}


   double met_MPF(double met, double metphi, double pt, double phi)
{
    return 1.+met*pt*std::cos( deltaPhi(metphi,phi) ) / (pt*pt);

}

double resolutionBias(double eta)
{
// return 0;//Nominal!
  if(eta< 0.5) return 0.052;
  if(eta< 1.1) return 0.057;
  if(eta< 1.7) return 0.096;
  if(eta< 2.3) return 0.134;
  if(eta< 5) return 0.28;
  return 0;
}

double evalJERBias( double ptreco, double ptgen, double eta1){
  double eta = fabs(eta1);
  double cor =1;   
  if ((fabs(ptreco - ptgen)/ ptreco)<0.5) { //Limit the effect to the core 
     cor = (ptreco +resolutionBias(eta) *(ptreco-ptgen))/ptreco;   
  }
  if (ptgen > 0.) return ptreco*cor;
  else return ptreco;
}

double evalEt( double pt, double eta, double phi, double e){
  TLorentzVector j;
  j.SetPtEtaPhiE(pt,eta,phi, e );
  return j.Et(); 

}

double evalMt( double pt, double eta, double phi, double e){
  TLorentzVector j;
  j.SetPtEtaPhiE(pt,eta,phi, e );
  return j.Mt(); 

}
/*double evalJECUnc( double pt, double eta){
// Total uncertainty for reference
JetCorrectionUncertainty *total = new JetCorrectionUncertainty("/shome/nmohr/CMSSW_5_2_6_patch1/src/UserCode/VHbb/data/START53_V15MC_Uncertainty_AK5PFchs.txt");

total->setJetPt(pt);
total->setJetEta(eta);
double uncert =  total->getUncertainty(true);
delete total;
return uncert;
}*/

double ptWeightDY( double lheV_pt)
{
    double SF = 1.;
    if (50. < lheV_pt && lheV_pt < 100.){
        SF = 0.873885+0.00175853*lheV_pt;
    }
    else if (lheV_pt > 100){
        SF = 1.10651-0.000705265*lheV_pt;
    }
    return SF;
}



}

