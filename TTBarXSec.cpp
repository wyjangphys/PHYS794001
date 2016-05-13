#define TTBarXSec_cxx

#define DEBUG 1

#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#ifndef ROOT_HEADER
#define ROOT_HEADER
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#endif

#ifndef MY_HEADER
#define MY_HEADER
#include "TTBarXSec.h"
#include "CommonTools.h"
#endif

using namespace std;

/*
 * @brief  This method defines the dielectron analysis loop
 * @return
 */
void TTBarXSec::ElElLoop()
{/*{{{*/
  if (fChain == 0) return;

  unsigned int nEntries = fChain->GetEntriesFast();
  unsigned int nBytes = 0;
  unsigned int nb = 0;

  ///My variables
  unsigned int __tot_evt = 0;
  unsigned int nElecTrigEvent = 0;

  ////////////////////////
  /// start event loop ///
  ////////////////////////
  int nEle = 0;                       // Number of electrons which passed the electron requirement.
  int nObjEle = 0;
  int nDilep= 0;
  int nJet = 0;
  int nMET = 0;
  for (Long64_t jentry=0; jentry < nEntries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if ( ientry < 0 )
    {
      printf("ERROR: Failed to load the tree!!!\n");
      break;
    }

    nb = fChain->GetEntry(jentry);   nBytes += nb;

    if ( jentry % 10000 == 0 ) printf("Event %lld\n", jentry); //%lld supports Long64_t

    __tot_evt++;

    //////////////////////////////////////
    //  start any calculation and cuts  //
    //////////////////////////////////////

    ////////////////////////////////////////
    // Example of Event Weight            //
    // (Only for MC Samples ...           //
    // DO NOT APPLY EVENT WEIGHT TO DATA )//
    ////////////////////////////////////////

    double evt_weight_ = 1.0;
    if( !Info_isData )
      evt_weight_ = GetEventWeight();

    /////////////////////////////////////////////
    // Example of Vertex Filter (EventFillter) //
    /////////////////////////////////////////////
    if ( Filter_PV->at(0) == false ) { continue; }

    ///////////////////////////////////////////////////
    // Here is for EleEle scenario                   //
    ///////////////////////////////////////////////////
    // Step 0. Trigger requirement
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )

    // Step 0. Trigger requirement
    //   Most of codes are implemented in the member function TTBarXSec::ElectronTriggerRequirement
    if( this->ElectronTriggerRequirement() != 1 ) continue;
    nElecTrigEvent++;
    if( Info_isData == false )          /// When the input file is MC,
      if( strstr(infile, "TTBar_Sample") )
        if( Channel_Idx != 22 )
          continue; /// Check the channel index for dielectron trigger.

    // Step 1. Lepton requirement
    //     Among the events passed the trigger requirement, apply the electron requirement.
    //  Most of processes are implemented as a member function TTBarXSec::ElectronRequirement
    vector<int> selectedEleIdx;         // A container to store electron indices which passed the electron requirement.
    selectedEleIdx.clear();

    for( int i = 0; i < Elec_Count; ++i )
    {
      if( this->ElectronRequirement(i) == true ) selectedEleIdx.push_back(i);
    }
    nObjEle += selectedEleIdx.size();
    if( selectedEleIdx.size() != 2 ) continue; // Step 1. Third lepton veto

    // Step 1. Di-lepton mass cut, third lepton veto and charge opposite sign check.
    double q1, q2;                      // Electron charges
    TLorentzVector dilep;               // Dilepton TLorentzVector

    q1 = Elec_Charge->at( selectedEleIdx.at(0) );
    q2 = Elec_Charge->at( selectedEleIdx.at(1) );
    TLorentzVector* ele_1 = (TLorentzVector*)Elec->At( selectedEleIdx.at(0) );
    TLorentzVector* ele_2 = (TLorentzVector*)Elec->At( selectedEleIdx.at(1) );
    dilep = *ele_1 + *ele_2;

    if( dilep.M() < 20 )                   continue;  // Step 1. Di-Lepton mass (> 20 GeV) cut
    if( q1 * q2 > 0 )                      continue;  // Step 1. Opposite charge cut
    if( dilep.M() > 76 && dilep.M() < 106) continue;  // Step 2. Z-mass veto for dielectron channel
    nDilep++;

    // Step 3. Jet selection and jet cleaning process
    vector<int> selectedJetIdx;                       // A container to store selected jet indices.
    selectedJetIdx.clear();

    for( int i = 0; i < Jet_Count; i++)
    {
      if( !( this->JetRequirement(i) ) ) continue;    // Select jets satisfying jet requirements.
      if( !( this->IsClearJet(i) ) ) continue;
      nJet++;
      selectedJetIdx.push_back(i);
    }

    cout << "NJet : " << selectedJetIdx.size() << endl;
    if( !( selectedJetIdx.size() >= 2 ) ) continue;          // Step 3. # of Jets >= 2

    TLorentzVector* met = (TLorentzVector*)MET->At(0);
    cout << "MET-Pt : " << met->Pt() << " GeV/c" << endl;
    if( !( met->Pt() > 40 ) ) continue;                    // Step 4. MET > 40 GeV
    nMET++;

    vector<int> bTaggedJetIdx;
    bTaggedJetIdx.clear();
    for( int i = 0; i < selectedJetIdx.size(); i++ )   // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
    {
      if( !( Jet_bDisc->at(i) > 0.605 ) ) continue;
      else bTaggedJetIdx.push_back( selectedJetIdx.at(i) );
    }
    if( !( bTaggedJetIdx.size() >= 1 ) ) continue;

    nEle++;

    FillHisto( hElEl_ElPt,      ele_1->Pt(),           evt_weight_ );
    FillHisto( hElEl_ElEnergy,  ele_1->Energy(),       evt_weight_ );
    FillHisto( hElEl_ElEta,     ele_1->Eta(),          evt_weight_ );
    FillHisto( hElEl_ElPhi,     ele_1->Phi(),          evt_weight_ );
    FillHisto( hElEl_ElInvMass, dilep.M(),             evt_weight_ );
    FillHisto( hElEl_NJets,     selectedJetIdx.size(), evt_weight_ );
    FillHisto( hElEl_NEl,       selectedEleIdx.size(), evt_weight_ );
    // FillHisto(TH1F*, variable, eventweight)
  }

  /////////////////////////
  /// end of event loop ///
  /////////////////////////

  printf("[ElEl] Total processed number of events: %lld\n", __tot_evt);
  printf("[ElEl] Events with dielectron trigger: %lld\n", nElecTrigEvent);
  printf("[ElEl] Object level electrons: %lld\n", nObjEle);
  printf("[ElEl] Selected dielectrons: %lld\n", nDilep);
  printf("[ElEl] njet: %d\n", nJet);
  printf("[ElEl] nmet: %d\n", nMET);
  printf("[ElEl] Selected / Total = %d / %d = %f\n", nEle, __tot_evt, (float)nEle/(float)__tot_evt);
}//end Loop function/*}}}*/

