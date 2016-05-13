void draw()
{/*{{{*/
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
}/*}}}*/

void drawElEl()
{/*{{{*/
  TFile* fInput = new TFile("ElEl.root");
  TH1F* hData1 = (TH1F*)fInput->Get("EleEle/hElEl_NEl");
  cout << hData1->GetName() << " : Loaded." << endl;
  hData1->SetFillColor(kRed);
  hData1->SetLineColor(kRed);
  hData1->SetMarkerStyle(21);
  hData1->SetMarkerColor(kRed);
  TH1F* hData2 = (TH1F*)fInput->Get("EleEle/hElEl_ElPt");
  cout << hData2->GetName() << " : Loaded." << endl;
  hData2->SetFillColor(kRed);
  hData2->SetLineColor(kRed);
  hData2->SetMarkerStyle(21);
  hData2->SetMarkerColor(kRed);
  TH1F* hData3 = (TH1F*)fInput->Get("EleEle/hElEl_ElEnergy");
  cout << hData3->GetName() << " : Loaded." << endl;
  hData3->SetFillColor(kRed);
  hData3->SetLineColor(kRed);
  hData3->SetMarkerStyle(21);
  hData3->SetMarkerColor(kRed);
  TH1F* hData4 = (TH1F*)fInput->Get("EleEle/hElEl_ElEta");
  cout << hData4->GetName() << " : Loaded." << endl;
  hData4->SetFillColor(kRed);
  hData4->SetLineColor(kRed);
  hData4->SetMarkerStyle(21);
  hData4->SetMarkerColor(kRed);
  TH1F* hData5 = (TH1F*)fInput->Get("EleEle/hElEl_ElPhi");
  cout << hData5->GetName() << " : Loaded." << endl;
  hData5->SetFillColor(kRed);
  hData5->SetLineColor(kRed);
  hData5->SetMarkerStyle(21);
  hData5->SetMarkerColor(kRed);
  TH1F* hData6 = (TH1F*)fInput->Get("EleEle/hElEl_ElInvMass");
  cout << hData6->GetName() << " : Loaded." << endl;
  hData6->SetFillColor(kRed);
  hData6->SetLineColor(kRed);
  hData6->SetMarkerStyle(21);
  hData6->SetMarkerColor(kRed);
  TH1F* hData7 = (TH1F*)fInput->Get("EleEle/hElEl_NJets");
  cout << hData7->GetName() << " : Loaded." << endl;
  hData7->SetFillColor(kRed);
  hData7->SetLineColor(kRed);
  hData7->SetMarkerStyle(21);
  hData7->SetMarkerColor(kRed);

  vector<string> sampleNames;
  sampleNames.push_back("DYJetsToLL_M_10To50");    // 
  sampleNames.push_back("DYJetsToLL_M_50");
  sampleNames.push_back("ST_tW_antitop");
  sampleNames.push_back("ST_tW_top");
  sampleNames.push_back("TTBar_Sample");
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
  vector<TH1F*> histVector5;
  vector<TH1F*> histVector6;
  vector<TH1F*> histVector7;

  THStack* hMC_NElectronsStack = new THStack("hNElectrons", "Stacked Histogram of Number of Electrons from Various Sources, (dielectron)");
  THStack* hMC_PtStack         = new THStack("hMC_PtStack", "Stacked Histogram of p_{T} from Various Sources, (dielectron)");
  THStack* hMC_EnergyStack     = new THStack("hMC_EnergyStack", "Stacked Histogram of Energy from Various Sources, (dielectron)");
  THStack* hMC_EtaStack        = new THStack("hMC_EtaStack", "Stacked Histogram of Eta distribution from Various Sources, (dielectron)");
  THStack* hMC_PhiStack        = new THStack("hMC_PhiStack", "Stacked Histogram of Phi distribution from Various Sources, (dielectron)");
  THStack* hMC_InvMassStack    = new THStack("hMC_InvMassStack", "Stacked Histogram of Invariant Mass from Various Sources, (dielectron)");
  THStack* hMC_CleanJetStack   = new THStack("hMC_CleanJetStack", "Stacked Histogram of Number of Clean Jets from Various Sources, (dielectron)");

  TLegend* l1 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l2 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l3 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l4 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l5 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l6 = new TLegend(0.37, 0.25, 0.86, 0.83);
  TLegend* l7 = new TLegend(0.37, 0.25, 0.86, 0.83);

  for(int i = 0; i < sampleNames.size(); i++)
  {
    fileNames[i] += ".root";
    fileVector.push_back( new TFile( fileNames[i].c_str(), "READ") );
  }

  for(int i = 0; i < sampleNames.size(); i++)
  {
    TFile* fPointer = fileVector[i];
    if( fPointer->IsOpen() ) cout << "File opened: " << fPointer->GetName() << endl;

    histVector1.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_NEl") );
    histVector2.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_ElPt") );
    histVector3.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_ElEnergy") );
    histVector4.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_ElEta") );
    histVector5.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_ElPhi") );
    histVector6.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_ElInvMass") );
    histVector7.push_back( (TH1F*)fPointer->Get("EleEle/hElEl_NJets") );

    TH1F* h1 = histVector1.at(i);
    TH1F* h2 = histVector2.at(i);
    TH1F* h3 = histVector3.at(i);
    TH1F* h4 = histVector4.at(i);
    TH1F* h5 = histVector5.at(i);
    TH1F* h6 = histVector6.at(i);
    TH1F* h7 = histVector7.at(i);

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
    hMC_PtStack->Add(h2);
    l2->AddEntry(h2, fPointer->GetName());

    string h3Title = sampleNames[i];
    h3Title += " Dielectron Chn.";
    h3->SetTitle(h3Title.c_str());
    h3->SetFillColor(kAzure+i);
    h3->SetLineColor(kAzure+i);
    h3->Sumw2(kFALSE);
    h3->SetDrawOption("BAR");
    hMC_EnergyStack->Add(h3);
    l3->AddEntry(h3, fPointer->GetName());

    string h4Title = sampleNames[i];
    h4Title += " Dielectron Chn.";
    h4->SetTitle(h4Title.c_str());
    h4->SetFillColor(kAzure+i);
    h4->SetLineColor(kAzure+i);
    h4->Sumw2(kFALSE);
    h4->SetDrawOption("BAR");
    hMC_EtaStack->Add(h4);
    l4->AddEntry(h4, fPointer->GetName());

    string h5Title = sampleNames[i];
    h5Title += " Dielectron Chn.";
    h5->SetTitle(h5Title.c_str());
    h5->SetFillColor(kAzure+i);
    h5->SetLineColor(kAzure+i);
    h5->Sumw2(kFALSE);
    h5->SetDrawOption("BAR");
    hMC_PhiStack->Add(h5);
    l5->AddEntry(h5, fPointer->GetName());

    string h6Title = sampleNames[i];
    h6Title += " Dielectron Chn.";
    h6->SetTitle(h6Title.c_str());
    h6->SetFillColor(kAzure+i);
    h6->SetLineColor(kAzure+i);
    h6->Sumw2(kFALSE);
    h6->SetDrawOption("BAR");
    hMC_InvMassStack->Add(h6);
    l6->AddEntry(h6, fPointer->GetName());

    string h7Title = sampleNames[i];
    h7Title += " Dielectron Chn.";
    h7->SetTitle(h7Title.c_str());
    h7->SetFillColor(kAzure+i);
    h7->SetLineColor(kAzure+i);
    h7->Sumw2(kFALSE);
    h7->SetDrawOption("BAR");
    hMC_CleanJetStack->Add(h7);
    l7->AddEntry(h7, fPointer->GetName());
  }

  TCanvas* c1 = new TCanvas("c1", "Stacked histograms", 50, 50, 700, 700);
  c1->Divide(4,2);

  c1->cd(1);
  hMC_NElectronsStack->Draw();
  hData1->Draw("same");
  l1->Draw();

  c1->cd(2);
  hMC_PtStack->Draw();
  hData2->Draw("same");
  l2->Draw();

  c1->cd(3);
  hMC_EnergyStack->Draw();
  hData3->Draw("same");
  l3->Draw();

  c1->cd(4);
  hMC_EtaStack->Draw();
  hData4->Draw("same");
  l4->Draw();

  c1->cd(5);
  hMC_PhiStack->Draw();
  hData5->Draw("same");
  l5->Draw();

  c1->cd(6);
  hMC_InvMassStack->Draw();
  hData6->Draw("same");
  l6->Draw();

  c1->cd(7);
  hMC_CleanJetStack->Draw();
  hData7->Draw("same");
  l7->Draw();

  // Error analysis
  vector<Float_t> sigma;
  sigma.clear();
  for(Int_t i = 0; i < hData2->GetNbinsX(); i++)
  {
    sigma.push_back(hData2->GetBinError(i));
  }
  // Considering error propagation, total statistical uncertainty is quadratic sum of uncertainties of each bins
  Float_t Sigma = 0;
  for(Int_t i = 0; i < hData2->GetNbinsX(); i++)
  {
    Sigma += sigma.at(i) * sigma.at(i);
  }
  Sigma = TMath::Sqrt(Sigma);
  cout << "N = " << hData2->GetEntries() << " +/- " << Sigma << endl;
  cout << "SQRT(N) = " << TMath::Sqrt(hData2->GetEntries()) << endl;
  c1->cd(2);
  TPaveText* t = new TPaveText(0.8, 0.8, 1, 1, "brNDC");
  t->AddText(Form("N: %d #pm %f", (Int_t)hData2->GetEntries(), Sigma));
  t->Draw();

  TFile* fOut = new TFile("drawOut_ElEl.root", "recreate");
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
}/*}}}*/

