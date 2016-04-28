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
 * @brief  This method defines the main loop
 * @return
 */
void TTBarXSec::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  ///My variables
  Long64_t __tot_evt = 0;

  ////////////////////////
  /// start event loop ///
  ////////////////////////
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
    {
      printf("ERROR: Failed to load the tree!!!\n");
      break;
    }

    nb = fChain->GetEntry(jentry);   nbytes += nb;

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
    // Here is for MuMu scenario                     //
    ///////////////////////////////////////////////////
    if( this->MuonTriggerRequirement() == 1 ) // Step 0. Trigger requirement/*{{{*/
    {
      if( Info_isData == false )
      {
        if( strstr(infile, "TTBar_Sample") )
        {
          if( Channel_Idx != 26 )
          {
            //cout << "return 0 no matching index" << endl;
            continue;
          }
        }
      }

      int nMuon = 0;
      TLorentzVector diMuon;
      TLorentzVector leadingMuon;

      vector<int> selectedMuonIdx;
      selectedMuonIdx.clear();

      for ( int i = 0; i < Muon_Count; ++i )
      {
        if( this->MuonRequirement(i) )                      // Step 1. Lepton requirement
        {
          selectedMuonIdx.push_back(i);
          nMuon++;
        }
      }

      for( int i = 0; i < nMuon; ++i )
      {
        for( int j = i+1; j < nMuon; ++j)
        {
          TLorentzVector* mu_i = (TLorentzVector*)Muon->At(selectedMuonIdx.at(i));
          TLorentzVector* mu_j = (TLorentzVector*)Muon->At(selectedMuonIdx.at(j));
          diMuon = *mu_i + *mu_j;
          //cout << Form("[%d, %d] / %f GeV", selectedMuonIdx.at(i), selectedMuonIdx.at(j), diMuon.M()) << endl;
          if( diMuon.M() < 20 ) continue;
          if( Muon_Charge->at( selectedMuonIdx.at(i) ) * Muon_Charge->at( selectedMuonIdx.at(j) ) != -1 ) continue;
          if( nMuon >= 3 ) continue;
          if( diMuon.M() > 76 && diMuon.M() < 106 ) continue;
        }
      }

      // Step 3. Jet selection and jet cleaning process
      vector<int> selectedJetIdx;
      selectedJetIdx.clear();
      for( int i = 0; i < Jet_Count; i++ )
      {
        if( this->JetRequirement(i) ) selectedJetIdx.push_back(i);
      }

      vector<int> cleanJetIdx;
      cleanJetIdx.clear();
      for( int i = 0; i < selectedJetIdx.size(); i++ )
      {
        if( this->IsClearJet( selectedJetIdx.at(i) ) != true ) continue;
        else
        {
          cleanJetIdx.push_back( selectedJetIdx.at(i) );
        }
      }

      if( cleanJetIdx.size() < 2 ) continue;
      TLorentzVector* met = (TLorentzVector*)MET->At(0);
      if( met->Pt() < 40 ) continue;                       // Step 4. MET > 40 GeV

      vector<int> bTaggedJetIdx;
      bTaggedJetIdx.clear();
      for( int i = 0; i < cleanJetIdx.size(); i++ )
      {
        if( Jet_bDisc->at(i) >= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
      }
      if( bTaggedJetIdx.size()  < 1 ) continue;

      if( nMuon != 0 )
      {
        leadingMuon = *(TLorentzVector*)Muon->At( selectedMuonIdx.at(0) );
        FillHisto(hMuMu_MuonPt, leadingMuon.Pt(), evt_weight_);
        FillHisto(hMuMu_MuonEnergy, leadingMuon.Energy(), evt_weight_);
        FillHisto(hMuMu_MuonEta, leadingMuon.Eta(), evt_weight_);
        FillHisto(hMuMu_MuonPhi, leadingMuon.Phi(), evt_weight_);
      }
      FillHisto(hMuMu_MuonInvMass, diMuon.M(), evt_weight_);
      FillHisto(hMuMu_NJets, cleanJetIdx.size(), evt_weight_);
      FillHisto(hMuMu_NMuon, nMuon, evt_weight_);
    }/*}}}*/

    ///////////////////////////////////////////////////
    // Here is for EleEle scenario                   //
    ///////////////////////////////////////////////////
    /*{{{*/
    // Step 0. Trigger requirement
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )

    // Step 0. Trigger requirement
    //     Most of codes are implemented in the member function TTBarXSec::ElectronTriggerRequirement
    else if( this->ElectronTriggerRequirement() == 1 )
    {
      if( Info_isData == false )          /// When the input file is MC,
        {
          if( Channel_Idx != 22 ) continue; /// Check the channel index for dielectron trigger.
        }

      // Step 1. Lepton requirement
      //     Among the events passed the trigger requirement, apply the electron requirement.
      //  Most of processes are implemented as a member function TTBarXSec::ElectronRequirement
      int nEle = 0;                       /// Number of electrons which passed the electron requirement.
      TLorentzVector dilep;               /// Dilepton TLorentzVector
      TLorentzVector leadingElectron;

      vector<int> selectedEleIdx;         /// A container to store electron indices which are passed the electron requirement.
      selectedEleIdx.clear();

      for ( int i = 0; i < Elec_Count; ++i )
      {
        if( this->ElectronRequirement(i) )
        {
          selectedEleIdx.push_back(i);
          nEle++;
        }
      }
      if( selectedEleIdx.size() >= 3 ) continue; // Step 1. Third lepton veto

      /// Step 1. Di-lepton mass cut, third lepton veto and charge opposite sign check.
      for( int i = 0; i < selectedEleIdx.size(); ++i )
      {
        for( int j = 0; j < selectedEleIdx.size(); ++j )
        {
          if( i == j ) continue;
          if( i >  j ) continue;
          TLorentzVector* ele_i = (TLorentzVector*)Elec->At(selectedEleIdx.at(i));
          TLorentzVector* ele_j = (TLorentzVector*)Elec->At(selectedEleIdx.at(j));
          dilep = *ele_i + *ele_j;
          if( dilep.M() < 20 ) continue;                                            // Step 1. Di-Lepton mass (> 20 GeV) cut
          if( Elec_Charge->at( selectedEleIdx.at(i) ) * Elec_Charge->at( selectedEleIdx.at(j) ) == 1 ) continue; // Step 1. Opposite charge cut
          if( dilep.M() > 76 && dilep.M() < 106) continue;                          // Step 2. Z-mass veto
          if( dilep.Pt() < 20) continue;
        }
      }

      // Step 3. Jet selection and jet cleaning process
      vector<int> selectedJetIdx;                               // A container to store selected jet indices.
      selectedJetIdx.clear();
      for( int i = 0; i < Jet_Count; i++)
      {
        if( this->JetRequirement(i) ) selectedJetIdx.push_back(i); // Select jets satisfying jet requirements.
      }

      vector<int> cleanJetIdx;
      cleanJetIdx.clear();
      for( int i = 0; i < selectedJetIdx.size(); i++ )
      {
        if( this->IsClearJet( selectedJetIdx.at(i) ) != true ) continue; // Jet cleaning process.
        else
        {
          cleanJetIdx.push_back( selectedJetIdx.at(i) );
        }
      }

      if( cleanJetIdx.size() < 2 ) continue;                        // Step 3. # of Jets >= 2
      TLorentzVector* met = (TLorentzVector*)MET->At(0);
      if( met->Pt() < 40 ) continue;                       // Step 4. MET > 40 GeV

      vector<int> bTaggedJetIdx;
      bTaggedJetIdx.clear();
      for( int i = 0; i < cleanJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
      {
        if( Jet_bDisc->at(i) >= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
      }
      if( bTaggedJetIdx.size() < 1 ) continue;

      if( nEle != 0 )
      {
        leadingElectron = *(TLorentzVector*)Elec->At( selectedEleIdx.at(0) );
        FillHisto(hElEl_ElPt, leadingElectron.Pt(), evt_weight_);
        FillHisto(hElEl_ElEnergy, leadingElectron.Energy(), evt_weight_);
        FillHisto(hElEl_ElEta, leadingElectron.Eta(), evt_weight_);
        FillHisto(hElEl_ElPhi, leadingElectron.Phi(), evt_weight_);
      }
      FillHisto(hElEl_ElInvMass, dilep.M(), evt_weight_);
      FillHisto(hElEl_NJets, cleanJetIdx.size(), evt_weight_);
      FillHisto(hElEl_NEl, nEle, evt_weight_); // FillHisto(TH1F*, variable, eventweight)
    }/*}}}*/

    ///////////////////////////////////////////////////
    // Here is for EleMu scenario                    //
    ///////////////////////////////////////////////////
    // Step 0. Trigger requirement/*{{{*/
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )
    else if( this->MuonEleTriggerRequirement() == 1 )
    {
      //cout << "MuonEleTriggerRequirement == 1" << endl;
      if( Info_isData == false )
      {
        if( Channel_Idx != 22 )             // In case of MC input file, check channel index.
        {
          //cout << "return 0 no matching index" << endl;
          continue;
        }
      }
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

      for( int i = 0; i < Muon_Count; ++i )
      {
        if( this->MuonRequirement(i) )
        {
          selectedMuonIdx.push_back(i);
          nMuon++;
        }
      }

      for( int i = 0; i < nEle; i++ )
      {
        TLorentzVector* ele_i  = (TLorentzVector*)Elec->At(selectedEleIdx.at(i));
        for( int j = 0; j < nMuon; j++ )
        {
          TLorentzVector dilep;
          TLorentzVector* muon_j = (TLorentzVector*)Muon->At(selectedMuonIdx.at(j));
          dilep = *ele_i + *muon_j;
          //cout << Form("[%d, %d] / %f GeV", selectedEleIdx.at(i), selectedMuonIdx.at(j), dilep.M()) << endl;
          if( dilep.M() < 20 ) continue;                                           // Step 1. Di-Lepton mass (> 20 GeV) cut
          if( Elec_Charge->at( selectedEleIdx.at(i) ) * Muon_Charge->at( selectedMuonIdx.at(j) ) == 1 ) continue;
          if( nEle + nMuon >= 3 ) continue;
          if( dilep.M() > 76 && dilep.M() < 106 ) continue;
        }
      }

      // Step 3. Jet selection and jet cleaning process
      vector<int> selectedJetIdx;                           // A container to store selected jet indices.
      selectedJetIdx.clear();
      for( int i = 0; i < Jet_Count; i++)
      {
        if( this->JetRequirement(i) ) selectedJetIdx.push_back(i); // Select jets satisfying jet requirements.
      }

      vector<int> cleanJetIdx;                              // A container to store jets survived jet cleaning process.
      cleanJetIdx.clear();
      for( int i = 0; i < selectedJetIdx.size(); i++)
      {
        if( this->IsClearJet( selectedJetIdx.at(i) ) != true ) continue;    // Jet cleaning process.
        else
        {
          cleanJetIdx.push_back( selectedJetIdx.at(i) );
        }
      }

      if( cleanJetIdx.size() < 2 ) continue;                        // Step 3. # of Jets >= 2
      TLorentzVector* met = (TLorentzVector*)MET->At(0);
      //if( met->Pt() < 40 ) continue;                       // Step 4. MET > 40 GeV

      vector<int> bTaggedJetIdx;
      bTaggedJetIdx.clear();
      for( int i = 0; i < cleanJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
      {
        if( Jet_bDisc->at( cleanJetIdx.at(i) ) <= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
      }
      if( bTaggedJetIdx.size() < 1 ) continue;

      if( nMuon != 0 )
      {
        leadingMuonInMuEl = *(TLorentzVector*)Muon->At( selectedMuonIdx.at(0) );
        FillHisto(hElMu_MuPt, leadingMuonInMuEl.Pt(), evt_weight_);
        FillHisto(hElMu_MuEnergy, leadingMuonInMuEl.E(), evt_weight_);
        FillHisto(hElMu_MuEta, leadingMuonInMuEl.Eta(), evt_weight_);
        FillHisto(hElMu_MuPhi, leadingMuonInMuEl.Phi(), evt_weight_);
      }
      if( nEle != 0 )
      {
        leadingElectronInMuEl = *(TLorentzVector*)Elec->At( selectedEleIdx.at(0) );
        FillHisto(hElMu_ElPt, leadingElectronInMuEl.Pt(), evt_weight_);
        FillHisto(hElMu_ElEnergy, leadingElectronInMuEl.E(), evt_weight_);
        FillHisto(hElMu_ElEta, leadingElectronInMuEl.Eta(), evt_weight_);
        FillHisto(hElMu_ElPhi, leadingElectronInMuEl.Phi(), evt_weight_);
      }
      FillHisto(hElMu_NJets,  cleanJetIdx.size(),  evt_weight_);
      FillHisto(hElMu_NMu, nMuon, evt_weight_);
      FillHisto(hElMu_NEl, nEle, evt_weight_);
    }/*}}}*/
    else
    {
      //cout << "Event: " << jentry << " - No good trigger in this event" << endl;
      continue;
    }
  }//event loop

  /////////////////////////
  /// end of event loop ///
  /////////////////////////

  printf("Total processed number of events: %lld\n", __tot_evt);

}//end Loop function

/*
 * @brief
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
  hMuMu_NMuon = new TH1F("hMuMu_NMuon", "Number of Muons;NCleanJets", 30, 0, 30);
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
  hElEl_NEl = new TH1F(Form("hElEl_NEl"), Form("Number of Electrons;NCleanJets"), 30, 0, 30);
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
}/*}}}*/

void TTBarXSec::End()
{/*{{{*/
  //NPositiveWeightEvents->Fill(nPositiveWeightEvent);
  //NNegativeWeightEvents->Fill(nNegativeWeightEvent);
  fout->Write();
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

int TTBarXSec::ElectronTriggerRequirement()
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
  if( trigpass == false ) return 0;

  return 1;
}/*}}}*/

int TTBarXSec::ElectronRequirement(int i)
{/*{{{*/
  TLorentzVector* ele_tag = (TLorentzVector*)Elec->At(i);
  if ( Elec_PFIsoRho03->at(i) > 0.0766 )                 return 0;
  if ( fabs( Elec_Supercluster_Eta->at(i) ) > 1.4442 &&
      fabs( Elec_Supercluster_Eta->at(i) ) < 1.566 )    return 0;
  if ( !Elec_SCB_Medium->at(i) )                         return 0;
  if ( Elec_Inner_Hit->at(i) > 1 )                       return 0;
  if ( !Elec_ChargeId_GsfPx->at(i) )                     return 0;
  if ( ele_tag->Pt() < 20 )                              return 0;
  if ( fabs( ele_tag->Eta() ) > 2.5 )                    return 0;
  if ( fabs( Elec_Supercluster_Eta->at(i) ) <= 1.479 )
  {
    if ( Elec_Track_GsfdXY->at(i) > 0.0118 )              return 0;
    if ( Elec_Track_GsfdZ->at(i) > 0.373 )                return 0;
    if ( !Elec_Conversion->at(i) )                        return 0;
  }
  else if ( fabs( Elec_Supercluster_Eta->at(i) ) > 1.479 && 
      fabs( Elec_Supercluster_Eta->at(i) ) < 2.5 )
  {
    if ( Elec_Track_GsfdXY->at(i) > 0.0739 )              return 0;
    if ( Elec_Track_GsfdZ->at(i) > 0.602 )                return 0;
    if ( !Elec_Conversion->at(i) )                        return 0;
  }
  return 1;
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

int TTBarXSec::MuonRequirement(int i)
{/*{{{*/
  TLorentzVector* mu_tag = (TLorentzVector*)Muon->At(i);
  if ( Muon_PFIsodBeta04->at(i) > 0.12 ) return 0;
  if ( !Muon_isTight->at(i) )            return 0;
  if ( mu_tag->Pt() < 20 )               return 0;
  if ( mu_tag->Eta() > 2.4 )             return 0;

  return 1;
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

int TTBarXSec::JetRequirement(int i)
{/*{{{*/
  if( Jet_PFId->at(i) < 1 ) return 0;

  TLorentzVector* jet = (TLorentzVector*)Jet->At(i);
  if( jet->Pt() < 30. ) return 0;
  if( jet->Eta() > 2.4 ) return 0;

  return 1;
}/*}}}*/

bool TTBarXSec::IsClearJet(int i)
{/*{{{*/
  TLorentzVector* jet = (TLorentzVector*)Jet->At(i);

  // Is there any electron near the jet?
  for(int j = 0; j < Elec_Count; j++)
  {
    TLorentzVector* elec = (TLorentzVector*)Elec->At(j);

    if( jet->DeltaR(*elec) < 0.4 ) return false;
  }
  // Is there any muon near the jet?
  for(int j = 0; j < Muon_Count; j++)
  {
    TLorentzVector* muon = (TLorentzVector*)Muon->At(j);

    if( jet->DeltaR(*muon) < 0.4 ) return false;
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
