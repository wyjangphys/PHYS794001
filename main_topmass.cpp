//////////////////////////////////////////////////
//                                              //
//                                              //
//  Author: Sehwook Lee, sehwook.lee@knu.ac.kr  //
//  Modified by Wooyoung Jang 160407            //
//                       wyjang@knu.ac.kr       //
//                                              //
//                                              //
//////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include <TROOT.h>
#include <TUnixSystem.h>
#include <TChain.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

#include "analysis/SSBTree.h"
#include "TopMass.hpp"

using namespace std;

TROOT root ("Plots", "Program for CMS Analysis");

//argc: # of arguments, argv:array for arguments
int main(int argc, char **argv)
{
  cout << "This is modified version of main_topmass.cpp to be used for job submission" << endl;
  char* inputFileName = argv[1];
  char* outputFileName = argv[2];

  std::vector<double> entries_pertree;

  entries_pertree.clear();

  TChain* ch = new TChain("ssbanalyzer/SSBTree");
  cout << "adding: " << inputFileName << endl;
  ch->Add(inputFileName, 0);
  entries_pertree.push_back(ch->GetEntries());

  cout << "Total number of events after merging root files: " << ch->GetEntries() << endl;
  //gDirectory->Add(ch);
  //gDirectory->pwd();
  //gDirectory->ls("-l");
  //gDirectory->cd("rootree:/muonid");
  //gDirectory->pwd();
  //gDirectory->GetList()->FindObject("MuID");
  //gDirectory->Print();
  //cout <<"ssibal " << gDirectory->GetPath() << endl;
  //TTree* tree = (TTree*)gDirectory->Get("muonid/MuID");

  TopMass *topmass = new TopMass(ch);

  // Setup cuts. 
  topmass->SetOutputFileName(outputFileName);


  // Run event loop
  topmass->Start();
  topmass->Loop();
  topmass->End();

  cout << "End processing..." << endl << endl; 

  return 0;
}