void drawMuMu()
{/*{{{*/
  TFile* fInput = new TFile("MuMu.root");
  TH1F* hData1 = (TH1F*)fInput->Get("MuMu/hMuMu_NMuon");
  hData1->SetFillColor(kRed);
  hData1->SetLineColor(kRed);
  hData1->SetMarkerStyle(21);
  hData1->SetMarkerColor(kRed);
  cout << "OK" << endl;
  TH1F* hData2 = (TH1F*)fInput->Get("MuMu/hMuMu_MuonPt");
  hData2->SetFillColor(kRed);
  hData2->SetLineColor(kRed);
  hData2->SetMarkerStyle(21);
  hData2->SetMarkerColor(kRed);
  cout << "OK" << endl;
  TH1F* hData3 = (TH1F*)fInput->Get("MuMu/hMuMu_MuonInvMass");
  hData3->SetFillColor(kRed);
  hData3->SetLineColor(kRed);
  hData3->SetMarkerStyle(21);
  hData3->SetMarkerColor(kRed);
  cout << "OK" << endl;
  TH1F* hData4 = (TH1F*)fInput->Get("MuMu/hMuMu_NJets");
  hData4->SetFillColor(kRed);
  hData4->SetLineColor(kRed);
  hData4->SetMarkerStyle(21);
  hData4->SetMarkerColor(kRed);
  cout << "OK" << endl;

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

  THStack* hMC_NMuonsStack = new THStack("hNMuons", "Stacked Histogram of Number of Muons from Various Sources, (dimuon)");
  THStack* hMC_PtStack = new THStack("hMC_PtStack", "Stacked Histogram of p_{T} from Various Sources, (dimuon)");
  THStack* hMC_InvMassStack = new THStack("hMC_InvMassStack", "Stacked Histogram of Invariant Mass from Various Sources, (dimuon)");
  THStack* hMC_CleanJetStack = new THStack("hMC_CleanJetStack", "Stacked Histogram of Number of Clean Jets from Various Sources, (dimuon)");

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

    histVector1.push_back( (TH1F*)fPointer->Get("MuMu/hMuMu_NMuon") );
    histVector2.push_back( (TH1F*)fPointer->Get("MuMu/hMuMu_MuonInvMass") );
    histVector3.push_back( (TH1F*)fPointer->Get("MuMu/hMuMu_MuonPt") );
    histVector4.push_back( (TH1F*)fPointer->Get("MuMu/hMuMu_NJets") );

    TH1F* h1 = histVector1.at(i);
    TH1F* h2 = histVector2.at(i);
    TH1F* h3 = histVector3.at(i);
    TH1F* h4 = histVector4.at(i);

    string h1Title = sampleNames[i];
    h1Title += " Dimuon Chn.";
    h1->SetTitle(h1Title.c_str());
    h1->SetFillColor(kAzure+i);
    h1->SetLineColor(kAzure+i);
    h1->Sumw2(kFALSE);
    h1->SetDrawOption("BAR");
    hMC_NMuonsStack->Add(h1);
    l1->AddEntry(h1, fPointer->GetName());

    string h2Title = sampleNames[i];
    h2Title += " Dimuon Chn.";
    h2->SetTitle(h2Title.c_str());
    h2->SetFillColor(kAzure+i);
    h2->SetLineColor(kAzure+i);
    h2->Sumw2(kFALSE);
    h2->SetDrawOption("BAR");
    hMC_InvMassStack->Add(h2);
    l2->AddEntry(h2, fPointer->GetName());

    string h3Title = sampleNames[i];
    h3Title += " Dimuon Chn.";
    h3->SetTitle(h3Title.c_str());
    h3->SetFillColor(kAzure+i);
    h3->SetLineColor(kAzure+i);
    h3->Sumw2(kFALSE);
    h3->SetDrawOption("BAR");
    hMC_PtStack->Add(h3);
    l3->AddEntry(h3, fPointer->GetName());

    string h4Title = sampleNames[i];
    h4Title += " Dimuon Chn.";
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
  hMC_NMuonsStack->Draw("same");
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

  TFile* fOut = new TFile("drawOut_Muon.root", "recreate");
  c1->Write();
  fOut->Close();
}/*}}}*/
