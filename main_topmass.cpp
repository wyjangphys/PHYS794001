/**
 * @file main_topmass.cpp
 * @brief main function of ttbar cross-section analysis.
 * @author Wooyoung Jang, wyjang@knu.ac.kr
 * @date 2016.04.07
 *
 * This is source code of main function of ttbar analysis
 * Originally written by Prof. Seh-wook Lee, and lots of
 * modifications have been done by Wooyoung Jang.
 */

#include <iostream>
#include <string>
#include <cstring>
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

/**
 * @brief main function.
 * @return 0: successfull end of program.
 *
 * argc: # of arguments, argv:array for arguments
 */
int main(int argc, char **argv)
{
  cout << "This is modified version of main_topmass.cpp to be used for job submission" << endl;
  char* inputFileName = argv[1];
  char* outputFileName = argv[2];

  std::vector<double> entries_pertree;

  entries_pertree.clear();

  TChain* ch = new TChain("ssbanalyzer/SSBTree");

  cout << "adding: " << inputFileName << endl;
  ch->Add( inputFileName, 0 );
  entries_pertree.push_back( ch->GetEntries() );

  if( strstr( inputFileName, "MC" ) ) 
    TopMass *topmass = new TopMass(ch, true);
  else
    TopMass *topmass = new TopMass(ch, false);

  // Setup input file name.
  topmass->SetInputFileName(inputFileName);
  // Setup output file name. 
  topmass->SetOutputFileName(outputFileName);

  // Check Weighting Factor Sign Counter
  //topmass->SetWeightSignCounter();

  /// Run event loop
  topmass->Start();
  topmass->Loop();
  topmass->End();

  cout << "End processing..." << endl << endl; 

  return 0;
}
