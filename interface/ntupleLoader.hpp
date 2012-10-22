//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 14 17:42:52 2012 by ROOT version 5.32/00
// from TTree tree/myTree
// found on file: ZllH.Jun14.DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root
//////////////////////////////////////////////////////////

#ifndef ntupleLoader_hpp
#define ntupleLoader_hpp

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "BTagReshaping.h"

class ntupleLoader {
public :
  TTree * tree;

  BTagShapeInterface reshape;
  BTagShapeInterface reshape_bTagUp;
  BTagShapeInterface reshape_bTagDown;
  BTagShapeInterface reshape_misTagUp;
  BTagShapeInterface reshape_misTagDown;

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain


   // Declaration of leaf types
   Int_t           H_HiggsFlag;
   Float_t         H_mass;
   Float_t         H_pt;
   Float_t         H_eta;
   Float_t         H_phi;
   Float_t         H_dR;
   Float_t         H_dPhi;
   Float_t         H_dEta;
   Float_t         V_mass;
   Float_t         V_pt;
   Float_t         V_eta;
   Float_t         V_phi;
   Int_t           FatH_FatHiggsFlag;
   Float_t         FatH_mass;
   Float_t         FatH_pt;
   Float_t         FatH_eta;
   Float_t         FatH_phi;
   Float_t         FatH_filteredmass;
   Float_t         FatH_filteredpt;
   Float_t         FatH_filteredeta;
   Float_t         FatH_filteredphi;
   Float_t         lheV_pt;
   Float_t         lheHT;
   Float_t         lheNj;
   Float_t         genZ_mass;
   Float_t         genZ_pt;
   Float_t         genZ_eta;
   Float_t         genZ_phi;
   Float_t         genZ_status;
   Float_t         genZ_charge;
   Float_t         genZ_momid;
   Float_t         genZstar_mass;
   Float_t         genZstar_pt;
   Float_t         genZstar_eta;
   Float_t         genZstar_phi;
   Float_t         genZstar_status;
   Float_t         genZstar_charge;
   Float_t         genZstar_momid;
   Float_t         genW_mass;
   Float_t         genW_pt;
   Float_t         genW_eta;
   Float_t         genW_phi;
   Float_t         genW_status;
   Float_t         genW_charge;
   Float_t         genW_momid;
   Float_t         genWstar_mass;
   Float_t         genWstar_pt;
   Float_t         genWstar_eta;
   Float_t         genWstar_phi;
   Float_t         genWstar_status;
   Float_t         genWstar_charge;
   Float_t         genWstar_momid;
   Float_t         genH_mass;
   Float_t         genH_pt;
   Float_t         genH_eta;
   Float_t         genH_phi;
   Float_t         genH_status;
   Float_t         genH_charge;
   Float_t         genH_momid;
   Float_t         genB_mass;
   Float_t         genB_pt;
   Float_t         genB_eta;
   Float_t         genB_phi;
   Float_t         genB_status;
   Float_t         genB_charge;
   Float_t         genB_momid;
   Float_t         genBbar_mass;
   Float_t         genBbar_pt;
   Float_t         genBbar_eta;
   Float_t         genBbar_phi;
   Float_t         genBbar_status;
   Float_t         genBbar_charge;
   Float_t         genBbar_momid;
   Float_t         genTop_bmass;
   Float_t         genTop_bpt;
   Float_t         genTop_beta;
   Float_t         genTop_bphi;
   Float_t         genTop_bstatus;
   Float_t         genTop_wdau1mass;
   Float_t         genTop_wdau1pt;
   Float_t         genTop_wdau1eta;
   Float_t         genTop_wdau1phi;
   Float_t         genTop_wdau1id;
   Float_t         genTop_wdau2mass;
   Float_t         genTop_wdau2pt;
   Float_t         genTop_wdau2eta;
   Float_t         genTop_wdau2phi;
   Float_t         genTop_wdau2id;
   Float_t         genTbar_bmass;
   Float_t         genTbar_bpt;
   Float_t         genTbar_beta;
   Float_t         genTbar_bphi;
   Float_t         genTbar_bstatus;
   Float_t         genTbar_wdau1mass;
   Float_t         genTbar_wdau1pt;
   Float_t         genTbar_wdau1eta;
   Float_t         genTbar_wdau1phi;
   Float_t         genTbar_wdau1id;
   Float_t         genTbar_wdau2mass;
   Float_t         genTbar_wdau2pt;
   Float_t         genTbar_wdau2eta;
   Float_t         genTbar_wdau2phi;
   Float_t         genTbar_wdau2id;
   UChar_t         TkSharing_HiggsCSVtkSharing;
   UChar_t         TkSharing_HiggsIPtkSharing;
   UChar_t         TkSharing_HiggsSVtkSharing;
   UChar_t         TkSharing_FatHiggsCSVtkSharing;
   UChar_t         TkSharing_FatHiggsIPtkSharing;
   UChar_t         TkSharing_FatHiggsSVtkSharing;
   Int_t           nhJets;
   Int_t           nfathFilterJets;
   Int_t           naJets;
   Float_t         hJet_pt[2];   //[nhJets]
   Float_t         hJet_eta[2];   //[nhJets]
   Float_t         hJet_phi[2];   //[nhJets]
   Float_t         hJet_e[2];   //[nhJets]
   Float_t         hJet_csv[2];   //[nhJets]
   Float_t         hJet_csv_nominal[2];   //[nhJets]
   Float_t         hJet_csv_upBC[2];   //[nhJets]
   Float_t         hJet_csv_downBC[2];   //[nhJets]
   Float_t         hJet_csv_upL[2];   //[nhJets]
   Float_t         hJet_csv_downL[2];   //[nhJets]
   Float_t         hJet_csvivf[2];   //[nhJets]
   Float_t         hJet_cmva[2];   //[nhJets]
   Float_t         hJet_cosTheta[2];   //[nhJets]
   Int_t           hJet_numTracksSV[2];   //[nhJets]
   Float_t         hJet_chf[2];   //[nhJets]
   Float_t         hJet_nhf[2];   //[nhJets]
   Float_t         hJet_cef[2];   //[nhJets]
   Float_t         hJet_nef[2];   //[nhJets]
   Float_t         hJet_nch[2];   //[nhJets]
   Float_t         hJet_nconstituents[2];   //[nhJets]
   Float_t         hJet_flavour[2];   //[nhJets]
   Int_t           hJet_isSemiLept[2];   //[nhJets]
   Int_t           hJet_isSemiLeptMCtruth[2];   //[nhJets]
   Int_t           hJet_SoftLeptpdgId[2];   //[nhJets]
   Int_t           hJet_SoftLeptIdlooseMu[2];   //[nhJets]
   Int_t           hJet_SoftLeptId95[2];   //[nhJets]
   Float_t         hJet_SoftLeptPt[2];   //[nhJets]
   Float_t         hJet_SoftLeptdR[2];   //[nhJets]
   Float_t         hJet_SoftLeptptRel[2];   //[nhJets]
   Float_t         hJet_SoftLeptRelCombIso[2];   //[nhJets]
   Float_t         hJet_genPt[2];   //[nhJets]
   Float_t         hJet_genEta[2];   //[nhJets]
   Float_t         hJet_genPhi[2];   //[nhJets]
   Float_t         hJet_JECUnc[2];   //[nhJets]
   Float_t         hJet_vtxMass[2];   //[nhJets]
   Float_t         hJet_vtxPt[2];   //[nhJets]
   Float_t         hJet_vtxEta[2];   //[nhJets]
   Float_t         hJet_vtxPhi[2];   //[nhJets]
   Float_t         hJet_vtxE[2];   //[nhJets]
   Float_t         hJet_vtx3dL[2];   //[nhJets]
   Float_t         hJet_vtx3deL[2];   //[nhJets]
   UChar_t         hJet_id[2];   //[nhJets]
   UChar_t         hJet_SF_CSVL[2];   //[nhJets]
   UChar_t         hJet_SF_CSVM[2];   //[nhJets]
   UChar_t         hJet_SF_CSVT[2];   //[nhJets]
   UChar_t         hJet_SF_CSVLerr[2];   //[nhJets]
   UChar_t         hJet_SF_CSVMerr[2];   //[nhJets]
   UChar_t         hJet_SF_CSVTerr[2];   //[nhJets]
   Float_t         hJet_ptRaw[2];   //[nhJets]
   Float_t         hJet_ptLeadTrack[2];   //[nhJets]
   Float_t         hJet_puJetIdL[2];   //[nhJets]
   Float_t         hJet_puJetIdM[2];   //[nhJets]
   Float_t         hJet_puJetIdT[2];   //[nhJets]
   Float_t         hJet_puJetIdMva[2];   //[nhJets]
   Float_t         fathFilterJets_pt[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_eta[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_phi[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_e[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_csv[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_chf[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_ptRaw[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_ptLeadTrack[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_flavour[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_isSemiLept[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_isSemiLeptMCtruth[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_genPt[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_genEta[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_genPhi[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtxMass[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtx3dL[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtx3deL[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtxPt[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtxEta[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtxPhi[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_vtxE[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_csvivf[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_cmva[3];   //[nfathFilterJets]
   Float_t         fathFilterJets_AnglePVtoSVmom[3];   //!
   Float_t         fathFilterJets_AnglePVtoJetmom[3];   //!
   Float_t         aJet_pt[19];   //[naJets]
   Float_t         aJet_eta[19];   //[naJets]
   Float_t         aJet_phi[19];   //[naJets]
   Float_t         aJet_e[19];   //[naJets]
   Float_t         aJet_csv[19];   //[naJets]
   Float_t         aJet_csv_nominal[19];   //[naJets]
   Float_t         aJet_csv_upBC[19];   //[naJets]
   Float_t         aJet_csv_downBC[19];   //[naJets]
   Float_t         aJet_csv_upL[19];   //[naJets]
   Float_t         aJet_csv_downL[19];   //[naJets]
   Float_t         aJet_csvivf[19];   //[naJets]
   Float_t         aJet_cmva[19];   //[naJets]
   Float_t         aJet_cosTheta[19];   //[naJets]
   Int_t           aJet_numTracksSV[19];   //[naJets]
   Float_t         aJet_chf[19];   //[naJets]
   Float_t         aJet_nhf[19];   //[naJets]
   Float_t         aJet_cef[19];   //[naJets]
   Float_t         aJet_nef[19];   //[naJets]
   Float_t         aJet_nch[19];   //[naJets]
   Float_t         aJet_nconstituents[19];   //[naJets]
   Float_t         aJet_flavour[19];   //[naJets]
   Int_t           aJet_isSemiLept[19];   //[naJets]
   Int_t           aJet_isSemiLeptMCtruth[19];   //[naJets]
   Int_t           aJet_SoftLeptpdgId[19];   //[naJets]
   Int_t           aJet_SoftLeptIdlooseMu[19];   //[naJets]
   Int_t           aJet_SoftLeptId95[19];   //[naJets]
   Float_t         aJet_SoftLeptPt[19];   //[naJets]
   Float_t         aJet_SoftLeptdR[19];   //[naJets]
   Float_t         aJet_SoftLeptptRel[19];   //[naJets]
   Float_t         aJet_SoftLeptRelCombIso[19];   //[naJets]
   Float_t         aJet_puJetIdL[19];   //[naJets]
   Float_t         aJet_puJetIdM[19];   //[naJets]
   Float_t         aJet_puJetIdT[19];   //[naJets]
   Float_t         aJet_puJetIdMva[19];   //[naJets]
   Float_t         aJet_genPt[19];   //[naJets]
   Float_t         aJet_genEta[19];   //[naJets]
   Float_t         aJet_genPhi[19];   //[naJets]
   Float_t         aJet_JECUnc[19];   //[naJets]
   Float_t         aJet_vtxMass[19];   //[naJets]
   Float_t         aJet_vtx3dL[19];   //[naJets]
   Float_t         aJet_vtx3deL[19];   //[naJets]
   UChar_t         aJet_id[19];   //[naJets]
   UChar_t         aJet_SF_CSVL[19];   //[naJets]
   UChar_t         aJet_SF_CSVM[19];   //[naJets]
   UChar_t         aJet_SF_CSVT[19];   //[naJets]
   UChar_t         aJet_SF_CSVLerr[19];   //[naJets]
   UChar_t         aJet_SF_CSVMerr[19];   //[naJets]
   UChar_t         aJet_SF_CSVTerr[19];   //[naJets]
   Int_t           naJetsFat;
   Float_t         aJetFat_pt[16];   //[naJetsFat]
   Float_t         aJetFat_eta[16];   //[naJetsFat]
   Float_t         aJetFat_phi[16];   //[naJetsFat]
   Float_t         aJetFat_e[16];   //[naJetsFat]
   Float_t         aJetFat_csv[16];   //[naJetsFat]
   Int_t           numJets;
   Int_t           numBJets;
   Float_t         deltaPullAngle;
   Float_t         deltaPullAngle2;
   Float_t         gendrcc;
   Float_t         gendrbb;
   Float_t         genZpt;
   Float_t         genWpt;
   Float_t         genHpt;
   Float_t         lheWeight;
   Float_t         weightTrig;
   Float_t         weightTrigMay;
   Float_t         weightTrigV4;
   Float_t         weightTrigMET;
   Float_t         weightTrigOrMu30;
   Float_t         weightEleRecoAndId;
   Float_t         weightEleTrigJetMETPart;
   Float_t         weightEleTrigElePart;
   Float_t         weightEleTrigEleAugPart;
   Float_t         weightTrigMET80;
   Float_t         weightTrigMET100;
   Float_t         weightTrig2CJet20;
   Float_t         weightTrigMET150;
   Float_t         weightTrigMET802CJet;
   Float_t         weightTrigMET1002CJet;
   Float_t         weightTrigMETLP;
   Float_t         weightTrig2012;
   Float_t         weightTrig2012A;
   Float_t         weightTrig2012ADiMuon;
   Float_t         weightTrig2012ADiEle;
   Float_t         weightTrig2012ASingleMuon;
   Float_t         weightTrig2012ASingleEle;
   Float_t         weightTrig2012AMuonPlusWCandPt;
   Float_t         weightTrig2012DiJet30MHT80;
   Float_t         weightTrig2012PFMET150;
   Float_t         weightTrig2012SumpT100MET100;
   Float_t         deltaPullAngleAK7;
   Float_t         deltaPullAngle2AK7;
   Float_t         PU0;
   Float_t         PUm1;
   Float_t         PUp1;
   Float_t         PUweight;
   Float_t         PUweight2011B;
   Float_t         PUweight1DObs;
   Int_t           eventFlav;
   Int_t           Vtype;
   Float_t         HVdPhi;
   Float_t         HVMass;
   Float_t         HMETdPhi;
   Float_t         VMt;
   Int_t           nvlep;
   Int_t           nalep;
   Float_t         vLepton_mass[2];   //[nvlep]
   Float_t         vLepton_pt[2];   //[nvlep]
   Float_t         vLepton_eta[2];   //[nvlep]
   Float_t         vLepton_phi[2];   //[nvlep]
   Float_t         vLepton_aodCombRelIso[2];   //[nvlep]
   Float_t         vLepton_pfCombRelIso[2];   //[nvlep]
   Float_t         vLepton_photonIso[2];   //[nvlep]
   Float_t         vLepton_neutralHadIso[2];   //[nvlep]
   Float_t         vLepton_chargedHadIso[2];   //[nvlep]
   Float_t         vLepton_chargedPUIso[2];   //[nvlep]
   Float_t         vLepton_particleIso[2];   //[nvlep]
   Float_t         vLepton_dxy[2];   //[nvlep]
   Float_t         vLepton_dz[2];   //[nvlep]
   Int_t           vLepton_type[2];   //[nvlep]
   Float_t         vLepton_id80[2];   //[nvlep]
   Float_t         vLepton_id95[2];   //[nvlep]
   Float_t         vLepton_vbtf[2];   //[nvlep]
   Float_t         vLepton_id80NoIso[2];   //[nvlep]
   Float_t         vLepton_genPt[2];   //[nvlep]
   Float_t         vLepton_genEta[2];   //[nvlep]
   Float_t         vLepton_genPhi[2];   //[nvlep]
   Float_t         vLepton_charge[2];   //[nvlep]
   Float_t         vLepton_pfCorrIso[2];   //[nvlep]
   Float_t         vLepton_id2012tight[2];   //[nvlep]
   Float_t         vLepton_idMVAnotrig[2];   //[nvlep]
   Float_t         vLepton_idMVAtrig[2];   //[nvlep]
   Float_t         vLepton_idMVApresel[2];   //[nvlep]
   Float_t         vLepton_innerHits[2];   //[nvlep]
   Float_t         vLepton_photonIsoDoubleCount[2];   //[nvlep]
   Float_t         vLepton_wpHWW[2];   //[nvlep]
   Float_t         vLepton_wp95[2];   //[nvlep]
   Float_t         vLepton_wp90[2];   //[nvlep]
   Float_t         vLepton_wp85[2];   //[nvlep]
   Float_t         vLepton_wp80[2];   //[nvlep]
   Float_t         vLepton_wp70[2];   //[nvlep]
   Float_t         aLepton_mass[55];   //[nalep]
   Float_t         aLepton_pt[55];   //[nalep]
   Float_t         aLepton_eta[55];   //[nalep]
   Float_t         aLepton_phi[55];   //[nalep]
   Float_t         aLepton_aodCombRelIso[55];   //[nalep]
   Float_t         aLepton_pfCombRelIso[55];   //[nalep]
   Float_t         aLepton_photonIso[55];   //[nalep]
   Float_t         aLepton_neutralHadIso[55];   //[nalep]
   Float_t         aLepton_chargedHadIso[55];   //[nalep]
   Float_t         aLepton_chargedPUIso[55];   //[nalep]
   Float_t         aLepton_particleIso[55];   //[nalep]
   Float_t         aLepton_dxy[55];   //[nalep]
   Float_t         aLepton_dz[55];   //[nalep]
   Int_t           aLepton_type[55];   //[nalep]
   Float_t         aLepton_id80[55];   //[nalep]
   Float_t         aLepton_id95[55];   //[nalep]
   Float_t         aLepton_vbtf[55];   //[nalep]
   Float_t         aLepton_id80NoIso[55];   //[nalep]
   Float_t         aLepton_genPt[55];   //[nalep]
   Float_t         aLepton_genEta[55];   //[nalep]
   Float_t         aLepton_genPhi[55];   //[nalep]
   Float_t         aLepton_charge[55];   //[nalep]
   Float_t         aLepton_pfCorrIso[55];   //[nalep]
   Float_t         aLepton_id2012tight[55];   //[nalep]
   Float_t         aLepton_idMVAnotrig[55];   //[nalep]
   Float_t         aLepton_idMVAtrig[55];   //[nalep]
   Float_t         aLepton_idMVApresel[55];   //[nalep]
   Float_t         aLepton_innerHits[55];   //[nalep]
   Float_t         aLepton_photonIsoDoubleCount[55];   //[nalep]
   Float_t         aLepton_wpHWW[55];   //[nalep]
   Float_t         aLepton_wp95[55];   //[nalep]
   Float_t         aLepton_wp90[55];   //[nalep]
   Float_t         aLepton_wp85[55];   //[nalep]
   Float_t         aLepton_wp80[55];   //[nalep]
   Float_t         aLepton_wp70[55];   //[nalep]
   Float_t         top_mass;
   Float_t         top_pt;
   Float_t         top_wMass;
   Int_t           WplusMode;
   Int_t           WminusMode;
   Int_t           nSvs;
   Float_t         Sv_massBCand[4];   //[nSvs]
   Float_t         Sv_massSv[4];   //[nSvs]
   Float_t         Sv_pt[4];   //[nSvs]
   Float_t         Sv_eta[4];   //[nSvs]
   Float_t         Sv_phi[4];   //[nSvs]
   Float_t         Sv_dist3D[4];   //[nSvs]
   Float_t         Sv_dist2D[4];   //[nSvs]
   Float_t         Sv_distSim2D[4];   //[nSvs]
   Float_t         Sv_distSig3D[4];   //[nSvs]
   Float_t         Sv_dist3D_norm[4];   //[nSvs]
   Float_t         SVH_mass;
   Float_t         SVH_pt;
   Float_t         SVH_eta;
   Float_t         SVH_phi;
   Float_t         SVH_dR;
   Float_t         SVH_dPhi;
   Float_t         SVH_dEta;
   Int_t           nSimBs;
   Float_t         SimBs_mass[8];   //[nSimBs]
   Float_t         SimBs_pt[8];   //[nSimBs]
   Float_t         SimBs_eta[8];   //[nSimBs]
   Float_t         SimBs_phi[8];   //[nSimBs]
   Float_t         SimBs_vtx_x[8];   //[nSimBs]
   Float_t         SimBs_vtx_y[8];   //[nSimBs]
   Float_t         SimBs_vtx_z[8];   //[nSimBs]
   Float_t         SimBs_pdgId[8];   //[nSimBs]
   Float_t         SimBs_status[8];   //[nSimBs]
   Float_t         SimBsH_mass;
   Float_t         SimBsH_pt;
   Float_t         SimBsH_eta;
   Float_t         SimBsH_phi;
   Float_t         SimBsH_dR;
   Float_t         SimBsH_dPhi;
   Float_t         SimBsH_dEta;
   Float_t         rho;
   Float_t         rho25;
   Float_t         rhoN;
   Int_t           nPVs;
   Float_t         METnoPU_et;
   Float_t         METnoPU_sumet;
   Float_t         METnoPU_sig;
   Float_t         METnoPU_phi;
   Float_t         METnoPUCh_et;
   Float_t         METnoPUCh_sumet;
   Float_t         METnoPUCh_sig;
   Float_t         METnoPUCh_phi;
   Float_t         MET_et;
   Float_t         MET_sumet;
   Float_t         MET_sig;
   Float_t         MET_phi;
   Float_t         METtype1corr_et;
   Float_t         METtype1corr_sumet;
   Float_t         METtype1corr_sig;
   Float_t         METtype1corr_phi;
   Float_t         METtype1p2corr_et;
   Float_t         METtype1p2corr_sumet;
   Float_t         METtype1p2corr_sig;
   Float_t         METtype1p2corr_phi;
   Float_t         METnoPUtype1corr_et;
   Float_t         METnoPUtype1corr_sumet;
   Float_t         METnoPUtype1corr_sig;
   Float_t         METnoPUtype1corr_phi;
   Float_t         METnoPUtype1p2corr_et;
   Float_t         METnoPUtype1p2corr_sumet;
   Float_t         METnoPUtype1p2corr_sig;
   Float_t         METnoPUtype1p2corr_phi;
   Float_t         metUnc_et[24];
   Float_t         metUnc_phi[24];
   Float_t         metUnc_sumet[24];
   Float_t         fakeMET_et;
   Float_t         fakeMET_sumet;
   Float_t         fakeMET_sig;
   Float_t         fakeMET_phi;
   Float_t         MHT_mht;
   Float_t         MHT_ht;
   Float_t         MHT_sig;
   Float_t         MHT_phi;
   Float_t         minDeltaPhijetMET;
   Float_t         jetPt_minDeltaPhijetMET;
   UChar_t         triggerFlags[50];
   Int_t           EVENT_run;
   Int_t           EVENT_lumi;
   Int_t           EVENT_event;
   Int_t           EVENT_json;
   UChar_t         hbhe;
   UChar_t         totalKinematics;
   UChar_t         ecalFlag;
   UChar_t         cschaloFlag;
   UChar_t         hcallaserFlag;
   UChar_t         trackingfailureFlag;
   Float_t         btag1TSF;
   Float_t         btag2TSF;
   Float_t         btag1T2CSF;
   Float_t         btag2CSF;
   Float_t         btagA0CSF;
   Float_t         btagA0TSF;
   Float_t         btag1TA1C;
   Float_t         PUweight2011BUp;
   Float_t         PUweight2011BDown;
   Float_t         hJet_csvOld[2];   //[nhJets]
   Float_t         hJet_csvDown[2];   //[nhJets]
   Float_t         hJet_csvUp[2];   //[nhJets]
   Float_t         hJet_csvFDown[2];   //[nhJets]
   Float_t         hJet_csvFUp[2];   //[nhJets]
   Float_t         weightTrig_up;
   Float_t         weightTrigMay_up;
   Float_t         weightTrigV4_up;
   Float_t         weightTrigMET_up;
   Float_t         weightTrigOrMu30_up;
   Float_t         weightEleRecoAndId_up;
   Float_t         weightEleTrigJetMETPart_up;
   Float_t         weightEleTrigElePart_up;

   // List of branches
   TBranch        *b_H;   //!
   TBranch        *b_V;   //!
   TBranch        *b_FatH;   //!
   TBranch        *b_lheV_pt;   //!
   TBranch        *b_lheHT;   //!
   TBranch        *b_lheNj;   //!
   TBranch        *b_genZ;   //!
   TBranch        *b_genZstar;   //!
   TBranch        *b_genW;   //!
   TBranch        *b_genWstar;   //!
   TBranch        *b_genH;   //!
   TBranch        *b_genB;   //!
   TBranch        *b_genBbar;   //!
   TBranch        *b_genTop;   //!
   TBranch        *b_genTbar;   //!
   TBranch        *b_TkSharing;   //!
   TBranch        *b_nhJets;   //!
   TBranch        *b_nfathFilterJets;   //!
   TBranch        *b_naJets;   //!
   TBranch        *b_hJet_pt;   //!
   TBranch        *b_hJet_eta;   //!
   TBranch        *b_hJet_phi;   //!
   TBranch        *b_hJet_e;   //!
   TBranch        *b_hJet_csv;   //!
   TBranch        *b_hJet_csv_nominal;   //!
   TBranch        *b_hJet_csv_upBC;   //!
   TBranch        *b_hJet_csv_downBC;   //!
   TBranch        *b_hJet_csv_upL;   //!
   TBranch        *b_hJet_csv_downL;   //!
   TBranch        *b_hJet_csvivf;   //!
   TBranch        *b_hJet_cmva;   //!
   TBranch        *b_hJet_cosTheta;   //!
   TBranch        *b_hJet_numTracksSV;   //!
   TBranch        *b_hJet_chf;   //!
   TBranch        *b_hJet_nhf;   //!
   TBranch        *b_hJet_cef;   //!
   TBranch        *b_hJet_nef;   //!
   TBranch        *b_hJet_nch;   //!
   TBranch        *b_hJet_nconstituents;   //!
   TBranch        *b_hJet_flavour;   //!
   TBranch        *b_hJet_isSemiLept;   //!
   TBranch        *b_hJet_isSemiLeptMCtruth;   //!
   TBranch        *b_hJet_SoftLeptpdgId;   //!
   TBranch        *b_hJet_SoftLeptIdlooseMu;   //!
   TBranch        *b_hJet_SoftLeptId95;   //!
   TBranch        *b_hJet_SoftLeptPt;   //!
   TBranch        *b_hJet_SoftLeptdR;   //!
   TBranch        *b_hJet_SoftLeptptRel;   //!
   TBranch        *b_hJet_SoftLeptRelCombIso;   //!
   TBranch        *b_hJet_genPt;   //!
   TBranch        *b_hJet_genEta;   //!
   TBranch        *b_hJet_genPhi;   //!
   TBranch        *b_hJet_JECUnc;   //!
   TBranch        *b_hJet_vtxMass;   //!
   TBranch        *b_hJet_vtxPt;   //!
   TBranch        *b_hJet_vtxEta;   //!
   TBranch        *b_hJet_vtxPhi;   //!
   TBranch        *b_hJet_vtxE;   //!
   TBranch        *b_hJet_vtx3dL;   //!
   TBranch        *b_hJet_vtx3deL;   //!
   TBranch        *b_hJet_id;   //!
   TBranch        *b_hJet_SF_CSVL;   //!
   TBranch        *b_hJet_SF_CSVM;   //!
   TBranch        *b_hJet_SF_CSVT;   //!
   TBranch        *b_hJet_SF_CSVLerr;   //!
   TBranch        *b_hJet_SF_CSVMerr;   //!
   TBranch        *b_hJet_SF_CSVTerr;   //!
   TBranch        *b_hJet_ptRaw;   //!
   TBranch        *b_hJet_ptLeadTrack;   //!
   TBranch        *b_hJet_puJetIdL;   //!
   TBranch        *b_hJet_puJetIdM;   //!
   TBranch        *b_hJet_puJetIdT;   //!
   TBranch        *b_hJet_puJetIdMva;   //!
   TBranch        *b_fathFilterJets_pt;   //!
   TBranch        *b_fathFilterJets_eta;   //!
   TBranch        *b_fathFilterJets_phi;   //!
   TBranch        *b_fathFilterJets_e;   //!
   TBranch        *b_fathFilterJets_csv;   //!
   TBranch        *b_fathFilterJets_chf;   //!
   TBranch        *b_fathFilterJets_ptRaw;   //!
   TBranch        *b_fathFilterJets_ptLeadTrack;   //!
   TBranch        *b_fathFilterJets_flavour;   //!
   TBranch        *b_fathFilterJets_isSemiLept;   //!
   TBranch        *b_fathFilterJets_isSemiLeptMCtruth;   //!
   TBranch        *b_fathFilterJets_genPt;   //!
   TBranch        *b_fathFilterJets_genEta;   //!
   TBranch        *b_fathFilterJets_genPhi;   //!
   TBranch        *b_fathFilterJets_vtxMass;   //!
   TBranch        *b_fathFilterJets_vtx3dL;   //!
   TBranch        *b_fathFilterJets_vtx3deL;   //!
   TBranch        *b_fathFilterJets_vtxPt;   //!
   TBranch        *b_fathFilterJets_vtxEta;   //!
   TBranch        *b_fathFilterJets_vtxPhi;   //!
   TBranch        *b_fathFilterJets_vtxE;   //!
   TBranch        *b_fathFilterJets_AnglePVtoSVmom;   //!
   TBranch        *b_fathFilterJets_AnglePVtoJetmom;   //!
   TBranch        *b_fathFilterJets_csvivf;   //!
   TBranch        *b_fathFilterJets_cmva;   //!
   TBranch        *b_aJet_pt;   //!
   TBranch        *b_aJet_eta;   //!
   TBranch        *b_aJet_phi;   //!
   TBranch        *b_aJet_e;   //!
   TBranch        *b_aJet_csv;   //!
   TBranch        *b_aJet_csv_nominal;   //!
   TBranch        *b_aJet_csv_upBC;   //!
   TBranch        *b_aJet_csv_downBC;   //!
   TBranch        *b_aJet_csv_upL;   //!
   TBranch        *b_aJet_csv_downL;   //!
   TBranch        *b_aJet_csvivf;   //!
   TBranch        *b_aJet_cmva;   //!
   TBranch        *b_aJet_cosTheta;   //!
   TBranch        *b_aJet_numTracksSV;   //!
   TBranch        *b_aJet_chf;   //!
   TBranch        *b_aJet_nhf;   //!
   TBranch        *b_aJet_cef;   //!
   TBranch        *b_aJet_nef;   //!
   TBranch        *b_aJet_nch;   //!
   TBranch        *b_aJet_nconstituents;   //!
   TBranch        *b_aJet_flavour;   //!
   TBranch        *b_aJet_isSemiLept;   //!
   TBranch        *b_aJet_isSemiLeptMCtruth;   //!
   TBranch        *b_aJet_SoftLeptpdgId;   //!
   TBranch        *b_aJet_SoftLeptIdlooseMu;   //!
   TBranch        *b_aJet_SoftLeptId95;   //!
   TBranch        *b_aJet_SoftLeptPt;   //!
   TBranch        *b_aJet_SoftLeptdR;   //!
   TBranch        *b_aJet_SoftLeptptRel;   //!
   TBranch        *b_aJet_SoftLeptRelCombIso;   //!
   TBranch        *b_aJet_puJetIdL;   //!
   TBranch        *b_aJet_puJetIdM;   //!
   TBranch        *b_aJet_puJetIdT;   //!
   TBranch        *b_aJet_puJetIdMva;   //!
   TBranch        *b_aJet_genPt;   //!
   TBranch        *b_aJet_genEta;   //!
   TBranch        *b_aJet_genPhi;   //!
   TBranch        *b_aJet_JECUnc;   //!
   TBranch        *b_aJet_vtxMass;   //!
   TBranch        *b_aJet_vtx3dL;   //!
   TBranch        *b_aJet_vtx3deL;   //!
   TBranch        *b_aJet_id;   //!
   TBranch        *b_aJet_SF_CSVL;   //!
   TBranch        *b_aJet_SF_CSVM;   //!
   TBranch        *b_aJet_SF_CSVT;   //!
   TBranch        *b_aJet_SF_CSVLerr;   //!
   TBranch        *b_aJet_SF_CSVMerr;   //!
   TBranch        *b_aJet_SF_CSVTerr;   //!
   TBranch        *b_naJetsFat;   //!
   TBranch        *b_aJetFat_pt;   //!
   TBranch        *b_aJetFat_eta;   //!
   TBranch        *b_aJetFat_phi;   //!
   TBranch        *b_aJetFat_e;   //!
   TBranch        *b_aJetFat_csv;   //!
   TBranch        *b_numJets;   //!
   TBranch        *b_numBJets;   //!
   TBranch        *b_deltaPullAngle;   //!
   TBranch        *b_deltaPullAngle2;   //!
   TBranch        *b_gendrcc;   //!
   TBranch        *b_gendrbb;   //!
   TBranch        *b_genZpt;   //!
   TBranch        *b_genWpt;   //!
   TBranch        *b_genHpt;   //!
   TBranch        *b_lheWeight;   //!
   TBranch        *b_weightTrig;   //!
   TBranch        *b_weightTrigMay;   //!
   TBranch        *b_weightTrigV4;   //!
   TBranch        *b_weightTrigMET;   //!
   TBranch        *b_weightTrigOrMu30;   //!
   TBranch        *b_weightEleRecoAndId;   //!
   TBranch        *b_weightEleTrigJetMETPart;   //!
   TBranch        *b_weightEleTrigElePart;   //!
   TBranch        *b_weightEleTrigEleAugPart;   //!
   TBranch        *b_weightTrigMET80;   //!
   TBranch        *b_weightTrigMET100;   //!
   TBranch        *b_weightTrig2CJet20;   //!
   TBranch        *b_weightTrigMET150;   //!
   TBranch        *b_weightTrigMET802CJet;   //!
   TBranch        *b_weightTrigMET1002CJet;   //!
   TBranch        *b_weightTrigMETLP;   //!
   TBranch        *b_weightTrig2012;   //!
   TBranch        *b_weightTrig2012A;   //!
   TBranch        *b_weightTrig2012ADiMuon;   //!
   TBranch        *b_weightTrig2012ADiEle;   //!
   TBranch        *b_weightTrig2012ASingleMuon;   //!
   TBranch        *b_weightTrig2012ASingleEle;   //!
   TBranch        *b_weightTrig2012AMuonPlusWCandPt;   //!
   TBranch        *b_weightTrig2012DiJet30MHT80;   //!
   TBranch        *b_weightTrig2012PFMET150;   //!
   TBranch        *b_weightTrig2012SumpT100MET100;   //!
   TBranch        *b_deltaPullAngleAK7;   //!
   TBranch        *b_deltaPullAngle2AK7;   //!
   TBranch        *b_PU0;   //!
   TBranch        *b_PUm1;   //!
   TBranch        *b_PUp1;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_PUweight2011B;   //!
   TBranch        *b_PUweight1DObs;   //!
   TBranch        *b_eventFlav;   //!
   TBranch        *b_Vtype;   //!
   TBranch        *b_HVdPhi;   //!
   TBranch        *b_HVMass;   //!
   TBranch        *b_HMETdPhi;   //!
   TBranch        *b_VMt;   //!
   TBranch        *b_nvlep;   //!
   TBranch        *b_nalep;   //!
   TBranch        *b_vLepton_mass;   //!
   TBranch        *b_vLepton_pt;   //!
   TBranch        *b_vLepton_eta;   //!
   TBranch        *b_vLepton_phi;   //!
   TBranch        *b_vLepton_aodCombRelIso;   //!
   TBranch        *b_vLepton_pfCombRelIso;   //!
   TBranch        *b_vLepton_photonIso;   //!
   TBranch        *b_vLepton_neutralHadIso;   //!
   TBranch        *b_vLepton_chargedHadIso;   //!
   TBranch        *b_vLepton_chargedPUIso;   //!
   TBranch        *b_vLepton_particleIso;   //!
   TBranch        *b_vLepton_dxy;   //!
   TBranch        *b_vLepton_dz;   //!
   TBranch        *b_vLepton_type;   //!
   TBranch        *b_vLepton_id80;   //!
   TBranch        *b_vLepton_id95;   //!
   TBranch        *b_vLepton_vbtf;   //!
   TBranch        *b_vLepton_id80NoIso;   //!
   TBranch        *b_vLepton_genPt;   //!
   TBranch        *b_vLepton_genEta;   //!
   TBranch        *b_vLepton_genPhi;   //!
   TBranch        *b_vLepton_charge;   //!
   TBranch        *b_vLepton_pfCorrIso;   //!
   TBranch        *b_vLepton_id2012tight;   //!
   TBranch        *b_vLepton_idMVAnotrig;   //!
   TBranch        *b_vLepton_idMVAtrig;   //!
   TBranch        *b_vLepton_idMVApresel;   //!
   TBranch        *b_vLepton_innerHits;   //!
   TBranch        *b_vLepton_photonIsoDoubleCount;   //!
   TBranch        *b_vLepton_wpHWW;   //!
   TBranch        *b_vLepton_wp95;   //!
   TBranch        *b_vLepton_wp90;   //!
   TBranch        *b_vLepton_wp85;   //!
   TBranch        *b_vLepton_wp80;   //!
   TBranch        *b_vLepton_wp70;   //!
   TBranch        *b_aLepton_mass;   //!
   TBranch        *b_aLepton_pt;   //!
   TBranch        *b_aLepton_eta;   //!
   TBranch        *b_aLepton_phi;   //!
   TBranch        *b_aLepton_aodCombRelIso;   //!
   TBranch        *b_aLepton_pfCombRelIso;   //!
   TBranch        *b_aLepton_photonIso;   //!
   TBranch        *b_aLepton_neutralHadIso;   //!
   TBranch        *b_aLepton_chargedHadIso;   //!
   TBranch        *b_aLepton_chargedPUIso;   //!
   TBranch        *b_aLepton_particleIso;   //!
   TBranch        *b_aLepton_dxy;   //!
   TBranch        *b_aLepton_dz;   //!
   TBranch        *b_aLepton_type;   //!
   TBranch        *b_aLepton_id80;   //!
   TBranch        *b_aLepton_id95;   //!
   TBranch        *b_aLepton_vbtf;   //!
   TBranch        *b_aLepton_id80NoIso;   //!
   TBranch        *b_aLepton_genPt;   //!
   TBranch        *b_aLepton_genEta;   //!
   TBranch        *b_aLepton_genPhi;   //!
   TBranch        *b_aLepton_charge;   //!
   TBranch        *b_aLepton_pfCorrIso;   //!
   TBranch        *b_aLepton_id2012tight;   //!
   TBranch        *b_aLepton_idMVAnotrig;   //!
   TBranch        *b_aLepton_idMVAtrig;   //!
   TBranch        *b_aLepton_idMVApresel;   //!
   TBranch        *b_aLepton_innerHits;   //!
   TBranch        *b_aLepton_photonIsoDoubleCount;   //!
   TBranch        *b_aLepton_wpHWW;   //!
   TBranch        *b_aLepton_wp95;   //!
   TBranch        *b_aLepton_wp90;   //!
   TBranch        *b_aLepton_wp85;   //!
   TBranch        *b_aLepton_wp80;   //!
   TBranch        *b_aLepton_wp70;   //!
   TBranch        *b_top;   //!
   TBranch        *b_WplusMode;   //!
   TBranch        *b_WminusMode;   //!
   TBranch        *b_nSvs;   //!
   TBranch        *b_Sv_massBCand;   //!
   TBranch        *b_Sv_massSv;   //!
   TBranch        *b_Sv_pt;   //!
   TBranch        *b_Sv_eta;   //!
   TBranch        *b_Sv_phi;   //!
   TBranch        *b_Sv_dist3D;   //!
   TBranch        *b_Sv_dist2D;   //!
   TBranch        *b_Sv_distSim2D;   //!
   TBranch        *b_Sv_distSig3D;   //!
   TBranch        *b_Sv_dist3D_norm;   //!
   TBranch        *b_SVH;   //!
   TBranch        *b_nSimBs;   //!
   TBranch        *b_SimBs_mass;   //!
   TBranch        *b_SimBs_pt;   //!
   TBranch        *b_SimBs_eta;   //!
   TBranch        *b_SimBs_phi;   //!
   TBranch        *b_SimBs_vtx_x;   //!
   TBranch        *b_SimBs_vtx_y;   //!
   TBranch        *b_SimBs_vtx_z;   //!
   TBranch        *b_SimBs_pdgId;   //!
   TBranch        *b_SimBs_status;   //!
   TBranch        *b_SimBsH;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rho25;   //!
   TBranch        *b_rhoN;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_METnoPU;   //!
   TBranch        *b_METnoPUCh;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METtype1corr;   //!
   TBranch        *b_METtype1p2corr;   //!
   TBranch        *b_METnoPUtype1corr;   //!
   TBranch        *b_METnoPUtype1p2corr;   //!
   TBranch        *b_et;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_sumet;   //!
   TBranch        *b_fakeMET;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_minDeltaPhijetMET;   //!
   TBranch        *b_jetPt_minDeltaPhijetMET;   //!
   TBranch        *b_triggerFlags;   //!
   TBranch        *b_EVENT;   //!
   TBranch        *b_hbhe;   //!
   TBranch        *b_totalKinematics;   //!
   TBranch        *b_ecalFlag;   //!
   TBranch        *b_cschaloFlag;   //!
   TBranch        *b_hcallaserFlag;   //!
   TBranch        *b_trackingfailureFlag;   //!
   TBranch        *b_btag1TSF;   //!
   TBranch        *b_btag2TSF;   //!
   TBranch        *b_btag1T2CSF;   //!
   TBranch        *b_btag2CSF;   //!
   TBranch        *b_btagA0CSF;   //!
   TBranch        *b_btagA0TSF;   //!
   TBranch        *b_btag1TA1C;   //!
   TBranch        *b_PUweight2011BUp;   //!
   TBranch        *b_PUweight2011BDown;   //!
   TBranch        *b_hJet_csvOld;   //!
   TBranch        *b_hJet_csvDown;   //!
   TBranch        *b_hJet_csvUp;   //!
   TBranch        *b_hJet_csvFDown;   //!
   TBranch        *b_hJet_csvFUp;   //!
   TBranch        *b_weightTrig_up;   //!
   TBranch        *b_weightTrigMay_up;   //!
   TBranch        *b_weightTrigV4_up;   //!
   TBranch        *b_weightTrigMET_up;   //!
   TBranch        *b_weightTrigOrMu30_up;   //!
   TBranch        *b_weightEleRecoAndId_up;   //!
   TBranch        *b_weightEleTrigJetMETPart_up;   //!
   TBranch        *b_weightEleTrigElePart_up;   //!

   ntupleLoader(const char *infile);
   virtual ~ntupleLoader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


ntupleLoader::ntupleLoader(const char * infile): 
  reshape("../data/csvdiscr.root",0,0),
  reshape_bTagUp("../data/csvdiscr.root",1,0),
  reshape_bTagDown("../data/csvdiscr.root",-1,0),
  reshape_misTagUp("../data/csvdiscr.root",0,1),
  reshape_misTagDown("../data/csvdiscr.root",0,-1)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  tree=0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(infile);
      if (!f || !f->IsOpen()) {
         f = new TFile(infile);
      }
      f->GetObject("tree",tree);

   }
   Init(tree);

//    //for the reshaping
//    BTagShapeInterface btagSh("../data/csvdisc.root",0,0);
//    sh = btagSh;

}

ntupleLoader::~ntupleLoader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ntupleLoader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ntupleLoader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ntupleLoader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("H", &H_HiggsFlag, &b_H);
   fChain->SetBranchAddress("V", &V_mass, &b_V);
   fChain->SetBranchAddress("FatH", &FatH_FatHiggsFlag, &b_FatH);
   fChain->SetBranchAddress("lheV_pt", &lheV_pt, &b_lheV_pt);
   fChain->SetBranchAddress("lheHT", &lheHT, &b_lheHT);
   fChain->SetBranchAddress("lheNj", &lheNj, &b_lheNj);
   fChain->SetBranchAddress("genZ", &genZ_mass, &b_genZ);
   fChain->SetBranchAddress("genZstar", &genZstar_mass, &b_genZstar);
   fChain->SetBranchAddress("genW", &genW_mass, &b_genW);
   fChain->SetBranchAddress("genWstar", &genWstar_mass, &b_genWstar);
   fChain->SetBranchAddress("genH", &genH_mass, &b_genH);
   fChain->SetBranchAddress("genB", &genB_mass, &b_genB);
   fChain->SetBranchAddress("genBbar", &genBbar_mass, &b_genBbar);
   fChain->SetBranchAddress("genTop", &genTop_bmass, &b_genTop);
   fChain->SetBranchAddress("genTbar", &genTbar_bmass, &b_genTbar);
   fChain->SetBranchAddress("TkSharing", &TkSharing_HiggsCSVtkSharing, &b_TkSharing);
   fChain->SetBranchAddress("nhJets", &nhJets, &b_nhJets);
   fChain->SetBranchAddress("nfathFilterJets", &nfathFilterJets, &b_nfathFilterJets);
   fChain->SetBranchAddress("naJets", &naJets, &b_naJets);
   fChain->SetBranchAddress("hJet_pt", hJet_pt, &b_hJet_pt);
   fChain->SetBranchAddress("hJet_eta", hJet_eta, &b_hJet_eta);
   fChain->SetBranchAddress("hJet_phi", hJet_phi, &b_hJet_phi);
   fChain->SetBranchAddress("hJet_e", hJet_e, &b_hJet_e);
   fChain->SetBranchAddress("hJet_csv", hJet_csv, &b_hJet_csv);
   fChain->SetBranchAddress("hJet_csv_nominal", hJet_csv_nominal, &b_hJet_csv_nominal);
   fChain->SetBranchAddress("hJet_csv_upBC", hJet_csv_upBC, &b_hJet_csv_upBC);
   fChain->SetBranchAddress("hJet_csv_downBC", hJet_csv_downBC, &b_hJet_csv_downBC);
   fChain->SetBranchAddress("hJet_csv_upL", hJet_csv_upL, &b_hJet_csv_upL);
   fChain->SetBranchAddress("hJet_csv_downL", hJet_csv_downL, &b_hJet_csv_downL);
   fChain->SetBranchAddress("hJet_csvivf", hJet_csvivf, &b_hJet_csvivf);
   fChain->SetBranchAddress("hJet_cmva", hJet_cmva, &b_hJet_cmva);
   fChain->SetBranchAddress("hJet_cosTheta", hJet_cosTheta, &b_hJet_cosTheta);
   fChain->SetBranchAddress("hJet_numTracksSV", hJet_numTracksSV, &b_hJet_numTracksSV);
   fChain->SetBranchAddress("hJet_chf", hJet_chf, &b_hJet_chf);
   fChain->SetBranchAddress("hJet_nhf", hJet_nhf, &b_hJet_nhf);
   fChain->SetBranchAddress("hJet_cef", hJet_cef, &b_hJet_cef);
   fChain->SetBranchAddress("hJet_nef", hJet_nef, &b_hJet_nef);
   fChain->SetBranchAddress("hJet_nch", hJet_nch, &b_hJet_nch);
   fChain->SetBranchAddress("hJet_nconstituents", hJet_nconstituents, &b_hJet_nconstituents);
   fChain->SetBranchAddress("hJet_flavour", hJet_flavour, &b_hJet_flavour);
   fChain->SetBranchAddress("hJet_isSemiLept", hJet_isSemiLept, &b_hJet_isSemiLept);
   fChain->SetBranchAddress("hJet_isSemiLeptMCtruth", hJet_isSemiLeptMCtruth, &b_hJet_isSemiLeptMCtruth);
   fChain->SetBranchAddress("hJet_SoftLeptpdgId", hJet_SoftLeptpdgId, &b_hJet_SoftLeptpdgId);
   fChain->SetBranchAddress("hJet_SoftLeptIdlooseMu", hJet_SoftLeptIdlooseMu, &b_hJet_SoftLeptIdlooseMu);
   fChain->SetBranchAddress("hJet_SoftLeptId95", hJet_SoftLeptId95, &b_hJet_SoftLeptId95);
   fChain->SetBranchAddress("hJet_SoftLeptPt", hJet_SoftLeptPt, &b_hJet_SoftLeptPt);
   fChain->SetBranchAddress("hJet_SoftLeptdR", hJet_SoftLeptdR, &b_hJet_SoftLeptdR);
   fChain->SetBranchAddress("hJet_SoftLeptptRel", hJet_SoftLeptptRel, &b_hJet_SoftLeptptRel);
   fChain->SetBranchAddress("hJet_SoftLeptRelCombIso", hJet_SoftLeptRelCombIso, &b_hJet_SoftLeptRelCombIso);
   fChain->SetBranchAddress("hJet_genPt", hJet_genPt, &b_hJet_genPt);
   fChain->SetBranchAddress("hJet_genEta", hJet_genEta, &b_hJet_genEta);
   fChain->SetBranchAddress("hJet_genPhi", hJet_genPhi, &b_hJet_genPhi);
   fChain->SetBranchAddress("hJet_JECUnc", hJet_JECUnc, &b_hJet_JECUnc);
   fChain->SetBranchAddress("hJet_vtxMass", hJet_vtxMass, &b_hJet_vtxMass);
   fChain->SetBranchAddress("hJet_vtxPt", hJet_vtxPt, &b_hJet_vtxPt);
   fChain->SetBranchAddress("hJet_vtxEta", hJet_vtxEta, &b_hJet_vtxEta);
   fChain->SetBranchAddress("hJet_vtxPhi", hJet_vtxPhi, &b_hJet_vtxPhi);
   fChain->SetBranchAddress("hJet_vtxE", hJet_vtxE, &b_hJet_vtxE);
   fChain->SetBranchAddress("hJet_vtx3dL", hJet_vtx3dL, &b_hJet_vtx3dL);
   fChain->SetBranchAddress("hJet_vtx3deL", hJet_vtx3deL, &b_hJet_vtx3deL);
   fChain->SetBranchAddress("hJet_id", hJet_id, &b_hJet_id);
   fChain->SetBranchAddress("hJet_SF_CSVL", hJet_SF_CSVL, &b_hJet_SF_CSVL);
   fChain->SetBranchAddress("hJet_SF_CSVM", hJet_SF_CSVM, &b_hJet_SF_CSVM);
   fChain->SetBranchAddress("hJet_SF_CSVT", hJet_SF_CSVT, &b_hJet_SF_CSVT);
   fChain->SetBranchAddress("hJet_SF_CSVLerr", hJet_SF_CSVLerr, &b_hJet_SF_CSVLerr);
   fChain->SetBranchAddress("hJet_SF_CSVMerr", hJet_SF_CSVMerr, &b_hJet_SF_CSVMerr);
   fChain->SetBranchAddress("hJet_SF_CSVTerr", hJet_SF_CSVTerr, &b_hJet_SF_CSVTerr);
   fChain->SetBranchAddress("hJet_ptRaw", hJet_ptRaw, &b_hJet_ptRaw);
   fChain->SetBranchAddress("hJet_ptLeadTrack", hJet_ptLeadTrack, &b_hJet_ptLeadTrack);
   fChain->SetBranchAddress("hJet_puJetIdL", hJet_puJetIdL, &b_hJet_puJetIdL);
   fChain->SetBranchAddress("hJet_puJetIdM", hJet_puJetIdM, &b_hJet_puJetIdM);
   fChain->SetBranchAddress("hJet_puJetIdT", hJet_puJetIdT, &b_hJet_puJetIdT);
   fChain->SetBranchAddress("hJet_puJetIdMva", hJet_puJetIdMva, &b_hJet_puJetIdMva);
   fChain->SetBranchAddress("fathFilterJets_pt", fathFilterJets_pt, &b_fathFilterJets_pt);
   fChain->SetBranchAddress("fathFilterJets_eta", fathFilterJets_eta, &b_fathFilterJets_eta);
   fChain->SetBranchAddress("fathFilterJets_phi", fathFilterJets_phi, &b_fathFilterJets_phi);
   fChain->SetBranchAddress("fathFilterJets_e", fathFilterJets_e, &b_fathFilterJets_e);
   fChain->SetBranchAddress("fathFilterJets_csv", fathFilterJets_csv, &b_fathFilterJets_csv);
   fChain->SetBranchAddress("fathFilterJets_chf", fathFilterJets_chf, &b_fathFilterJets_chf);
   fChain->SetBranchAddress("fathFilterJets_ptRaw", fathFilterJets_ptRaw, &b_fathFilterJets_ptRaw);
   fChain->SetBranchAddress("fathFilterJets_ptLeadTrack", fathFilterJets_ptLeadTrack, &b_fathFilterJets_ptLeadTrack);
   fChain->SetBranchAddress("fathFilterJets_flavour", fathFilterJets_flavour, &b_fathFilterJets_flavour);
   fChain->SetBranchAddress("fathFilterJets_isSemiLept", fathFilterJets_isSemiLept, &b_fathFilterJets_isSemiLept);
   fChain->SetBranchAddress("fathFilterJets_isSemiLeptMCtruth", fathFilterJets_isSemiLeptMCtruth, &b_fathFilterJets_isSemiLeptMCtruth);
   fChain->SetBranchAddress("fathFilterJets_genPt", fathFilterJets_genPt, &b_fathFilterJets_genPt);
   fChain->SetBranchAddress("fathFilterJets_genEta", fathFilterJets_genEta, &b_fathFilterJets_genEta);
   fChain->SetBranchAddress("fathFilterJets_genPhi", fathFilterJets_genPhi, &b_fathFilterJets_genPhi);
   fChain->SetBranchAddress("fathFilterJets_vtxMass", fathFilterJets_vtxMass, &b_fathFilterJets_vtxMass);
   fChain->SetBranchAddress("fathFilterJets_vtx3dL", fathFilterJets_vtx3dL, &b_fathFilterJets_vtx3dL);
   fChain->SetBranchAddress("fathFilterJets_vtx3deL", fathFilterJets_vtx3deL, &b_fathFilterJets_vtx3deL);
   fChain->SetBranchAddress("fathFilterJets_vtxPt", fathFilterJets_vtxPt, &b_fathFilterJets_vtxPt);
   fChain->SetBranchAddress("fathFilterJets_vtxEta", fathFilterJets_vtxEta, &b_fathFilterJets_vtxEta);
   fChain->SetBranchAddress("fathFilterJets_vtxPhi", fathFilterJets_vtxPhi, &b_fathFilterJets_vtxPhi);
   fChain->SetBranchAddress("fathFilterJets_vtxE", fathFilterJets_vtxE, &b_fathFilterJets_vtxE);
   fChain->SetBranchAddress("fathFilterJets_AnglePVtoSVmom", fathFilterJets_AnglePVtoSVmom, &b_fathFilterJets_AnglePVtoSVmom);
   fChain->SetBranchAddress("fathFilterJets_AnglePVtoJetmom", fathFilterJets_AnglePVtoJetmom, &b_fathFilterJets_AnglePVtoJetmom);
   fChain->SetBranchAddress("fathFilterJets_csvivf", fathFilterJets_csvivf, &b_fathFilterJets_csvivf);
   fChain->SetBranchAddress("fathFilterJets_cmva", fathFilterJets_cmva, &b_fathFilterJets_cmva);
   fChain->SetBranchAddress("aJet_pt", aJet_pt, &b_aJet_pt);
   fChain->SetBranchAddress("aJet_eta", aJet_eta, &b_aJet_eta);
   fChain->SetBranchAddress("aJet_phi", aJet_phi, &b_aJet_phi);
   fChain->SetBranchAddress("aJet_e", aJet_e, &b_aJet_e);
   fChain->SetBranchAddress("aJet_csv", aJet_csv, &b_aJet_csv);
   fChain->SetBranchAddress("aJet_csv_nominal", aJet_csv_nominal, &b_aJet_csv_nominal);
   fChain->SetBranchAddress("aJet_csv_upBC", aJet_csv_upBC, &b_aJet_csv_upBC);
   fChain->SetBranchAddress("aJet_csv_downBC", aJet_csv_downBC, &b_aJet_csv_downBC);
   fChain->SetBranchAddress("aJet_csv_upL", aJet_csv_upL, &b_aJet_csv_upL);
   fChain->SetBranchAddress("aJet_csv_downL", aJet_csv_downL, &b_aJet_csv_downL);
   fChain->SetBranchAddress("aJet_csvivf", aJet_csvivf, &b_aJet_csvivf);
   fChain->SetBranchAddress("aJet_cmva", aJet_cmva, &b_aJet_cmva);
   fChain->SetBranchAddress("aJet_cosTheta", aJet_cosTheta, &b_aJet_cosTheta);
   fChain->SetBranchAddress("aJet_numTracksSV", aJet_numTracksSV, &b_aJet_numTracksSV);
   fChain->SetBranchAddress("aJet_chf", aJet_chf, &b_aJet_chf);
   fChain->SetBranchAddress("aJet_nhf", aJet_nhf, &b_aJet_nhf);
   fChain->SetBranchAddress("aJet_cef", aJet_cef, &b_aJet_cef);
   fChain->SetBranchAddress("aJet_nef", aJet_nef, &b_aJet_nef);
   fChain->SetBranchAddress("aJet_nch", aJet_nch, &b_aJet_nch);
   fChain->SetBranchAddress("aJet_nconstituents", aJet_nconstituents, &b_aJet_nconstituents);
   fChain->SetBranchAddress("aJet_flavour", aJet_flavour, &b_aJet_flavour);
   fChain->SetBranchAddress("aJet_isSemiLept", aJet_isSemiLept, &b_aJet_isSemiLept);
   fChain->SetBranchAddress("aJet_isSemiLeptMCtruth", aJet_isSemiLeptMCtruth, &b_aJet_isSemiLeptMCtruth);
   fChain->SetBranchAddress("aJet_SoftLeptpdgId", aJet_SoftLeptpdgId, &b_aJet_SoftLeptpdgId);
   fChain->SetBranchAddress("aJet_SoftLeptIdlooseMu", aJet_SoftLeptIdlooseMu, &b_aJet_SoftLeptIdlooseMu);
   fChain->SetBranchAddress("aJet_SoftLeptId95", aJet_SoftLeptId95, &b_aJet_SoftLeptId95);
   fChain->SetBranchAddress("aJet_SoftLeptPt", aJet_SoftLeptPt, &b_aJet_SoftLeptPt);
   fChain->SetBranchAddress("aJet_SoftLeptdR", aJet_SoftLeptdR, &b_aJet_SoftLeptdR);
   fChain->SetBranchAddress("aJet_SoftLeptptRel", aJet_SoftLeptptRel, &b_aJet_SoftLeptptRel);
   fChain->SetBranchAddress("aJet_SoftLeptRelCombIso", aJet_SoftLeptRelCombIso, &b_aJet_SoftLeptRelCombIso);
   fChain->SetBranchAddress("aJet_puJetIdL", aJet_puJetIdL, &b_aJet_puJetIdL);
   fChain->SetBranchAddress("aJet_puJetIdM", aJet_puJetIdM, &b_aJet_puJetIdM);
   fChain->SetBranchAddress("aJet_puJetIdT", aJet_puJetIdT, &b_aJet_puJetIdT);
   fChain->SetBranchAddress("aJet_puJetIdMva", aJet_puJetIdMva, &b_aJet_puJetIdMva);
   fChain->SetBranchAddress("aJet_genPt", aJet_genPt, &b_aJet_genPt);
   fChain->SetBranchAddress("aJet_genEta", aJet_genEta, &b_aJet_genEta);
   fChain->SetBranchAddress("aJet_genPhi", aJet_genPhi, &b_aJet_genPhi);
   fChain->SetBranchAddress("aJet_JECUnc", aJet_JECUnc, &b_aJet_JECUnc);
   fChain->SetBranchAddress("aJet_vtxMass", aJet_vtxMass, &b_aJet_vtxMass);
   fChain->SetBranchAddress("aJet_vtx3dL", aJet_vtx3dL, &b_aJet_vtx3dL);
   fChain->SetBranchAddress("aJet_vtx3deL", aJet_vtx3deL, &b_aJet_vtx3deL);
   fChain->SetBranchAddress("aJet_id", aJet_id, &b_aJet_id);
   fChain->SetBranchAddress("aJet_SF_CSVL", aJet_SF_CSVL, &b_aJet_SF_CSVL);
   fChain->SetBranchAddress("aJet_SF_CSVM", aJet_SF_CSVM, &b_aJet_SF_CSVM);
   fChain->SetBranchAddress("aJet_SF_CSVT", aJet_SF_CSVT, &b_aJet_SF_CSVT);
   fChain->SetBranchAddress("aJet_SF_CSVLerr", aJet_SF_CSVLerr, &b_aJet_SF_CSVLerr);
   fChain->SetBranchAddress("aJet_SF_CSVMerr", aJet_SF_CSVMerr, &b_aJet_SF_CSVMerr);
   fChain->SetBranchAddress("aJet_SF_CSVTerr", aJet_SF_CSVTerr, &b_aJet_SF_CSVTerr);
   fChain->SetBranchAddress("naJetsFat", &naJetsFat, &b_naJetsFat);
   fChain->SetBranchAddress("aJetFat_pt", aJetFat_pt, &b_aJetFat_pt);
   fChain->SetBranchAddress("aJetFat_eta", aJetFat_eta, &b_aJetFat_eta);
   fChain->SetBranchAddress("aJetFat_phi", aJetFat_phi, &b_aJetFat_phi);
   fChain->SetBranchAddress("aJetFat_e", aJetFat_e, &b_aJetFat_e);
   fChain->SetBranchAddress("aJetFat_csv", aJetFat_csv, &b_aJetFat_csv);
   fChain->SetBranchAddress("numJets", &numJets, &b_numJets);
   fChain->SetBranchAddress("numBJets", &numBJets, &b_numBJets);
   fChain->SetBranchAddress("deltaPullAngle", &deltaPullAngle, &b_deltaPullAngle);
   fChain->SetBranchAddress("deltaPullAngle2", &deltaPullAngle2, &b_deltaPullAngle2);
   fChain->SetBranchAddress("gendrcc", &gendrcc, &b_gendrcc);
   fChain->SetBranchAddress("gendrbb", &gendrbb, &b_gendrbb);
   fChain->SetBranchAddress("genZpt", &genZpt, &b_genZpt);
   fChain->SetBranchAddress("genWpt", &genWpt, &b_genWpt);
   fChain->SetBranchAddress("genHpt", &genHpt, &b_genHpt);
   fChain->SetBranchAddress("lheWeight", &lheWeight, &b_lheWeight);
   fChain->SetBranchAddress("weightTrig", &weightTrig, &b_weightTrig);
   fChain->SetBranchAddress("weightTrigMay", &weightTrigMay, &b_weightTrigMay);
   fChain->SetBranchAddress("weightTrigV4", &weightTrigV4, &b_weightTrigV4);
   fChain->SetBranchAddress("weightTrigMET", &weightTrigMET, &b_weightTrigMET);
   fChain->SetBranchAddress("weightTrigOrMu30", &weightTrigOrMu30, &b_weightTrigOrMu30);
   fChain->SetBranchAddress("weightEleRecoAndId", &weightEleRecoAndId, &b_weightEleRecoAndId);
   fChain->SetBranchAddress("weightEleTrigJetMETPart", &weightEleTrigJetMETPart, &b_weightEleTrigJetMETPart);
   fChain->SetBranchAddress("weightEleTrigElePart", &weightEleTrigElePart, &b_weightEleTrigElePart);
   fChain->SetBranchAddress("weightEleTrigEleAugPart", &weightEleTrigEleAugPart, &b_weightEleTrigEleAugPart);
   fChain->SetBranchAddress("weightTrigMET80", &weightTrigMET80, &b_weightTrigMET80);
   fChain->SetBranchAddress("weightTrigMET100", &weightTrigMET100, &b_weightTrigMET100);
   fChain->SetBranchAddress("weightTrig2CJet20", &weightTrig2CJet20, &b_weightTrig2CJet20);
   fChain->SetBranchAddress("weightTrigMET150", &weightTrigMET150, &b_weightTrigMET150);
   fChain->SetBranchAddress("weightTrigMET802CJet", &weightTrigMET802CJet, &b_weightTrigMET802CJet);
   fChain->SetBranchAddress("weightTrigMET1002CJet", &weightTrigMET1002CJet, &b_weightTrigMET1002CJet);
   fChain->SetBranchAddress("weightTrigMETLP", &weightTrigMETLP, &b_weightTrigMETLP);
   fChain->SetBranchAddress("weightTrig2012", &weightTrig2012, &b_weightTrig2012);
   fChain->SetBranchAddress("weightTrig2012A", &weightTrig2012A, &b_weightTrig2012A);
   fChain->SetBranchAddress("weightTrig2012ADiMuon", &weightTrig2012ADiMuon, &b_weightTrig2012ADiMuon);
   fChain->SetBranchAddress("weightTrig2012ADiEle", &weightTrig2012ADiEle, &b_weightTrig2012ADiEle);
   fChain->SetBranchAddress("weightTrig2012ASingleMuon", &weightTrig2012ASingleMuon, &b_weightTrig2012ASingleMuon);
   fChain->SetBranchAddress("weightTrig2012ASingleEle", &weightTrig2012ASingleEle, &b_weightTrig2012ASingleEle);
   fChain->SetBranchAddress("weightTrig2012AMuonPlusWCandPt", &weightTrig2012AMuonPlusWCandPt, &b_weightTrig2012AMuonPlusWCandPt);
   fChain->SetBranchAddress("weightTrig2012DiJet30MHT80", &weightTrig2012DiJet30MHT80, &b_weightTrig2012DiJet30MHT80);
   fChain->SetBranchAddress("weightTrig2012PFMET150", &weightTrig2012PFMET150, &b_weightTrig2012PFMET150);
   fChain->SetBranchAddress("weightTrig2012SumpT100MET100", &weightTrig2012SumpT100MET100, &b_weightTrig2012SumpT100MET100);
   fChain->SetBranchAddress("deltaPullAngleAK7", &deltaPullAngleAK7, &b_deltaPullAngleAK7);
   fChain->SetBranchAddress("deltaPullAngle2AK7", &deltaPullAngle2AK7, &b_deltaPullAngle2AK7);
   fChain->SetBranchAddress("PU0", &PU0, &b_PU0);
   fChain->SetBranchAddress("PUm1", &PUm1, &b_PUm1);
   fChain->SetBranchAddress("PUp1", &PUp1, &b_PUp1);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("PUweight2011B", &PUweight2011B, &b_PUweight2011B);
   fChain->SetBranchAddress("PUweight1DObs", &PUweight1DObs, &b_PUweight1DObs);
   fChain->SetBranchAddress("eventFlav", &eventFlav, &b_eventFlav);
   fChain->SetBranchAddress("Vtype", &Vtype, &b_Vtype);
   fChain->SetBranchAddress("HVdPhi", &HVdPhi, &b_HVdPhi);
   fChain->SetBranchAddress("HVMass", &HVMass, &b_HVMass);
   fChain->SetBranchAddress("HMETdPhi", &HMETdPhi, &b_HMETdPhi);
   fChain->SetBranchAddress("VMt", &VMt, &b_VMt);
   fChain->SetBranchAddress("nvlep", &nvlep, &b_nvlep);
   fChain->SetBranchAddress("nalep", &nalep, &b_nalep);
   fChain->SetBranchAddress("vLepton_mass", vLepton_mass, &b_vLepton_mass);
   fChain->SetBranchAddress("vLepton_pt", vLepton_pt, &b_vLepton_pt);
   fChain->SetBranchAddress("vLepton_eta", vLepton_eta, &b_vLepton_eta);
   fChain->SetBranchAddress("vLepton_phi", vLepton_phi, &b_vLepton_phi);
   fChain->SetBranchAddress("vLepton_aodCombRelIso", vLepton_aodCombRelIso, &b_vLepton_aodCombRelIso);
   fChain->SetBranchAddress("vLepton_pfCombRelIso", vLepton_pfCombRelIso, &b_vLepton_pfCombRelIso);
   fChain->SetBranchAddress("vLepton_photonIso", vLepton_photonIso, &b_vLepton_photonIso);
   fChain->SetBranchAddress("vLepton_neutralHadIso", vLepton_neutralHadIso, &b_vLepton_neutralHadIso);
   fChain->SetBranchAddress("vLepton_chargedHadIso", vLepton_chargedHadIso, &b_vLepton_chargedHadIso);
   fChain->SetBranchAddress("vLepton_chargedPUIso", vLepton_chargedPUIso, &b_vLepton_chargedPUIso);
   fChain->SetBranchAddress("vLepton_particleIso", vLepton_particleIso, &b_vLepton_particleIso);
   fChain->SetBranchAddress("vLepton_dxy", vLepton_dxy, &b_vLepton_dxy);
   fChain->SetBranchAddress("vLepton_dz", vLepton_dz, &b_vLepton_dz);
   fChain->SetBranchAddress("vLepton_type", vLepton_type, &b_vLepton_type);
   fChain->SetBranchAddress("vLepton_id80", vLepton_id80, &b_vLepton_id80);
   fChain->SetBranchAddress("vLepton_id95", vLepton_id95, &b_vLepton_id95);
   fChain->SetBranchAddress("vLepton_vbtf", vLepton_vbtf, &b_vLepton_vbtf);
   fChain->SetBranchAddress("vLepton_id80NoIso", vLepton_id80NoIso, &b_vLepton_id80NoIso);
   fChain->SetBranchAddress("vLepton_genPt", vLepton_genPt, &b_vLepton_genPt);
   fChain->SetBranchAddress("vLepton_genEta", vLepton_genEta, &b_vLepton_genEta);
   fChain->SetBranchAddress("vLepton_genPhi", vLepton_genPhi, &b_vLepton_genPhi);
   fChain->SetBranchAddress("vLepton_charge", vLepton_charge, &b_vLepton_charge);
   fChain->SetBranchAddress("vLepton_pfCorrIso", vLepton_pfCorrIso, &b_vLepton_pfCorrIso);
   fChain->SetBranchAddress("vLepton_id2012tight", vLepton_id2012tight, &b_vLepton_id2012tight);
   fChain->SetBranchAddress("vLepton_idMVAnotrig", vLepton_idMVAnotrig, &b_vLepton_idMVAnotrig);
   fChain->SetBranchAddress("vLepton_idMVAtrig", vLepton_idMVAtrig, &b_vLepton_idMVAtrig);
   fChain->SetBranchAddress("vLepton_idMVApresel", vLepton_idMVApresel, &b_vLepton_idMVApresel);
   fChain->SetBranchAddress("vLepton_innerHits", vLepton_innerHits, &b_vLepton_innerHits);
   fChain->SetBranchAddress("vLepton_photonIsoDoubleCount", vLepton_photonIsoDoubleCount, &b_vLepton_photonIsoDoubleCount);
   fChain->SetBranchAddress("vLepton_wpHWW", vLepton_wpHWW, &b_vLepton_wpHWW);
   fChain->SetBranchAddress("vLepton_wp95", vLepton_wp95, &b_vLepton_wp95);
   fChain->SetBranchAddress("vLepton_wp90", vLepton_wp90, &b_vLepton_wp90);
   fChain->SetBranchAddress("vLepton_wp85", vLepton_wp85, &b_vLepton_wp85);
   fChain->SetBranchAddress("vLepton_wp80", vLepton_wp80, &b_vLepton_wp80);
   fChain->SetBranchAddress("vLepton_wp70", vLepton_wp70, &b_vLepton_wp70);
   fChain->SetBranchAddress("aLepton_mass", aLepton_mass, &b_aLepton_mass);
   fChain->SetBranchAddress("aLepton_pt", aLepton_pt, &b_aLepton_pt);
   fChain->SetBranchAddress("aLepton_eta", aLepton_eta, &b_aLepton_eta);
   fChain->SetBranchAddress("aLepton_phi", aLepton_phi, &b_aLepton_phi);
   fChain->SetBranchAddress("aLepton_aodCombRelIso", aLepton_aodCombRelIso, &b_aLepton_aodCombRelIso);
   fChain->SetBranchAddress("aLepton_pfCombRelIso", aLepton_pfCombRelIso, &b_aLepton_pfCombRelIso);
   fChain->SetBranchAddress("aLepton_photonIso", aLepton_photonIso, &b_aLepton_photonIso);
   fChain->SetBranchAddress("aLepton_neutralHadIso", aLepton_neutralHadIso, &b_aLepton_neutralHadIso);
   fChain->SetBranchAddress("aLepton_chargedHadIso", aLepton_chargedHadIso, &b_aLepton_chargedHadIso);
   fChain->SetBranchAddress("aLepton_chargedPUIso", aLepton_chargedPUIso, &b_aLepton_chargedPUIso);
   fChain->SetBranchAddress("aLepton_particleIso", aLepton_particleIso, &b_aLepton_particleIso);
   fChain->SetBranchAddress("aLepton_dxy", aLepton_dxy, &b_aLepton_dxy);
   fChain->SetBranchAddress("aLepton_dz", aLepton_dz, &b_aLepton_dz);
   fChain->SetBranchAddress("aLepton_type", aLepton_type, &b_aLepton_type);
   fChain->SetBranchAddress("aLepton_id80", aLepton_id80, &b_aLepton_id80);
   fChain->SetBranchAddress("aLepton_id95", aLepton_id95, &b_aLepton_id95);
   fChain->SetBranchAddress("aLepton_vbtf", aLepton_vbtf, &b_aLepton_vbtf);
   fChain->SetBranchAddress("aLepton_id80NoIso", aLepton_id80NoIso, &b_aLepton_id80NoIso);
   fChain->SetBranchAddress("aLepton_genPt", aLepton_genPt, &b_aLepton_genPt);
   fChain->SetBranchAddress("aLepton_genEta", aLepton_genEta, &b_aLepton_genEta);
   fChain->SetBranchAddress("aLepton_genPhi", aLepton_genPhi, &b_aLepton_genPhi);
   fChain->SetBranchAddress("aLepton_charge", aLepton_charge, &b_aLepton_charge);
   fChain->SetBranchAddress("aLepton_pfCorrIso", aLepton_pfCorrIso, &b_aLepton_pfCorrIso);
   fChain->SetBranchAddress("aLepton_id2012tight", aLepton_id2012tight, &b_aLepton_id2012tight);
   fChain->SetBranchAddress("aLepton_idMVAnotrig", aLepton_idMVAnotrig, &b_aLepton_idMVAnotrig);
   fChain->SetBranchAddress("aLepton_idMVAtrig", aLepton_idMVAtrig, &b_aLepton_idMVAtrig);
   fChain->SetBranchAddress("aLepton_idMVApresel", aLepton_idMVApresel, &b_aLepton_idMVApresel);
   fChain->SetBranchAddress("aLepton_innerHits", aLepton_innerHits, &b_aLepton_innerHits);
   fChain->SetBranchAddress("aLepton_photonIsoDoubleCount", aLepton_photonIsoDoubleCount, &b_aLepton_photonIsoDoubleCount);
   fChain->SetBranchAddress("aLepton_wpHWW", aLepton_wpHWW, &b_aLepton_wpHWW);
   fChain->SetBranchAddress("aLepton_wp95", aLepton_wp95, &b_aLepton_wp95);
   fChain->SetBranchAddress("aLepton_wp90", aLepton_wp90, &b_aLepton_wp90);
   fChain->SetBranchAddress("aLepton_wp85", aLepton_wp85, &b_aLepton_wp85);
   fChain->SetBranchAddress("aLepton_wp80", aLepton_wp80, &b_aLepton_wp80);
   fChain->SetBranchAddress("aLepton_wp70", aLepton_wp70, &b_aLepton_wp70);
   fChain->SetBranchAddress("top", &top_mass, &b_top);
   fChain->SetBranchAddress("WplusMode", &WplusMode, &b_WplusMode);
   fChain->SetBranchAddress("WminusMode", &WminusMode, &b_WminusMode);
   fChain->SetBranchAddress("nSvs", &nSvs, &b_nSvs);
   fChain->SetBranchAddress("Sv_massBCand", Sv_massBCand, &b_Sv_massBCand);
   fChain->SetBranchAddress("Sv_massSv", Sv_massSv, &b_Sv_massSv);
   fChain->SetBranchAddress("Sv_pt", Sv_pt, &b_Sv_pt);
   fChain->SetBranchAddress("Sv_eta", Sv_eta, &b_Sv_eta);
   fChain->SetBranchAddress("Sv_phi", Sv_phi, &b_Sv_phi);
   fChain->SetBranchAddress("Sv_dist3D", Sv_dist3D, &b_Sv_dist3D);
   fChain->SetBranchAddress("Sv_dist2D", Sv_dist2D, &b_Sv_dist2D);
   fChain->SetBranchAddress("Sv_distSim2D", Sv_distSim2D, &b_Sv_distSim2D);
   fChain->SetBranchAddress("Sv_distSig3D", Sv_distSig3D, &b_Sv_distSig3D);
   fChain->SetBranchAddress("Sv_dist3D_norm", Sv_dist3D_norm, &b_Sv_dist3D_norm);
   fChain->SetBranchAddress("SVH", &SVH_mass, &b_SVH);
   fChain->SetBranchAddress("nSimBs", &nSimBs, &b_nSimBs);
   fChain->SetBranchAddress("SimBs_mass", SimBs_mass, &b_SimBs_mass);
   fChain->SetBranchAddress("SimBs_pt", SimBs_pt, &b_SimBs_pt);
   fChain->SetBranchAddress("SimBs_eta", SimBs_eta, &b_SimBs_eta);
   fChain->SetBranchAddress("SimBs_phi", SimBs_phi, &b_SimBs_phi);
   fChain->SetBranchAddress("SimBs_vtx_x", SimBs_vtx_x, &b_SimBs_vtx_x);
   fChain->SetBranchAddress("SimBs_vtx_y", SimBs_vtx_y, &b_SimBs_vtx_y);
   fChain->SetBranchAddress("SimBs_vtx_z", SimBs_vtx_z, &b_SimBs_vtx_z);
   fChain->SetBranchAddress("SimBs_pdgId", SimBs_pdgId, &b_SimBs_pdgId);
   fChain->SetBranchAddress("SimBs_status", SimBs_status, &b_SimBs_status);
   fChain->SetBranchAddress("SimBsH", &SimBsH_mass, &b_SimBsH);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
   fChain->SetBranchAddress("rhoN", &rhoN, &b_rhoN);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("METnoPU", &METnoPU_et, &b_METnoPU);
   fChain->SetBranchAddress("METnoPUCh", &METnoPUCh_et, &b_METnoPUCh);
   fChain->SetBranchAddress("MET", &MET_et, &b_MET);
   fChain->SetBranchAddress("METtype1corr", &METtype1corr_et, &b_METtype1corr);
   fChain->SetBranchAddress("METtype1p2corr", &METtype1p2corr_et, &b_METtype1p2corr);
   fChain->SetBranchAddress("METnoPUtype1corr", &METnoPUtype1corr_et, &b_METnoPUtype1corr);
   fChain->SetBranchAddress("METnoPUtype1p2corr", &METnoPUtype1p2corr_et, &b_METnoPUtype1p2corr);
   fChain->SetBranchAddress("metUnc_et", metUnc_et, &b_et);
   fChain->SetBranchAddress("metUnc_phi", metUnc_phi, &b_phi);
   fChain->SetBranchAddress("metUnc_sumet", metUnc_sumet, &b_sumet);
   fChain->SetBranchAddress("fakeMET", &fakeMET_et, &b_fakeMET);
   fChain->SetBranchAddress("MHT", &MHT_mht, &b_MHT);
   fChain->SetBranchAddress("minDeltaPhijetMET", &minDeltaPhijetMET, &b_minDeltaPhijetMET);
   fChain->SetBranchAddress("jetPt_minDeltaPhijetMET", &jetPt_minDeltaPhijetMET, &b_jetPt_minDeltaPhijetMET);
   fChain->SetBranchAddress("triggerFlags", triggerFlags, &b_triggerFlags);
   fChain->SetBranchAddress("EVENT", &EVENT_run, &b_EVENT);
   fChain->SetBranchAddress("hbhe", &hbhe, &b_hbhe);
   fChain->SetBranchAddress("totalKinematics", &totalKinematics, &b_totalKinematics);
   fChain->SetBranchAddress("ecalFlag", &ecalFlag, &b_ecalFlag);
   fChain->SetBranchAddress("cschaloFlag", &cschaloFlag, &b_cschaloFlag);
   fChain->SetBranchAddress("hcallaserFlag", &hcallaserFlag, &b_hcallaserFlag);
   fChain->SetBranchAddress("trackingfailureFlag", &trackingfailureFlag, &b_trackingfailureFlag);
   fChain->SetBranchAddress("btag1TSF", &btag1TSF, &b_btag1TSF);
   fChain->SetBranchAddress("btag2TSF", &btag2TSF, &b_btag2TSF);
   fChain->SetBranchAddress("btag1T2CSF", &btag1T2CSF, &b_btag1T2CSF);
   fChain->SetBranchAddress("btag2CSF", &btag2CSF, &b_btag2CSF);
   fChain->SetBranchAddress("btagA0CSF", &btagA0CSF, &b_btagA0CSF);
   fChain->SetBranchAddress("btagA0TSF", &btagA0TSF, &b_btagA0TSF);
   fChain->SetBranchAddress("btag1TA1C", &btag1TA1C, &b_btag1TA1C);
   fChain->SetBranchAddress("PUweight2011BUp", &PUweight2011BUp, &b_PUweight2011BUp);
   fChain->SetBranchAddress("PUweight2011BDown", &PUweight2011BDown, &b_PUweight2011BDown);
   fChain->SetBranchAddress("hJet_csvOld", hJet_csvOld, &b_hJet_csvOld);
   fChain->SetBranchAddress("hJet_csvDown", hJet_csvDown, &b_hJet_csvDown);
   fChain->SetBranchAddress("hJet_csvUp", hJet_csvUp, &b_hJet_csvUp);
   fChain->SetBranchAddress("hJet_csvFDown", hJet_csvFDown, &b_hJet_csvFDown);
   fChain->SetBranchAddress("hJet_csvFUp", hJet_csvFUp, &b_hJet_csvFUp);
   fChain->SetBranchAddress("weightTrig_up", &weightTrig_up, &b_weightTrig_up);
   fChain->SetBranchAddress("weightTrigMay_up", &weightTrigMay_up, &b_weightTrigMay);
   fChain->SetBranchAddress("weightTrigV4_up", &weightTrigV4_up, &b_weightTrigV4);
   fChain->SetBranchAddress("weightTrigMET_up", &weightTrigMET_up, &b_weightTrigMET);
   fChain->SetBranchAddress("weightTrigOrMu30_up", &weightTrigOrMu30_up, &b_weightTrigOrMu30);
   fChain->SetBranchAddress("weightEleRecoAndId_up", &weightEleRecoAndId_up, &b_weightEleRecoAndId);
   fChain->SetBranchAddress("weightEleTrigJetMETPart_up", &weightEleTrigJetMETPart_up, &b_weightEleTrigJetMETPart);
   fChain->SetBranchAddress("weightEleTrigElePart_up", &weightEleTrigElePart_up, &b_weightEleTrigElePart);
   Notify();
}

Bool_t ntupleLoader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ntupleLoader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntupleLoader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ntupleLoader_cxx
