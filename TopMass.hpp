#ifndef _TopMass_

#define _TopMass_

#include <set>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TGraphErrors.h>
#include "TLorentzVector.h"

#include "analysis/SSBTree.h"

using namespace std;

class TopMass : public SSBTree 
{
   public:
      //declare functions
      TopMass(TTree *tree=0, bool mcflag = false);
      virtual ~TopMass();

      //basic frame
      virtual void Loop();
      void Start();
      void End();

      //user define functions
      void SetInputFileName(char* inputname);
      void SetOutputFileName(char *outname);
      void DeclareHistos();
      int ElectronRequirement(int i);
      int ElectronTriggerRequirement();
      int MuonRequirement(int i);
      int MuonTriggerRequirement();
      int MuonEleTriggerRequirement();
      int JetRequirement(int i);
      bool IsClearJet(int i);
      double GetEventWeight();
      void SetWeightSignCounter();

   private:
      //put variables that you want
      bool isMC;
      char *infile;
      char *outfile;
      char *sampleName;
      TFile *fin;
      TFile *fout;
      Long64_t nPositiveWeightEvent;
      Long64_t nNegativeWeightEvent;

      // Declare user variables

   public:
      //declare histograms

      TH1F* Num_Muon;
      TH1F* MuonSpectrum;
      TH1F* MuonInvMass;
      TH1F* MuonEta;
      TH1F* MuonPhi;
      TH1F* NCleanJetsInMuMu;

      TH1F* Num_Electron;
      TH1F* EleSpectrum;
      TH1F* EleInvMass;
      TH1F* EleEta;
      TH1F* ElePhi;
      TH1F* NCleanJetsInElEl;

      TH1F* Num_Mu;
      TH1F* Num_El;
      TH1F* Num_MuonEle;
      TH1F* ElePtDistribution;
      TH1F* EleEta_MuEl;
      TH1F* ElePhi_MuEl;
      TH1F* MuEta_MuEl;
      TH1F* MuPhi_MuEl;
      TH1F* MuPtDistribution;
      TH1F* MuonEleSpectrum;
      TH1F* MuonEleInvMass;
      TH1F* NCleanJetsInElMu;

   public:
      // some public variables
};

#endif

#ifdef TopMass_cxx

TopMass::TopMass(TTree *tree, bool mcflag = false)
{
   if (tree == 0)
   {
      printf("ERROR: Can't find any input tree.\n");
   }
   Init(tree);
   isMC = mcflag;
}

TopMass::~TopMass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

#endif