void TTBarXSec::MuMuLoop()
{/*{{{*/
  if (fChain == 0) return;

  unsigned int nEntries = fChain->GetEntriesFast();
  unsigned int nBytes = 0;
  unsigned int nb = 0;

  ///My variables
  unsigned int __tot_evt = 0;

  ////////////////////////
  /// start event loop ///
  ////////////////////////

  int nMu = 0;                       // Number of electrons which passed the electron requirement.
  unsigned int nMuonTrigEvent = 0;

  for (Long64_t jentry=0; jentry<nEntries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
    {
      printf("ERROR: Failed to load the tree!!!\n");
      break;
    }

    nb = fChain->GetEntry(jentry);   nBytes += nb;

    if (jentry % 10000 == 0) printf("Event %lld\n", jentry); //%lld supports Long64_t

    __tot_evt++;

    //////////////////////////////////////
    /// start any calculation and cuts ///
    //////////////////////////////////////

    ////////////////////////////////////////
    // Example of Event Weight            //
    // (Only for MC Samples ...           //
    // DO NOT APPLY EVENT WEIGHT TO DATA )//
    ////////////////////////////////////////

    double evt_weight_ = 1.0;
    if( !Info_isData )
      evt_weight_ = GetEventWeight();

    /////////////////////////////////////////////
    // Example of Vertex Filter (EventFillter) //
    /////////////////////////////////////////////
    if ( Filter_PV->at(0) == false ) {continue;}

    ///////////////////////////////////////////////////
    // Here is for EleEle scenario                   //
    ///////////////////////////////////////////////////
    // Step 0. Trigger requirement
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )

    // Step 0. Trigger requirement
    //     Most of codes are implemented in the member function TTBarXSec::ElectronTriggerRequirement
    if( this->MuonTriggerRequirement() != 1 ) continue;
    nMuonTrigEvent++;
    if( Info_isData == false )          /// When the input file is MC,
      {
        if( strstr(infile, "TTBar_Sample") )
        {
          if( Channel_Idx != 26 ) continue; /// Check the channel index for dielectron trigger.
        }
      }

    // Step 1. Lepton requirement
    //     Among the events passed the trigger requirement, apply the electron requirement.
    //  Most of processes are implemented as a member function TTBarXSec::ElectronRequirement
    vector<int> selectedMuonIdx;         // A container to store electron indices which are passed the electron requirement.
    selectedMuonIdx.clear();
    for ( int i = 0; i < Muon_Count; ++i )
    {
      if( MuonRequirement(i) ) selectedMuonIdx.push_back(i);
    }
    if( selectedMuonIdx.size() != 2 ) continue; // Step 1. Third lepton veto

    // Step 1. Di-lepton mass cut, third lepton veto and charge opposite sign check.
    double q1, q2;                      // Electron charges
    TLorentzVector dilep;               // Dilepton TLorentzVector

    q1 = Muon_Charge->at( selectedMuonIdx.at(0) );
    q2 = Muon_Charge->at( selectedMuonIdx.at(1) );
    TLorentzVector* mu_1 = (TLorentzVector*)Muon->At(selectedMuonIdx.at(0));
    TLorentzVector* mu_2 = (TLorentzVector*)Muon->At(selectedMuonIdx.at(1));
    dilep = *mu_1 + *mu_2;

    if( dilep.M() < 20 ) continue;                                            // Step 1. Di-Lepton mass (> 20 GeV) cut
    if( !( q1 * q2 < 0 ) ) continue;                                          // Step 1. Opposite charge cut
    if( dilep.M() > 76 && dilep.M() < 106) continue;                          // Step 2. Z-mass veto for dielectron channel

    // Step 3. Jet selection and jet cleaning process
    vector<int> selectedJetIdx;                               // A container to store selected jet indices.
    selectedJetIdx.clear();

    for( int i = 0; i < Jet_Count; i++)
    {
      if( !( this->JetRequirement(i) ) ) continue; // Select jets satisfying jet requirements.
      if( !( this->IsClearJet(i) ) ) continue;
      selectedJetIdx.push_back(i);
    }

    if( !( selectedJetIdx.size() >= 2 ) ) continue;                        // Step 3. # of Jets >= 2

    TLorentzVector* met = (TLorentzVector*)MET->At(0);
    if( met->Pt() < 40 ) continue;                                // Step 4. MET > 40 GeV

    vector<int> bTaggedJetIdx;
    bTaggedJetIdx.clear();
    for( int i = 0; i < selectedJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
    {
      if( !( Jet_bDisc->at(i) > 0.605 ) ) continue;
      else bTaggedJetIdx.push_back( selectedJetIdx.at(i) );
    }
    if( bTaggedJetIdx.size() < 1 ) continue;

    nMu++;

    FillHisto( hMuMu_MuonPt,      mu_1->Pt(),             evt_weight_ );
    FillHisto( hMuMu_MuonEnergy,  mu_1->Energy(),         evt_weight_ );
    FillHisto( hMuMu_MuonEta,     mu_1->Eta(),            evt_weight_ );
    FillHisto( hMuMu_MuonPhi,     mu_1->Phi(),            evt_weight_ );
    FillHisto( hMuMu_MuonInvMass, dilep.M(),              evt_weight_ );
    FillHisto( hMuMu_NJets,       selectedJetIdx.size(),  evt_weight_ );
    FillHisto( hMuMu_NMuon,       selectedMuonIdx.size(), evt_weight_ );
    // FillHisto(TH1F*, variable, eventweight)
  }

  /////////////////////////
  /// end of event loop ///
  /////////////////////////

  printf("[MuMu] Total processed number of events: %lld\n", __tot_evt);
  printf("[MuMu] Events with dimuon trigger: %lld\n", nMuonTrigEvent);
  printf("[MuMu] Selected dimuon events: %lld\n", nMu);
  printf("[MuMu] Selected / Total = %f\n", (float)nMu/(float)__tot_evt);
}//end Loop function/*}}}*/

