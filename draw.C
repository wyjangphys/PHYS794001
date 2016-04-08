void draw()
{
  TFile* fInput = new TFile("TTBar_Sample.root");
  THStack* hStack = new THStack("hStack", "Stacked Histogram of Various Invariant Mass Plots");
  TH1F* hEleEle = (TH1F*)fInput->Get("EleEle/EleInvMass");
  hEleEle->SetFillColor(kRed);
  hEleEle->SetMarkerStyle(21);
  hEleEle->SetMarkerColor(kRed);
  hStack->Add(hEleEle);
  TH1F* hMuMu   = (TH1F*)fInput->Get("MuMu/MuonInvMass");
  hMuMu->SetFillColor(kBlue);
  hMuMu->SetMarkerStyle(21);
  hMuMu->SetMarkerColor(kBlue);
  hStack->Add(hMuMu);
  TH1F* hEleMu  = (TH1F*)fInput->Get("MuEle/MuonEleInvMass");
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
  return c1;
}
