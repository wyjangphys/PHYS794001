void draw()
{
  char* colorCode[13];
  vector<string> sampleNames;
  sampleNames.push_back("DYJetsTOLL_M_10To50");    // 
  sampleNames.push_back("DYJetsToLL_M_50");
  sampleNames.push_back("ST_tW_antitop");
  //sampleNames.push_back("ST_tW_top");
  sampleNames.push_back("TTBar_Sample");
  sampleNames.push_back("TTJets");
  sampleNames.push_back("WJetsToLNu");
  sampleNames.push_back("WW");
  sampleNames.push_back("WZ");
  sampleNames.push_back("ZZ");
  sampleNames.push_back("ElEl");
  sampleNames.push_back("MuMu");
  sampleNames.push_back("MuEl");

  vector<string> fileNames = sampleNames;

  vector<TFile*> fileVector;
  vector<TH1F*> histVector;

  for(int i = 0; i < sampleNames.size(); i++)
  {
    fileNames[i] += ".root";
    fileVector.push_back( new TFile( fileNames[i].c_str(), "READ") );
  }

  THStack* hStack_Pt = new THStack("hStack_Pt", "Stacked Histogram of p_{T} from Various Sources");
  THStack* hStack_Pt_MuMu = new THStack("hStack_Pt_MuMu", "Stacked Histogram of p_{T} from Various Sources, (dimuon)");
  THStack* hStack_Pt_ElEl = new THStack("hStack_Pt_ElEl", "Stacked Histogram of p_{T} from Various Sources, (dielectron)");
  THStack* hStack_Pt_MuEl = new THStack("hStack_Pt_MuEl", "Stacked Histogram of p_{T} from Various Sources, (Electron-muon)");

  for(int i = 0; i < sampleNames.size(); i++)
  {
    TFile* fPointer = fileVector[i];
    if( fPointer->IsOpen() ) cout << "File opened: " << fPointer->GetName() << endl;

    histVector.push_back( (TH1F*)fPointer->Get("EleEle/EleSpectrum") );
    histVector.push_back( (TH1F*)fPointer->Get("MuMu/MuonSpectrum") );
    histVector.push_back( (TH1F*)fPointer->Get("MuEle/MuonEleSpectrum") );

    TH1F* h1 = histVector.at(i);
    TH1F* h2 = histVector.at(i+1);
    TH1F* h3 = histVector.at(i+2);

    string h1Title = sampleNames[i];
    h1Title += " Dielectron Chn.";
    h1->SetTitle(h1Title.c_str());
    h1->SetFillColor(kRed+i);
    h1->SetLineColor(kRed+i);
    h1->SetMarkerStyle(21);
    h1->SetMarkerColor(kRed+i);
    h1->SetOption("B");
    cout << h1->GetOption() << endl;
    hStack_Pt->Add(h1);

    string h2Title = sampleNames[i];
    h2Title += " Dimuon Chn.";
    h2->SetTitle(h2Title.c_str());
    h2->SetFillColor(kGreen+i);
    h2->SetLineColor(kGreen+i);
    h2->SetMarkerStyle(21);
    h2->SetMarkerColor(kGreen+i);
    h2->SetOption("B");
    hStack_Pt->Add(h2);

    string h3Title = sampleNames[i];
    h3Title += " Electron-Muon Chn.";
    h3->SetTitle(h1Title.c_str());
    h3->SetFillColor(kBlue+i);
    h3->SetLineColor(kBlue+i);
    h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlue+i);
    h3->SetOption("B");
    hStack_Pt->Add(h3);
  }

  TCanvas* c1 = new TCanvas("c1", "Stacked histograms", 10, 10, 700, 700);
  hStack_Pt->Draw();
  hStack_Pt->ls();
  c1->BuildLegend();
}

void draw2()
{
  TFile* fInput = new TFile("ElEl.root");
  TH1F* h1 = (TH1F*)fInput->Get("EleEle/EleSpectrum");
  h1->SetFillColor(kRed);
  h1->SetLineColor(kRed);
  h1->Draw();

  vector<string> sampleNames;
  sampleNames.push_back("DYJetsTOLL_M_10To50");    // 
  sampleNames.push_back("DYJetsToLL_M_50");
  sampleNames.push_back("ST_tW_antitop");
  //sampleNames.push_back("ST_tW_top");
  sampleNames.push_back("TTBar_Sample");
  sampleNames.push_back("TTJets");
  sampleNames.push_back("WJetsToLNu");
  sampleNames.push_back("WW");
  sampleNames.push_back("WZ");
  sampleNames.push_back("ZZ");

  vector<string> fileNames = sampleNames;
  vector<TFile*> fileVector;
  vector<TH1F*> histVector;

  THStack* hMCStack = new THStack("hMCStack", "Stacked Histogram of p_{T} from Various Sources, (dielectron)");

  for(int i = 0; i < sampleNames.size(); i++)
  {
    fileNames[i] += ".root";
    fileVector.push_back( new TFile( fileNames[i].c_str(), "READ") );
  }

  for(int i = 0; i < sampleNames.size(); i++)
  {
    TFile* fPointer = fileVector[i];
    if( fPointer->IsOpen() ) cout << "File opened: " << fPointer->GetName() << endl;

    histVector.push_back( (TH1F*)fPointer->Get("EleEle/EleSpectrum") );

    TH1F* h1 = histVector.at(i);

    string h1Title = sampleNames[i];
    h1Title += " Dielectron Chn.";
    h1->SetTitle(h1Title.c_str());
    h1->SetFillColor(kBlue+i);
    h1->SetLineColor(kBlue+i);
    h1->Sumw2(kFALSE);
    h1->SetDrawOption("BAR");
    hMCStack->Add(h1);
  }
  hMCStack->Draw("same");

  /*
  TFile* fInputMC1 = new TFile("DYJetsTOLL_M_10To50.root");
  TH1F* h2 = (TH1F*)fInputMC1->Get("EleEle/EleSpectrum");
  h2->SetDrawOption("BAR");
  h2->SetFillColor(kBlue);
  h2->SetLineColor(kBlue);
  h2->Sumw2(kFALSE);
  hMCStack->Add(h2);

  TFile* fInputMC2 = new TFile("DYJetsToLL_M_50.root");
  TH1F* h3 = (TH1F*)fInputMC2->Get("EleEle/EleSpectrum");
  h3->SetDrawOption("BAR");
  h3->SetFillColor(kBlue+1);
  h3->SetLineColor(kBlue+1);
  h3->Sumw2(kFALSE);
  hMCStack->Add(h3);

  TFile* fInputMC3 = new TFile("ST_tW_antitop.root");
  TH1F* h4 = (TH1F*)fInputMC3->Get("EleEle/EleSpectrum");
  h4->SetDrawOption("BAR");
  h4->SetFillColor(kBlue+2);
  h4->SetLineColor(kBlue+2);
  h4->Sumw2(kFALSE);
  hMCStack->Add(h4);
  hMCStack->Draw("same");
  */

}
