/* RT Analyis */
#include "figTemplate.cpp"
#include "figTemplate.h"
#include <cmath>
void multi_ST() {
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

   // 3)Creating hists and reading trees

  TFile *input2 = new TFile("../ROOT_RT_Analysis/P1_r.root",
                            "read"); // Reading the data.root file  (With_RH)

  TProfile *hprof = new TProfile("hprof", "Without_RH", 100, 1, 10, 0, 5);
  TProfile *hprof1 =
      new TProfile("hprof1", "With_RH", 25, 0, 5, 0, 40); // Transverse
  TProfile *hprof2 =
      new TProfile("hprof2", "With_RH", 25, 0, 5, 0, 40); // Transverse
  TProfile *hprof3 =
      new TProfile("hprof3", "With_RH", 25, 0, 5, 0, 40); // Transverse

  TH1F *hist = new TH1F("hist", " ", 50, 0, 4);
  /*Reading the TTree attached in the root file */

  hprof2->SetMinimum(0);
  hprof2->SetMaximum(20.0);

  TTree *rtree5 = (TTree *)input2->Get("tree5");
  TTree *rtree4 = (TTree *)input2->Get("tree4");
  TTree *rtree1 = (TTree *)input2->Get("tree1");

  int id, event, size, no, Neve;
  double n_density1, n_density2, n_density3, n_charged1, n_charged2, n_charged3,
      density_factor, Nch, St, pT_sum1, meanPt, Av_Ptsum, pT_lead_lower_cut,
      pT_lead_upper_cut;
  double pT_lead, eta_1, y_1, phi_1;

  int entries = rtree5->GetEntries();
  int enteries_1 = rtree1->GetEntries();
  int enteries_4 = rtree4->GetEntries();
  cout << entries << endl;
  cout << enteries_1 << endl;
  cout << enteries_4 << endl;

  rtree4->SetBranchAddress(
      "n_density1", &n_density1); // Transverse momentum for charged particle
  rtree4->SetBranchAddress("n_density2", &n_density2);
  rtree4->SetBranchAddress("n_density3", &n_density3);
  rtree4->SetBranchAddress("pT_lead", &pT_lead);
  rtree4->SetBranchAddress("pT_sum1", &pT_sum1);
  rtree1->SetBranchAddress("eta_1", &eta_1);

  // Initialization
  Av_Ptsum = 0;
  Neve = 0; // For total number of analyzed events
  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  double eta_cut = 0.8; // Kinematic cuts to be used
  double pT_cut = 0.15;

  density_factor = 4 * M_PI * eta_cut / 3;

  /* 1) For <pTSum> ------------------ */
  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);

    if (pT_lead > pT_lead_lower_cut &&
        pT_lead < pT_lead_upper_cut) { // Analyze within pT lead cut
      Av_Ptsum = Av_Ptsum + pT_sum1;   // average over all events analyzed
      Neve = Neve + 1;
    }
  }

  Av_Ptsum = Av_Ptsum * density_factor / Neve;

  cout << "Av_Ptsum: " << Av_Ptsum << endl;

  /* 2) RT calculation for each event ------------ */

  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);

    n_charged1 = n_density1 * density_factor;
    n_charged2 = n_density2 * density_factor;
    n_charged3 = n_density3 * density_factor;

    St = pT_sum1 * density_factor / Av_Ptsum;

    // hist->Fill(pT_sum2);
    if (pT_lead > pT_lead_lower_cut && pT_lead < pT_lead_upper_cut) {
      hprof1->Fill(St, n_charged1, 1);
      hprof2->Fill(St, n_charged2, 1);
      hprof3->Fill(St, n_charged3, 1);

      // hist->Fill(Rt);
    }
  }

  /* 3) Plotting ------------------------ */

  THStack *hs = new THStack("hs", "");

  c1->SetTickx(1);
  c1->SetTicky(1);

  
  hprof1->SetMarkerColor(ALICEfigtemplate::colors[2]); // blue
  hprof1->SetLineColor(ALICEfigtemplate::colors[2]);
  // hist-> SetLineWidth(2);
  hprof1->SetMarkerStyle(kFullCircle);
  hprof1->SetMarkerSize(2);

  hs->Add(hprof1);

  hprof2->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  hprof2->SetLineColor(ALICEfigtemplate::colors[1]);
  // hist-> SetLineWidth(2);
  hprof2->SetMarkerStyle(kFullSquare);
  hprof2->SetMarkerSize(2);

  hs->Add(hprof2);

  hprof3->SetMarkerColor(ALICEfigtemplate::colors[3]); // Green
  hprof3->SetLineColor(ALICEfigtemplate::colors[3]);
  // hist-> SetLineWidth(2);
  hprof3->SetMarkerStyle(kFullTriangleUp);
  hprof3->SetMarkerSize(2);

  hs->Add(hprof3);

  hs->Draw("NOSTACK P");
  // hs->GetXaxis()->SetTitleSize(0.05);
  // hs->GetYaxis()->SetTitleSize(0.05);
  // hs->GetXaxis()->SetLabelSize(0.05);
  // hs->GetYaxis()->SetLabelSize(0.06);
  hs->GetYaxis()->SetTitle("<N_{ch}>");
  // hs->GetYaxis()->SetTitleOffset(0.75);
  hs->GetXaxis()->SetTitle("S_{T}");

  hs->GetXaxis()->SetRangeUser(0, 5);

  TLegend *legend = new TLegend(0.25, 0.65, 0.40, 0.80); // Already NDC

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.);
  legend->AddEntry(hprof1, "Transverse", "lep");
  legend->AddEntry(hprof2, "Toward", "lep");
  legend->AddEntry(hprof3, "Away", "lep");

  legend->Draw();

  TLatex energy;

  energy.SetNDC(1);
  energy.SetTextSize(0.05); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.57, 0.25, "pp, #sqrt{#it{s}} = 13 TeV");


  c1->Update();
}
