/* loading data from a TTree and using it for analysis */
/* loading data from a TTree and using it for analysis */
#include "figTemplate.cpp"
#include "figTemplate.h"

void RT_l_ratio_spectra2() {

  //tree, id, pT, region

  double Rt;

  int id_1, event, size, no, event_number_1;
  double pT_1, eta_1, y_1, phi_1;

  int id_2, event_number_2;
  double pT_2, eta_2, y_2, phi_2;

  int id_3, event_number_3;
  double pT_3, eta_3, y_3, phi_3;

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
  TFile *input = new TFile("../ROOT_RT_Analysis/P1_r.root",
                           "read"); // Reading the data.root file  (With_RH)

  TFile *input2 = new TFile(" ../ROOT_RT_Analysis/RT.root",
                            "read"); // Reading the data.root file (Without_RH)

  // 3)Creating hists and reading trees

  TH1F *hist = new TH1F("hist", "", 100, 0, 10);    // Creating histogram object
  TH1F *hist2 = new TH1F("hist2", " ", 100, 0, 10); // Creating histogram object
  TH1F *hist3 = new TH1F("hist3", " ", 100, 0, 10); // Creating histogram object
  TH1F *hist4 = new TH1F("hist4", " ", 100, 0, 10); // Creating histogram object
  TH1F *hist5 = new TH1F("hist5", " ", 100, 0, 10); // Creating histogram object

  THStack *hs = new THStack("hs", "");

  /*Reading the TTree attached in the root file */
  TTree *tree1 = (TTree *)input->Get("tree1");
  TTree *tree2 = (TTree *)input->Get("tree2");
  TTree *tree3 = (TTree *)input->Get("tree3");
  TTree *tree5 = (TTree *)input->Get("tree5");
  TTree *tree4 = (TTree *)input->Get("tree4");

  TTree *rttree1 = (TTree *)input2->Get("tree1");

  // access the variables that were stored inside the tree

  //--
  tree2->SetBranchAddress("pT_2", &pT_2);
  tree2->SetBranchAddress("id_2", &id_2);

  tree2->SetBranchAddress("eta_2", &eta_2);
  tree2->SetBranchAddress("event_number_2", &event_number_2);

  rttree1->SetBranchAddress("Rt", &Rt);

  
  int entries =
      tree2->GetEntries(); // total number of enteries for variable pT_1
  int entries2 = tree2->GetEntries();
  int entries3 = tree3->GetEntries();

  cout << entries << endl;

  int entries5 = tree5->GetEntries();

  /*4) Main plotting algo*/
  for (int i = 0; i < entries; i++) {
    //--
    tree2->GetEntry(i);
    rttree1->GetEntry(event_number_2);

    //--
    if (Rt >= 0.0 && Rt < 0.5) {
      if (abs(id_2) == 3122) { // fill only for K0S particle
        hist->Fill(pT_2);
      }
    }

    if (Rt >= 0.5 && Rt < 1.5) {
      if (abs(id_2) == 3122) { // fill only for K0S particle
        hist2->Fill(pT_2);
      }
    }

    if (Rt >= 1.5 && Rt < 2.5) {
      if (abs(id_2) == 3122) { // fill only for K0S particle
        hist3->Fill(pT_2);
      }
    }

    if (Rt >= 2.5 && Rt < 5.0) {
      if (abs(id_2) == 3122) { // fill only for K0S particle
        hist4->Fill(pT_2);
      }
    }

    if (Rt >= 0) {
      if (abs(id_2) == 3122) { // fill only for K0S particle
        hist5->Fill(pT_2);
      }
    }
  }

  cout << "Filling hists done" << endl;

  hist->SetStats(0);

  hist->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  hist->SetLineColor(ALICEfigtemplate::colors[1]);
  // hist-> SetLineWidth(2);
  hist->SetMarkerStyle(kFullCircle);
  hist->SetMarkerSize(2);
  // noramlizing
  Double_t scale = 1 / hist->Integral(); // 1.0 / 98627.0; //
  hist->Scale(scale);
  hs->Add(hist);

  hist2->SetStats(0);

  hist2->SetMarkerColor(ALICEfigtemplate::colors[6]); // cyan
  hist2->SetLineColor(ALICEfigtemplate::colors[6]);
  // hist2-> SetLineWidth(2);
  hist2->SetMarkerStyle(kFullSquare); //
  hist2->SetMarkerSize(2);
  // noramlizing
  Double_t scale2 = 1 / hist2->Integral(); // 1.0 / 209166.0; //
  hist2->Scale(scale2);
  hs->Add(hist2);

  hist3->SetStats(3);

  hist3->SetMarkerColor(ALICEfigtemplate::colors[0]); // black
  hist3->SetLineColor(ALICEfigtemplate::colors[0]);
  // hist3-> SetLineWidth(2);
  hist3->SetMarkerStyle(kFullFourTrianglesPlus); //
  hist3->SetMarkerSize(2);
  // noramlizing
  Double_t scale3 = 1 / hist3->Integral(); // 1.0 / 83550.0; //
  hist3->Scale(scale3);
  hs->Add(hist3);

  hist4->SetStats(0);

  hist4->SetMarkerColor(ALICEfigtemplate::colors[2]); // blue
  hist4->SetLineColor(ALICEfigtemplate::colors[2]);
  // hist4-> SetLineWidth(2);
  hist4->SetMarkerStyle(kFullTriangleUp);
  hist4->SetMarkerSize(2);
  // noramlizing
  Double_t scale4 = 1 / hist4->Integral(); // 1.0 / 11598.0; //
  hist4->Scale(scale4);

  hs->Add(hist4);

  hist5->SetStats(0);

  hist5->SetLineColor(9);
  hist5->SetLineWidth(2);
  // noramlizing
  Double_t scale5 = 1 / hist5->Integral(); // 1.0 / 402941.0; //
  hist5->Scale(scale5);
  // hs->Add(hist5);

  // Creating ratios with RT>=0

  THStack *hs2 = new THStack("hs2", "");

  TH1F *ratio1 = (TH1F *)hist->Clone("hist");
  ratio1->Divide(hist5);

  ratio1->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  ratio1->SetLineColor(ALICEfigtemplate::colors[1]);

  ratio1->SetMarkerStyle(kFullCircle);
  ratio1->SetMarkerSize(2);
  // ratio1->SetMinimum(0);
  // ratio1->SetMaximum(10);

  hs2->Add(ratio1);

  TH1F *ratio2 = (TH1F *)hist2->Clone("hist2");
  ratio2->Divide(hist5);
  // ratio2->SetMinimum(0);

  ratio2->SetMarkerColor(ALICEfigtemplate::colors[6]); // cyan
  ratio2->SetLineColor(ALICEfigtemplate::colors[6]);
  // hist2-> SetLineWidth(2);
  ratio2->SetMarkerStyle(kFullSquare); //
  ratio2->SetMarkerSize(2);
  // ratio2->SetMaximum(5);
  hs2->Add(ratio2);

  TH1F *ratio3 = (TH1F *)hist3->Clone("hist3");
  ratio3->Divide(hist5);

  ratio3->SetMarkerColor(ALICEfigtemplate::colors[0]); // black
  ratio3->SetLineColor(ALICEfigtemplate::colors[0]);
  // hist3-> SetLineWidth(2);
  ratio3->SetMarkerStyle(kFullFourTrianglesPlus); //
  ratio3->SetMarkerSize(2);
  // ratio3->SetMinimum(0);
  // ratio3->SetMaximum(5);
  hs2->Add(ratio3);

  TH1F *ratio4 = (TH1F *)hist4->Clone("hist4");
  ratio4->Divide(hist5);
  ratio4->SetMarkerColor(ALICEfigtemplate::colors[2]); // blue
  ratio4->SetLineColor(ALICEfigtemplate::colors[2]);
  // hist4-> SetLineWidth(2);
  ratio4->SetMarkerStyle(kFullTriangleUp);
  ratio4->SetMarkerSize(2);
  // ratio4->SetMinimum(0);
  // ratio4->SetMaximum(5);
  hs2->Add(ratio4);

  // PAD 1 -----------------------------------

  TPad *p1 =
      new TPad("p1", "p1", 0.0, 0.4, 1.0, 1.0); // xlow, ylow, xup, yup in NDC

  p1->SetBottomMargin(0.025);
  p1->Draw();
  p1->cd();

  p1->SetTickx(1);
  p1->SetTicky(1);
  // c1->SetGridx();    // setting grid on
  // c1->SetGridy();

  hs->Draw("NOSTACK ");
  hs->GetXaxis()->SetTitleSize(0.);
  hs->GetYaxis()->SetTitleSize(0.08);
  hs->GetXaxis()->SetLabelSize(0.);
  hs->GetYaxis()->SetLabelSize(0.06);
  hs->GetYaxis()->SetTitle("d#rho/dp_{T} [GeV rad]^{-1}");
  hs->GetYaxis()->SetTitleOffset(0.65); // Increase to bring to left
  hs->GetXaxis()->SetTitle("p_{T} [GeV]");

  hs->GetXaxis()->SetRangeUser(0, 5);
  gPad->SetLogy(1);
  // gPad->BuildLegend(0.15,0.15,0.30,0.30,"");

  TLegend *legend = new TLegend(0.20, 0.25, 0.45, 0.50); // Already NDC

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.);
  legend->AddEntry(hist, "0. #leq R_{T} < 0.5 ", "lep");
  legend->AddEntry(hist2, "0.5 #leq R_{T} < 1.5", "lep");
  legend->AddEntry(hist3, "1.5 #leq R_{T} < 2.5", "lep");
  legend->AddEntry(hist4, "2.5 #leq R_{T} < 5.0", "lep");
  legend->Draw();

  c1->Update();

  // Annotations and legends

  TLatex latex;
  TLatex latex2;
  TLatex energy;
  latex.SetNDC(1);
  latex.SetTextSize(0.1); // Set NDC
  latex.SetTextAlign(13);
  latex.DrawLatex(0.67, 0.88, "#bf{#Lambda^{0} + #bar{#Lambda^{0}}}");

  // You should always specify the colliding system
  // NOTATION: pp, p-Pb, Pb-Pb.
  // Don't forget to use #sqrt{s_{NN}} for p-Pb and Pb-Pb
  // You can change the position of this with
  energy.SetNDC(1);
  energy.SetTextSize(0.07); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.22, 0.15, "pp, #sqrt{#it{s}} = 13 TeV");

  latex2.SetNDC(1); // Set NDC
  latex2.SetTextSize(0.07);
  latex2.SetTextAlign(13);
  //---
  latex2.DrawLatex(0.67, 0.72, "#bf{Toward Region}");

  // PAD 2-------------------
  c1->cd();

  TPad *p2 =
      new TPad("p2", "p2", 0.0, 0.05, 1.0, 0.4); // xlow, ylow, xup, yup in NDC

  p2->SetBottomMargin(0.180);
  p2->Draw();
  p2->cd();

  p2->SetTickx(1);
  p2->SetTicky(1);

  hs2->Draw("NOSTACK");
  hs2->GetXaxis()->SetTitleSize(0.11);
  hs2->GetYaxis()->SetTitleSize(0.12);
  hs2->GetXaxis()->SetLabelSize(0.10);
  hs2->GetYaxis()->SetLabelSize(0.09);
  hs2->GetYaxis()->SetTitle("Ratio to R_{T} #geq 0");
  hs2->GetYaxis()->SetTitleOffset(0.40); // increase to bring to left

  hs2->GetXaxis()->SetTitle("p_{T} [GeV]");
  hs2->GetXaxis()->SetTickLength(0.07);

  hs2->GetYaxis()->SetRangeUser(0, 5);
  hs2->GetXaxis()->SetRangeUser(0, 5);

  //gPad->SetLogy(1); // 1 = log 10

  TLine *line = new TLine(0, 1, 5, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2);
  line->SetLineStyle(2); // kSolid      = 1,  kDashed     = 2 , kDotted     = 3
                         // ,kDashDotted = 4
  line->Draw("same");

  // input->Close();
}


