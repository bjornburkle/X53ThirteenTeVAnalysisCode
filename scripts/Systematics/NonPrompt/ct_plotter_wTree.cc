
void DrawCumulative(TH1F* h_pred, TH1F* h_obs, std::string pdfname, std::string flavor, std::string lepflavor){

  TCanvas* c = new TCanvas();
  c->SetLogy();
  //make tpads
  TPad* pad1 = new TPad("pad1","pad1",0.01,0.2,1,1);
  TPad* pad2 = new TPad("pad2","pad2",0.01,0.,1,0.2);

  pad1->SetTopMargin(0.1);
  pad1->SetLogy();
  pad2->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();
  pad2->Draw();
  //cd to top pad for drawing
  pad1->cd();

  std::string title = "Predicted vs. Observed H_{T}^{Lep} for "+flavor+" "+lepflavor+" - Cumulative;H_{T};N_{Events}";

  //if(flavor=="unmatched") std::cout<<"unmatched observed events before lumi: "<<h_obs->Integral();

  //make lumi weight
  //sumw2
  h_obs->Sumw2();
  //h_pred->Sumw2();
  float lumiweight = 35800*  (831.76 / 115091972);
  h_pred->Scale(lumiweight);
  h_obs->Scale(lumiweight);

  //make cumulative
  TH1F* h_pred_cum = (TH1F*) h_pred->Clone("h_pred_cum");
  h_pred_cum->Sumw2();
  TH1F* h_obs_cum = (TH1F*) h_pred->Clone("h_obs_cum");
  h_obs_cum->Sumw2();
  for(int i=1; i<=h_pred_cum->GetNbinsX();i++){
    Double_t obserr=0.;
    float obs = h_obs->IntegralAndError(i,26,obserr);
    Double_t prederr=0.;
    float pred = h_pred->IntegralAndError(i,26,prederr);
    h_pred_cum->SetBinContent(i,pred);
    h_pred_cum->SetBinError(i,prederr);
    h_obs_cum->SetBinContent(i,obs);
    h_obs_cum->SetBinError(i,obserr);
  }

  h_pred_cum->SetTitle(title.c_str());
  h_pred_cum->SetTitleSize(0.12);
  h_pred_cum->GetYaxis()->SetTitleOffset(1.4);
  h_pred_cum->GetYaxis()->CenterTitle();
  h_pred_cum->SetLineColor(kRed+1);
  h_obs_cum->SetMarkerStyle(20);
  h_obs_cum->SetMarkerColor(kBlack);
  h_obs_cum->SetLineColor(kBlack);

  h_pred_cum->Draw("hist e");
  h_obs_cum->Draw("pesame");

  TLegend* leg = new TLegend(0.4,0.6,0.9,0.8);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  std::string predleg = "Predicted Events for "+flavor+" "+lepflavor;
  std::string obsleg = "Observed Events for "+flavor+" "+lepflavor;
  leg->AddEntry(h_obs_cum,obsleg.c_str(),"p");
  leg->AddEntry(h_pred_cum,predleg.c_str(),"l");
  leg->Draw("same");

  //now go to pad2 and draw ratio
  pad2->cd();
  TH1F* h_ratio = (TH1F*) h_obs_cum->Clone("h_ratio");
  h_ratio->Divide(h_pred_cum);
  h_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  h_ratio->GetYaxis()->SetTitle("Obs/Pred");
  h_ratio->GetYaxis()->SetTitleOffset(0.4);
  h_ratio->GetYaxis()->SetTitleSize(0.12);
  h_ratio->GetYaxis()->CenterTitle();
  h_ratio->GetYaxis()->SetLabelSize(0.10);
  h_ratio->GetXaxis()->SetTitle("H_{T}^{Lep}");
  h_ratio->GetXaxis()->SetTitleSize(0.12);
  h_ratio->GetXaxis()->CenterTitle();
  h_ratio->GetXaxis()->SetLabelSize(0.10);
  h_ratio->GetYaxis()->SetNdivisions(205);
  h_ratio->Draw("pe");
  TLine* baseline = new TLine(0,1,3000,1);
  baseline->SetLineColor(kBlack);
  baseline->SetLineStyle(2);
  baseline->Draw();

  c->Update();
  c->Print(pdfname.c_str());
  delete c;

}

