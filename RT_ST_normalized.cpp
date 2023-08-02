/* RT Analyis */

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THnSparse.h"
#include "TLegend.h"
#include "TMath.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include "TVector3.h"
#include <TNtuple.h>
#include <TTree.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "figTemplate.cpp"
#include "figTemplate.h"

using namespace std;

void RT_ST_normalized() {

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
  TFile *input2 = new TFile("../ROOT_RT_Analysis/P1_r.root",
                            "read"); // Reading the data.root file  (With_RH)

  TProfile *hprof = new TProfile("hprof", "Without_RH", 100, 1, 10, 0, 5);
  TProfile *hprof2 =
      new TProfile("hprof2", "With_RH", 25, 0, 10, 0, 5); // rope hadronization
  TH1F *hist = new TH1F("hist", " ", 22, 0, 5);
  TH1F *hist2 = new TH1F("hist2", " ", 22, 0, 5);
  /*Reading the TTree attached in the root file */

  TTree *rtree5 = (TTree *)input2->Get("tree5");
  TTree *rtree4 = (TTree *)input2->Get("tree4");
  TTree *rtree1 = (TTree *)input2->Get("tree1");

  int id, event, size, no, Neve;
  double n_density1, n_charged1, density_factor, Nch, Rt, St, pT_sum1, meanPt,
      Av_Ptsum, pT_lead_lower_cut, pT_lead_upper_cut;
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

  // Initialization
  Av_Ptsum = 0;
  Nch = 0;
  Neve = 0; // For total number of analyzed events
  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  double eta_cut = 0.8; // Kinematic cuts to be used
  double pT_cut = 0.15;

  density_factor = 4 * M_PI * eta_cut / 3;

  /* 1) For <NchT> ------------------ */
  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);

    if (pT_lead > pT_lead_lower_cut &&
        pT_lead < pT_lead_upper_cut) { // Analyze within pT lead cut
      Nch = Nch + n_density1;          // average over all events analyzed
      Av_Ptsum = Av_Ptsum + pT_sum1;
      Neve = Neve + 1;
    }
  }

  Av_Ptsum = Av_Ptsum * density_factor / Neve;
  Nch = Nch * density_factor / Neve;

  cout << "NchT" << Nch << endl;

  cout << "Av_Ptsum: " << Av_Ptsum << endl;

  /* 2) RT calculation for each event ------------ */

  for (int i = 0; i < entries; i++) {
    rtree5->GetEntry(i);
    rtree4->GetEntry(i);
    n_charged1 = n_density1 * density_factor;
    Rt = n_charged1 / Nch;
    St = pT_sum1 * density_factor / Av_Ptsum;
    // meanPt  = double(pT_sum2/n_charged2);

    // hist->Fill(pT_sum2);
    if (pT_lead > pT_lead_lower_cut && pT_lead < pT_lead_upper_cut) {
      // hprof2->Fill(Rt, meanPt,1);
      hist->Fill(Rt);
      hist2->Fill(St);
    }
  }

  // noramlizing
  Double_t scale = 1 / hist->Integral();
  hist->Scale(scale);

  Double_t scale2 = 1 / hist2->Integral();
  hist2->Scale(scale2);

  hist->SetLineColor(kRed);
  hist2->SetLineColor(kBlue);

  hist->SetLineWidth(2);
  hist2->SetLineWidth(2);


  hist->Fit("pol5", "", "", 0, 5);
  hist2->Fit("pol7", "", "", 0, 7);

  TF1 *myfunc1 = hist->GetFunction("pol5");
  TF1 *myfunc2 = hist2->GetFunction("pol7");

  c1->SetTickx(1);
  c1->SetTicky(1);

  /* 3) Plotting ------------------------ */

  c1->Clear();

  myfunc1->SetLineColor(kRed);
  myfunc1->GetXaxis()->SetTitleSize(0);
  myfunc1->SetMaximum(0.18);
  myfunc1->SetTitle("");

  myfunc1->GetYaxis()->SetTitleSize(0.05);
  myfunc1->GetXaxis()->SetTitleSize(0.05);
  myfunc1->GetXaxis()->SetLabelSize(0.05);
  myfunc1->GetYaxis()->SetLabelSize(0.05); // 3
  myfunc1->GetYaxis()->SetTitle("P(X)");
  myfunc1->GetXaxis()->SetTitle("X");
  // myfunc1->GetYaxis()->SetTitleOffset(0.93);
  myfunc1->SetLineWidth(2);
  myfunc1->SetLineStyle(2);

  myfunc1->GetXaxis()->SetTickLength(0.04);

  myfunc1->Draw("");

  myfunc2->SetLineColor(kBlue);
  myfunc2->SetLineWidth(2);
  myfunc2->SetLineStyle(1); // 1=solid, 2=dash, 3=dot, 4=dash-dot

  myfunc2->Draw("SAME");

  TLegend *legend = new TLegend(0.50, 0.67, 0.75, 0.82); // Already NDC


  // You should always specify the colliding system
  // NOTATION: pp, p-Pb, Pb-Pb.
  // Don't forget to use #sqrt{s_{NN}} for p-Pb and Pb-Pb
  // You can change the position of this with
  TLatex energy;
  energy.SetNDC(1);
  energy.SetTextSize(0.05); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.50, 0.57, "pp, #sqrt{#it{s}} = 13 TeV");

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.02);
  legend->AddEntry(myfunc1, "X = R_{T}", "l");
  legend->AddEntry(myfunc2, "X = S_{T}", "l");
  legend->Draw();

  /*d = " ";
  d += pT_lead_lower_cut;
  d += " < p_{T}^{lead} (GeV) < " ;
  d += pT_lead_upper_cut;

  l.SetNDC(1);                                    // Set NDC
  l.SetTextSize(0.05);                                  // Set NDC
  l.SetTextAlign(13);
  l.DrawLatex(0.57,0.75,d.Data());

  latex.SetNDC(1);
  latex.SetTextSize(0.05);
  latex.DrawLatex(0.51,0.82, "p_{T} #geq 0.15  GeV  and   |#eta| #leq 0.8");*/
}
