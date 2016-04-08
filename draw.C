void draw()
{
  vector<string> sampleNames;
  sampleNames.push_back("DYJetsTOLL_M_10To50");
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

  TClonesArray fileArray("TFile", sampleNames.size());

  vector<TFile*> fileVector;
  vector<TH1F*> histVector;

  for(int i = 0; i < sampleNames.size(); i++)
  {
    fileNames[i] += ".root";
    fileVector.push_back( new TFile( fileNames[i].c_str(), "READ") );
    //new(fileArray[i]) TFile( fileNames[i].c_str() , "READ");
    cout << fileVector.at(i)->GetName() << endl;
  }

  THStack* hStack_Pt = new THStack("hStack_Pt", "Stacked Histogram of p_{T} from Various Channels");

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
    hStack_Pt->Add(h1);

    string h2Title = sampleNames[i];
    h2Title += " Dimuon Chn.";
    h2->SetTitle(h2Title.c_str());
    h2->SetFillColor(kGreen+i);
    h2->SetLineColor(kGreen+i);
    h2->SetMarkerStyle(21);
    h2->SetMarkerColor(kGreen+i);
    hStack_Pt->Add(h2);

    string h3Title = sampleNames[i];
    h3Title += " Electron-Muon Chn.";
    h3->SetTitle(h1Title.c_str());
    h3->SetFillColor(kBlue+i);
    h3->SetLineColor(kBlue+i);
    h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlue+i);
    hStack_Pt->Add(h3);
  }

  TCanvas* c1 = new TCanvas("c1", "Stacked histograms", 10, 10, 700, 700);
  hStack_Pt->Draw();
  hStack_Pt->ls();
  /*

  TFile* fInput = new TFile("TTBar_Sample.root");

  THStack* hStack = new THStack("hStack", "Stacked Histogram of Various Invariant Mass Plots");
  TH1F* hEleEle = (TH1F*)fInput->Get("EleEle/EleSpectrum");
  hEleEle->SetFillColor(kRed);
  hEleEle->SetMarkerStyle(21);
  hEleEle->SetMarkerColor(kRed);
  hStack->Add(hEleEle);
  TH1F* hMuMu   = (TH1F*)fInput->Get("MuMu/MuonSpectrum");
  hMuMu->SetFillColor(kBlue);
  hMuMu->SetMarkerStyle(21);
  hMuMu->SetMarkerColor(kBlue);
  hStack->Add(hMuMu);
  TH1F* hEleMu  = (TH1F*)fInput->Get("MuEle/MuonEleSpectrum");
  hEleMu->SetFillColor(kGreen);
  hEleMu->SetMarkerStyle(21);
  hEleMu->SetMarkerColor(kGreen);
  hStack->Add(hEleMu);

  TCanvas* c1 = new TCanvas("c1", "Stacked histograms", 10, 10, 700, 700);
  c1->SetFillColor(41);
  c1->Divide(2, 2);
  c1->cd(1);
  hStack->Draw();
  c1->cd(2);
  gPad->SetGrid();
  hStack->Draw("nostack,e1p");
  c1->cd(3);
  gPad->SetFrameFillColor(17);
  gPad->SetTheta(3.77);
  gPad->SetPhi(2.9);
  hStack->Draw("lego1");
  c1->cd(4);
  */
}
