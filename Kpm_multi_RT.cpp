/* RT Analyis */
#include "figTemplate.cpp"
#include "figTemplate.h"
#include <cmath>
void Kpm_multi_RT()
{
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

  TFile *input = new TFile("../ROOT_RT_Analysis/RT.root",
                           "read"); // Reading the data.root file (Without_RH)
  TFile *input2 = new TFile("../ROOT_RT_Analysis/meanPts.root",
                            "read"); // Reading the data.root file  (With_RH)
  TFile *input3 = new TFile("../ROOT_RT_Analysis/P1_r.root",
                            "read"); // Reading the data.root file  (With_RH)

  TProfile *hprof  = new TProfile("hprof","Without_RH",100,1,10,0,5);
  TProfile *hprof1  = new TProfile("hprof1","With_RH",25,0,5,0,40);      // Transverse
  TProfile *hprof2  = new TProfile("hprof2","With_RH",25,0,5,0,40);      // Transverse
  TProfile *hprof3  = new TProfile("hprof3","With_RH",25,0,5,0,40);      // Transverse

  TH1F *hist = new TH1F("hist", " ", 50, 0, 4);
  /*Reading the TTree attached in the root file */



  hprof2->SetMinimum(0);
  hprof2->SetMaximum(2.5);

  TTree *stree1 = (TTree*)input->Get("tree1");           // to get St
  TTree *mtree1 = (TTree*)input2->Get("tree1");          // to get npions from meanPts.root
  TTree *mtree2 = (TTree*)input2->Get("tree2");
  TTree *mtree3 = (TTree*)input2->Get("tree3");
  TTree *rtree4 = (TTree*)input3->Get("tree4");

  int id, event, size, no, nkpm1, nkpm2, nkpm3;
  double density_factor, Rt,pT_lead_lower_cut, pT_lead_upper_cut;
  double pT_lead, eta_1, y_1, phi_1;



  int entries = rtree4 ->GetEntries();
  int enteries_1 = mtree1 ->GetEntries();
  cout << entries << endl;
  cout << enteries_1 << endl;


  // Get access to variables
  stree1 ->SetBranchAddress("Rt", &Rt);
  mtree1 ->SetBranchAddress("nkpm1", &nkpm1);
  mtree2 ->SetBranchAddress("nkpm2", &nkpm2);
  mtree3 ->SetBranchAddress("nkpm3", &nkpm3);
  rtree4 ->SetBranchAddress("pT_lead",&pT_lead);



  // Initialization

  pT_lead_lower_cut = 5.0;
  pT_lead_upper_cut = 40.0;
  double eta_cut = 0.8 ;          // Kinematic cuts to be used
  double pT_cut = 0.15 ;

  density_factor = 4*M_PI*eta_cut/3;




  /* 2) Plotting St vs mult for each event ------------ */

  for (int i = 0; i < entries; i++)
  {
    rtree4->GetEntry(i);
    stree1->GetEntry(i);
    mtree1->GetEntry(i);
    mtree2->GetEntry(i);
    mtree3->GetEntry(i);

    if (pT_lead > pT_lead_lower_cut && pT_lead < pT_lead_upper_cut ) {
        hprof1->Fill(Rt, nkpm1,1);
        hprof2->Fill(Rt, nkpm2,1);
        hprof3->Fill(Rt, nkpm3,1);

    }

  }


  /* 3) Plotting ------------------------ */


  THStack *hs = new THStack("hs","");


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
  hs->GetXaxis()->SetTitle("R_{T}");

  hs->GetXaxis()->SetRangeUser(0, 5);


  TLatex latex;


  latex.SetNDC(1);                                    // Set NDC
  latex.SetTextSize(0.08);                                  // Set NDC
  latex.SetTextAlign(13);
  latex.DrawLatex(0.60,0.82,"#bf{K^{+} + K^{-}}");

  TLegend *legend = new TLegend(0.20, 0.65, 0.40, 0.80);         // Already NDC

  legend->SetBorderSize(0);
      //legend->SetLegendFont(42);
      //legend->SetLegendTextSize(0.);
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
