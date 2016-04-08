//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 18 14:35:48 2016 by ROOT version 5.34/32
// from TTree SSBTree/Tree for Physics Analyses at CMS
// found on file: SSBTree_29_6_kWr.root
//////////////////////////////////////////////////////////

#ifndef SSBTree_h
#define SSBTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// User add some header files which user need
#include <TH1F.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <TLorentzVector.h>
// Fixed size dimensions of array or collections stored in the TTree if any.

using namespace std;

class SSBTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Info_EventNumber;
   Int_t           Info_Luminosity;
   Int_t           Info_RunNumber;
   //Char_t          Info_isData;
   Bool_t          Info_isData;
   Int_t           Channel_Idx;
   Int_t           Channel_Idx_Final;
   Int_t           Channel_Lepton_Count;
   Int_t           Channel_Lepton_Count_Final;
   TClonesArray    *Elec;
   TClonesArray    *Elec_ShiftedEnDown;
   TClonesArray    *Elec_ShiftedEnUp;
   vector<int>     *Elec_Charge;
   vector<bool>    *Elec_ChargeId_GsfCtf;
   vector<bool>    *Elec_ChargeId_GsfCtfPx;
   vector<bool>    *Elec_ChargeId_GsfPx;
   vector<double>  *Elec_Charge_CtfTr;
   vector<double>  *Elec_Charge_GsfTr;
   vector<double>  *Elec_Charge_Px;
   vector<bool>    *Elec_Conversion;
   Int_t           Elec_Count;
   vector<int>     *Elec_Id_Loose;
   vector<int>     *Elec_Id_RobustHighEnergy;
   vector<int>     *Elec_Id_RobustLoose;
   vector<int>     *Elec_Id_RobustTight;
   vector<int>     *Elec_Id_Tight;
   vector<int>     *Elec_Inner_Hit;
   vector<bool>    *Elec_MVANonTrig_Medium;
   vector<bool>    *Elec_MVANonTrig_Tight;
   vector<bool>    *Elec_MVATrig_Medium;
   vector<bool>    *Elec_MVATrig_Tight;
   vector<float>   *Elec_MVA_NonTrigV0;
   vector<float>   *Elec_MVA_TrigNoIPV0;
   vector<float>   *Elec_MVA_TrigV0;
   vector<double>  *Elec_PFIsoRho03;
   vector<double>  *Elec_PFIsoRho04;
   vector<bool>    *Elec_PFIsoValid;
   vector<double>  *Elec_PFIsodBeta03;
   vector<double>  *Elec_PFIsodBeta04;
   vector<bool>    *Elec_SCB_Loose;
   vector<bool>    *Elec_SCB_Medium;
   vector<bool>    *Elec_SCB_Tight;
   vector<bool>    *Elec_SCB_Veto;
   vector<float>   *Elec_SCB_dEtaIn;
   vector<float>   *Elec_SCB_dPhiIn;
   vector<float>   *Elec_SCB_hOverE;
   vector<bool>    *Elec_SCB_HEEP;
   vector<float>   *Elec_SCB_ooEmooP;
   vector<float>   *Elec_SCB_sigmaIetaIeta;
   vector<double>  *Elec_Supercluster_Eta;
   vector<double>  *Elec_Track_CtfdXY;
   vector<double>  *Elec_Track_CtfdZ;
   vector<double>  *Elec_Track_GsfdXY;
   vector<double>  *Elec_Track_GsfdZ;
   vector<int>     *Elec_pdgId;
   vector<double>  *Elec_relIso03;
   vector<double>  *Elec_relIso04;
   vector<int>     *Elec_ShiftedEnDown_Charge;
   vector<bool>    *Elec_ShiftedEnDown_ChargeId_GsfCtf;
   vector<bool>    *Elec_ShiftedEnDown_ChargeId_GsfCtfPx;
   vector<bool>    *Elec_ShiftedEnDown_ChargeId_GsfPx;
   vector<double>  *Elec_ShiftedEnDown_Charge_CtfTr;
   vector<double>  *Elec_ShiftedEnDown_Charge_GsfTr;
   vector<bool>    *Elec_ShiftedEnDown_Conversion;
   Int_t           Elec_ShiftedEnDown_Count;
   vector<double>  *Elec_ShiftedEnDown_PFIsoRho03;
   vector<double>  *Elec_ShiftedEnDown_PFIsoRho04;
   vector<double>  *Elec_ShiftedEnDown_PFIsodBeta03;
   vector<double>  *Elec_ShiftedEnDown_PFIsodBeta04;
   vector<float>   *Elec_ShiftedEnDown_SCB_dEtaIn;
   vector<float>   *Elec_ShiftedEnDown_SCB_dPhiIn;
   vector<float>   *Elec_ShiftedEnDown_SCB_hOverE;
   vector<float>   *Elec_ShiftedEnDown_SCB_ooEmooP;
   vector<float>   *Elec_ShiftedEnDown_SCB_sigmaIetaIeta;
   vector<double>  *Elec_ShiftedEnDown_Supercluster_Eta;
   vector<int>     *Elec_ShiftedEnDown_pdgId;
   vector<double>  *Elec_ShiftedEnDown_relIso03;
   vector<double>  *Elec_ShiftedEnDown_relIso04;
   vector<int>     *Elec_ShiftedEnUp_Charge;
   vector<bool>    *Elec_ShiftedEnUp_ChargeId_GsfCtf;
   vector<bool>    *Elec_ShiftedEnUp_ChargeId_GsfCtfPx;
   vector<bool>    *Elec_ShiftedEnUp_ChargeId_GsfPx;
   vector<bool>    *Elec_ShiftedEnUp_Conversion;
   Int_t           Elec_ShiftedEnUp_Count;
   vector<double>  *Elec_ShiftedEnUp_PFIsoRho03;
   vector<double>  *Elec_ShiftedEnUp_PFIsoRho04;
   vector<double>  *Elec_ShiftedEnUp_PFIsodBeta03;
   vector<double>  *Elec_ShiftedEnUp_PFIsodBeta04;
   vector<float>   *Elec_ShiftedEnUp_SCB_dEtaIn;
   vector<float>   *Elec_ShiftedEnUp_SCB_dPhiIn;
   vector<float>   *Elec_ShiftedEnUp_SCB_hOverE;
   vector<float>   *Elec_ShiftedEnUp_SCB_ooEmooP;
   vector<float>   *Elec_ShiftedEnUp_SCB_sigmaIetaIeta;
   vector<double>  *Elec_ShiftedEnUp_Supercluster_Eta;
   vector<int>     *Elec_ShiftedEnUp_pdgId;
   vector<double>  *Elec_ShiftedEnUp_relIso03;
   vector<double>  *Elec_ShiftedEnUp_relIso04;
   Char_t          Filter_Greedy_Muon;
   Char_t          Filter_Inconsistent_MuonPt;
   Char_t          Filter_PFReco_Muon;
   vector<bool>    *Filter_PV;
   TClonesArray    *GenJet;
   Int_t           GenJet_Count;
   TClonesArray    *GenMET;
   Int_t           GenMET_Count;
   TClonesArray    *GenPar;
   Int_t           GenPar_Count;
   vector<int>     *GenPar_Dau1_Idx;
   vector<int>     *GenPar_Dau2_Idx;
   vector<int>     *GenPar_Dau_Counter;
   vector<int>     *GenPar_Idx;
   vector<int>     *GenPar_Mom1_Idx;
   vector<int>     *GenPar_Mom2_Idx;
   vector<int>     *GenPar_Mom_Counter;
   vector<int>     *GenPar_Status;
   vector<int>     *GenPar_pdgId;
   Double_t        Gen_EventWeight;
   TClonesArray    *Jet;
   vector<int>     *Jet_Charge;
   Int_t           Jet_Count;
   vector<double>  *Jet_EnShiftedDown;
   vector<double>  *Jet_EnShiftedUp;
   vector<int>     *Jet_PartonFlavour;
   vector<int>     *Jet_PFId;
   vector<int>     *Jet_PileUpId;
   vector<float>   *Jet_PileUpMVA;
   vector<float>   *Jet_bDisc;
   vector<bool>    *Jet_isJet;
   TClonesArray    *MET;
   TClonesArray    *METNoHF;
   vector<double>  *MET_JetEnShiftedUp_PT;
   vector<double>  *MET_JetEnShiftedUp_Phi;
   vector<double>  *MET_JetEnShiftedDown_PT;
   vector<double>  *MET_JetEnShiftedDown_Phi;
   vector<double>  *MET_MuonEnShiftedUp_PT;
   vector<double>  *MET_MuonEnShiftedUp_Phi;
   vector<double>  *MET_MuonEnShiftedDown_PT;
   vector<double>  *MET_MuonEnShiftedDown_Phi;
   vector<double>  *MET_ElectronEnShiftedUp_PT;
   vector<double>  *MET_ElectronEnShiftedUp_Phi;
   vector<double>  *MET_ElectronEnShiftedDown_PT;
   vector<double>  *MET_ElectronEnShiftedDown_Phi;
   vector<double>  *MET_UnclusteredEnShiftedUp_PT;
   vector<double>  *MET_UnclusteredEnShiftedUp_Phi;
   vector<double>  *MET_UnclusteredEnShiftedDown_PT;
   vector<double>  *MET_UnclusteredEnShiftedDown_Phi;
   TClonesArray    *Muon;
   TClonesArray    *Muon_ShiftedEnUp;
   TClonesArray    *Muon_ShiftedEnDown;
   vector<int>     *Muon_Charge;
   Int_t           Muon_Count;
   vector<double>  *Muon_PFIsodBeta03;
   vector<double>  *Muon_PFIsodBeta04;
   vector<bool>    *Muon_isHighPt;
   vector<bool>    *Muon_isLoose;
   vector<bool>    *Muon_isSoft;
   vector<bool>    *Muon_isTight;
   vector<int>     *Muon_pdgId;
   vector<double>  *Muon_relIso03;
   vector<double>  *Muon_relIso04;
   vector<int>     *Muon_ShiftedEnDown_Charge;
   Int_t           Muon_ShiftedEnDown_Count;
   vector<double>  *Muon_ShiftedEnDown_PFIsodBeta03;
   vector<double>  *Muon_ShiftedEnDown_PFIsodBeta04;
   vector<bool>    *Muon_ShiftedEnDown_isHighPt;
   vector<bool>    *Muon_ShiftedEnDown_isLoose;
   vector<bool>    *Muon_ShiftedEnDown_isSoft;
   vector<bool>    *Muon_ShiftedEnDown_isTight;
   vector<int>     *Muon_ShiftedEnDown_pdgId;
   vector<double>  *Muon_ShiftedEnDown_relIso03;
   vector<double>  *Muon_ShiftedEnDown_relIso04;
   vector<int>     *Muon_ShiftedEnUp_Charge;
   Int_t           Muon_ShiftedEnUp_Count;
   vector<double>  *Muon_ShiftedEnUp_PFIsodBeta03;
   vector<double>  *Muon_ShiftedEnUp_PFIsodBeta04;
   vector<bool>    *Muon_ShiftedEnUp_isHighPt;
   vector<bool>    *Muon_ShiftedEnUp_isLoose;
   vector<bool>    *Muon_ShiftedEnUp_isSoft;
   vector<bool>    *Muon_ShiftedEnUp_isTight;
   vector<int>     *Muon_ShiftedEnUp_pdgId;
   vector<double>  *Muon_ShiftedEnUp_relIso03;
   vector<double>  *Muon_ShiftedEnUp_relIso04;
   vector<double>  *PDFWeight_BjorkenX1;
   vector<double>  *PDFWeight_BjorkenX2;
   vector<double>  *PDFWeight_Cent;
   vector<double>  *PDFWeight_Cent_Down;
   vector<double>  *PDFWeight_Cent_Up;
   vector<double>  *PDFWeight_Var1_Down;
   vector<double>  *PDFWeight_Var2_Down;
   vector<int>     *PDFWeight_Id1;
   vector<int>     *PDFWeight_Id2;
   vector<double>  *PDFWeight_PDF1;
   vector<double>  *PDFWeight_PDF2;
   vector<double>  *PDFWeight_Q;
   vector<double>  *PDFWeight_Var1_Up;
   vector<double>  *PDFWeight_Var2_Up;
   Int_t           PV_Count;
   Int_t           PileUp_Count_Interaction;
   Float_t         PileUp_Count_Intime;
   vector<string>  *Trigger_Name;
   vector<unsigned int> *Trigger_PreScale;
   vector<bool>    *Trigger_isError;
   vector<bool>    *Trigger_isPass;
   vector<bool>    *Trigger_isRun;
   vector<double>  *Vertex_SumPtSquare;
   vector<double>  *Vertex_X;
   vector<double>  *Vertex_X_Error;
   vector<double>  *Vertex_Y;
   vector<double>  *Vertex_Y_Error;
   vector<double>  *Vertex_Z;
   vector<double>  *Vertex_Z_Error;
   vector<double>  *Weight_PileUp;
   vector<double>  *Weight_PileUp_ShiftedUp;
   vector<double>  *Weight_PileUp_ShiftedDown;

   // List of branches
   TBranch        *b_Info_EventNumber;   //!
   TBranch        *b_Info_Luminosity;   //!
   TBranch        *b_Info_RunNumber;   //!
   TBranch        *b_Info_isData;   //!
   TBranch        *b_Channel_Idx;   //!
   TBranch        *b_Channel_Idx_Final;   //!
   TBranch        *b_Channel_Lepton_Count;   //!
   TBranch        *b_Channel_Lepton_Count_Final;   //!
   TBranch        *b_Elec;   //!
   TBranch        *b_Elec_ShiftedEnDown;   //!
   TBranch        *b_Elec_ShiftedEnUp;   //!
   TBranch        *b_Elec_Charge;   //!
   TBranch        *b_Elec_ChargeId_GsfCtf;   //!
   TBranch        *b_Elec_ChargeId_GsfCtfPx;   //!
   TBranch        *b_Elec_ChargeId_GsfPx;   //!
   TBranch        *b_Elec_Charge_CtfTr;   //!
   TBranch        *b_Elec_Charge_GsfTr;   //!
   TBranch        *b_Elec_Charge_Px;   //!
   TBranch        *b_Elec_Conversion;   //!
   TBranch        *b_Elec_Count;   //!
   TBranch        *b_Elec_Id_Loose;   //!
   TBranch        *b_Elec_Id_RobustHighEnergy;   //!
   TBranch        *b_Elec_Id_RobustLoose;   //!
   TBranch        *b_Elec_Id_RobustTight;   //!
   TBranch        *b_Elec_Id_Tight;   //!
   TBranch        *b_Elec_Inner_Hit;   //!
   TBranch        *b_Elec_MVANonTrig_Medium;   //!
   TBranch        *b_Elec_MVANonTrig_Tight;   //!
   TBranch        *b_Elec_MVATrig_Medium;   //!
   TBranch        *b_Elec_MVATrig_Tight;   //!
   TBranch        *b_Elec_MVA_NonTrigV0;   //!
   TBranch        *b_Elec_MVA_TrigNoIPV0;   //!
   TBranch        *b_Elec_MVA_TrigV0;   //!
   TBranch        *b_Elec_PFIsoRho03;   //!
   TBranch        *b_Elec_PFIsoRho04;   //!
   TBranch        *b_Elec_PFIsoValid;   //!
   TBranch        *b_Elec_PFIsodBeta03;   //!
   TBranch        *b_Elec_PFIsodBeta04;   //!
   TBranch        *b_Elec_SCB_Loose;   //!
   TBranch        *b_Elec_SCB_Medium;   //!
   TBranch        *b_Elec_SCB_Tight;   //!
   TBranch        *b_Elec_SCB_Veto;   //!
   TBranch        *b_Elec_SCB_dEtaIn;   //!
   TBranch        *b_Elec_SCB_dPhiIn;   //!
   TBranch        *b_Elec_SCB_hOverE;   //!
   TBranch        *b_Elec_SCB_HEEP;   //!
   TBranch        *b_Elec_SCB_ooEmooP;   //!
   TBranch        *b_Elec_SCB_sigmaIetaIeta;   //!
   TBranch        *b_Elec_Supercluster_Eta;   //!
   TBranch        *b_Elec_Track_CtfdXY;   //!
   TBranch        *b_Elec_Track_CtfdZ;   //!
   TBranch        *b_Elec_Track_GsfdXY;   //!
   TBranch        *b_Elec_Track_GsfdZ;   //!
   TBranch        *b_Elec_pdgId;   //!
   TBranch        *b_Elec_relIso03;   //!
   TBranch        *b_Elec_relIso04;   //!
   TBranch        *b_Elec_ShiftedEnDown_Charge;   //!
   TBranch        *b_Elec_ShiftedEnDown_ChargeId_GsfCtf;   //!
   TBranch        *b_Elec_ShiftedEnDown_ChargeId_GsfCtfPx;   //!
   TBranch        *b_Elec_ShiftedEnDown_ChargeId_GsfPx;   //!
   TBranch        *b_Elec_ShiftedEnDown_Charge_CtfTr;   //!
   TBranch        *b_Elec_ShiftedEnDown_Charge_GsfTr;   //!
   TBranch        *b_Elec_ShiftedEnDown_Conversion;   //!
   TBranch        *b_Elec_ShiftedEnDown_Count;   //!
   TBranch        *b_Elec_ShiftedEnDown_PFIsoRho03;   //!
   TBranch        *b_Elec_ShiftedEnDown_PFIsoRho04;   //!
   TBranch        *b_Elec_ShiftedEnDown_PFIsodBeta03;   //!
   TBranch        *b_Elec_ShiftedEnDown_PFIsodBeta04;   //!
   TBranch        *b_Elec_ShiftedEnDown_SCB_dEtaIn;   //!
   TBranch        *b_Elec_ShiftedEnDown_SCB_dPhiIn;   //!
   TBranch        *b_Elec_ShiftedEnDown_SCB_hOverE;   //!
   TBranch        *b_Elec_ShiftedEnDown_SCB_ooEmooP;   //!
   TBranch        *b_Elec_ShiftedEnDown_SCB_sigmaIetaIeta;   //!
   TBranch        *b_Elec_ShiftedEnDown_Supercluster_Eta;   //!
   TBranch        *b_Elec_ShiftedEnDown_pdgId;   //!
   TBranch        *b_Elec_ShiftedEnDown_relIso03;   //!
   TBranch        *b_Elec_ShiftedEnDown_relIso04;   //!
   TBranch        *b_Elec_ShiftedEnUp_Charge;   //!
   TBranch        *b_Elec_ShiftedEnUp_ChargeId_GsfCtf;   //!
   TBranch        *b_Elec_ShiftedEnUp_ChargeId_GsfCtfPx;   //!
   TBranch        *b_Elec_ShiftedEnUp_ChargeId_GsfPx;   //!
   TBranch        *b_Elec_ShiftedEnUp_Conversion;   //!
   TBranch        *b_Elec_ShiftedEnUp_Count;   //!
   TBranch        *b_Elec_ShiftedEnUp_PFIsoRho03;   //!
   TBranch        *b_Elec_ShiftedEnUp_PFIsoRho04;   //!
   TBranch        *b_Elec_ShiftedEnUp_PFIsodBeta03;   //!
   TBranch        *b_Elec_ShiftedEnUp_PFIsodBeta04;   //!
   TBranch        *b_Elec_ShiftedEnUp_SCB_dEtaIn;   //!
   TBranch        *b_Elec_ShiftedEnUp_SCB_dPhiIn;   //!
   TBranch        *b_Elec_ShiftedEnUp_SCB_hOverE;   //!
   TBranch        *b_Elec_ShiftedEnUp_SCB_ooEmooP;   //!
   TBranch        *b_Elec_ShiftedEnUp_SCB_sigmaIetaIeta;   //!
   TBranch        *b_Elec_ShiftedEnUp_Supercluster_Eta;   //!
   TBranch        *b_Elec_ShiftedEnUp_pdgId;   //!
   TBranch        *b_Elec_ShiftedEnUp_relIso03;   //!
   TBranch        *b_Elec_ShiftedEnUp_relIso04;   //!
   TBranch        *b_Filter_Greedy_Muon;   //!
   TBranch        *b_Filter_Inconsistent_MuonPt;   //!
   TBranch        *b_Filter_PFReco_Muon;   //!
   TBranch        *b_Filter_PV;   //!
   TBranch        *b_GenJet;   //!
   TBranch        *b_GenJet_Count;   //!
   TBranch        *b_GenMET;   //!
   TBranch        *b_GenMET_Count;   //!
   TBranch        *b_GenPar;   //!
   TBranch        *b_GenPar_Count;   //!
   TBranch        *b_GenPar_Dau1_Idx;   //!
   TBranch        *b_GenPar_Dau2_Idx;   //!
   TBranch        *b_GenPar_Dau_Counter;   //!
   TBranch        *b_GenPar_Idx;   //!
   TBranch        *b_GenPar_Mom1_Idx;   //!
   TBranch        *b_GenPar_Mom2_Idx;   //!
   TBranch        *b_GenPar_Mom_Counter;   //!
   TBranch        *b_GenPar_Status;   //!
   TBranch        *b_GenPar_pdgId;   //!
   TBranch        *b_Gen_EventWeight;   //!
   TBranch        *b_Jet;   //!
   TBranch        *b_Jet_Charge;   //!
   TBranch        *b_Jet_Count;   //!
   TBranch        *b_Jet_EnShiftedDown;   //!
   TBranch        *b_Jet_EnShiftedUp;   //!
   TBranch        *b_Jet_PartonFlavour;   //!
   TBranch        *b_Jet_PFId;   //!
   TBranch        *b_Jet_PileUpId;   //!
   TBranch        *b_Jet_PileUpMVA;   //!
   TBranch        *b_Jet_bDisc;   //!
   TBranch        *b_Jet_isJet;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METNoHF;   //!
   TBranch        *b_MET_JetEnShiftedUp_PT;   //!
   TBranch        *b_MET_JetEnShiftedUp_Phi;   //!
   TBranch        *b_MET_JetEnShiftedDown_PT;   //!
   TBranch        *b_MET_JetEnShiftedDown_Phi;   //!
   TBranch        *b_MET_MuonEnShiftedUp_PT;   //!
   TBranch        *b_MET_MuonEnShiftedUp_Phi;   //!
   TBranch        *b_MET_MuonEnShiftedDown_PT;   //!
   TBranch        *b_MET_MuonEnShiftedDown_Phi;   //!
   TBranch        *b_MET_ElectronEnShiftedUp_PT;   //!
   TBranch        *b_MET_ElectronEnShiftedUp_Phi;   //!
   TBranch        *b_MET_ElectronEnShiftedDown_PT;   //!
   TBranch        *b_MET_ElectronEnShiftedDown_Phi;   //!
   TBranch        *b_MET_UnclusteredEnShiftedUp_PT;   //!
   TBranch        *b_MET_UnclusteredEnShiftedUp_Phi;   //!
   TBranch        *b_MET_UnclusteredEnShiftedDown_PT;   //!
   TBranch        *b_MET_UnclusteredEnShiftedDown_Phi;   //!
   TBranch        *b_Muon;   //!
   TBranch        *b_Muon_ShiftedEnUp;   //!
   TBranch        *b_Muon_ShiftedEnDown;   //!
   TBranch        *b_Muon_Charge;   //!
   TBranch        *b_Muon_Count;   //!
   TBranch        *b_Muon_PFIsodBeta03;   //!
   TBranch        *b_Muon_PFIsodBeta04;   //!
   TBranch        *b_Muon_isHighPt;   //!
   TBranch        *b_Muon_isLoose;   //!
   TBranch        *b_Muon_isSoft;   //!
   TBranch        *b_Muon_isTight;   //!
   TBranch        *b_Muon_pdgId;   //!
   TBranch        *b_Muon_relIso03;   //!
   TBranch        *b_Muon_relIso04;   //!
   TBranch        *b_Muon_ShiftedEnDown_Charge;   //!
   TBranch        *b_Muon_ShiftedEnDown_Count;   //!
   TBranch        *b_Muon_ShiftedEnDown_PFIsodBeta03;   //!
   TBranch        *b_Muon_ShiftedEnDown_PFIsodBeta04;   //!
   TBranch        *b_Muon_ShiftedEnDown_isHighPt;   //!
   TBranch        *b_Muon_ShiftedEnDown_isLoose;   //!
   TBranch        *b_Muon_ShiftedEnDown_isSoft;   //!
   TBranch        *b_Muon_ShiftedEnDown_isTight;   //!
   TBranch        *b_Muon_ShiftedEnDown_pdgId;   //!
   TBranch        *b_Muon_ShiftedEnDown_relIso03;   //!
   TBranch        *b_Muon_ShiftedEnDown_relIso04;   //!
   TBranch        *b_Muon_ShiftedEnUp_Charge;   //!
   TBranch        *b_Muon_ShiftedEnUp_Count;   //!
   TBranch        *b_Muon_ShiftedEnUp_PFIsodBeta03;   //!
   TBranch        *b_Muon_ShiftedEnUp_PFIsodBeta04;   //!
   TBranch        *b_Muon_ShiftedEnUp_isHighPt;   //!
   TBranch        *b_Muon_ShiftedEnUp_isLoose;   //!
   TBranch        *b_Muon_ShiftedEnUp_isSoft;   //!
   TBranch        *b_Muon_ShiftedEnUp_isTight;   //!
   TBranch        *b_Muon_ShiftedEnUp_pdgId;   //!
   TBranch        *b_Muon_ShiftedEnUp_relIso03;   //!
   TBranch        *b_Muon_ShiftedEnUp_relIso04;   //!
   TBranch        *b_PDFWeight_BjorkenX1;   //!
   TBranch        *b_PDFWeight_BjorkenX2;   //!
   TBranch        *b_PDFWeight_Cent;   //!
   TBranch        *b_PDFWeight_Cent_Down;   //!
   TBranch        *b_PDFWeight_Cent_Up;   //!
   TBranch        *b_PDFWeight_Var1_Down;   //!
   TBranch        *b_PDFWeight_Var2_Down;   //!
   TBranch        *b_PDFWeight_Id1;   //!
   TBranch        *b_PDFWeight_Id2;   //!
   TBranch        *b_PDFWeight_PDF1;   //!
   TBranch        *b_PDFWeight_PDF2;   //!
   TBranch        *b_PDFWeight_Q;   //!
   TBranch        *b_PDFWeight_Var1_Up;   //!
   TBranch        *b_PDFWeight_Var2_Up;   //!
   TBranch        *b_PV_Count;   //!
   TBranch        *b_PileUp_Count_Interaction;   //!
   TBranch        *b_PileUp_Count_Intime;   //!
   TBranch        *b_Trigger_Name;   //!
   TBranch        *b_Trigger_PreScale;   //!
   TBranch        *b_Trigger_isError;   //!
   TBranch        *b_Trigger_isPass;   //!
   TBranch        *b_Trigger_isRun;   //!
   TBranch        *b_Vertex_SumPtSquare;   //!
   TBranch        *b_Vertex_X;   //!
   TBranch        *b_Vertex_X_Error;   //!
   TBranch        *b_Vertex_Y;   //!
   TBranch        *b_Vertex_Y_Error;   //!
   TBranch        *b_Vertex_Z;   //!
   TBranch        *b_Vertex_Z_Error;   //!
   TBranch        *b_Weight_PileUp;   //!
   TBranch        *b_Weight_PileUp_ShiftedUp;   //!
   TBranch        *b_Weight_PileUp_ShiftedDown;   //!

   SSBTree(TTree *tree=0);
   virtual ~SSBTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SSBTree_cxx
