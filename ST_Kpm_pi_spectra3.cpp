/* loading data from a TTree and using it for analysis */



void ST_Kpm_pi_spectra3()
{

  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);
  TCanvas *c1 = new TCanvas("c1", "c1", 200,10,1000,1000);        ///2


  TFile *input = new TFile("P1_r.root", "read"); // Reading the data.root file
  TFile *input2 = new TFile("ST.root", "read"); // Reading the data.root file

  /*0) Reading the TTree attached in the root file */
  TTree *tree1 = (TTree*)input->Get("tree1");
  TTree *tree2 = (TTree*)input->Get("tree2");
  TTree *tree3 = (TTree*)input->Get("tree3");
  TTree *tree5 = (TTree*)input->Get("tree5");
  TTree *tree4 = (TTree*)input->Get("tree4");

  TTree *rttree1 = (TTree*)input2->Get("tree1");

  double St;


  int id_1, event, size, no, event_number_1;
  double pT_1, eta_1, y_1, phi_1;


  int id_2, event_number_2;
  double pT_2, eta_2, y_2, phi_2;

  int id_3, event_number_3;
  double pT_3, eta_3, y_3, phi_3;

  // access the variables that were stored with the name x and y inside the tree



  tree3 ->SetBranchAddress("pT_3", &pT_3);
  tree3 ->SetBranchAddress("id_3", &id_3);

  tree3 ->SetBranchAddress("eta_3", &eta_3);
  tree3 ->SetBranchAddress("event_number_3", &event_number_3);

  rttree1 ->SetBranchAddress("St", &St);

  int entries = tree1 ->GetEntries();    // total number of enteries for variable pT_1
  int entries2 = tree2 ->GetEntries();
  int entries3 = tree3 ->GetEntries();

  cout << entries3 << endl;


  TH1F *histkpm = new TH1F("histkpm", "", 100, 0, 10); // Creating histogram object
  TH1F *histkpm2 = new TH1F("histkpm2", " ", 100, 0, 10); // Creating histogram object
  TH1F *histkpm3 = new TH1F("histkpm3", " ", 100, 0, 10); // Creating histogram object
  TH1F *histkpm4 = new TH1F("histkpm4", " ", 100, 0, 10); // Creating histogram object

  TH1F *histpi = new TH1F("histpi", "", 100, 0, 10); // Creating histogram object
  TH1F *histpi2 = new TH1F("histpi2", " ", 100, 0, 10); // Creating histogram object
  TH1F *histpi3 = new TH1F("histpi3", " ", 100, 0, 10); // Creating histogram object
  TH1F *histpi4 = new TH1F("histpi4", " ", 100, 0, 10); // Creating histogram object

  THStack *hs = new THStack("hs","");

  THStack *hsratio = new THStack("hsratio","");

 int entries5 = tree5 ->GetEntries();

/*1) Filling various plots*/

for (int i = 0; i < entries3; i++)
{

  tree3->GetEntry(i);
  rttree1->GetEntry(event_number_3);

      if (St >=0.0 &&  St < 0.5)
        {
          if(abs(id_3) == 321 ) {         // fill only for K0S particle
            histkpm->Fill(pT_3);}

          if(abs(id_3) == 211 ) {         // fill only for K0S particle
            histpi->Fill(pT_3);}

        }



        if (St >=0.5 &&  St < 1.5)
          {
              if(abs(id_3) == 321 ) {         // fill only for K0S particle
              histkpm2->Fill(pT_3);}

              if(abs(id_3) == 211 ) {         // fill only for K0S particle
                histpi2->Fill(pT_3);}

          }


        if (St >=1.5 &&  St < 2.5)
          {
             if(abs(id_3) == 321 ) {         // fill only for K0S particle
             histkpm3->Fill(pT_3);}

             if(abs(id_3) == 211 ) {         // fill only for K0S particle
               histpi3->Fill(pT_3);}


          }

        if (St >=2.5 &&  St < 5.0)
          {
              if(abs(id_3) == 321 ) {         // fill only for K0S particle
              histkpm4->Fill(pT_3);}

              if(abs(id_3) == 211 ) {         // fill only for K0S particle
                histpi4->Fill(pT_3);}

          }

}



cout << "Filling hists done" << endl;


  /*3) Plotting the plots */

  histkpm->SetStats(0);

  histkpm->SetLineColor(2);
  histkpm-> SetLineWidth(3);

  TH1F *histkpmpi1 = (TH1F*)histkpm->Clone("histkpm");
  histkpmpi1->Divide(histpi);

  hs->Add(histkpmpi1);

  histkpm2->SetStats(0);

  histkpm2->SetLineColor(7);
  histkpm2-> SetLineWidth(3);


  TH1F *histkpmpi2 = (TH1F*)histkpm2->Clone("histkpm2");
  histkpmpi2->Divide(histpi2);

  hs->Add(histkpmpi2);

  histkpm3->SetStats(3);

  histkpm3->SetLineColor(1);
  histkpm3-> SetLineWidth(3);


  TH1F *histkpmpi3 = (TH1F*)histkpm3->Clone("histkpm3");
  histkpmpi3->Divide(histpi3);

  hs->Add(histkpmpi3);

  histkpm4->SetStats(0);

  histkpm4->SetLineColor(9);
  histkpm4-> SetLineWidth(3);


  TH1F *histkpmpi4 = (TH1F*)histkpm4->Clone("histkpm4");
  histkpmpi4->Divide(histpi4);


  hs->Add(histkpmpi4);




    c1->SetTickx(1);
    c1->SetTicky(1);
    //c1->SetGridx();    // setting grid on
    //c1->SetGridy();

    hs->SetMaximum(0.4);

    hs->Draw("HIST NOSTACK");
    hs->GetXaxis()->SetTitleSize(0.05);
    hs->GetYaxis()->SetTitleSize(0.05);
    hs->GetXaxis()->SetLabelSize(0.04);
    hs->GetYaxis()->SetLabelSize(0.04);
    hs->GetYaxis()->SetTitle("(K^{+} + K^{-})/(#pi^{+} + #pi^{-})");
    hs->GetYaxis()->SetTitleOffset(0.75);
    hs->GetXaxis()->SetTitle("p_{T} [GeV]");


    //gPad->BuildLegend(0.15,0.15,0.30,0.30,"");

    hs->GetXaxis()->SetRangeUser(0, 3);




    TLegend *legend = new TLegend(0.15, 0.57, 0.30, 0.72);         // Already NDC

    legend->SetBorderSize(0);
    //legend->SetLegendFont(42);
    //legend->SetLegendTextSize(0.);
    legend->AddEntry(histkpmpi1, "0. #leq S_{T} < 0.5 ", "l");
    legend->AddEntry(histkpmpi2, "0.5 #leq S_{T} < 1.5", "l");
    legend->AddEntry(histkpmpi3, "1.5 #leq S_{T} < 2.5", "l");
    legend->AddEntry(histkpmpi4, "2.5 #leq S_{T} < 5.0", "l");
    legend->Draw();


    c1->Update();


    TLatex latex;
    TLatex latex2;
    latex.SetNDC(1);
    latex.SetTextSize(0.07);                                  // Set NDC
    latex.SetTextAlign(13);
    //latex.DrawLatex(0.67,0.82,"K^{+} + K^{-}/#pi^{+} + #pi{-} ");

    latex2.SetNDC(1);                                    // Set NDC
    latex2.SetTextSize(0.04);
    latex2.SetTextAlign(13);
    latex2.DrawLatex(0.15,0.82,"Away Region");






  //input->Close();

}
/* loading data from a TTree and using it for analysis */