void DrawAndSave(TH1F* h_pred, TH1F* h_obs, std::string pdfname, std::string flavor, std::string lepflavor){

  TCanvas* c = new TCanvas();
  c->SetLogy();
  //make tpads
  TPad* pad1 = new TPad("pad1","pad1",0.01,0.2,1,1);
  TPad* pad2 = new TPad("pad2","pad2",0.01,0.,1,0.2);

  pad1->SetTopMargin(0.1);
  pad1->SetLogy();
  pad2->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();
  pad2->Draw();
  //cd to top pad for drawing
  pad1->cd();

  std::string title = "Predicted vs. Observed H_{T}^{Lep} for "+flavor+" "+lepflavor+";H_{T};N_{Events}";
  h_pred->SetTitle(title.c_str());
  h_pred->SetTitleSize(0.12);
  h_pred->GetYaxis()->SetTitleOffset(1.4);
  h_pred->GetYaxis()->CenterTitle();
  h_pred->SetLineColor(kRed+1);
  h_obs->SetMarkerStyle(20);
  h_obs->SetMarkerColor(kBlack);

  //if(flavor=="unmatched") std::cout<<"unmatched observed events before lumi: "<<h_obs->Integral();

  //make lumi weight
  //sumw2
  h_obs->Sumw2();
  //h_pred->Sumw2();
  float lumiweight = 35800*  (831.76 / 115091972);
  h_pred->Scale(lumiweight);
  h_obs->Scale(lumiweight);
  
  Double_t obserr=0.;
  float obs = h_obs->IntegralAndError(11,26,obserr);
  Double_t prederr=0.;
  float pred = h_pred->IntegralAndError(11,26,prederr);
  //  std::cout<<"bin low edge: "<<h_pred->GetXaxis()->GetBinLowEdge(11)<<std::endl;
  std::cout<<std::fixed<<setprecision(2)<<lepflavor<<"&"<<flavor<<"&$"<<obs<<"\\pm"<<obserr<<"$&$"<<pred<<"\\pm"<<prederr<<"$\\\\"<<std::endl;

  double totobserr=0;
  float totobs = h_obs->IntegralAndError(1,26,totobserr);
  double totprederr=0;
  float totpred = h_pred->IntegralAndError(1,26,totprederr);
  std::cout<<std::fixed<<setprecision(2)<<lepflavor<<"&"<<flavor<<"&$"<<totobs<<"\\pm"<<totobserr<<"$&$"<<totpred<<"\\pm"<<totprederr<<"$\\\\"<<std::endl;


  h_pred->Draw("hist e");
  h_obs->Draw("pesame");

  TLegend* leg = new TLegend(0.4,0.6,0.9,0.8);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  std::string predleg = "Predicted Events for "+flavor+" "+lepflavor;
  std::string obsleg = "Observed Events for "+flavor+" "+lepflavor;
  leg->AddEntry(h_obs,obsleg.c_str(),"p");
  leg->AddEntry(h_pred,predleg.c_str(),"l");
  leg->Draw("same");

  //latex
  TLatex* cmstex = new TLatex();
  cmstex->SetNDC();
  cmstex->SetTextSize(0.06);
  //draw latex
  cmstex->DrawLatex(0.68,0.93,"CMS Preliminary");


  //now go to pad2 and draw ratio
  pad2->cd();
  TH1F* h_ratio = (TH1F*) h_obs->Clone("h_ratio");
  h_ratio->Divide(h_pred);
  h_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  h_ratio->GetYaxis()->SetTitle("Obs/Pred");
  h_ratio->GetYaxis()->SetTitleOffset(0.4);
  h_ratio->GetYaxis()->SetTitleSize(0.12);
  h_ratio->GetYaxis()->CenterTitle();
  h_ratio->GetYaxis()->SetLabelSize(0.10);
  h_ratio->GetXaxis()->SetTitle("H_{T}^{Lep}");
  h_ratio->GetXaxis()->SetTitleSize(0.12);
  h_ratio->GetXaxis()->CenterTitle();
  h_ratio->GetXaxis()->SetLabelSize(0.10);
  h_ratio->GetYaxis()->SetNdivisions(205);
  h_ratio->Draw("pe");
  TLine* baseline = new TLine(0,1,3000,1);
  baseline->SetLineColor(kBlack);
  baseline->SetLineStyle(2);
  baseline->Draw();

  c->Update();
  c->Print(pdfname.c_str());
  delete c;

}