SSBTree::SSBTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("SSBTree_29_6_kWr.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../MuMu/SSBTree_1_2_Z3T.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
      if (!f || !f->IsOpen()) {
         //f = new TFile("SSBTree_29_6_kWr.root");
         //f = new TFile("../MuMu/SSBTree_1_2_Z3T.root");
         //f = new TFile("../../MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
         //f = new TFile("../SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
         f = new TFile("/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root");
      }
      //TDirectory * dir = (TDirectory*)f->Get("../../MC/TTBar_Sample/SSBTree_101_1_2bJ.root:/ssbanalyzer");
      //TDirectory * dir = (TDirectory*)f->Get("../SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root:/ssbanalyzer");
      TDirectory * dir = (TDirectory*)f->Get("/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/MC/TTBar_Sample/SSBTree_101_1_2bJ.root:/ssbanalyzer");
      dir->GetObject("SSBTree",tree);

   }
   Init(tree);
}

SSBTree::~SSBTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SSBTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SSBTree::LoadTree(Long64_t entry)
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

void SSBTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Elec = 0;
   Elec_ShiftedEnDown = 0;
   Elec_ShiftedEnUp = 0;
   Elec_Charge = 0;
   Elec_ChargeId_GsfCtf = 0;
   Elec_ChargeId_GsfCtfPx = 0;
   Elec_ChargeId_GsfPx = 0;
   Elec_Charge_CtfTr = 0;
   Elec_Charge_GsfTr = 0;
   Elec_Charge_Px = 0;
   Elec_Conversion = 0;
   Elec_Id_Loose = 0;
   Elec_Id_RobustHighEnergy = 0;
   Elec_Id_RobustLoose = 0;
   Elec_Id_RobustTight = 0;
   Elec_Id_Tight = 0;
   Elec_Inner_Hit = 0;
   Elec_MVANonTrig_Medium = 0;
   Elec_MVANonTrig_Tight = 0;
   Elec_MVATrig_Medium = 0;
   Elec_MVATrig_Tight = 0;
   Elec_MVA_NonTrigV0 = 0;
   Elec_MVA_TrigNoIPV0 = 0;
   Elec_MVA_TrigV0 = 0;
   Elec_PFIsoRho03 = 0;
   Elec_PFIsoRho04 = 0;
   Elec_PFIsoValid = 0;
   Elec_PFIsodBeta03 = 0;
   Elec_PFIsodBeta04 = 0;
   Elec_SCB_Loose = 0;
   Elec_SCB_Medium = 0;
   Elec_SCB_Tight = 0;
   Elec_SCB_Veto = 0;
   Elec_SCB_dEtaIn = 0;
   Elec_SCB_dPhiIn = 0;
   Elec_SCB_hOverE = 0;
   Elec_SCB_HEEP = 0;
   Elec_SCB_ooEmooP = 0;
   Elec_SCB_sigmaIetaIeta = 0;
   Elec_Supercluster_Eta = 0;
   Elec_Track_CtfdXY = 0;
   Elec_Track_CtfdZ = 0;
   Elec_Track_GsfdXY = 0;
   Elec_Track_GsfdZ = 0;
   Elec_pdgId = 0;
   Elec_relIso03 = 0;
   Elec_relIso04 = 0;
   Elec_ShiftedEnDown_Charge = 0;
   Elec_ShiftedEnDown_ChargeId_GsfCtf = 0;
   Elec_ShiftedEnDown_ChargeId_GsfCtfPx = 0;
   Elec_ShiftedEnDown_ChargeId_GsfPx = 0;
   Elec_ShiftedEnDown_Charge_CtfTr = 0;
   Elec_ShiftedEnDown_Charge_GsfTr = 0;
   Elec_ShiftedEnDown_Conversion = 0;
   Elec_ShiftedEnDown_PFIsoRho03 = 0;
   Elec_ShiftedEnDown_PFIsoRho04 = 0;
   Elec_ShiftedEnDown_PFIsodBeta03 = 0;
   Elec_ShiftedEnDown_PFIsodBeta04 = 0;
   Elec_ShiftedEnDown_SCB_dEtaIn = 0;
   Elec_ShiftedEnDown_SCB_dPhiIn = 0;
   Elec_ShiftedEnDown_SCB_hOverE = 0;
   Elec_ShiftedEnDown_SCB_ooEmooP = 0;
   Elec_ShiftedEnDown_SCB_sigmaIetaIeta = 0;
   Elec_ShiftedEnDown_Supercluster_Eta = 0;
   Elec_ShiftedEnDown_pdgId = 0;
   Elec_ShiftedEnDown_relIso03 = 0;
   Elec_ShiftedEnDown_relIso04 = 0;
   Elec_ShiftedEnUp_Charge = 0;
   Elec_ShiftedEnUp_ChargeId_GsfCtf = 0;
   Elec_ShiftedEnUp_ChargeId_GsfCtfPx = 0;
   Elec_ShiftedEnUp_ChargeId_GsfPx = 0;
   Elec_ShiftedEnUp_Conversion = 0;
   Elec_ShiftedEnUp_PFIsoRho03 = 0;
   Elec_ShiftedEnUp_PFIsoRho04 = 0;
   Elec_ShiftedEnUp_PFIsodBeta03 = 0;
   Elec_ShiftedEnUp_PFIsodBeta04 = 0;
   Elec_ShiftedEnUp_SCB_dEtaIn = 0;
   Elec_ShiftedEnUp_SCB_dPhiIn = 0;
   Elec_ShiftedEnUp_SCB_hOverE = 0;
   Elec_ShiftedEnUp_SCB_ooEmooP = 0;
   Elec_ShiftedEnUp_SCB_sigmaIetaIeta = 0;
   Elec_ShiftedEnUp_Supercluster_Eta = 0;
   Elec_ShiftedEnUp_pdgId = 0;
   Elec_ShiftedEnUp_relIso03 = 0;
   Elec_ShiftedEnUp_relIso04 = 0;
   Filter_PV = 0;
   GenJet = 0;
   GenMET = 0;
   GenPar = 0;
   GenPar_Dau1_Idx = 0;
   GenPar_Dau2_Idx = 0;
   GenPar_Dau_Counter = 0;
   GenPar_Idx = 0;
   GenPar_Mom1_Idx = 0;
   GenPar_Mom2_Idx = 0;
   GenPar_Mom_Counter = 0;
   GenPar_Status = 0;
   GenPar_pdgId = 0;
   Jet = 0;
   Jet_Charge = 0;
   Jet_EnShiftedDown = 0;
   Jet_EnShiftedUp = 0;
   Jet_PartonFlavour = 0;
   Jet_PFId = 0;
   Jet_PileUpId = 0;
   Jet_PileUpMVA = 0;
   Jet_bDisc = 0;
   Jet_isJet = 0;
   MET = 0;
   METNoHF = 0;
   MET_JetEnShiftedUp_PT = 0;
   MET_JetEnShiftedUp_Phi = 0;
   MET_JetEnShiftedDown_PT = 0;
   MET_JetEnShiftedDown_Phi = 0;
   MET_MuonEnShiftedUp_PT = 0;
   MET_MuonEnShiftedUp_Phi = 0;
   MET_MuonEnShiftedDown_PT = 0;
   MET_MuonEnShiftedDown_Phi = 0;
   MET_ElectronEnShiftedUp_PT = 0;
   MET_ElectronEnShiftedUp_Phi = 0;
   MET_ElectronEnShiftedDown_PT = 0;
   MET_ElectronEnShiftedDown_Phi = 0;
   MET_UnclusteredEnShiftedUp_PT = 0;
   MET_UnclusteredEnShiftedUp_Phi = 0;
   MET_UnclusteredEnShiftedDown_PT = 0;
   MET_UnclusteredEnShiftedDown_Phi = 0;
   Muon = 0;
   Muon_ShiftedEnUp = 0;
   Muon_ShiftedEnDown = 0;
   Muon_Charge = 0;
   Muon_PFIsodBeta03 = 0;
   Muon_PFIsodBeta04 = 0;
   Muon_isHighPt = 0;
   Muon_isLoose = 0;
   Muon_isSoft = 0;
   Muon_isTight = 0;
   Muon_pdgId = 0;
   Muon_relIso03 = 0;
   Muon_relIso04 = 0;
   Muon_ShiftedEnDown_Charge = 0;
   Muon_ShiftedEnDown_PFIsodBeta03 = 0;
   Muon_ShiftedEnDown_PFIsodBeta04 = 0;
   Muon_ShiftedEnDown_isHighPt = 0;
   Muon_ShiftedEnDown_isLoose = 0;
   Muon_ShiftedEnDown_isSoft = 0;
   Muon_ShiftedEnDown_isTight = 0;
   Muon_ShiftedEnDown_pdgId = 0;
   Muon_ShiftedEnDown_relIso03 = 0;
   Muon_ShiftedEnDown_relIso04 = 0;
   Muon_ShiftedEnUp_Charge = 0;
   Muon_ShiftedEnUp_PFIsodBeta03 = 0;
   Muon_ShiftedEnUp_PFIsodBeta04 = 0;
   Muon_ShiftedEnUp_isHighPt = 0;
   Muon_ShiftedEnUp_isLoose = 0;
   Muon_ShiftedEnUp_isSoft = 0;
   Muon_ShiftedEnUp_isTight = 0;
   Muon_ShiftedEnUp_pdgId = 0;
   Muon_ShiftedEnUp_relIso03 = 0;
   Muon_ShiftedEnUp_relIso04 = 0;
   PDFWeight_BjorkenX1 = 0;
   PDFWeight_BjorkenX2 = 0;
   PDFWeight_Cent = 0;
   PDFWeight_Cent_Down = 0;
   PDFWeight_Cent_Up = 0;
   PDFWeight_Var1_Down = 0;
   PDFWeight_Var2_Down = 0;
   PDFWeight_Id1 = 0;
   PDFWeight_Id2 = 0;
   PDFWeight_PDF1 = 0;
   PDFWeight_PDF2 = 0;
   PDFWeight_Q = 0;
   PDFWeight_Var1_Up = 0;
   PDFWeight_Var2_Up = 0;
   Trigger_Name = 0;
   Trigger_PreScale = 0;
   Trigger_isError = 0;
   Trigger_isPass = 0;
   Trigger_isRun = 0;
   Vertex_SumPtSquare = 0;
   Vertex_X = 0;
   Vertex_X_Error = 0;
   Vertex_Y = 0;
   Vertex_Y_Error = 0;
   Vertex_Z = 0;
   Vertex_Z_Error = 0;
   Weight_PileUp = 0;
   Weight_PileUp_ShiftedUp = 0;
   Weight_PileUp_ShiftedDown = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Info_EventNumber", &Info_EventNumber, &b_Info_EventNumber);
   fChain->SetBranchAddress("Info_Luminosity", &Info_Luminosity, &b_Info_Luminosity);
   fChain->SetBranchAddress("Info_RunNumber", &Info_RunNumber, &b_Info_RunNumber);
   fChain->SetBranchAddress("Info_isData", &Info_isData, &b_Info_isData);
   fChain->SetBranchAddress("Channel_Idx", &Channel_Idx, &b_Channel_Idx);
   fChain->SetBranchAddress("Channel_Idx_Final", &Channel_Idx_Final, &b_Channel_Idx_Final);
   fChain->SetBranchAddress("Channel_Lepton_Count", &Channel_Lepton_Count, &b_Channel_Lepton_Count);
   fChain->SetBranchAddress("Channel_Lepton_Count_Final", &Channel_Lepton_Count_Final, &b_Channel_Lepton_Count_Final);
   fChain->SetBranchAddress("Elec", &Elec, &b_Elec);
   fChain->SetBranchAddress("Elec_ShiftedEnDown", &Elec_ShiftedEnDown, &b_Elec_ShiftedEnDown);
   fChain->SetBranchAddress("Elec_ShiftedEnUp", &Elec_ShiftedEnUp, &b_Elec_ShiftedEnUp);
   fChain->SetBranchAddress("Elec_Charge", &Elec_Charge, &b_Elec_Charge);
   fChain->SetBranchAddress("Elec_ChargeId_GsfCtf", &Elec_ChargeId_GsfCtf, &b_Elec_ChargeId_GsfCtf);
   fChain->SetBranchAddress("Elec_ChargeId_GsfCtfPx", &Elec_ChargeId_GsfCtfPx, &b_Elec_ChargeId_GsfCtfPx);
   fChain->SetBranchAddress("Elec_ChargeId_GsfPx", &Elec_ChargeId_GsfPx, &b_Elec_ChargeId_GsfPx);
   fChain->SetBranchAddress("Elec_Charge_CtfTr", &Elec_Charge_CtfTr, &b_Elec_Charge_CtfTr);
   fChain->SetBranchAddress("Elec_Charge_GsfTr", &Elec_Charge_GsfTr, &b_Elec_Charge_GsfTr);
   fChain->SetBranchAddress("Elec_Charge_Px", &Elec_Charge_Px, &b_Elec_Charge_Px);
   fChain->SetBranchAddress("Elec_Conversion", &Elec_Conversion, &b_Elec_Conversion);
   fChain->SetBranchAddress("Elec_Count", &Elec_Count, &b_Elec_Count);
   fChain->SetBranchAddress("Elec_Id_Loose", &Elec_Id_Loose, &b_Elec_Id_Loose);
   fChain->SetBranchAddress("Elec_Id_RobustHighEnergy", &Elec_Id_RobustHighEnergy, &b_Elec_Id_RobustHighEnergy);
   fChain->SetBranchAddress("Elec_Id_RobustLoose", &Elec_Id_RobustLoose, &b_Elec_Id_RobustLoose);
   fChain->SetBranchAddress("Elec_Id_RobustTight", &Elec_Id_RobustTight, &b_Elec_Id_RobustTight);
   fChain->SetBranchAddress("Elec_Id_Tight", &Elec_Id_Tight, &b_Elec_Id_Tight);
   fChain->SetBranchAddress("Elec_Inner_Hit", &Elec_Inner_Hit, &b_Elec_Inner_Hit);
   fChain->SetBranchAddress("Elec_MVANonTrig_Medium", &Elec_MVANonTrig_Medium, &b_Elec_MVANonTrig_Medium);
   fChain->SetBranchAddress("Elec_MVANonTrig_Tight", &Elec_MVANonTrig_Tight, &b_Elec_MVANonTrig_Tight);
   fChain->SetBranchAddress("Elec_MVATrig_Medium", &Elec_MVATrig_Medium, &b_Elec_MVATrig_Medium);
   fChain->SetBranchAddress("Elec_MVATrig_Tight", &Elec_MVATrig_Tight, &b_Elec_MVATrig_Tight);
   fChain->SetBranchAddress("Elec_MVA_NonTrigV0", &Elec_MVA_NonTrigV0, &b_Elec_MVA_NonTrigV0);
   fChain->SetBranchAddress("Elec_MVA_TrigNoIPV0", &Elec_MVA_TrigNoIPV0, &b_Elec_MVA_TrigNoIPV0);
   fChain->SetBranchAddress("Elec_MVA_TrigV0", &Elec_MVA_TrigV0, &b_Elec_MVA_TrigV0);
   fChain->SetBranchAddress("Elec_PFIsoRho03", &Elec_PFIsoRho03, &b_Elec_PFIsoRho03);
   fChain->SetBranchAddress("Elec_PFIsoRho04", &Elec_PFIsoRho04, &b_Elec_PFIsoRho04);
   fChain->SetBranchAddress("Elec_PFIsoValid", &Elec_PFIsoValid, &b_Elec_PFIsoValid);
   fChain->SetBranchAddress("Elec_PFIsodBeta03", &Elec_PFIsodBeta03, &b_Elec_PFIsodBeta03);
   fChain->SetBranchAddress("Elec_PFIsodBeta04", &Elec_PFIsodBeta04, &b_Elec_PFIsodBeta04);
   fChain->SetBranchAddress("Elec_SCB_Loose", &Elec_SCB_Loose, &b_Elec_SCB_Loose);
   fChain->SetBranchAddress("Elec_SCB_Medium", &Elec_SCB_Medium, &b_Elec_SCB_Medium);
   fChain->SetBranchAddress("Elec_SCB_Tight", &Elec_SCB_Tight, &b_Elec_SCB_Tight);
   fChain->SetBranchAddress("Elec_SCB_Veto", &Elec_SCB_Veto, &b_Elec_SCB_Veto);
   fChain->SetBranchAddress("Elec_SCB_dEtaIn", &Elec_SCB_dEtaIn, &b_Elec_SCB_dEtaIn);
   fChain->SetBranchAddress("Elec_SCB_dPhiIn", &Elec_SCB_dPhiIn, &b_Elec_SCB_dPhiIn);
   fChain->SetBranchAddress("Elec_SCB_hOverE", &Elec_SCB_hOverE, &b_Elec_SCB_hOverE);
   fChain->SetBranchAddress("Elec_SCB_HEEP", &Elec_SCB_HEEP, &b_Elec_SCB_HEEP);
   fChain->SetBranchAddress("Elec_SCB_ooEmooP", &Elec_SCB_ooEmooP, &b_Elec_SCB_ooEmooP);
   fChain->SetBranchAddress("Elec_SCB_sigmaIetaIeta", &Elec_SCB_sigmaIetaIeta, &b_Elec_SCB_sigmaIetaIeta);
   fChain->SetBranchAddress("Elec_Supercluster_Eta", &Elec_Supercluster_Eta, &b_Elec_Supercluster_Eta);
   fChain->SetBranchAddress("Elec_Track_CtfdXY", &Elec_Track_CtfdXY, &b_Elec_Track_CtfdXY);
   fChain->SetBranchAddress("Elec_Track_CtfdZ", &Elec_Track_CtfdZ, &b_Elec_Track_CtfdZ);
   fChain->SetBranchAddress("Elec_Track_GsfdXY", &Elec_Track_GsfdXY, &b_Elec_Track_GsfdXY);
   fChain->SetBranchAddress("Elec_Track_GsfdZ", &Elec_Track_GsfdZ, &b_Elec_Track_GsfdZ);
   fChain->SetBranchAddress("Elec_pdgId", &Elec_pdgId, &b_Elec_pdgId);
   fChain->SetBranchAddress("Elec_relIso03", &Elec_relIso03, &b_Elec_relIso03);
   fChain->SetBranchAddress("Elec_relIso04", &Elec_relIso04, &b_Elec_relIso04);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Charge", &Elec_ShiftedEnDown_Charge, &b_Elec_ShiftedEnDown_Charge);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_ChargeId_GsfCtf", &Elec_ShiftedEnDown_ChargeId_GsfCtf, &b_Elec_ShiftedEnDown_ChargeId_GsfCtf);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_ChargeId_GsfCtfPx", &Elec_ShiftedEnDown_ChargeId_GsfCtfPx, &b_Elec_ShiftedEnDown_ChargeId_GsfCtfPx);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_ChargeId_GsfPx", &Elec_ShiftedEnDown_ChargeId_GsfPx, &b_Elec_ShiftedEnDown_ChargeId_GsfPx);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Charge_CtfTr", &Elec_ShiftedEnDown_Charge_CtfTr, &b_Elec_ShiftedEnDown_Charge_CtfTr);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Charge_GsfTr", &Elec_ShiftedEnDown_Charge_GsfTr, &b_Elec_ShiftedEnDown_Charge_GsfTr);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Conversion", &Elec_ShiftedEnDown_Conversion, &b_Elec_ShiftedEnDown_Conversion);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Count", &Elec_ShiftedEnDown_Count, &b_Elec_ShiftedEnDown_Count);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_PFIsoRho03", &Elec_ShiftedEnDown_PFIsoRho03, &b_Elec_ShiftedEnDown_PFIsoRho03);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_PFIsoRho04", &Elec_ShiftedEnDown_PFIsoRho04, &b_Elec_ShiftedEnDown_PFIsoRho04);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_PFIsodBeta03", &Elec_ShiftedEnDown_PFIsodBeta03, &b_Elec_ShiftedEnDown_PFIsodBeta03);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_PFIsodBeta04", &Elec_ShiftedEnDown_PFIsodBeta04, &b_Elec_ShiftedEnDown_PFIsodBeta04);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_SCB_dEtaIn", &Elec_ShiftedEnDown_SCB_dEtaIn, &b_Elec_ShiftedEnDown_SCB_dEtaIn);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_SCB_dPhiIn", &Elec_ShiftedEnDown_SCB_dPhiIn, &b_Elec_ShiftedEnDown_SCB_dPhiIn);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_SCB_hOverE", &Elec_ShiftedEnDown_SCB_hOverE, &b_Elec_ShiftedEnDown_SCB_hOverE);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_SCB_ooEmooP", &Elec_ShiftedEnDown_SCB_ooEmooP, &b_Elec_ShiftedEnDown_SCB_ooEmooP);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_SCB_sigmaIetaIeta", &Elec_ShiftedEnDown_SCB_sigmaIetaIeta, &b_Elec_ShiftedEnDown_SCB_sigmaIetaIeta);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_Supercluster_Eta", &Elec_ShiftedEnDown_Supercluster_Eta, &b_Elec_ShiftedEnDown_Supercluster_Eta);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_pdgId", &Elec_ShiftedEnDown_pdgId, &b_Elec_ShiftedEnDown_pdgId);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_relIso03", &Elec_ShiftedEnDown_relIso03, &b_Elec_ShiftedEnDown_relIso03);
   fChain->SetBranchAddress("Elec_ShiftedEnDown_relIso04", &Elec_ShiftedEnDown_relIso04, &b_Elec_ShiftedEnDown_relIso04);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_Charge", &Elec_ShiftedEnUp_Charge, &b_Elec_ShiftedEnUp_Charge);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_ChargeId_GsfCtf", &Elec_ShiftedEnUp_ChargeId_GsfCtf, &b_Elec_ShiftedEnUp_ChargeId_GsfCtf);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_ChargeId_GsfCtfPx", &Elec_ShiftedEnUp_ChargeId_GsfCtfPx, &b_Elec_ShiftedEnUp_ChargeId_GsfCtfPx);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_ChargeId_GsfPx", &Elec_ShiftedEnUp_ChargeId_GsfPx, &b_Elec_ShiftedEnUp_ChargeId_GsfPx);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_Conversion", &Elec_ShiftedEnUp_Conversion, &b_Elec_ShiftedEnUp_Conversion);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_Count", &Elec_ShiftedEnUp_Count, &b_Elec_ShiftedEnUp_Count);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_PFIsoRho03", &Elec_ShiftedEnUp_PFIsoRho03, &b_Elec_ShiftedEnUp_PFIsoRho03);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_PFIsoRho04", &Elec_ShiftedEnUp_PFIsoRho04, &b_Elec_ShiftedEnUp_PFIsoRho04);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_PFIsodBeta03", &Elec_ShiftedEnUp_PFIsodBeta03, &b_Elec_ShiftedEnUp_PFIsodBeta03);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_PFIsodBeta04", &Elec_ShiftedEnUp_PFIsodBeta04, &b_Elec_ShiftedEnUp_PFIsodBeta04);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_SCB_dEtaIn", &Elec_ShiftedEnUp_SCB_dEtaIn, &b_Elec_ShiftedEnUp_SCB_dEtaIn);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_SCB_dPhiIn", &Elec_ShiftedEnUp_SCB_dPhiIn, &b_Elec_ShiftedEnUp_SCB_dPhiIn);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_SCB_hOverE", &Elec_ShiftedEnUp_SCB_hOverE, &b_Elec_ShiftedEnUp_SCB_hOverE);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_SCB_ooEmooP", &Elec_ShiftedEnUp_SCB_ooEmooP, &b_Elec_ShiftedEnUp_SCB_ooEmooP);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_SCB_sigmaIetaIeta", &Elec_ShiftedEnUp_SCB_sigmaIetaIeta, &b_Elec_ShiftedEnUp_SCB_sigmaIetaIeta);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_Supercluster_Eta", &Elec_ShiftedEnUp_Supercluster_Eta, &b_Elec_ShiftedEnUp_Supercluster_Eta);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_pdgId", &Elec_ShiftedEnUp_pdgId, &b_Elec_ShiftedEnUp_pdgId);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_relIso03", &Elec_ShiftedEnUp_relIso03, &b_Elec_ShiftedEnUp_relIso03);
   fChain->SetBranchAddress("Elec_ShiftedEnUp_relIso04", &Elec_ShiftedEnUp_relIso04, &b_Elec_ShiftedEnUp_relIso04);
   fChain->SetBranchAddress("Filter_Greedy_Muon", &Filter_Greedy_Muon, &b_Filter_Greedy_Muon);
   fChain->SetBranchAddress("Filter_Inconsistent_MuonPt", &Filter_Inconsistent_MuonPt, &b_Filter_Inconsistent_MuonPt);
   fChain->SetBranchAddress("Filter_PFReco_Muon", &Filter_PFReco_Muon, &b_Filter_PFReco_Muon);
   fChain->SetBranchAddress("Filter_PV", &Filter_PV, &b_Filter_PV);
   fChain->SetBranchAddress("GenJet", &GenJet, &b_GenJet);
   fChain->SetBranchAddress("GenJet_Count", &GenJet_Count, &b_GenJet_Count);
   fChain->SetBranchAddress("GenMET", &GenMET, &b_GenMET);
   fChain->SetBranchAddress("GenMET_Count", &GenMET_Count, &b_GenMET_Count);
   fChain->SetBranchAddress("GenPar", &GenPar, &b_GenPar);
   fChain->SetBranchAddress("GenPar_Count", &GenPar_Count, &b_GenPar_Count);
   fChain->SetBranchAddress("GenPar_Dau1_Idx", &GenPar_Dau1_Idx, &b_GenPar_Dau1_Idx);
   fChain->SetBranchAddress("GenPar_Dau2_Idx", &GenPar_Dau2_Idx, &b_GenPar_Dau2_Idx);
   fChain->SetBranchAddress("GenPar_Dau_Counter", &GenPar_Dau_Counter, &b_GenPar_Dau_Counter);
   fChain->SetBranchAddress("GenPar_Idx", &GenPar_Idx, &b_GenPar_Idx);
   fChain->SetBranchAddress("GenPar_Mom1_Idx", &GenPar_Mom1_Idx, &b_GenPar_Mom1_Idx);
   fChain->SetBranchAddress("GenPar_Mom2_Idx", &GenPar_Mom2_Idx, &b_GenPar_Mom2_Idx);
   fChain->SetBranchAddress("GenPar_Mom_Counter", &GenPar_Mom_Counter, &b_GenPar_Mom_Counter);
   fChain->SetBranchAddress("GenPar_Status", &GenPar_Status, &b_GenPar_Status);
   fChain->SetBranchAddress("GenPar_pdgId", &GenPar_pdgId, &b_GenPar_pdgId);
   fChain->SetBranchAddress("Gen_EventWeight", &Gen_EventWeight, &b_Gen_EventWeight);
   fChain->SetBranchAddress("Jet", &Jet, &b_Jet);
   fChain->SetBranchAddress("Jet_Charge", &Jet_Charge, &b_Jet_Charge);
   fChain->SetBranchAddress("Jet_Count", &Jet_Count, &b_Jet_Count);
   fChain->SetBranchAddress("Jet_EnShiftedDown", &Jet_EnShiftedDown, &b_Jet_EnShiftedDown);
   fChain->SetBranchAddress("Jet_EnShiftedUp", &Jet_EnShiftedUp, &b_Jet_EnShiftedUp);
   fChain->SetBranchAddress("Jet_PartonFlavour", &Jet_PartonFlavour, &b_Jet_PartonFlavour);
   fChain->SetBranchAddress("Jet_PFId", &Jet_PFId, &b_Jet_PFId);
   fChain->SetBranchAddress("Jet_PileUpId", &Jet_PileUpId, &b_Jet_PileUpId);
   fChain->SetBranchAddress("Jet_PileUpMVA", &Jet_PileUpMVA, &b_Jet_PileUpMVA);
   fChain->SetBranchAddress("Jet_bDisc", &Jet_bDisc, &b_Jet_bDisc);
   fChain->SetBranchAddress("Jet_isJet", &Jet_isJet, &b_Jet_isJet);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METNoHF", &METNoHF, &b_METNoHF);
   fChain->SetBranchAddress("MET_JetEnShiftedUp_PT", &MET_JetEnShiftedUp_PT, &b_MET_JetEnShiftedUp_PT);
   fChain->SetBranchAddress("MET_JetEnShiftedUp_Phi", &MET_JetEnShiftedUp_Phi, &b_MET_JetEnShiftedUp_Phi);
   fChain->SetBranchAddress("MET_JetEnShiftedDown_PT", &MET_JetEnShiftedDown_PT, &b_MET_JetEnShiftedDown_PT);
   fChain->SetBranchAddress("MET_JetEnShiftedDown_Phi", &MET_JetEnShiftedDown_Phi, &b_MET_JetEnShiftedDown_Phi);
   fChain->SetBranchAddress("MET_MuonEnShiftedUp_PT", &MET_MuonEnShiftedUp_PT, &b_MET_MuonEnShiftedUp_PT);
   fChain->SetBranchAddress("MET_MuonEnShiftedUp_Phi", &MET_MuonEnShiftedUp_Phi, &b_MET_MuonEnShiftedUp_Phi);
   fChain->SetBranchAddress("MET_MuonEnShiftedDown_PT", &MET_MuonEnShiftedDown_PT, &b_MET_MuonEnShiftedDown_PT);
   fChain->SetBranchAddress("MET_MuonEnShiftedDown_Phi", &MET_MuonEnShiftedDown_Phi, &b_MET_MuonEnShiftedDown_Phi);
   fChain->SetBranchAddress("MET_ElectronEnShiftedUp_PT", &MET_ElectronEnShiftedUp_PT, &b_MET_ElectronEnShiftedUp_PT);
   fChain->SetBranchAddress("MET_ElectronEnShiftedUp_Phi", &MET_ElectronEnShiftedUp_Phi, &b_MET_ElectronEnShiftedUp_Phi);
   fChain->SetBranchAddress("MET_ElectronEnShiftedDown_PT", &MET_ElectronEnShiftedDown_PT, &b_MET_ElectronEnShiftedDown_PT);
   fChain->SetBranchAddress("MET_ElectronEnShiftedDown_Phi", &MET_ElectronEnShiftedDown_Phi, &b_MET_ElectronEnShiftedDown_Phi);
   fChain->SetBranchAddress("MET_UnclusteredEnShiftedUp_PT", &MET_UnclusteredEnShiftedUp_PT, &b_MET_UnclusteredEnShiftedUp_PT);
   fChain->SetBranchAddress("MET_UnclusteredEnShiftedUp_Phi", &MET_UnclusteredEnShiftedUp_Phi, &b_MET_UnclusteredEnShiftedUp_Phi);
   fChain->SetBranchAddress("MET_UnclusteredEnShiftedDown_PT", &MET_UnclusteredEnShiftedDown_PT, &b_MET_UnclusteredEnShiftedDown_PT);
   fChain->SetBranchAddress("MET_UnclusteredEnShiftedDown_Phi", &MET_UnclusteredEnShiftedDown_Phi, &b_MET_UnclusteredEnShiftedDown_Phi);
   fChain->SetBranchAddress("Muon", &Muon, &b_Muon);
   fChain->SetBranchAddress("Muon_ShiftedEnUp", &Muon_ShiftedEnUp, &b_Muon_ShiftedEnUp);
   fChain->SetBranchAddress("Muon_ShiftedEnDown", &Muon_ShiftedEnDown, &b_Muon_ShiftedEnDown);
   fChain->SetBranchAddress("Muon_Charge", &Muon_Charge, &b_Muon_Charge);
   fChain->SetBranchAddress("Muon_Count", &Muon_Count, &b_Muon_Count);
   fChain->SetBranchAddress("Muon_PFIsodBeta03", &Muon_PFIsodBeta03, &b_Muon_PFIsodBeta03);
   fChain->SetBranchAddress("Muon_PFIsodBeta04", &Muon_PFIsodBeta04, &b_Muon_PFIsodBeta04);
   fChain->SetBranchAddress("Muon_isHighPt", &Muon_isHighPt, &b_Muon_isHighPt);
   fChain->SetBranchAddress("Muon_isLoose", &Muon_isLoose, &b_Muon_isLoose);
   fChain->SetBranchAddress("Muon_isSoft", &Muon_isSoft, &b_Muon_isSoft);
   fChain->SetBranchAddress("Muon_isTight", &Muon_isTight, &b_Muon_isTight);
   fChain->SetBranchAddress("Muon_pdgId", &Muon_pdgId, &b_Muon_pdgId);
   fChain->SetBranchAddress("Muon_relIso03", &Muon_relIso03, &b_Muon_relIso03);
   fChain->SetBranchAddress("Muon_relIso04", &Muon_relIso04, &b_Muon_relIso04);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_Charge", &Muon_ShiftedEnDown_Charge, &b_Muon_ShiftedEnDown_Charge);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_Count", &Muon_ShiftedEnDown_Count, &b_Muon_ShiftedEnDown_Count);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_PFIsodBeta03", &Muon_ShiftedEnDown_PFIsodBeta03, &b_Muon_ShiftedEnDown_PFIsodBeta03);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_PFIsodBeta04", &Muon_ShiftedEnDown_PFIsodBeta04, &b_Muon_ShiftedEnDown_PFIsodBeta04);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_isHighPt", &Muon_ShiftedEnDown_isHighPt, &b_Muon_ShiftedEnDown_isHighPt);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_isLoose", &Muon_ShiftedEnDown_isLoose, &b_Muon_ShiftedEnDown_isLoose);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_isSoft", &Muon_ShiftedEnDown_isSoft, &b_Muon_ShiftedEnDown_isSoft);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_isTight", &Muon_ShiftedEnDown_isTight, &b_Muon_ShiftedEnDown_isTight);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_pdgId", &Muon_ShiftedEnDown_pdgId, &b_Muon_ShiftedEnDown_pdgId);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_relIso03", &Muon_ShiftedEnDown_relIso03, &b_Muon_ShiftedEnDown_relIso03);
   fChain->SetBranchAddress("Muon_ShiftedEnDown_relIso04", &Muon_ShiftedEnDown_relIso04, &b_Muon_ShiftedEnDown_relIso04);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_Charge", &Muon_ShiftedEnUp_Charge, &b_Muon_ShiftedEnUp_Charge);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_Count", &Muon_ShiftedEnUp_Count, &b_Muon_ShiftedEnUp_Count);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_PFIsodBeta03", &Muon_ShiftedEnUp_PFIsodBeta03, &b_Muon_ShiftedEnUp_PFIsodBeta03);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_PFIsodBeta04", &Muon_ShiftedEnUp_PFIsodBeta04, &b_Muon_ShiftedEnUp_PFIsodBeta04);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_isHighPt", &Muon_ShiftedEnUp_isHighPt, &b_Muon_ShiftedEnUp_isHighPt);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_isLoose", &Muon_ShiftedEnUp_isLoose, &b_Muon_ShiftedEnUp_isLoose);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_isSoft", &Muon_ShiftedEnUp_isSoft, &b_Muon_ShiftedEnUp_isSoft);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_isTight", &Muon_ShiftedEnUp_isTight, &b_Muon_ShiftedEnUp_isTight);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_pdgId", &Muon_ShiftedEnUp_pdgId, &b_Muon_ShiftedEnUp_pdgId);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_relIso03", &Muon_ShiftedEnUp_relIso03, &b_Muon_ShiftedEnUp_relIso03);
   fChain->SetBranchAddress("Muon_ShiftedEnUp_relIso04", &Muon_ShiftedEnUp_relIso04, &b_Muon_ShiftedEnUp_relIso04);
   fChain->SetBranchAddress("PDFWeight_BjorkenX1", &PDFWeight_BjorkenX1, &b_PDFWeight_BjorkenX1);
   fChain->SetBranchAddress("PDFWeight_BjorkenX2", &PDFWeight_BjorkenX2, &b_PDFWeight_BjorkenX2);
   fChain->SetBranchAddress("PDFWeight_Cent", &PDFWeight_Cent, &b_PDFWeight_Cent);
   fChain->SetBranchAddress("PDFWeight_Cent_Down", &PDFWeight_Cent_Down, &b_PDFWeight_Cent_Down);
   fChain->SetBranchAddress("PDFWeight_Cent_Up", &PDFWeight_Cent_Up, &b_PDFWeight_Cent_Up);
   fChain->SetBranchAddress("PDFWeight_Var1_Down", &PDFWeight_Var1_Down, &b_PDFWeight_Var1_Down);
   fChain->SetBranchAddress("PDFWeight_Var2_Down", &PDFWeight_Var2_Down, &b_PDFWeight_Var2_Down);
   fChain->SetBranchAddress("PDFWeight_Id1", &PDFWeight_Id1, &b_PDFWeight_Id1);
   fChain->SetBranchAddress("PDFWeight_Id2", &PDFWeight_Id2, &b_PDFWeight_Id2);
   fChain->SetBranchAddress("PDFWeight_PDF1", &PDFWeight_PDF1, &b_PDFWeight_PDF1);
   fChain->SetBranchAddress("PDFWeight_PDF2", &PDFWeight_PDF2, &b_PDFWeight_PDF2);
   fChain->SetBranchAddress("PDFWeight_Q", &PDFWeight_Q, &b_PDFWeight_Q);
   fChain->SetBranchAddress("PDFWeight_Var1_Up", &PDFWeight_Var1_Up, &b_PDFWeight_Var1_Up);
   fChain->SetBranchAddress("PDFWeight_Var2_Up", &PDFWeight_Var2_Up, &b_PDFWeight_Var2_Up);
   fChain->SetBranchAddress("PV_Count", &PV_Count, &b_PV_Count);
   fChain->SetBranchAddress("PileUp_Count_Interaction", &PileUp_Count_Interaction, &b_PileUp_Count_Interaction);
   fChain->SetBranchAddress("PileUp_Count_Intime", &PileUp_Count_Intime, &b_PileUp_Count_Intime);
   fChain->SetBranchAddress("Trigger_Name", &Trigger_Name, &b_Trigger_Name);
   fChain->SetBranchAddress("Trigger_PreScale", &Trigger_PreScale, &b_Trigger_PreScale);
   fChain->SetBranchAddress("Trigger_isError", &Trigger_isError, &b_Trigger_isError);
   fChain->SetBranchAddress("Trigger_isPass", &Trigger_isPass, &b_Trigger_isPass);
   fChain->SetBranchAddress("Trigger_isRun", &Trigger_isRun, &b_Trigger_isRun);
   fChain->SetBranchAddress("Vertex_SumPtSquare", &Vertex_SumPtSquare, &b_Vertex_SumPtSquare);
   fChain->SetBranchAddress("Vertex_X", &Vertex_X, &b_Vertex_X);
   fChain->SetBranchAddress("Vertex_X_Error", &Vertex_X_Error, &b_Vertex_X_Error);
   fChain->SetBranchAddress("Vertex_Y", &Vertex_Y, &b_Vertex_Y);
   fChain->SetBranchAddress("Vertex_Y_Error", &Vertex_Y_Error, &b_Vertex_Y_Error);
   fChain->SetBranchAddress("Vertex_Z", &Vertex_Z, &b_Vertex_Z);
   fChain->SetBranchAddress("Vertex_Z_Error", &Vertex_Z_Error, &b_Vertex_Z_Error);
   fChain->SetBranchAddress("Weight_PileUp", &Weight_PileUp, &b_Weight_PileUp);
   fChain->SetBranchAddress("Weight_PileUp_ShiftedUp", &Weight_PileUp_ShiftedUp, &b_Weight_PileUp_ShiftedUp);
   fChain->SetBranchAddress("Weight_PileUp_ShiftedDown", &Weight_PileUp_ShiftedDown, &b_Weight_PileUp_ShiftedDown);
   Notify();
}

Bool_t SSBTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SSBTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SSBTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SSBTree_cxx
