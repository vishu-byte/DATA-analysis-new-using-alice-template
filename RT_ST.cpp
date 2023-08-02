/* RT Analyis */
#include "figTemplate.cpp"
#include "figTemplate.h"
#include <cmath>
void RT_ST() {
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

  TFile *input3 = new TFile("../ROOT_RT_Analysis/RT.root",
                            "read"); // Reading the data.root file  (With_RH)
  TFile *input4 = new TFile("../ROOT_RT_Analysis/ST.root",
                            "read"); // Reading the data.root file  (With_RH)


  TProfile *hprof = new TProfile("hprof", "Without_RH", 100, 1, 10, 0, 5);
  TProfile *hprof2 =
      new TProfile("hprof2", "With_RH", 25, 0, 5, 0, 5); // rope hadronization
  TH1F *hist = new TH1F("hist", " ", 50, 0, 4);
  /*Reading the TTree attached in the root file */

  TTree *rtree5 = (TTree *)input2->Get("tree5");
  TTree *rtree4 = (TTree *)input2->Get("tree4");
  TTree *rtree1 = (TTree *)input2->Get("tree1");

  TTree *rttree1 = (TTree *)input3->Get("tree1");
  TTree *sttree1 = (TTree *)input4->Get("tree1");

  int id, event, size, no, Neve;
  double n_density1, n_charged1, density_factor, Nch, St, Rt, pT_sum1, meanPt,
      pT_lead_lower_cut, pT_lead_upper_cut;
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

  // Initialization
  Nch = 0;
  Neve = 0; // For total number of analyzed events
  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  density_factor = 10 * M_PI / 3;

  /* 2) RT calculation for each event ------------ */

  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);

    rttree1->GetEntry(i);
    sttree1->GetEntry(i);

    // hist->Fill(pT_sum2);
    if (pT_lead > pT_lead_lower_cut && pT_lead < pT_lead_upper_cut) {
      hprof2->Fill(St, Rt, 1);
      // hist->Fill(Rt);
    }
  }

  /* 3) Plotting ------------------------ */

  c1->SetTickx(1);
  c1->SetTicky(1);

  hprof2->SetStats(0);
  hprof2->SetLineColor(4);
  hprof2->SetLineWidth(2);

  hprof2->GetYaxis()->SetLabelSize(0.05);
  hprof2->GetXaxis()->SetTitleSize(0.05);
  hprof2->GetYaxis()->SetTitleSize(0.05);
  hprof2->GetXaxis()->SetLabelSize(0.05);
  hprof2->GetYaxis()->SetLabelSize(0.05); // 3
  hprof2->GetXaxis()->SetTitle("");

  TString d;

  TLatex latex, l, energy;



  hprof2->GetXaxis()->SetTitle("S_{T}");
  hprof2->GetYaxis()->SetTitle("<R_{T}>");
  // hprof2->GetYaxis()->SetTitleOffset(0.89);
  hprof2->SetTitle("  ");

  hprof2->Draw("HIST");

  energy.SetNDC(1);
  energy.SetTextSize(0.05); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.22, 0.85, "pp, #sqrt{#it{s}} = 13 TeV");
  /*d = " ";
  d += pT_lead_lower_cut;
  d += " < p_{T}^{lead} (GeV) < " ;
  d += pT_lead_upper_cut;

  l.SetNDC(1);                                    // Set NDC
  l.SetTextSize(0.05);                                  // Set NDC
  l.SetTextAlign(13);
  l.DrawLatex(0.17,0.75,d.Data());

  latex.SetNDC(1);
  latex.SetTextSize(0.05);
  latex.DrawLatex(0.11,0.82, "p_{T} #geq 0.15  GeV  and   |#eta| #leq 0.8");*/
}