void ct_plotter_wTree(){

  gStyle->SetOptStat(kFALSE);

  TFile* fRates = new TFile("Sys_FakeRateByFlavor.root");
  
  TH1F* h_rate_el_light = (TH1F*) fRates->Get("h_rate_el_l_eta");
  TH1F* h_rate_el_charm = (TH1F*) fRates->Get("h_rate_el_c_eta");
  TH1F* h_rate_el_bottom = (TH1F*) fRates->Get("h_rate_el_b_eta");
  TH1F* h_rate_el_unmatched = (TH1F*) fRates->Get("h_rate_el_u_eta");
  TH1F* h_rate_el_fake = (TH1F*) fRates->Get("h_rate_el_f_eta");

  TH1F* h_rate_mu_light = (TH1F*) fRates->Get("h_rate_mu_l_eta");
  TH1F* h_rate_mu_charm = (TH1F*) fRates->Get("h_rate_mu_c_eta");
  TH1F* h_rate_mu_bottom = (TH1F*) fRates->Get("h_rate_mu_b_eta");
  TH1F* h_rate_mu_unmatched = (TH1F*) fRates->Get("h_rate_mu_u_eta");
  TH1F* h_rate_mu_fake = (TH1F*) fRates->Get("h_rate_mu_f_eta");


  TFile* fIn = new TFile("SmartClosure_TTbar.root");
  TTree* t = (TTree*) fIn->Get("ClosureTest");
  float HT,LepEta,LepPt;
  int LepFlavor,LepSourceFlavor,Observed;
  t->SetBranchAddress("LepEta",&LepEta);
  t->SetBranchAddress("LepPt",&LepPt);
  t->SetBranchAddress("HT",&HT);
  t->SetBranchAddress("LepFlavor",&LepFlavor);
  t->SetBranchAddress("LepFlavorSource",&LepSourceFlavor);
  t->SetBranchAddress("Observed",&Observed);

  TH1F* h_el_obs_HT_light = new TH1F("h_el_obs_HT_light","H_{T} Electrons from Light Quarks",25,0,3000);
  TH1F* h_el_obs_HT_charm = new TH1F("h_el_obs_HT_charm","H_{T} Electrons from Charm Quarks",25,0,3000);
  TH1F* h_el_obs_HT_bottom = new TH1F("h_el_obs_HT_bottom","H_{T} Electrons from Bottom Quarks",25,0,3000);
  TH1F* h_el_obs_HT_unmatched = new TH1F("h_el_obs_HT_unmatched","H_{T} Electrons from Unmatched",25,0,3000);
  TH1F* h_el_obs_HT_fake = new TH1F("h_el_obs_HT_fake","H_{T} Electrons from Fakes",25,0,3000);

  TH1F* h_el_pred_HT_light = new TH1F("h_el_pred_HT_light","H_{T} Electrons from Light Quarks",25,0,3000);
  TH1F* h_el_pred_HT_charm = new TH1F("h_el_pred_HT_charm","H_{T} Electrons from Charm Quarks",25,0,3000);
  TH1F* h_el_pred_HT_bottom = new TH1F("h_el_pred_HT_bottom","H_{T} Electrons from Bottom Quarks",25,0,3000);
  TH1F* h_el_pred_HT_unmatched = new TH1F("h_el_pred_HT_unmatched","H_{T} Electrons from Unmatched",25,0,3000);
  TH1F* h_el_pred_HT_fake = new TH1F("h_el_pred_HT_fake","H_{T} Electrons from Fakes",25,0,3000);

  TH1F* h_el_obs_pt_light = new TH1F("h_el_obs_pt_light","p_{T} Electrons from Light Quarks",15,0,300);
  TH1F* h_el_obs_pt_charm = new TH1F("h_el_obs_pt_charm","p_{T} Electrons from Charm Quarks",15,0,300);
  TH1F* h_el_obs_pt_bottom = new TH1F("h_el_obs_pt_bottom","p_{T} Electrons from Bottom Quarks",15,0,300);
  TH1F* h_el_obs_pt_unmatched = new TH1F("h_el_obs_pt_unmatched","p_{T} Electrons from Unmatched",15,0,300);
  TH1F* h_el_obs_pt_fake = new TH1F("h_el_obs_pt_fake","p_{T} Electrons from Fakes",15,0,300);

  TH1F* h_el_pred_pt_light = new TH1F("h_el_pred_pt_light","p_{T} Electrons from Light Quarks",15,0,300);
  TH1F* h_el_pred_pt_charm = new TH1F("h_el_pred_pt_charm","p_{T} Electrons from Charm Quarks",15,0,300);
  TH1F* h_el_pred_pt_bottom = new TH1F("h_el_pred_pt_bottom","p_{T} Electrons from Bottom Quarks",15,0,300);
  TH1F* h_el_pred_pt_unmatched = new TH1F("h_el_pred_pt_unmatched","p_{T} Electrons from Unmatched",15,0,300);
  TH1F* h_el_pred_pt_fake = new TH1F("h_el_pred_pt_fake","p_{T} Electrons from Fakes",15,0,300);

  TH1F* h_mu_obs_HT_light = new TH1F("h_mu_obs_HT_light","H_{T} Muons from Light Quarks",25,0,3000);
  TH1F* h_mu_obs_HT_charm = new TH1F("h_mu_obs_HT_charm","H_{T} Muons from Charm Quarks",25,0,3000);
  TH1F* h_mu_obs_HT_bottom = new TH1F("h_mu_obs_HT_bottom","H_{T} Muons from Bottom Quarks",25,0,3000);
  TH1F* h_mu_obs_HT_unmatched = new TH1F("h_mu_obs_HT_unmatched","H_{T} Muons from Unmatched",25,0,3000);
  TH1F* h_mu_obs_HT_fake = new TH1F("h_mu_obs_HT_fake","H_{T} Muons from Fakes",25,0,3000);

  TH1F* h_mu_pred_HT_light = new TH1F("h_mu_pred_HT_light","H_{T} Muons from Light Quarks",25,0,3000);
  TH1F* h_mu_pred_HT_charm = new TH1F("h_mu_pred_HT_charm","H_{T} Muons from Charm Quarks",25,0,3000);
  TH1F* h_mu_pred_HT_bottom = new TH1F("h_mu_pred_HT_bottom","H_{T} Muons from Bottom Quarks",25,0,3000);
  TH1F* h_mu_pred_HT_unmatched = new TH1F("h_mu_pred_HT_unmatched","H_{T} Muons from Unmatched",25,0,3000);
  TH1F* h_mu_pred_HT_fake = new TH1F("h_mu_pred_HT_fake","H_{T} Muons from Fakes",25,0,3000);

  TH1F* h_mu_obs_pt_light = new TH1F("h_mu_obs_pt_light","p_{T} Muons from Light Quarks",15,0,300);
  TH1F* h_mu_obs_pt_charm = new TH1F("h_mu_obs_pt_charm","p_{T} Muons from Charm Quarks",15,0,300);
  TH1F* h_mu_obs_pt_bottom = new TH1F("h_mu_obs_pt_bottom","p_{T} Muons from Bottom Quarks",15,0,300);
  TH1F* h_mu_obs_pt_unmatched = new TH1F("h_mu_obs_pt_unmatched","p_{T} Muons from Unmatched",15,0,300);
  TH1F* h_mu_obs_pt_fake = new TH1F("h_mu_obs_pt_fake","p_{T} Muons from Fakes",15,0,300);

  TH1F* h_mu_pred_pt_light = new TH1F("h_mu_pred_pt_light","p_{T} Muons from Light Quarks",15,0,300);
  TH1F* h_mu_pred_pt_charm = new TH1F("h_mu_pred_pt_charm","p_{T} Muons from Charm Quarks",15,0,300);
  TH1F* h_mu_pred_pt_bottom = new TH1F("h_mu_pred_pt_bottom","p_{T} Muons from Bottom Quarks",15,0,300);
  TH1F* h_mu_pred_pt_unmatched = new TH1F("h_mu_pred_pt_unmatched","p_{T} Muons from Unmatched",15,0,300);
  TH1F* h_mu_pred_pt_fake = new TH1F("h_mu_pred_pt_fake","p_{T} Muons from Fakes",15,0,300);




  for(int i=0; i<t->GetEntries();i++){
    t->GetEntry(i);
    if(LepFlavor==0 && (fabs(LepEta)>1.4442 && fabs(LepEta)<1.566) ) continue;
    if(LepFlavor==0){//electrons
      if(LepSourceFlavor==0){//light
	if(Observed){
	  h_el_obs_HT_light->Fill(HT);
	  h_el_obs_pt_light->Fill(LepPt);
	}
	else{
	  int bin = h_rate_el_light->FindBin(LepEta);
	  float rate = h_rate_el_light->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_el_pred_HT_light->Fill(HT,weight);
	  h_el_pred_pt_light->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==1){//charm
	if(Observed){
	  h_el_obs_HT_charm->Fill(HT);
	  h_el_obs_pt_charm->Fill(LepPt);
	}
	else{
	  int bin = h_rate_el_charm->FindBin(LepEta);
	  float rate = h_rate_el_charm->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_el_pred_HT_charm->Fill(HT,weight);
	  h_el_pred_pt_charm->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==2){//bottom
	if(Observed){
	  h_el_obs_HT_bottom->Fill(HT);
	  h_el_obs_pt_bottom->Fill(LepPt);
	}
	else{
	  int bin = h_rate_el_bottom->FindBin(LepEta);
	  float rate = h_rate_el_bottom->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_el_pred_HT_bottom->Fill(HT,weight);
	  h_el_pred_pt_bottom->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==4){//unmatched
	if(Observed){
	  h_el_obs_HT_unmatched->Fill(HT);
	  h_el_obs_pt_unmatched->Fill(LepPt);
	}
	else{
	  int bin = h_rate_el_unmatched->FindBin(LepEta);
	  float rate = h_rate_el_unmatched->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  std::cout<<"rate: "<<rate<<"; weight: "<<weight<<"; eta: "<<LepEta<<std::endl;
	  h_el_pred_HT_unmatched->Fill(HT,weight);
	  h_el_pred_pt_unmatched->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==3){//fake
	if(Observed){
	  h_el_obs_HT_fake->Fill(HT);
	  h_el_obs_pt_fake->Fill(LepPt);
	}
	else{
	  int bin = h_rate_el_fake->FindBin(LepEta);
	  float rate = h_rate_el_fake->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_el_pred_HT_fake->Fill(HT,weight);
	  h_el_pred_pt_fake->Fill(LepPt,weight);
	}
      }
    }
    else{//muons

      if(LepSourceFlavor==0){//light
	if(Observed){
	  h_mu_obs_HT_light->Fill(HT);
	  h_mu_obs_pt_light->Fill(LepPt);
	}
	else{
	  int bin = h_rate_mu_light->FindBin(LepEta);
	  float rate = h_rate_mu_light->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_mu_pred_HT_light->Fill(HT,weight);
	  h_mu_pred_pt_light->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==1){//charm
	if(Observed){
	  h_mu_obs_HT_charm->Fill(HT);
	  h_mu_obs_pt_charm->Fill(LepPt);
	}
	else{
	  int bin = h_rate_mu_charm->FindBin(LepEta);
	  float rate = h_rate_mu_charm->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_mu_pred_HT_charm->Fill(HT,weight);
	  h_mu_pred_pt_charm->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==2){//bottom
	if(Observed){
	  h_mu_obs_HT_bottom->Fill(HT);
	  h_mu_obs_pt_bottom->Fill(LepPt);
	}
	else{
	  int bin = h_rate_mu_bottom->FindBin(LepEta);
	  float rate = h_rate_mu_bottom->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_mu_pred_HT_bottom->Fill(HT,weight);
	  h_mu_pred_pt_bottom->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==4){//unmatched
	if(Observed){
	  h_mu_obs_HT_unmatched->Fill(HT);
	  h_mu_obs_pt_unmatched->Fill(LepPt);
	}
	else{
	  int bin = h_rate_mu_unmatched->FindBin(LepEta);
	  float rate = h_rate_mu_unmatched->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_mu_pred_HT_unmatched->Fill(HT,weight);
	  h_mu_pred_pt_unmatched->Fill(LepPt,weight);
	}
      }
      else if(LepSourceFlavor==3){//fake
	if(Observed){
	  h_mu_obs_HT_fake->Fill(HT);
	  h_mu_obs_pt_fake->Fill(LepPt);
	}
	else{
	  int bin = h_rate_mu_fake->FindBin(LepEta);
	  float rate = h_rate_mu_fake->GetBinContent(bin);
	  float weight = rate / (1-rate);
	  h_mu_pred_HT_fake->Fill(HT,weight);
	  h_mu_pred_pt_fake->Fill(LepPt,weight);
	}
      }//end check on flavor source==fake
    }//end check on muons

  }//end event loop


  //draw and save
  DrawAndSave(h_el_pred_HT_light, h_el_obs_HT_light,"Closure_Light_Electrons_Twiki.pdf","light","Electrons");
  DrawAndSave(h_el_pred_HT_charm, h_el_obs_HT_charm,"Closure_Charm_Electrons_Twiki.pdf","charm","Electrons");
  DrawAndSave(h_el_pred_HT_bottom, h_el_obs_HT_bottom,"Closure_Bottom_Electrons_Twiki.pdf","bottom","Electrons");
  DrawAndSave(h_el_pred_HT_unmatched, h_el_obs_HT_unmatched,"Closure_UnMatched_Electrons_Twiki.pdf","unmatched","Electrons");
  DrawAndSave(h_el_pred_HT_fake, h_el_obs_HT_fake,"Closure_Fake_Electrons_Twiki.pdf","fake","Electrons");

  DrawAndSave(h_mu_pred_HT_light, h_mu_obs_HT_light,"Closure_Light_Muons_Twiki.pdf","light","Muons");
  DrawAndSave(h_mu_pred_HT_charm, h_mu_obs_HT_charm,"Closure_Charm_Muons_Twiki.pdf","charm","Muons");
  DrawAndSave(h_mu_pred_HT_bottom, h_mu_obs_HT_bottom,"Closure_Bottom_Muons_Twiki.pdf","bottom","Muons");
  DrawAndSave(h_mu_pred_HT_unmatched, h_mu_obs_HT_unmatched,"Closure_UnMatched_Muons_Twiki.pdf","unmatched","Muons");
  DrawAndSave(h_mu_pred_HT_fake, h_mu_obs_HT_fake,"Closure_Fake_Muons_Twiki.pdf","fake","Muons");


  DrawCumulative(h_el_pred_HT_light, h_el_obs_HT_light,"Closure_Light_Electrons_Cumulative_Twiki.pdf","light","Electrons");
  DrawCumulative(h_el_pred_HT_charm, h_el_obs_HT_charm,"Closure_Charm_Electrons_Cumulative_Twiki.pdf","charm","Electrons");
  DrawCumulative(h_el_pred_HT_bottom, h_el_obs_HT_bottom,"Closure_Bottom_Electrons_Cumulative_Twiki.pdf","bottom","Electrons");
  DrawCumulative(h_el_pred_HT_unmatched, h_el_obs_HT_unmatched,"Closure_UnMatched_Electrons_Cumulative_Twiki.pdf","unmatched","Electrons");
  DrawCumulative(h_el_pred_HT_fake, h_el_obs_HT_fake,"Closure_Fake_Electrons_Cumulative_Twiki.pdf","fake","Electrons");

  DrawCumulative(h_mu_pred_HT_light, h_mu_obs_HT_light,"Closure_Light_Muons_Cumulative_Twiki.pdf","light","Muons");
  DrawCumulative(h_mu_pred_HT_charm, h_mu_obs_HT_charm,"Closure_Charm_Muons_Cumulative_Twiki.pdf","charm","Muons");
  DrawCumulative(h_mu_pred_HT_bottom, h_mu_obs_HT_bottom,"Closure_Bottom_Muons_Cumulative_Twiki.pdf","bottom","Muons");
  DrawCumulative(h_mu_pred_HT_unmatched, h_mu_obs_HT_unmatched,"Closure_UnMatched_Muons_Cumulative_Twiki.pdf","unmatched","Muons");
  DrawCumulative(h_mu_pred_HT_fake, h_mu_obs_HT_fake,"Closure_Fake_Muons_Cumulative_Twiki.pdf","fake","Muons");

}
