void draw()
{
  char* colorCode[13];
  vector<string> sampleNames;
  sampleNames.push_back("DYJetsToLL_M_10To50");    // 
  sampleNames.push_back("DYJetsToLL_M_50");
  sampleNames.push_back("ST_tW_antitop");
  sampleNames.push_back("ST_tW_top");
  sampleNames.push_back("TTBar_Sample");
//  sampleNames.push_back("TTJets");
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
  TH1F* hData1 = (TH1F*)fInput->Get("EleEle/Num_Electron");
  hData1->SetFillColor(kRed);
  hData1->SetLineColor(kRed);
  hData1->SetMarkerStyle(21);
  hData1->SetMarkerColor(kRed);
  TH1F* hData2 = (TH1F*)fInput->Get("EleEle/EleSpectrum");
  hData2->SetFillColor(kRed);
  hData2->SetLineColor(kRed);
  hData2->SetMarkerStyle(21);
  hData2->SetMarkerColor(kRed);
  TH1F* hData3 = (TH1F*)fInput->Get("EleEle/EleInvMass");
  hData3->SetFillColor(kRed);
  hData3->SetLineColor(kRed);
  hData3->SetMarkerStyle(21);
  hData3->SetMarkerColor(kRed);
  TH1F* hData4 = (TH1F*)fInput->Get("EleEle/NCleanJetsInElEl");
  hData4->SetFillColor(kRed);
  hData4->SetLineColor(kRed);
  hData4->SetMarkerStyle(21);
  hData4->SetMarkerColor(kRed);

  vector<string> sampleNames;
  sampleNames.push_back("DYJetsToLL_M_10To50");    // 
  sampleNames.push_back("DYJetsToLL_M_50");
  sampleNames.push_back("ST_tW_antitop");
  sampleNames.push_back("ST_tW_top");
  sampleNames.push_back("TTBar_Sample");
  //sampleNames.push_back("TTJets");
  sampleNames.push_back("WJetsToLNu");
  sampleNames.push_back("WW");
  sampleNames.push_back("WZ");
  sampleNames.push_back("ZZ");

  vector<string> fileNames = sampleNames;
  vector<TFile*> fileVector;
  vector<TH1F*> histVector1;
  vector<TH1F*> histVector2;
  vector<TH1F*> histVector3;
  vector<TH1F*> histVector4;

  THStack* hMC_NElectronsStack = new THStack("hNElectrons", "Stacked Histogram of Number of Electrons from Various Sources, (dielectron)");
  THStack* hMC_PtStack = new THStack("hMC_PtStack", "Stacked Histogram of p_{T} from Various Sources, (dielectron)");
  THStack* hMC_InvMassStack = new THStack("hMC_InvMassStack", "Stacked Histogram of Invariant Mass from Various Sources, (dielectron)");
  THStack* hMC_CleanJetStack = new THStack("hMC_CleanJetStack", "Stacked Histogram of Number of Clean Jets from Various Sources, (dielectron)");

  TLegend* l1 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l2 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l3 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l4 = new TLegend(0.37, 0.25, 0.86, 0.83);

  for(int i = 0; i < sampleNames.size(); i++)
  {
    fileNames[i] += ".root";
    fileVector.push_back( new TFile( fileNames[i].c_str(), "READ") );
  }

  for(int i = 0; i < sampleNames.size(); i++)
  {
    TFile* fPointer = fileVector[i];
    if( fPointer->IsOpen() ) cout << "File opened: " << fPointer->GetName() << endl;

    histVector1.push_back( (TH1F*)fPointer->Get("EleEle/Num_Electron") );
    histVector2.push_back( (TH1F*)fPointer->Get("EleEle/EleInvMass") );
    histVector3.push_back( (TH1F*)fPointer->Get("EleEle/EleSpectrum") );
    histVector4.push_back( (TH1F*)fPointer->Get("EleEle/NCleanJetsInElEl") );

    TH1F* h1 = histVector1.at(i);
    TH1F* h2 = histVector2.at(i);
    TH1F* h3 = histVector3.at(i);
    TH1F* h4 = histVector4.at(i);

    string h1Title = sampleNames[i];
    h1Title += " Dielectron Chn.";
    h1->SetTitle(h1Title.c_str());
    h1->SetFillColor(kAzure+i);
    h1->SetLineColor(kAzure+i);
    h1->Sumw2(kFALSE);
    h1->SetDrawOption("BAR");
    hMC_NElectronsStack->Add(h1);
    l1->AddEntry(h1, fPointer->GetName());

    string h2Title = sampleNames[i];
    h2Title += " Dielectron Chn.";
    h2->SetTitle(h2Title.c_str());
    h2->SetFillColor(kAzure+i);
    h2->SetLineColor(kAzure+i);
    h2->Sumw2(kFALSE);
    h2->SetDrawOption("BAR");
    hMC_InvMassStack->Add(h2);
    l2->AddEntry(h2, fPointer->GetName());

    string h3Title = sampleNames[i];
    h3Title += " Dielectron Chn.";
    h3->SetTitle(h3Title.c_str());
    h3->SetFillColor(kAzure+i);
    h3->SetLineColor(kAzure+i);
    h3->Sumw2(kFALSE);
    h3->SetDrawOption("BAR");
    hMC_PtStack->Add(h3);
    l3->AddEntry(h3, fPointer->GetName());

    string h4Title = sampleNames[i];
    h4Title += " Dielectron Chn.";
    h4->SetTitle(h4Title.c_str());
    h4->SetFillColor(kAzure+i);
    h4->SetLineColor(kAzure+i);
    h4->Sumw2(kFALSE);
    h4->SetDrawOption("BAR");
    hMC_CleanJetStack->Add(h4);
    l4->AddEntry(h4, fPointer->GetName());
  }

  TCanvas* c1 = new TCanvas("c1", "Stacked histograms", 50, 50, 700, 700);
  c1->Divide(2,2);
  c1->cd(1);
  hData1->Draw();
  hMC_NElectronsStack->Draw("same");
  l1->Draw();
  c1->cd(2);
  hData2->Draw();
  hMC_PtStack->Draw("same");
  l2->Draw();
  c1->cd(3);
  hData3->Draw();
  hMC_InvMassStack->Draw("same");
  l3->Draw();
  c1->cd(4);
  hData4->Draw();
  hMC_CleanJetStack->Draw("same");
  l4->Draw();

  TFile* fOut = new TFile("drawOut.root", "recreate");
  c1->Write();
  fOut->Close();
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