void TTBarXSec::ElMuLoop()
{/*{{{*/
  if (fChain == 0) return;

  unsigned int nEntries = fChain->GetEntriesFast();
  unsigned int nBytes = 0;
  unsigned int nb = 0;

  ///My variables
  unsigned int __tot_evt = 0;

  ////////////////////////
  /// start event loop ///
  ////////////////////////
  for (Long64_t jentry=0; jentry<nEntries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
    {
      printf("ERROR: Failed to load the tree!!!\n");
      break;
    }

    nb = fChain->GetEntry(jentry);   nBytes += nb;

    if (jentry % 10000 == 0) printf("Event %lld\n", jentry); //%lld supports Long64_t

    __tot_evt++;

    //////////////////////////////////////
    /// start any calculation and cuts ///
    //////////////////////////////////////

    ////////////////////////////////////////
    // Example of Event Weight            //
    // (Only for MC Samples ...           //
    // DO NOT APPLY EVENT WEIGHT TO DATA )//
    ////////////////////////////////////////

    double evt_weight_ = 1.0;
    if( !Info_isData )
      evt_weight_ = GetEventWeight();

    /////////////////////////////////////////////
    // Example of Vertex Filter (EventFillter) //
    /////////////////////////////////////////////
    if ( Filter_PV->at(0) == false ) {continue;}

    ///////////////////////////////////////////////////
    // Here is for EleMu scenario                    //
    ///////////////////////////////////////////////////
    // Step 0. Trigger requirement
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // (Skip this for ElMu) Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )
    if( MuonEleTriggerRequirement() != 1 ) continue;
    if( Info_isData == false )
      if( strstr(infile, "TTBar_Sample") )
        if( Channel_Idx != 24 )             // In case of MC input file, check channel index.
          continue;

    int nMuonEle = 0;
    int nEle = 0;
    int nMuon = 0;
    int nJet = 0;
    int nCleanJet = 0;

    TLorentzVector leadingMuonInMuEl;
    TLorentzVector leadingElectronInMuEl;
    vector<int> selectedMuonIdx;
    vector<int> selectedEleIdx;
    selectedMuonIdx.clear();
    selectedEleIdx.clear();

    for( int i = 0; i < Elec_Count; ++i )
    {
      if( this->ElectronRequirement(i) )
      {
        selectedEleIdx.push_back(i);
        nEle++;
      }
    }
    if( selectedEleIdx.size() != 1 ) continue;

    for( int i = 0; i < Muon_Count; ++i )
    {
      if( this->MuonRequirement(i) )
      {
        selectedMuonIdx.push_back(i);
        nMuon++;
      }
    }
    if( selectedMuonIdx.size() != 1 ) continue;

    double q1, q2;
    TLorentzVector dilep;

    q1 = Elec_Charge->at( selectedEleIdx.at(0) );
    q2 = Muon_Charge->at( selectedMuonIdx.at(0) );
    TLorentzVector* ele_i = (TLorentzVector*)Elec->At(selectedEleIdx.at(0));
    TLorentzVector* muon_j = (TLorentzVector*)Muon->At(selectedMuonIdx.at(0));
    dilep = *ele_i + *muon_j;

    //cout << Form("[%d, %d] / %f GeV", selectedEleIdx.at(i), selectedMuonIdx.at(j), dilep.M()) << endl;
    if( dilep.M() < 20 ) continue;                                           // Step 1. Di-Lepton mass (> 20 GeV) cut
    if( Elec_Charge->at( selectedEleIdx.at(0) ) * Muon_Charge->at( selectedMuonIdx.at(0) ) == 1 ) continue;
    if( selectedEleIdx.size() != 1 && selectedMuonIdx.size() != 1 ) continue;

    // Step 3. Jet selection and jet cleaning process
    vector<int> selectedJetIdx;                           // A container to store selected jet indices.
    selectedJetIdx.clear();
    for( int i = 0; i < Jet_Count; i++)
    {
      if( !( this->JetRequirement(i) ) ) continue; // Select jets satisfying jet requirements.
      if( !( this->IsClearJet(i) ) ) continue;
      selectedJetIdx.push_back(i);
    }

    if( selectedJetIdx.size() < 2 ) continue;                        // Step 3. # of Jets >= 2

    vector<int> bTaggedJetIdx;
    bTaggedJetIdx.clear();
    for( int i = 0; i < selectedJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
    {
      if( !( Jet_bDisc->at( selectedJetIdx.at(i) ) > 0.605 ) ) continue;
      else bTaggedJetIdx.push_back( selectedJetIdx.at(i) );
    }
    if( !( bTaggedJetIdx.size() >= 1 ) ) continue;

    leadingMuonInMuEl = *(TLorentzVector*)Muon->At( selectedMuonIdx.at(0) );
    FillHisto(hElMu_MuPt,     leadingMuonInMuEl.Pt(),      evt_weight_);
    FillHisto(hElMu_MuEnergy, leadingMuonInMuEl.E(),       evt_weight_);
    FillHisto(hElMu_MuEta,    leadingMuonInMuEl.Eta(),     evt_weight_);
    FillHisto(hElMu_MuPhi,    leadingMuonInMuEl.Phi(),     evt_weight_);
    leadingElectronInMuEl = *(TLorentzVector*)Elec->At( selectedEleIdx.at(0) );
    FillHisto(hElMu_ElPt,     leadingElectronInMuEl.Pt(),  evt_weight_);
    FillHisto(hElMu_ElEnergy, leadingElectronInMuEl.E(),   evt_weight_);
    FillHisto(hElMu_ElEta,    leadingElectronInMuEl.Eta(), evt_weight_);
    FillHisto(hElMu_ElPhi,    leadingElectronInMuEl.Phi(), evt_weight_);
    FillHisto(hElMu_NJets,    selectedJetIdx.size(),       evt_weight_);
    FillHisto(hElMu_NMu,      selectedMuonIdx.size(),      evt_weight_);
    FillHisto(hElMu_NEl,      selectedEleIdx.size(),       evt_weight_);
  }//event loop

  /////////////////////////
  /// end of event loop ///
  /////////////////////////

  printf("Total processed number of events: %lld\n", __tot_evt);

}//end Loop function/*}}}*/

/*
 * @brief  Initialize TFile objects and call histogram declaration function
 */
void TTBarXSec::Start()
{/*{{{*/
  fin  = new TFile(Form("%s",infile) ,"READ");
  fout = new TFile(Form("%s",outfile),"RECREATE");
  fout->mkdir("EleEle");
  fout->mkdir("MuMu");
  fout->mkdir("MuEle");
  fout->cd("");

  TDirectory *dir = gDirectory;
  dir->cd();

  DeclareHistos();
}/*}}}*/

void TTBarXSec::DeclareHistos()
{/*{{{*/
  fout->cd("MuMu");
  hMuMu_NMuon = new TH1F("hMuMu_NMuon", "Number of Muons;Number of Muons", 30, 0, 30);
  hMuMu_NMuon->Sumw2();
  hMuMu_MuonPt = new TH1F("hMuMu_MuonPt", "p^{T} distribution of dimuons; GeV/c", 100, 0, 1000);
  hMuMu_MuonPt->Sumw2();
  hMuMu_MuonEnergy = new TH1F("hMuMu_MuonEnergy", "Energy distribution of leading muon; GeV; Entries", 100, 0, 1000);
  hMuMu_MuonEnergy->Sumw2();
  hMuMu_MuonEta = new TH1F("hMuMu_MuonEta", "#eta distribution of muon", 100, -5, 5);
  hMuMu_MuonEta->Sumw2();
  hMuMu_MuonPhi = new TH1F("hMuMu_MuonPhi", "#phi distribution of muon", 100, 0, TMath::TwoPi());
  hMuMu_MuonPhi->Sumw2();
  hMuMu_MuonInvMass = new TH1F("hMuMu_MuonInvMass", "Invariant Mass [MuMu]; GeV/c2" , 100, 0, 1000);
  hMuMu_MuonInvMass->Sumw2();
  hMuMu_NJets = new TH1F("hMuMu_NJets", "Number of clean jets in dimuon events; NJets", 30, 0, 30);
  hMuMu_NJets->Sumw2();

  fout->cd("EleEle");
  hElEl_NEl = new TH1F(Form("hElEl_NEl"), Form("Number of Electrons;Number of Electrons"), 30, 0, 30);
  hElEl_NEl->Sumw2();
  hElEl_ElPt = new TH1F(Form("hElEl_ElPt"), Form("p^{T} distribution of leading electrons;GeV/c"), 100, 0, 1000);
  hElEl_ElPt->Sumw2();
  hElEl_ElEnergy = new TH1F("hElEl_ElEnergy", "Energy distribution of leading electrons; GeV; Entries", 100, 0, 1000);
  hElEl_ElEnergy->Sumw2();
  hElEl_ElEta = new TH1F("hElEl_ElEta", "#eta distribution of electron", 100, -5, 5);
  hElEl_ElEta->Sumw2();
  hElEl_ElPhi = new TH1F("hElEl_ElPhi", "#phi distribution of electron", 100, 0, TMath::TwoPi());
  hElEl_ElPhi->Sumw2();
  hElEl_ElInvMass = new TH1F(Form("hElEl_ElInvMass"), Form("Invariant Mass; GeV"), 100,0,1000);
  hElEl_ElInvMass->Sumw2();
  hElEl_NJets = new TH1F("hElEl_NJets", "Number of clean jets in dielectron events; NJets", 30, 0, 30);
  hElEl_NJets->Sumw2();

  fout->cd("MuEle");
  hElMu_NMu = new TH1F("hElMu_NMu", "Number of Muon Events in e#mu channel; NMuon", 30, 0, 30);
  hElMu_NMu->Sumw2();
  hElMu_NEl = new TH1F("hElMu_NEl", "Number of Electron Events in e#mu channel; NElectron", 30, 0, 30);
  hElMu_NEl->Sumw2();
  hElMu_MuPt = new TH1F("hElMu_MuPt", "p^{T} distribution of leading muons;GeV/c;Entries", 100, 0, 1000);
  hElMu_MuPt->Sumw2();
  hElMu_MuEnergy = new TH1F("hElMu_MuEnergy", "Energy distribution of leading muons in e#mu channel;GeV;Entries", 100, 0, 1000);
  hElMu_MuEnergy->Sumw2();
  hElMu_MuEta = new TH1F("hElMu_MuEta", "#eta distribution of muons in e#mu channel;#eta;Entries", 100, -5, 5);
  hElMu_MuEta->Sumw2();
  hElMu_MuPhi = new TH1F("hElMu_MuPhi", "#phi distribution of muons in e#mu channel;#phi;Entries", 100, 0, TMath::TwoPi());
  hElMu_MuPhi->Sumw2();
  hElMu_ElPt = new TH1F("hElMu_ElPt", "p^{T} distribution of electrons in e#mu channel;GeV/c;Entries", 100, 0, 1000);
  hElMu_ElPt->Sumw2();
  hElMu_ElEnergy = new TH1F("hElMu_ElEnergy", "Energy distribution of leading electrons in e#mu channel;GeV;entries", 100, 0, 1000);
  hElMu_ElEnergy->Sumw2();
  hElMu_ElEta = new TH1F("hElMu_ElEta", "#eta distribution of muons in e#mu channel;#eta;Entries", 100, -5, 5);
  hElMu_ElEta->Sumw2();
  hElMu_ElPhi = new TH1F("hElMu_ElPhi", "#phi distribution of muons in e#mu channel;#phi;Entries", 100, 0, TMath::TwoPi());
  hElMu_ElPhi->Sumw2();
  hElMu_NJets = new TH1F("hElMu_NJets", "Number of clean jets in dielectron events; NJets", 30, 0, 30);
  hElMu_NJets->Sumw2();
}/*}}}*/

void TTBarXSec::End()
{/*{{{*/
  //NPositiveWeightEvents->Fill(nPositiveWeightEvent);
  //NNegativeWeightEvents->Fill(nNegativeWeightEvent);
  cout << "End processing..." << endl << endl; 
  if( fout->Write() ) cout << fout->GetName() << " is written." << endl;
  fout->Close();
}/*}}}*/

void TTBarXSec::SetInputFileName(char *inputname)
{/*{{{*/
  infile = inputname;
}/*}}}*/

void TTBarXSec::SetOutputFileName(char *outname)
{/*{{{*/
  outfile = outname;
}/*}}}*/

bool TTBarXSec::ElectronTriggerRequirement()
{/*{{{*/
  int ptrigindex = 0;
  bool trigpass  = false;

  for( unsigned int i = 0; i < Trigger_Name->size(); i++)
  {
    if ( TString( Trigger_Name->at(i) ).Contains( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ) ) 
    {
      if ( ( Trigger_isPass->at(i) ) && !( Trigger_isError->at(i) ) && ( Trigger_isRun->at(i) ) ){ ptrigindex = ptrigindex+1; }
    }
  }
  if( ptrigindex > 0 ) trigpass = true;
  if( trigpass == false ) return false;

  return true;
}/*}}}*/

bool TTBarXSec::ElectronRequirement(int i)
{/*{{{*/
  TLorentzVector* ele_tag = (TLorentzVector*)Elec->At(i);
  float absSuperClusterEta = fabs( Elec_Supercluster_Eta->at(i) );
  float absEta = fabs( ele_tag->Eta() );

  if ( !( Elec_PFIsoRho03->at(i) < 0.0766 ) )             return false;
  if ( ( absSuperClusterEta > 1.4442 && absSuperClusterEta < 1.566 ) ) return false;
  if ( !Elec_SCB_Medium->at(i) )                          return false;
  if ( !( Elec_Inner_Hit->at(i) <= 1 ) )                  return false;
  if ( !Elec_ChargeId_GsfPx->at(i) )                      return false;
  if ( !( ele_tag->Pt() > 20 ) )                          return false;
  if ( !( absEta < 2.5 ) )                                return false;
  if ( absSuperClusterEta <= 1.479 )
  {
    if ( !( fabs(Elec_Track_GsfdXY->at(i)) < 0.0118 ) )   return false;
    if ( !( fabs(Elec_Track_GsfdZ->at(i))  < 0.373 ) )    return false;
    if ( !Elec_Conversion->at(i) )                        return false;
  }
  if ( absSuperClusterEta > 1.479 && absSuperClusterEta < 2.5 ) 
  {
    if ( !( fabs(Elec_Track_GsfdXY->at(i)) < 0.0739 ) )   return false;
    if ( !( fabs(Elec_Track_GsfdZ->at(i))  < 0.602 ) )    return false;
    if ( !Elec_Conversion->at(i) )                        return false;
  }
  return true;
}/*}}}*/

int TTBarXSec::MuonTriggerRequirement()
{/*{{{*/
  int ptrigindex = 0;
  bool trigpass  = false;

  for( unsigned int i = 0; i < Trigger_Name->size(); i++)
  {
    if( TString( Trigger_Name->at(i) ).Contains( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v" )
        || TString( Trigger_Name->at(i) ).Contains( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v" ) )
    {
      if ( ( Trigger_isPass->at(i) )
          && !( Trigger_isError->at(i) )
          &&  ( Trigger_isRun->at(i) ) )
      {
        ptrigindex = ptrigindex+1;
      }
    }
  }

  if( ptrigindex > 0 ) trigpass = true;

  return trigpass;
}/*}}}*/

bool TTBarXSec::MuonRequirement(int i)
{/*{{{*/
  TLorentzVector* mu_tag = (TLorentzVector*)Muon->At(i);
  if ( !( Muon_PFIsodBeta04->at(i) < 0.12 ) ) return false;
  if ( !Muon_isTight->at(i) )                 return false;
  if ( !( mu_tag->Pt() > 20 ) )               return false;
  if ( !( mu_tag->Eta() < 2.4 ) )             return false;

  return true;
}/*}}}*/

int TTBarXSec::MuonEleTriggerRequirement()
{/*{{{*/
  int ptrigindex;
  bool trigpass;

  ptrigindex = 0;
  trigpass = false;

  for( unsigned int i = 0; i < Trigger_Name->size(); i++ )
  {
    if( TString( Trigger_Name->at(i) ).Contains( "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v" )
     || TString( Trigger_Name->at(i) ).Contains( "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v" ) )
      if( ( Trigger_isPass->at(i) ) && !( Trigger_isError->at(i) ) && (Trigger_isRun->at(i) ) ){ ptrigindex++; }
  }
  if( ptrigindex > 0 ) trigpass = true;
  if( trigpass == false ) return 0;

  return 1;
}/*}}}*/

bool TTBarXSec::JetRequirement(int i)
{/*{{{*/
  if( !( Jet_PFId->at(i) >= 1 ) )     return false;
  if( !( Jet_bDisc->at(i) > 0.605 ) ) return false;

  TLorentzVector* jet = (TLorentzVector*)Jet->At(i);
  float absEta = fabs( jet->Eta() );
  if( !( jet->Pt() > 30. ) )          return false;
  if( !( absEta < 2.4 ) )             return false;

  return true;
}/*}}}*/

bool TTBarXSec::IsClearJet(int i)
{/*{{{*/
  TLorentzVector* jet = (TLorentzVector*)Jet->At(i);

  // Is there any electron near the jet?
  for(int j = 0; j < Elec_Count; j++)
  {
    TLorentzVector* elec = (TLorentzVector*)Elec->At(j);
    float absEta = fabs( elec->Eta() );
    if( !( Elec_PFIsoRho03->at(j) <  0.11 ) ) continue;
    if(    Elec_SCB_Veto->at(j)   != true   ) continue;
    if( !( elec->Pt()             >  20.  ) ) continue;
    if( !( absEta                 <  2.5  ) ) continue;
    if( absEta <= 1.479 )
    {
      if( !( fabs( Elec_Track_GsfdXY->at(j) ) < 0.060279 ) ) continue;
      if( Elec_Conversion->at(j) != true )                   continue;
      if( Elec_Inner_Hit->at(j) != 2. )                      continue;
    }
    else if( absEta > 1.479 && absEta < 2.5 )
    {
      if( !( fabs( Elec_Track_GsfdXY->at(j) ) < 0.273097 ) ) continue;
      if( Elec_Conversion->at(j) != true )                   continue;
      if( Elec_Inner_Hit->at(j) != 3. )                      continue;
    }
    if( jet->DeltaR(*elec) < 0.4 )                           return false;
  }

  // Is there any muon near the jet?
  for(int j = 0; j < Muon_Count; j++)
  {
    TLorentzVector* muon = (TLorentzVector*)Muon->At(j);
    if( !( Muon_PFIsodBeta03->at(j) < 0.1 ) ) continue;
    if( Muon_isLoose->at(j) != true )         continue;
    if( !( muon->Pt()  > 20. ) )              continue;
    if( !( fabs( muon->Eta() ) < 2.4 ) )      continue;

    if( jet->DeltaR(*muon) < 0.4 )            return false;
  }

  return true;
}/*}}}*/

double TTBarXSec::GetEventWeight()
{/*{{{*/
  if( Info_isData == true ) { return 1; }

  Double_t weight           = 1.;
  Double_t pileUp           = Weight_PileUp->at(0);
  Double_t mcGenEventWeight = 1.;
  Double_t mcScaleFactor    = 1.;
  const Double_t lumi       = 2.11e03;
  Int_t mcSampleIdx         = -1;
  Double_t xsec[9] = {
    831.76, // TTBar_Sample
    18610., // DYJetsToLL_M_10To50
    6025.,  // DYJetsToLL_M_50
    61526., // WJetsToLNu
    118.7,  // WW
    65.9,   // WZ
    31.8,   // ZZ
    35.6,   // ST_tW_antitop
    35.6    // ST_tW_top
  };

  if      ( strstr(infile, "TTBar_Sample")        ) { mcSampleIdx = 0; nPositiveWeightEvent = 19757190; nNegativeWeightEvent = 0; }
  else if ( strstr(infile, "DYJetsToLL_M_10To50") ) { mcSampleIdx = 1; nPositiveWeightEvent = 26023312; nNegativeWeightEvent = 4103247; }
  else if ( strstr(infile, "DYJetsToLL_M_50")     ) { mcSampleIdx = 2; nPositiveWeightEvent = 24003538; nNegativeWeightEvent = 4744431; }
  else if ( strstr(infile, "WJetsToLNu")          ) { mcSampleIdx = 3; nPositiveWeightEvent = 20363007; nNegativeWeightEvent = 3821759; }
  else if ( strstr(infile, "WW")                  ) { mcSampleIdx = 4; nPositiveWeightEvent = 993640;   nNegativeWeightEvent = 0; }
  else if ( strstr(infile, "WZ")                  ) { mcSampleIdx = 5; nPositiveWeightEvent = 978512;   nNegativeWeightEvent = 0; }
  else if ( strstr(infile, "ZZ")                  ) { mcSampleIdx = 6; nPositiveWeightEvent = 996944;   nNegativeWeightEvent = 0; }
  else if ( strstr(infile, "ST_tW_antitop")       ) { mcSampleIdx = 7; nPositiveWeightEvent = 988500;   nNegativeWeightEvent = 0; }
  else if ( strstr(infile, "ST_tW_top")           ) { mcSampleIdx = 8; nPositiveWeightEvent = 995600;   nNegativeWeightEvent = 0; }

  if( mcSampleIdx == -1 ) { cout << "A Critical Bug : MC sample index can not be determined." << endl; }

  mcScaleFactor = ( lumi * xsec[mcSampleIdx] ) / ( nPositiveWeightEvent - nNegativeWeightEvent );
  weight = pileUp * ( Gen_EventWeight < -.00001 ? -1 : 1 ) * mcScaleFactor;

  return weight;
}/*}}}*/

void TTBarXSec::SetWeightSignCounter()
{/*{{{*/
  // This function usually not called during the run.
  // Once you check the each positive and negative sign counters of weight,
  // you should keep that numbers and use them for your analysis.
  /*char* mcListFile[9] = {
    "TTBar_Sample.list",
    "DYJetsToLL_M_10To50.list",
    "DYJetsToLL_M_50.list",
    "WJetsToLNu.list",
    "WW.list",
    "WZ.list",
    "ZZ.list",
    "ST_tW_antitop.list",
    "ST_tW_top.list"};
    */

  char filename[256] = "ST_tW_top.list";
  FILE* pListFile;
  pListFile = fopen(filename, "r");

  TChain* chain = new TChain("ssbgeninfor/SSBGenTree");

  while( fscanf(pListFile, "%s", filename) != EOF )
  {
    chain->Add(filename, 0);
    cout << filename << " is added to chain" << endl;
  }

  Double_t mcGenEventWeight = 1.;
  nPositiveWeightEvent = 0;
  nNegativeWeightEvent = 0;
  //TTree* tempTree = (TTree*)fin->Get("ssbgeninfor/SSBGenTree");
  chain->SetBranchAddress("Gen_EventWeight", &mcGenEventWeight);
  for( Long64_t i = 0; i < chain->GetEntries(); i++ ) { chain->GetEntry(i); mcGenEventWeight < -.00001 ? nNegativeWeightEvent++ : nPositiveWeightEvent++; }
  cout << "# Positive = " << nPositiveWeightEvent << endl;
  cout << "# Negative = " << nNegativeWeightEvent << endl;
}/*}}}*/
