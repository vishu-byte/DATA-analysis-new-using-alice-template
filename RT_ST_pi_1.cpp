/* RT Analyis */
#include "figTemplate.cpp"
#include "figTemplate.h"

#include <cmath>
void RT_ST_pi_1() {

  /*0) Declare objects and call trees */

  /*0) Declare objects and call trees */

  // 1)Creating the canvas: (generic process)
  // Loading neccessary libraries
  ALICEfigtemplate::LoadLibs();
  // Setting the style of the canvas
  ALICEfigtemplate ::SetStyle();

  gStyle->SetFrameLineWidth(1);

  // Prepare Figure, please stick to the default canvas size(s) unless
  // absolutely necessary in your case Rectangular
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
  // Square
  // TCanvas *cfig = new TCanvas("cfig", "Alice Figure Template", 800, 800);

  // TH1 * h = c1->DrawFrame(0,10,10,1000);

  // 2)Reading data
  // TFile *input = new TFile("P1.root", "read"); // Reading the data.root file
  // (Without_RH)
  TFile *input2 = new TFile("../ROOT_RT_Analysis/P1_r.root",
                            "read"); // Reading the data.root file  (With_RH)

  TFile *input31 = new TFile("../ROOT_RT_Analysis/RT.root",
                             "read"); // Reading the data.root file  (With_RH)
  TFile *input32 = new TFile("../ROOT_RT_Analysis/ST.root",
                             "read"); // Reading the data.root file  (With_RH)

  TFile *input4 = new TFile("../ROOT_RT_Analysis/meanPts.root",
                            "read"); // Reading the data.root file  (With_RH)

  TProfile *hprof1 =
      new TProfile("hprof1", "ST", 100, 0, 5, 0, 5); // rope hadronization
  TProfile *hprof2 =
      new TProfile("hprof2", "RT", 100, 0, 5, 0, 5); // rope hadronization

  TH1F *hist = new TH1F("hist", " ", 50, 0, 4);
  /*Reading the TTree attached in the root file */

  TTree *rtree5 = (TTree *)input2->Get("tree5");
  TTree *rtree4 = (TTree *)input2->Get("tree4");
  TTree *rtree1 = (TTree *)input2->Get("tree1");

  TTree *rttree1 = (TTree *)input31->Get("tree1");
  TTree *sttree1 = (TTree *)input32->Get("tree1");

  TTree *pttree1 = (TTree *)input4->Get("tree1");

  int id, event, size, no, Neve;
  double n_density1, n_charged1, density_factor, Nch, Rt, St, pT_sum1,
      meanPtpi1, pT_lead_lower_cut, pT_lead_upper_cut;
  double pT_lead, eta_1, y_1, phi_1;

  int entries = rtree5->GetEntries();
  int enteries_1 = rtree1->GetEntries();
  int enteries_4 = rtree4->GetEntries();

  cout << entries << endl;
  cout << enteries_1 << endl;
  cout << enteries_4 << endl;

  rtree4->SetBranchAddress(
      "n_density1", &n_density1); // Transverse momentum for charged particle
  rtree4->SetBranchAddress("pT_lead", &pT_lead);
  rtree4->SetBranchAddress("pT_sum1", &pT_sum1);
  rtree1->SetBranchAddress("eta_1", &eta_1);

  rttree1->SetBranchAddress("Rt", &Rt);
  sttree1->SetBranchAddress("St", &St);
  pttree1->SetBranchAddress("meanPtpi1", &meanPtpi1);

  // Initialization

  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  density_factor = 10 * M_PI / 3;

  /* 1) Create histograms for mean pt vs rt and st ------------------ */
  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);
    rttree1->GetEntry(i);
    sttree1->GetEntry(i);
    pttree1->GetEntry(i);

    if (pT_lead > pT_lead_lower_cut &&
        pT_lead < pT_lead_upper_cut) { // Analyze within pT lead cut
      hprof1->Fill(St, meanPtpi1, 1);
      hprof2->Fill(Rt, meanPtpi1, 1);
    }
  }

  hprof1->SetStats(0);
  hprof2->SetStats(0);

  /*2) Fit the histograms and get the curves ------------- */

  hprof1->Fit("pol8", "", "", 0, 5);
  hprof2->Fit("pol8", "", "", 0, 5);

  TF1 *myfunc1 = hprof1->GetFunction("pol8");
  TF1 *myfunc2 = hprof2->GetFunction("pol8");

  // Take ratios of two in other TF1 curve
  TProfile *h3 = (TProfile *)hprof1->Clone("hprof1");
  h3->Divide(hprof2);

  h3->Fit("pol8", "", "", 0, 5);

  TF1 *Ratio = h3->GetFunction("pol8");

  c1->Clear();

  /*3) Plot various curves and beautify them */

  // Create first pad and draw in it
  TPad *p1 = new TPad("p1", "p1", 0.0, 0.3, 1.0, 1.0);

  p1->SetBottomMargin(0.025);
  p1->Draw();
  p1->cd();

  myfunc1->SetLineColor(kBlue);
  myfunc1->GetXaxis()->SetTitleSize(0);
  //  myfunc1->SetMaximum(1.5);
  myfunc1->SetMinimum(0.);
  myfunc1->SetTitle("");

  myfunc1->GetYaxis()->SetTitleSize(0.07);
  myfunc1->GetXaxis()->SetLabelSize(0.0);
  myfunc1->GetYaxis()->SetLabelSize(0.06); // 3
  myfunc1->GetYaxis()->SetTitle("< p_{T} > [GeV]");
  myfunc1->GetYaxis()->SetTitleOffset(0.67);
  myfunc1->SetLineWidth(2);

  myfunc1->GetXaxis()->SetTickLength(0.04);

  myfunc1->Draw("");

  myfunc2->SetLineColor(kRed);
  myfunc2->SetLineWidth(2);
  myfunc2->SetLineStyle(2); // 1=solid, 2=dash, 3=dot, 4=dash-dot

  myfunc2->Draw("SAME");

  TLegend *legend = new TLegend(0.20, 0.67, 0.35, 0.82); // Already NDC

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.02);
  legend->AddEntry(myfunc1, "X = S_{T}", "l");
  legend->AddEntry(myfunc2, "X = R_{T}", "l");
  legend->Draw();

  p1->SetTickx(1);
  p1->SetTicky(1);
  p1->SetTopMargin(0.1);

  TLatex latex;
  TLatex latex2;

  latex.SetNDC(1);         // Set NDC
  latex.SetTextSize(0.08); // Set NDC
  latex.SetTextAlign(13);
  latex.DrawLatex(0.57, 0.32, "#bf{#pi^{+} + #pi^{-}}");

  latex2.SetNDC(1); // Set NDC
  latex2.SetTextSize(0.06);
  latex2.SetTextAlign(13);
  latex2.DrawLatex(0.57, 0.22, "#bf{Transverse Region}");

  // Create 2nd pad and draw in it

  c1->cd();

  TPad *p2 = new TPad("p2", "p2", 0.0, 0.05, 1.0, 0.3);

  p2->SetBottomMargin(0.37);
  p2->Draw();
  p2->cd();

  Ratio->SetTitle("");
  Ratio->GetXaxis()->SetTitleSize(0.18);
  Ratio->GetYaxis()->SetTitleSize(0.18);

  Ratio->GetXaxis()->SetLabelSize(0.15);
  Ratio->GetYaxis()->SetLabelSize(0.15);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("X");

  Ratio->GetYaxis()->SetTitleOffset(0.25);
  Ratio->GetYaxis()->SetRangeUser(0.8, 2.0);
  Ratio->GetYaxis()->SetNdivisions(5);

  p2->SetTickx(1);
  p2->SetTicky(1);
  Ratio->GetXaxis()->SetTickLength(0.07);

  Ratio->SetLineColor(kViolet);

  Ratio->Draw();

  TLine *line = new TLine(0, 1, 5, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2);
  line->Draw("same");

  // Annotations
}
