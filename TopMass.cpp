#define TopMass_cxx

#define DEBUG 1

#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "TMath.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "TopMass.hpp"
#include "CommonTools.hpp"

using namespace std;

void TopMass::Loop()
{/*{{{*/
  //////////
  if (fChain == 0) return;
  //////////

  //////////
  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  //////////

  ///My variables
  Long64_t __tot_evt = 0;

  ////////////////////////
  /// start event loop ///
  ////////////////////////
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    //cout << jentry << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
    {
      printf("ERROR: Could not load tree!!!\n");
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
    double evt_pileUp_ = Weight_PileUp->at(0);
    double evt_gen_ = 1.0;
    // Getting the sign of Gen_EventWeight //
    if ( Gen_EventWeight < -0.00001 ) { evt_gen_ = -1; }
    else { evt_gen_ = 1; }

    // Calculating Event-Weight //
    if ( Info_isData == false ) { evt_weight_ = evt_pileUp_*evt_gen_; } // the Case of input files are MC,
    else { evt_weight_ = 1.0; }
    // cout << "evt_weight_ " << evt_weight_ << endl;
    // cout << "Info_isData --  " << Info_isData << endl;

    /////////////////////////////////////////////
    // Example of Vertex Filter (EventFillter) //
    /////////////////////////////////////////////
    if ( Filter_PV->at(0) == false ) {continue;}

    ///////////////////////////////////////////////////
    // Here is for MuMu scenario                     //
    ///////////////////////////////////////////////////
    if( this->MuonTriggerRequirement() == 1 )              // Step 0. Trigger requirement
    {
      //cout << "MuonTriggerRequirement() == 1" << endl;
      if( Info_isData == false )
      {
        if( Channel_Idx != 26 )
        {
          //cout << "return 0 no matching index" << endl;
          continue;
        }
      }

      int nMuon = 0;
      TLorentzVector diMuon;

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

      //cout << "Invariant mass table [Dimuon]" << endl;
      //cout << "[i, j] / Invariant Mass [GeV]" << endl;
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
          FillHisto(MuonInvMass, diMuon.M(), evt_weight_);
          FillHisto(MuonSpectrum, diMuon.Pt(), evt_weight_);
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
      int nBTaggedJet = 0;
      for( int i = 0; i < cleanJetIdx.size(); i++ )
      {
        if( Jet_bDisc->at(i) >= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
        nBTaggedJet++;
      }
      if( nBTaggedJet < 1 ) continue;

      FillHisto(NCleanJets, cleanJetIdx.size(), evt_weight_);
      FillHisto(Num_Muon, nMuon, evt_weight_);
    }

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
    //     Most of codes are implemented in the member function TopMass::ElectronTriggerRequirement
    if( this->ElectronTriggerRequirement() == 1 )
    {
      if( Info_isData == false )          /// When the input file is MC,
      {
        if( Channel_Idx != 22 ) continue; /// Check the channel index for dielectron trigger.
      }

      // Step 1. Lepton requirement
      //     Among the events passed the trigger requirement, apply the electron requirement.
      //  Most of processes are implemented as a member function TopMass::ElectronRequirement
      int nEle = 0;                       /// Number of electrons which passed the electron requirement.
      TLorentzVector dilep;               /// Dilepton TLorentzVector

      vector<int> selectedEleIdx;         /// A container to store electron indices which are passed the electron requirement.
      selectedEleIdx.clear();

      for ( int i = 0; i < Elec_Count; ++i )
      {
        if( this->ElectronRequirement(i) )
        {
          //cout << "Elec_Count: " << i << " meets lepton requirements." << endl;
          selectedEleIdx.push_back(i);
          nEle++;
        }
      }

      /// Step 1. Di-lepton mass cut, third lepton veto and charge opposite sign check.
      //cout << "Invariant mass table" << endl;
      //cout << "[i, j] / Invariant Mass [GeV]" << endl;
      for( int i = 0; i < nEle; ++i )
      {
        for( int j = i+1; j < nEle; ++j )
        {
          TLorentzVector* ele_i = (TLorentzVector*)Elec->At(selectedEleIdx.at(i));
          TLorentzVector* ele_j = (TLorentzVector*)Elec->At(selectedEleIdx.at(j));
          dilep = *ele_i + *ele_j;
          //cout << Form("[%d, %d] / %f GeV", selectedEleIdx.at(i), selectedEleIdx.at(j), dilep.M()) << endl;
          if( dilep.M() < 20 ) continue;                                            // Step 1. Di-Lepton mass (> 20 GeV) cut
          if( Elec_Charge->at( selectedEleIdx.at(i) ) * Elec_Charge->at( selectedEleIdx.at(j) ) == 1 ) continue; // Step 1. Opposite charge cut
          if( nEle >= 3 ) continue; // Step 1. Third lepton veto
          if( dilep.M() > 76 && dilep.M() < 106) continue;                          // Step 2. Z-mass veto
          FillHisto(EleInvMass, dilep.M(), evt_weight_);
          FillHisto(EleSpectrum, dilep.Pt(), evt_weight_);
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
      int nBTaggedJet = 0;
      for( int i = 0; i < cleanJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
      {
        if( Jet_bDisc->at(i) >= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
        nBTaggedJet++;
      }
      if( nBTaggedJet < 1 ) continue;

      FillHisto(NCleanJets, cleanJetIdx.size(), evt_weight_);
      FillHisto(Num_Electron, nEle, evt_weight_); // FillHisto(TH1F*, variable, eventweight)
    }

    ///////////////////////////////////////////////////
    // Here is for EleMu scenario                    //
    ///////////////////////////////////////////////////
    // Step 0. Trigger requirement
    // Step 1. Lepton requirement & Di-Lepton mass (> 20 GeV)cut & Third Lepton Veto & Charge opposite sign
    // Step 2. Z-mass veto for Di-Muon & Di-Electron channels (< 76 GeV or > 106 GeV)
    // Step 3. # of Jets >= 2
    // Step 4. MET > 40 GeV (Di-Muon & Di-Electron)
    // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging )
    if( this->MuonEleTriggerRequirement() == 1 )
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
      int nBTaggedJet = 0;

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

      //cout << "Invariant mass table" << Form(" / Selected %d electrons and %d muons", nEle, nMuon) << endl;
      //cout << "[i, j] / Invariant Mass [GeV]" << endl;
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
          FillHisto(MuonEleInvMass, dilep.M(), evt_weight_);
          FillHisto(MuonEleSpectrum, dilep.Pt(), evt_weight_);
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
      if( met->Pt() < 40 ) continue;                       // Step 4. MET > 40 GeV

      vector<int> bTaggedJetIdx;
      bTaggedJetIdx.clear();
      for( int i = 0; i < cleanJetIdx.size(); i++)                  // Step 5. 1 or more b tagged Jets (Loose working point for b-Tagging)
      {
        if( Jet_bDisc->at( cleanJetIdx.at(i) ) <= 0.605 ) continue;
        else bTaggedJetIdx.push_back( cleanJetIdx.at(i) );
        nBTaggedJet++;
      }
      if( nBTaggedJet < 1 ) continue;

      FillHisto(NCleanJets,  cleanJetIdx.size(),  evt_weight_);
      FillHisto(Num_MuonEle, nEle+nMuon, evt_weight_); // FillHisto(TH1F*, variable, eventweight)
    }
    else
    {
      //cout << "No good trigger in this event" << endl;
      continue;
    }
  }//event loop

  printf("Total processed number of events: %lld\n", __tot_evt);

}//end Loop function/*}}}*/

void TopMass::Start()
{/*{{{*/
  fout = new TFile(Form("%s",outfile),"RECREATE");
  fout->mkdir("EleEle");
  fout->mkdir("MuMu");
  fout->mkdir("MuEle");
  fout->cd("");

  TDirectory *dir = gDirectory;
  dir->cd();

  DeclareHistos();
}/*}}}*/

void TopMass::DeclareHistos()
{/*{{{*/
  fout->cd("MuMu");
  Num_Muon = new TH1F("Num_Muon", "Number of Muons;NCleanJets", 30, 0, 30);
  Num_Muon->Sumw2();
  MuonSpectrum = new TH1F("MuonSpectrum", "Momentum distribution of muons; GeV/c", 300, 0, 300);
  MuonSpectrum->Sumw2();
  MuonInvMass = new TH1F("MuonInvMass", "Invariant Mass [MuMu]; GeV/c2" , 100, 0, 1000);
  MuonInvMass->Sumw2();
  fout->cd("EleEle");
  Num_Electron = new TH1F(Form("Num_Electron"), Form("Number of Electrons;NCleanJets"), 30, 0, 30);
  Num_Electron->Sumw2();
  EleSpectrum = new TH1F(Form("EleSpectrum"), Form("Momentum distribution of electrons;GeV"), 300, 0, 300);
  EleSpectrum->Sumw2();
  EleInvMass      = new TH1F(Form("EleInvMass"), Form("Invariant Mass; GeV"), 100,0,1000);
  EleInvMass->Sumw2();
  fout->cd("MuEle");
  Num_MuonEle = new TH1F("Num_MuonEle", "Number of Muon + Electron Events;NCleanJets", 30, 0, 30);
  Num_MuonEle->Sumw2();
  MuonEleSpectrum = new TH1F("MuonEleSpectrum", "Pt distribution of muon+ele; GeV/c", 300, 0, 300);
  MuonEleSpectrum->Sumw2();
  MuonEleInvMass = new TH1F("MuonEleInvMass", "Invariant Mass [MuEle]; GeV/c2", 100, 0, 1000);
  MuonEleInvMass->Sumw2();
  fout->cd("");
  NCleanJets = new TH1F("NCleanJets", "Number of Jets in Event; NCleanJets", 30, 0, 30);
  NCleanJets->Sumw2();
}/*}}}*/

void TopMass::End()
{/*{{{*/
  fout->Write();
  fout->Close();
}/*}}}*/

void TopMass::SetOutputFileName(char *outname)
{/*{{{*/
  outfile = outname;
}/*}}}*/

int TopMass::ElectronTriggerRequirement()
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

int TopMass::ElectronRequirement(int i)
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

int TopMass::MuonTriggerRequirement()
{/*{{{*/
  int ptrigindex;
  bool trigpass;

  ptrigindex = 0;
  trigpass = false;

  for( unsigned int i = 0; i < Trigger_Name->size(); i++)
  {
    //cout << "Checking Triggers...." << endl;
    //cout << TString( Trigger_Name->at(i) ) << " / Trigger_isPass : " << Trigger_isPass->at(i) << " / Trigger_isError: " << Trigger_isError->at(i) << " / Trigger_isRun: " << Trigger_isRun->at(i) << endl;
    if( TString( Trigger_Name->at(i) ).Contains( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v" )
        || TString( Trigger_Name->at(i) ).Contains( "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") )
      if ( ( Trigger_isPass->at(i) ) && !( Trigger_isError->at(i) ) && ( Trigger_isRun->at(i) ) ){ ptrigindex = ptrigindex+1; }
  }
  if( ptrigindex > 0 ) trigpass = true;
  if( trigpass == false )
  {
    //cout << "return 0 for trigpass false" << endl;
    return 0;
  }

  return 1;
}/*}}}*/

int TopMass::MuonRequirement(int i)
{/*{{{*/
  TLorentzVector* mu_tag = (TLorentzVector*)Muon->At(i);
  if ( Muon_PFIsodBeta04->at(i) > 0.12 ) return 0;
  if ( !Muon_isTight->at(i) )            return 0;
  if ( mu_tag->Pt() < 20 )               return 0;
  if ( mu_tag->Eta() > 2.4 )             return 0;

  return 1;
}/*}}}*/

int TopMass::MuonEleTriggerRequirement()
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

int TopMass::JetRequirement(int i)
{/*{{{*/
  if( Jet_PFId->at(i) < 1 ) return 0;

  TLorentzVector* jet = (TLorentzVector*)Jet->At(i);
  if( jet->Pt() < 30. ) return 0;
  if( jet->Eta() > 2.4 ) return 0;

  return 1;
}/*}}}*/

bool TopMass::IsClearJet(int i)
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
