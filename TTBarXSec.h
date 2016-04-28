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
      TTBarXSec(TTree *tree=0, bool mcflag = false, int runtype);
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

#ifdef TTBarXSec_cxx

TTBarXSec::TTBarXSec(TTree *tree, bool mcflag = false, int runtype)
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
