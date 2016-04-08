#define SSBTree_cxx
#include "SSBTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;
void SSBTree::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L SSBTree.C
//      Root > SSBTree t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   ////////////////////////////
   // Declare of output file //
   ////////////////////////////
   TFile *fout = new TFile("histo.root","recreate");
   fout->cd("");

   ///////////////////////////
   // Example of Using TH1F //
   ///////////////////////////
   TH1F *Num_Electron   = new TH1F("Num_Electron","The Number of Electrons", 30, 0,30);
   TH1F *ElecSpectrum   = new TH1F("ElecSpectrum", "Momentum distribution of electrons", 300, 0, 300);
   Num_Electron->Sumw2();
   ElecSpectrum->Sumw2();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if( jentry == 1 )
        cout << "EventNo / i / pT / eta / Elec_PFIsoRho03 / Elec_Supercluster_Eta / Elec_SCB_Medium / Elec_Inner_Hit / Elec_ChargeId_GsfPx / Elec_Track_GsfdXY / Elec_Track_GsfdZ / Elec_Conversion " << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

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
      //cout << "evt_weight_ " << evt_weight_ << endl;
      //cout << "Info_isData --  " << Info_isData << endl;

      /////////////////////////////////////////////
      // Example of Vertex Filter (EventFillter) //
      /////////////////////////////////////////////
      if ( Filter_PV->at(0) == false ) {continue;}

      ///////////////////////////////////////////////////
      // Example for Trigger Requirement of Dielectron //
      ///////////////////////////////////////////////////
      int ptrigindex;
      bool trigpass;

      ptrigindex =0;
      trigpass = false;

      for (unsigned int i =0; i < Trigger_Name->size(); i++)
      {
         if ( TString( Trigger_Name->at(i) ).Contains( "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ) ) 
         {
            if ( ( Trigger_isPass->at(i) ) && !( Trigger_isError->at(i) ) && ( Trigger_isRun->at(i) ) )
            {
              ptrigindex = ptrigindex+1;
            }
         }
      }
      if ( ptrigindex > 0 ) { trigpass = true; }
      if ( trigpass == false ) {continue;} // Non passed Event Veto //

      ///////////////////////////////////////////////////////
      // Example for Using TClonesArray and TLorentzVector //
      ///////////////////////////////////////////////////////

      int num_Elec = 0;
      TLorentzVector vSum;

      for ( int i = 0; i < Elec_Count; ++i )
      {
         TLorentzVector* ele = (TLorentzVector*)Elec->At(i); // Elec is TClonesArray //

         if ( Elec_PFIsoRho03->at(i) > 0.0766 )                 continue;
         if ( abs( Elec_Supercluster_Eta->at(i) ) > 1.4442 &&
             abs( Elec_Supercluster_Eta->at(i) ) < 1.566 )      continue;
         if ( !Elec_SCB_Medium->at(i) )                         continue;
         if ( Elec_Inner_Hit->at(i) > 1 )                       continue;
         if ( !Elec_ChargeId_GsfPx->at(i) )                     continue;
         if ( ele->Pt() < 20 )                                  continue; // pT cut ...
         if ( fabs( ele->Eta() ) > 2.5 )                        continue; // eta cut ...
         if ( abs( Elec_Supercluster_Eta->at(i) ) <= 1.479 )
         {
           if( Elec_Track_GsfdXY->at(i) > 0.0118 )              continue;
           if( Elec_Track_GsfdZ->at(i) > 0.373 )                continue;
           if( !Elec_Conversion->at(i) )                        continue;
         }
         else if ( abs( Elec_Supercluster_Eta->at(i) ) > 1.479 && abs( Elec_Supercluster_Eta->at(i) ) < 2.5 )
         {
           if( Elec_Track_GsfdXY->at(i) > 0.0739 )              continue;
           if( Elec_Track_GsfdZ->at(i) > 0.602 )                continue;
           if( !Elec_Conversion->at(i) )                        continue;
         }

         cout << "Event :" << jentry << "/";
         cout << i;
         cout << "/" << ele->Pt();
         cout << "/" << ele->Eta();
         cout << "/" << Elec_PFIsoRho03->at(i);
         cout << "/" << Elec_Supercluster_Eta->at(i);
         cout << "/" << Elec_SCB_Medium->at(i);
         cout << "/" << Elec_Inner_Hit->at(i);
         cout << "/" << Elec_ChargeId_GsfPx->at(i);
         cout << "/" << Elec_Track_GsfdXY->at(i);
         cout << "/" << Elec_Track_GsfdZ->at(i);
         cout << "/" << Elec_Conversion->at(i);
         cout << endl;

         if( num_Elec == 0 ) vSum = *ele;
         else
           vSum += *ele;
         /*
         if( ele->Mag() < 20 ) continue; // Di-Lepton mass (> 20 GeV) cut
         if( ele->Mag() < 76 && ele->Mag() > 106) continue; // Z-mass veto

         if( Jet_Count < 2 ) continue;
         if( Jet_PFId->at(i) < 1 ) continue;
         if( Jet_bDisc->at(i) >= 0.605 ) continue;
         TLorentzVector* jet = (TLorentzVector*)Jet->At(i);
         if( jet->Pt() < 30 ) continue;
         if( jet->Eta() > 2.4 ) continue;

         TLorentzVector* met = (TLorentzVector*)MET->At(i);
         if( met->Pt() < 40 ) continue;
         */

         num_Elec++;
         if( num_Elec >= 2 )
          ElecSpectrum->Fill(ele->Pt(), evt_weight_);

      }

      Num_Electron->Fill(num_Elec,evt_weight_); 

      if( num_Elec == 2) 
      {
        TLorentzVector* v1 = (TLorentzVector*)Elec->At(0);
        TLorentzVector* v2 = (TLorentzVector*)Elec->At(1);
        TLorentzVector v3 = *v1 + *v2;
        cout << "/" << vSum.M() << endl;
      }
   } // End of nentries loop
   fout->Write();
   fout->Close();
} // End of Loop() Function 
