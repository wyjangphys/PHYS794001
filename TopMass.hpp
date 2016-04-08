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
      TopMass(TTree *tree=0);
      virtual ~TopMass();

      //basic frame
      virtual void Loop();
      void Start();
      void End();
      int ElectronRequirement(int i);
      int ElectronTriggerRequirement();
      int MuonRequirement(int i);
      int MuonTriggerRequirement();
      int MuonEleTriggerRequirement();

      //user define functions
      void SetOutputFileName(char *outname);
      void DeclareHistos();

   private:
      //put variables that you want
      char *outfile;
      TFile *fout;

      // Declare user variables

   public:
      //declare histograms

      TH1F* Num_Muon;
      TH1F* MuonSpectrum;
      TH1F* MuonInvMass;
      TH1F* Num_Electron;
      TH1F* EleSpectrum;
      TH1F* EleInvMass;
      TH1F* Num_MuonEle;
      TH1F* MuonEleSpectrum;
      TH1F* MuonEleInvMass;
};

#endif

#ifdef TopMass_cxx

TopMass::TopMass(TTree *tree)
{
   if (tree == 0)
   {
      printf("ERROR: Can't find any input tree.\n");
   }
   Init(tree);
}

TopMass::~TopMass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

#endif
