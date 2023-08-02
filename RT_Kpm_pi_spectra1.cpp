/* loading data from a TTree and using it for analysis */
#include "figTemplate.cpp"
#include "figTemplate.h"

void RT_Kpm_pi_spectra1() {

  double Rt;

  int id_1, event, size, no, event_number_1;
  double pT_1, eta_1, y_1, phi_1;

  int id_2;
  double pT_2, eta_2, y_2, phi_2;

  int id_3;
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

  TH1F *histkpm =
      new TH1F("histkpm", "", 100, 0, 10); // Creating histogram object
  TH1F *histkpm2 =
      new TH1F("histkpm2", " ", 100, 0, 10); // Creating histogram object
  TH1F *histkpm3 =
      new TH1F("histkpm3", " ", 100, 0, 10); // Creating histogram object
  TH1F *histkpm4 =
      new TH1F("histkpm4", " ", 100, 0, 10); // Creating histogram object

  TH1F *histpi =
      new TH1F("histpi", "", 100, 0, 10); // Creating histogram object
  TH1F *histpi2 =
      new TH1F("histpi2", " ", 100, 0, 10); // Creating histogram object
  TH1F *histpi3 =
      new TH1F("histpi3", " ", 100, 0, 10); // Creating histogram object
  TH1F *histpi4 =
      new TH1F("histpi4", " ", 100, 0, 10); // Creating histogram object

  THStack *hs = new THStack("hs", "");

  THStack *hsratio = new THStack("hsratio", "");
  /*Reading the TTree attached in the root file */
  TTree *tree1 = (TTree *)input->Get("tree1");
  TTree *tree2 = (TTree *)input->Get("tree2");
  TTree *tree3 = (TTree *)input->Get("tree3");
  TTree *tree5 = (TTree *)input->Get("tree5");
  TTree *tree4 = (TTree *)input->Get("tree4");

  TTree *rttree1 = (TTree *)input2->Get("tree1");

  // access the variables that were stored with the name x and y inside the tree

  tree1->SetBranchAddress("pT_1", &pT_1);
  tree1->SetBranchAddress("id_1", &id_1);

  tree1->SetBranchAddress("eta_1", &eta_1);
  tree1->SetBranchAddress("event_number_1", &event_number_1);

  rttree1->SetBranchAddress("Rt", &Rt);

  int entries =
      tree1->GetEntries(); // total number of enteries for variable pT_1
  int entries2 = tree2->GetEntries();
  int entries3 = tree3->GetEntries();

  cout << entries << endl;

  int entries5 = tree5->GetEntries();

  // 4)Main plotting and algo
  for (int i = 0; i < entries; i++) {

    tree1->GetEntry(i);
    rttree1->GetEntry(event_number_1);

    if (Rt >= 0.0 && Rt < 0.5) {
      if (abs(id_1) == 321) { // fill only for K0S particle
        histkpm->Fill(pT_1);
      }

      if (abs(id_1) == 211) { // fill only for K0S particle
        histpi->Fill(pT_1);
      }
    }

    if (Rt >= 0.5 && Rt < 1.5) {
      if (abs(id_1) == 321) { // fill only for K0S particle
        histkpm2->Fill(pT_1);
      }

      if (abs(id_1) == 211) { // fill only for K0S particle
        histpi2->Fill(pT_1);
      }
    }

    if (Rt >= 1.5 && Rt < 2.5) {
      if (abs(id_1) == 321) { // fill only for K0S particle
        histkpm3->Fill(pT_1);
      }

      if (abs(id_1) == 211) { // fill only for K0S particle
        histpi3->Fill(pT_1);
      }
    }

    if (Rt >= 2.5 && Rt < 5.0) {
      if (abs(id_1) == 321) { // fill only for K0S particle
        histkpm4->Fill(pT_1);
      }

      if (abs(id_1) == 211) { // fill only for K0S particle
        histpi4->Fill(pT_1);
      }
    }
  }

  cout << "Filling hists done" << endl;

  histkpm->SetStats(0);
  histkpm->Divide(histpi);

  histkpm->SetMarkerStyle(kFullCircle);

  histkpm->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  histkpm->SetLineColor(ALICEfigtemplate::colors[1]);
  histkpm->SetMarkerSize(2);
 
  histkpm->Draw("HIST P");

  // TH1F *histkpmpi1 = (TH1F *)histkpm->Clone("histkpm");


  // histkpmpi1->SetMarkerColor(ALICEfigtemplate::colors[1]); // red
  // histkpmpi1->SetLineColor(ALICEfigtemplate::colors[1]);
  // // hist-> SetLineWidth(2);
  // histkpmpi1->SetMarkerStyle(kFullCircle);
  // histkpmpi1->SetMarkerSize(2);

  // hs->Add(histkpm);

  histkpm2->SetStats(0);

  // TH1F *histkpmpi2 = (TH1F *)histkpm2->Clone("histkpm2");
  histkpm2->Divide(histpi2);

  histkpm2->SetMarkerStyle(kFullSquare);
  histkpm2->SetMarkerColor(ALICEfigtemplate::colors[6]); // cyan
  histkpm2->SetLineColor(ALICEfigtemplate::colors[6]);
  // hist-> SetLineWidth(2);
  histkpm2->SetMarkerSize(2);

  histkpm2->Draw("SAME ");
  // hs->Add(histkpmpi2);

  histkpm3->SetStats(3);

  TH1F *histkpmpi3 = (TH1F *)histkpm3->Clone("histkpm3");
  histkpmpi3->Divide(histpi3);

  histkpmpi3->SetMarkerColor(ALICEfigtemplate::colors[0]); // black
  histkpmpi3->SetLineColor(ALICEfigtemplate::colors[0]);
  // hist-> SetLineWidth(2);
  histkpmpi3->SetMarkerStyle(kFullFourTrianglesPlus);
  histkpmpi3->SetMarkerSize(2);

  hs->Add(histkpmpi3);

  histkpm4->SetStats(0);

  TH1F *histkpmpi4 = (TH1F *)histkpm4->Clone("histkpm4");
  histkpmpi4->Divide(histpi4);

  histkpmpi4->SetMarkerColor(ALICEfigtemplate::colors[2]); // blue
  histkpmpi4->SetLineColor(ALICEfigtemplate::colors[2]);
  // hist-> SetLineWidth(2);
  histkpmpi4->SetMarkerStyle(kFullTriangleUp);
  histkpmpi4->SetMarkerSize(2);

  hs->Add(histkpmpi4);

  c1->SetTickx(1);
  c1->SetTicky(1);
  // c1->SetGridx();    // setting grid on
  // c1->SetGridy();

  hs->SetMaximum(0.4);
  c1->Draw();
  c1->cd();

  //hs->Draw("PLC PMC");

  hs->GetXaxis()->SetRangeUser(0, 5);
  // hs->GetXaxis()->SetTitleSize(0.05);
  // hs->GetYaxis()->SetTitleSize(0.05);
  // hs->GetXaxis()->SetLabelSize(0.04);
  // hs->GetYaxis()->SetLabelSize(0.04);
  hs->GetYaxis()->SetTitle("(K^{+} + K^{-})/(#pi^{+} + #pi^{-})");
  //hs->GetYaxis()->SetTitleOffset(0.75);
  hs->GetXaxis()->SetTitle("p_{T} [GeV]");

  hs->GetXaxis()->SetRangeUser(0, 3);

  // gPad->BuildLegend(0.15,0.15,0.30,0.30,"");

  TLegend *legend = new TLegend(0.20, 0.57, 0.35, 0.72); // Already NDC

  legend->SetBorderSize(0);
  // legend->SetLegendFont(42);
  // legend->SetLegendTextSize(0.);
  legend->AddEntry(histkpm, "0. #leq R_{T} < 0.5 ", "l");
  legend->AddEntry(histkpm, "0.5 #leq R_{T} < 1.5", "l");
  // legend->AddEntry(histkpmpi3, "1.5 #leq R_{T} < 2.5", "l");
  // legend->AddEntry(histkpmpi4, "2.5 #leq R_{T} < 5.0", "l");
  legend->Draw();

  c1->Update();

  TLatex energy;
  energy.SetNDC(1);
  energy.SetTextSize(0.04); // Set ND
  energy.SetTextAlign(13);
  energy.DrawLatex(0.65, 0.30, "pp, #sqrt{#it{s}} = 13 TeV");

  // TLatex latex;
  // latex.SetNDC(1);
  // latex.SetTextSize(0.07); // Set NDC
  // latex.SetTextAlign(13);
  // latex.DrawLatex(0.67,0.82,"K^{+} + K^{-}/#pi^{+} + #pi{-} ");

  TLatex latex2;
  latex2.SetNDC(1); // Set NDC
  latex2.SetTextSize(0.05);
  latex2.SetTextAlign(13);
  latex2.DrawLatex(0.20, 0.82, "#bf{Transverse Region}");



  // input->Close();
}
/* loading data from a TTree and using it for analysis */
