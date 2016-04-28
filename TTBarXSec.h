#ifndef _TTBarXSec_

#define _TTBarXSec_

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

class TTBarXSec : public SSBTree 
{
   public:
      //declare functions
      TTBarXSec(TTree *tree=0, bool mcflag = false, int runtype = 0);
      virtual ~TTBarXSec();

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
      char sampleName[32];
      int runType;
      TFile *fin;
      TFile *fout;
      Long64_t nPositiveWeightEvent;
      Long64_t nNegativeWeightEvent;

      // Declare user variables

   public:
      //declare histograms

      TH1F* hMuMu_NMuon;
      TH1F* hMuMu_MuonPt;
      TH1F* hMuMu_MuonEnergy;
      TH1F* hMuMu_MuonEta;
      TH1F* hMuMu_MuonPhi;
      TH1F* hMuMu_MuonInvMass;
      TH1F* hMuMu_NJets;

      TH1F* hElEl_NEl;
      TH1F* hElEl_ElPt;
      TH1F* hElEl_ElEnergy;
      TH1F* hElEl_ElEta;
      TH1F* hElEl_ElPhi;
      TH1F* hElEl_ElInvMass;
      TH1F* hElEl_NJets;

      TH1F* hElMu_NMu;
      TH1F* hElMu_NEl;
      TH1F* hElMu_MuPt;
      TH1F* hElMu_MuEnergy;
      TH1F* hElMu_MuEta;
      TH1F* hElMu_MuPhi;
      TH1F* hElMu_ElPt;
      TH1F* hElMu_ElEnergy;
      TH1F* hElMu_ElEta;
      TH1F* hElMu_ElPhi;
      TH1F* hElMu_NJets;

   public:
      // some public variables
};

#endif

#ifdef TTBarXSec_cxx

TTBarXSec::TTBarXSec(TTree *tree, bool mcflag, int runtype)
{
   if (tree == 0)
   {
      printf("ERROR: Can't find any input tree.\n");
   }
   Init(tree);
   isMC = mcflag;
   runType = runtype;
   switch(runtype)
   {
     case 0:
       strcpy(sampleName, "TTBar_Sample");
       break;
     case 1:
       strcpy(sampleName, "DYJetsToLL_M_10To50");
       break;
     case 2:
       strcpy(sampleName, "DYJetsToLL_M_50");
       break;
     case 3:
       strcpy(sampleName, "WJetsToLNu");
       break;
     case 4:
       strcpy(sampleName, "WW");
       break;
     case 5:
       strcpy(sampleName, "WZ");
       break;
     case 6:
       strcpy(sampleName, "ZZ");
       break;
     case 7:
       strcpy(sampleName, "ST_tW_antitop");
       break;
     case 8:
       strcpy(sampleName, "ST_tW_top");
       break;
     default:
       break;
   }
}

TTBarXSec::~TTBarXSec()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

#endif
