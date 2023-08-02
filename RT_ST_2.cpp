/* RT Analyis */
#include "figTemplate.cpp"
#include "figTemplate.h"

#include <cmath>
void RT_ST_2() {

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
      new TProfile("hprof2", "RT", 25, 0, 5, 0, 5); // rope hadronization

  TH1F *hist = new TH1F("hist", " ", 50, 0, 4);
  /*Reading the TTree attached in the root file */

  hprof1->SetMinimum(0);
  hprof1->SetMaximum(4.5);

  hprof2->SetMinimum(0);
  hprof2->SetMaximum(4.5);

  TTree *rtree5 = (TTree *)input2->Get("tree5");
  TTree *rtree4 = (TTree *)input2->Get("tree4");
  TTree *rtree1 = (TTree *)input2->Get("tree1");

  TTree *rttree1 = (TTree *)input31->Get("tree1");
  TTree *sttree1 = (TTree *)input32->Get("tree1");

  TTree *pttree1 = (TTree *)input4->Get("tree1");

  int id, event, size, no, Neve;
  double n_density2, n_charged2, density_factor, Nch, Rt, St, pT_sum2, meanPt2,
      pT_lead_lower_cut, pT_lead_upper_cut;
  double pT_lead, eta_2, y_2, phi_2;

  int entries = rtree5->GetEntries();
  int enteries_1 = rtree1->GetEntries();
  int enteries_4 = rtree4->GetEntries();

  cout << entries << endl;
  cout << enteries_1 << endl;
  cout << enteries_4 << endl;

  rtree4->SetBranchAddress(
      "n_density2", &n_density2); // Transverse momentum for charged particle
  rtree4->SetBranchAddress("pT_lead", &pT_lead);
  rtree4->SetBranchAddress("pT_sum2", &pT_sum2);
  // rtree1 ->SetBranchAddress("eta_2", &eta_2);

  rttree1->SetBranchAddress("Rt", &Rt);
  sttree1->SetBranchAddress("St", &St);
  // pttree1 ->SetBranchAddress("meanPtkpm1", &meanPtkpm1);

  // Initialization

  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  double eta_cut = 0.8; // Kinematic cuts to be used
  double pT_cut = 0.15;

  density_factor = 4 * M_PI * eta_cut / 3;

  /* 1) Create histograms for mean pt vs rt and st ------------------ */
  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);
    rttree1->GetEntry(i);
    sttree1->GetEntry(i);
    pttree1->GetEntry(i);

    n_charged2 = n_density2 * density_factor;
    meanPt2 = double(pT_sum2 * density_factor / n_charged2);

    if (pT_lead > pT_lead_lower_cut &&
        pT_lead < pT_lead_upper_cut) { // Analyze within pT lead cut
      hprof1->Fill(St, meanPt2, 1);
      hprof2->Fill(Rt, meanPt2, 1);
    }
  }

  hprof1->SetStats(0);
  hprof2->SetStats(0);

  /*2) Fit the histograms and get the curves ------------- */

  /*hprof1->Fit("pol8", "", "", 0, 3.5);
  hprof2->Fit("pol8", "", "", 0, 3.5);

  TF1 *myfunc1 = hprof1->GetFunction("pol8");
  TF1 *myfunc2 = hprof2->GetFunction("pol8");

  // Take ratios of two in other TF1 curve
  TProfile *h3 = (TProfile*)hprof1->Clone("hprof1");
  h3->Divide(hprof2);

  h3->Fit("pol8", "", "", 0, 3.5);

  TF1 *Ratio = h3->GetFunction("pol8");

  */

  c1->Clear();

  c1->SetTickx(1);
  c1->SetTicky(1);

  /*3) Plot various curves and beautify them */

  hprof1->SetMarkerColor(ALICEfigtemplate::colors[2]); // blue
  hprof1->SetLineColor(ALICEfigtemplate::colors[2]);
  // hist-> SetLineWidth(2);
  hprof1->SetMarkerStyle(kFullCircle);
  hprof1->SetMarkerSize(2);

  hprof2->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  hprof2->SetLineColor(ALICEfigtemplate::colors[1]);
  // hist-> SetLineWidth(2);
  hprof2->SetMarkerStyle(kFullSquare);
  hprof2->SetMarkerSize(2);

  THStack *hs = new THStack("hs2", "");

  hs->Add(hprof1);
  hs->Add(hprof2);

  hs->Draw("NOSTACK P");

  hs->GetYaxis()->SetLabelSize(0.05);
  hs->GetXaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetXaxis()->SetLabelSize(0.05);
  hs->GetYaxis()->SetLabelSize(0.05);

  hs->GetXaxis()->SetTitle("X");
  hs->GetYaxis()->SetTitle("<p_{T}> [GeV]");

  TLegend *legend = new TLegend(0.20, 0.67, 0.35, 0.82); // Already NDC

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.02);
  legend->AddEntry(hprof1, "X = S_{T}", "lep");
  legend->AddEntry(hprof2, "X = R_{T}", "lep");
  legend->Draw();

  TLatex latex2, energy;

  latex2.SetNDC(1); // Set NDC
  latex2.SetTextSize(0.06);
  latex2.SetTextAlign(13);
  latex2.DrawLatex(0.57, 0.82, "#bf{Toward Region}");

  energy.SetNDC(1);
  energy.SetTextSize(0.07); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.57, 0.25, "pp, #sqrt{#it{s}} = 13 TeV");
}
