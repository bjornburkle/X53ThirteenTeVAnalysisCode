#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"

//helper functions
std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, std::string ID);
bool ZVetoCheck(TLepton* lepton, std::vector<TJet*> jets);
bool AwayJetCheck(TLepton* lepton, std::vector<TJet*> jets);

int main(int argc, char* argv[]){

  //example usage: ./FakeRate.o Data Electrons <ID>
  std::cout<<"dummy"<<std::endl;
  if(argc<4){
    std::cout<<"Error! You must specify whether running on 'Data' of 'MC' as option as well as electrons or muons and the ID used"<<std::endl;
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];
  std::string ID = argv[3];
  std::string argv4 = argv[4];
  if(argv1.find("Data")==std::string::npos && argv1.find("MC")==std::string::npos){
    std::cout<<"Error! You must specify whether running on 'Data' of 'MC' as option"<<std::endl;
    return 0;
  }

  std::cout<<"arg 1: "<<argv1<<" arg2: "<<argv2<<" arg3: "<<ID<<" arg4: "<<argv4<<std::endl;
    //now get boolean for data or mc
  bool data=false;
  if(argv1.find("Data")!=std::string::npos) data=true;

  //boolean for channel
  bool MuonChannel=false;
  if(argv2.find("Muons")!=std::string::npos) MuonChannel=true;


  //make output file
  std::vector<std::string> outname;
  if(data){
    if(MuonChannel) outname.push_back("FakeRate_Data_"+argv4+"Muons_"+ID+"_modifiedLepPt.root");
    else outname.push_back("FakeRate_Data_"+argv4+"Electrons_"+ID+"_modifiedLepPt_IsoElTrig.root");
  }

  else{
    if(MuonChannel){
      if(argv1=="WJets-MC") outname.push_back("FakeRate_WJets-MC_Muons"+ID+"modifiedLepPt.root");
      else if(argv1=="DYJets-MC") outname.push_back("FakeRate_DYJets-MC_Muons"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt0") outname.push_back("FakeRate_TTbar-MC_Muons_pt0"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt1") outname.push_back("FakeRate_TTbar-MC_Muons_pt1"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt2") outname.push_back("FakeRate_TTbar-MC_Muons_pt2"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt3") outname.push_back("FakeRate_TTbar-MC_Muons_pt3"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt4") outname.push_back("FakeRate_TTbar-MC_Muons_pt4"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt5") outname.push_back("FakeRate_TTbar-MC_Muons_pt5"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt6") outname.push_back("FakeRate_TTbar-MC_Muons_pt6"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt7") outname.push_back("FakeRate_TTbar-MC_Muons_pt7"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt8") outname.push_back("FakeRate_TTbar-MC_Muons_pt8"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt9") outname.push_back("FakeRate_TTbar-MC_Muons_pt9"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt15to30") outname.push_back("FakeRate_QCD_Pt15to30_Muons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt30to50") outname.push_back("FakeRate_QCD_Pt30to50_Muons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt50to80") outname.push_back("FakeRate_QCD_Pt50to80_Muons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt80to120") outname.push_back("FakeRate_QCD_Pt80to120_Muons_"+ID+"modifiedLepPt.root");
    }
    else{
      if(argv1=="WJets-MC") outname.push_back("FakeRate_WJets-MC_Electrons"+ID+"modifiedLepPt.root");
      else if(argv1=="DYJets-MC") outname.push_back("FakeRate_DYJets-MC_Electrons"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt0") outname.push_back("FakeRate_TTbar-MC_Electrons_pt0"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt1") outname.push_back("FakeRate_TTbar-MC_Electrons_pt1"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt2") outname.push_back("FakeRate_TTbar-MC_Electrons_pt2"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt3") outname.push_back("FakeRate_TTbar-MC_Electrons_pt3"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt4") outname.push_back("FakeRate_TTbar-MC_Electrons_pt4"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt5") outname.push_back("FakeRate_TTbar-MC_Electrons_pt5"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt6") outname.push_back("FakeRate_TTbar-MC_Electrons_pt6"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt7") outname.push_back("FakeRate_TTbar-MC_Electrons_pt7"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt8") outname.push_back("FakeRate_TTbar-MC_Electrons_pt8"+ID+"modifiedLepPt.root");
      else if(argv1=="TTbar-MC_pt9") outname.push_back("FakeRate_TTbar-MC_Electrons_pt9"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt15to30") outname.push_back("FakeRate_QCD_Pt15to30_Electrons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt30to50") outname.push_back("FakeRate_QCD_Pt30to50_Electrons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt50to80") outname.push_back("FakeRate_QCD_Pt50to80_Electrons_"+ID+"modifiedLepPt.root");
      else if(argv1=="QCD_MC-Pt80to120") outname.push_back("FakeRate_QCD_Pt80to120_Electrons_"+ID+"modifiedLepPt.root");
    }
  }


  //get correct file
  std::vector<std::string> filenames;
  if(argv1.find("Data")!=std::string::npos) {
    if(MuonChannel)       {
      if(argv4=="2016B") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016B-03Feb2017-v3.root");
      else if(argv4=="2016C") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016C-03Feb2017-v1.root");
      else if(argv4=="2016D") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016D-03Feb2017-v1.root");
      else if(argv4=="2016E") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016E-03Feb2017-v1.root");
      else if(argv4=="2016F") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016F-03Feb2017-v1.root");
      else if(argv4=="2016G") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016G-03Feb2017-v1.root");
      else if(argv4=="2016H2") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016H-03Feb2017-v2.root");
      else if(argv4=="2016H3") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleMuon-Run2016H-03Feb2017-v3.root");
    }
    else if(!MuonChannel){
      if(argv4=="2016B") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016B-03Feb2017-v3.root");
      else if(argv4=="2016C") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016C-03Feb2017-v1.root");
      else if(argv4=="2016D") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016D-03Feb2017-v1.root");
      else if(argv4=="2016E") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016E-03Feb2017-v1.root");
      else if(argv4=="2016F") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016F-03Feb2017-v1.root");
      else if(argv4=="2016G") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016G-03Feb2017-v1.root");
      else if(argv4=="2016H2") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016H-03Feb2017-v2.root");
      else if(argv4=="2016H3") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/FakeRate/25ns/Feb16/ljmet_trees/ljmet_FakeRate_DoubleEG-Run2016H-03Feb2017-v3.root");

    }
    
  }
  else{
    if(argv1=="WJets-MC") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_WJets_SingleLep.root");
    else if(argv1=="DYJets-MC") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_DYJets.root");
    else if(argv1=="TTbar-MC_pt0") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt0.root");
    else if(argv1=="TTbar-MC_pt1") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt1.root");
    else if(argv1=="TTbar-MC_pt2") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt2.root");
    else if(argv1=="TTbar-MC_pt3") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt3.root");
    else if(argv1=="TTbar-MC_pt4") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt4.root");
    else if(argv1=="TTbar-MC_pt5") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt5.root");
    else if(argv1=="TTbar-MC_pt6") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt6.root");
    else if(argv1=="TTbar-MC_pt7") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt7.root");
    else if(argv1=="TTbar-MC_pt8") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt8.root");
    else if(argv1=="TTbar-MC_pt9") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_TTbar_pt9.root");
    else if(argv1=="QCD_MC-Pt15to30") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_QCD_Pt15to30_SingleLep.root");
    else if(argv1=="QCD_MC-Pt30to50") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_QCD_Pt30to50_SingleLep.root");
    else if(argv1=="QCD_MC-Pt50to80") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_QCD_Pt50to80_SingleLep.root");
    else if(argv1=="QCD_MC-Pt80to120") filenames.push_back("root://cmseos.fnal.gov//store/user/lpctlbsm/clint/Spring16/25ns/Jan09/ljmet_trees/ljmet_QCD_Pt80to120_SingleLep.root");
  }

  for(unsigned int i =0; i<filenames.size(); i++){
    
    TFile* fout = new TFile(outname.at(i).c_str(),"RECREATE");

    //output tree
    TTree* outTree = new TTree("FakeRate","FakeRate");
    float LepPt_,LepEta_,LepPhi_,LepE_,LepMiniIso_,LepMinDR_,LepSusyIso_,m_T,MET;
    int LepIsLoose_,LepIsTight_,LepCharge_;
    outTree->Branch("LepPt",&LepPt_);
    outTree->Branch("LepEta",&LepEta_);
    outTree->Branch("LepPhi",&LepPhi_);
    outTree->Branch("LepE",&LepE_);
    outTree->Branch("LepCharge",&LepCharge_);
    outTree->Branch("LepMiniIso",&LepMiniIso_);
    outTree->Branch("LepSusyIso",&LepSusyIso_);
    outTree->Branch("LepIsLoose",&LepIsLoose_);
    outTree->Branch("LepIsTight",&LepIsTight_);
    outTree->Branch("LepMinDR",&LepMinDR_);
    outTree->Branch("mT",&m_T);
    outTree->Branch("MET",&MET);

    //get tree reader to read in data
    TreeReader* tr= new TreeReader(filenames.at(i).c_str(),false,false);
    TTree* t=tr->tree;


    
    //initialize needed histograms
    TH1F* ptNumHist = new TH1F("ptNumHist","p_{T} of Tight Leptons",20,0,600);
    TH1F* ptDenHist = new TH1F("ptDenHist","p_{T} of All Leptons",20,0,600);
    TH1F* etaNumHist = new TH1F("etaNumHist","#eta of Tight Leptons",12,-5,5);
    TH1F* etaDenHist = new TH1F("etaDenHist","#eta of All Leptons",12,-5,5);

    TH1F* etaHist_all = new TH1F("etaHist_all","#eta of all Loose Leptons",12,-5,5);
    TH1F* etaHist_ZVeto = new TH1F("etaHist_ZVeto","#eta of Leptons after zVeto",12,-5,5);
    TH1F* etaHist_MET = new TH1F("etaHist_MET","#eta of Leptons after MET cut",12,-5,5);
    TH1F* etaHist_MT = new TH1F("etaHist_MT","#eta of Leptons after M_{T} cut",12,-5,5);
    TH1F* etaHist_AwayJet = new TH1F("etaHist_AwayJet","#eta of Leptons after AwayJet cut",12,-5,5);


    //get number of entries and start event loop
    int nEntries = t->GetEntries();
    for(int ient=0; ient<nEntries; ient++){

      
      tr->GetEntry(ient);
      
      if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

      //make sure correct trigger was fired
      bool muTrig = tr->HLT_Mu17;
      //bool elTrig = tr->HLT_Ele17Iso;
      bool elTrig = tr->HLT_Ele17;
      bool analyze = false;
      if(data){
	if((MuonChannel && muTrig) || (!MuonChannel && elTrig)) analyze = true;
      }
      else analyze=true;

      if (!analyze) continue;

      //make vector of leptons
      std::vector<TLepton*> leptons = makeLeptons(tr->allMuons,tr->allElectrons,MuonChannel, ID);

      //veto on events with more than one lepton or no leptons
      if((leptons.size()==0) || (leptons.size() >1) ) continue;      
      //now just take the lepton remaining
      TLepton* lep = leptons.at(0);
      //skip if not the correct flavor
      if(MuonChannel && !(leptons.at(0)->isMu)) continue;
      if(!MuonChannel && !(leptons.at(0)->isEl)) continue;
      //skip if it has pt not between 25 and 35 - REMOVE THIS TO STUDY FAKE RATE VS PT
      //if( !(lep->pt < 35 && lep->pt>25)) continue;
      etaHist_all->Fill(lep->eta);

      //make sure not much met in event to veto on leptons from Ws -relaxed for now to do more in depth studies
      //if(tr->MET > 25) continue;
      etaHist_MET->Fill(lep->eta);
      //std::cout<<"lepton eta after MET cut : "<<lep->eta<<std::endl;      
      //check transverse mass is less than 25 GeV
      //search through jet collection to check for jet mass
      bool Zveto = ZVetoCheck(lep,tr->cleanedAK4Jets);
      if(Zveto) continue;
      etaHist_ZVeto->Fill(lep->eta);

      //check for away jet
      bool awayJet = AwayJetCheck(lep,tr->cleanedAK4Jets);
      if(!awayJet) continue;
      etaHist_AwayJet->Fill(lep->eta);
      
      float et = tr->MET+lep->energy;
      float pt1y = lep->pt*sin(lep->phi);
      float pt1x = lep->pt*cos(lep->phi);
      float pt2y = tr->MET*sin(tr->MET_phi);
      float pt2x = tr->MET*cos(tr->MET_phi);
      float mT = pow(et,2) - pow(lep->pt,2) - pow(tr->MET,2) - 2*(pt1y*pt2y - pt1x*pt2x);
      mT = pow(mT, 0.5);

      double dphi = fabs(tr->MET_phi - lep->phi);
      if (dphi > TMath::Pi()) dphi = TMath::TwoPi() - dphi;

      double mt2 = 2 * lep->pt * tr->MET * (1 - cos(dphi));;
      double mt  = sqrt(mt2);

      //std::cout<<"Clint mt: "<<mT<<" Aram mt: "<<mt<<std::endl;

      //if(mt>25) continue; //change to Arams value
      etaHist_MT->Fill(lep->eta);      

      //Now just fill histograms
      etaDenHist->Fill(lep->eta); ptDenHist->Fill(lep->pt);
      if(lep->Tight){etaNumHist->Fill(lep->eta);ptNumHist->Fill(lep->pt);}

      //fill tree
      LepPt_ = lep->pt;
      LepEta_= lep->eta;
      LepPhi_= lep->phi;
      LepE_  = lep->energy;
      LepCharge_ = lep->charge;
      LepMiniIso_ = lep->miniIso;
      LepSusyIso_ = lep->susyIso;
      LepIsTight_ = (int) lep->Tight;
      LepIsLoose_ = (int) lep->Loose;
      m_T = mt;
      MET = tr->MET;
      //find minDR
      float minDR=999;
      for(unsigned int i=0; i< tr->cleanedAK4Jets.size();i++){
	float drtemp = pow( pow(lep->eta - tr->cleanedAK4Jets.at(i)->eta, 2) + pow( lep->phi - tr->cleanedAK4Jets.at(0)->phi, 2) , 0.5);
	if(drtemp<minDR) minDR = drtemp;
      }
      LepMinDR_ = minDR;
      outTree->Fill();

    }//end event loop
    
    fout->WriteTObject(outTree);
    fout->Append(ptNumHist);
    fout->Append(ptDenHist);
    fout->Append(etaNumHist);
    fout->Append(etaDenHist);

    fout->Append(etaHist_all);
    fout->Append(etaHist_MET);
    fout->Append(etaHist_MT);
    fout->Append(etaHist_ZVeto);
    fout->Append(etaHist_AwayJet);

    TGraphAsymmErrors* ptgraph = new TGraphAsymmErrors(ptNumHist,ptDenHist);
    TGraphAsymmErrors* etagraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
    
    fout->Append(ptgraph);
    fout->Append(etagraph);
    fout->Write();
    fout->Close();

    //delete tree reader to free up space
    delete tr;

  }//end loop over filenames
}

std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, std::string ID){

  std::vector<TLepton*> Leptons;

  //fill with  muons
  for(unsigned int uimu=0; uimu<muons.size(); uimu++){
    TMuon* imu = muons.at(uimu);
    TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge,imu->relIso,imu->miniIso,imu->susyIso);
    if(ID=="CBTight"){
      iLep->Tight=imu->cutBasedTight();
      iLep->Loose=imu->cutBasedLoose();
    }
    else if(ID=="CBLoose"){
      iLep->Tight=imu->cutBasedLoose();
      iLep->Loose=true; //in case 'loose ID' is specified as 'tight', take any muon as loose ID
    }
    else if(ID=="CBTightMiniIso"){
      iLep->Tight=imu->cutBasedTight_NoIso();
      iLep->Loose=imu->cutBasedLooseMiniIso();
    }
    iLep->isMu = true;
    iLep->isEl = false;
    //only save if at least loose
    if(iLep->Tight || iLep->Loose){
      //apply pt cut
      if(iLep->pt>20){ Leptons.push_back(iLep);}
      //if(iLep->pt>25 && iLep->pt<35) Leptons.push_back(iLep);
    }
  }




  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge,iel->relIsoEA,iel->miniIso,iel->susyIso);
    if(ID=="CBTight"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
    }
    if(ID=="CBTightRC"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MCRC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MCRC();
    }
    else if(ID=="CBLoose"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
      iLep->Loose=true;
    }
    else if(ID=="MVATightNew"){
      iLep->Tight=iel->mvaTightNew();
      iLep->Loose=iel->mvaLooseNew();
    }
    else if(ID=="MVATightNewRC"){
      iLep->Tight=iel->mvaTightNewRC();
      iLep->Loose=iel->mvaLooseNewRC();
    }
    else if(ID=="MVATight"){
      iLep->Tight=iel->mvaTightIso();
      iLep->Loose=iel->mvaLooseIso();
    }
    else if(ID=="MVATightNoIso"){
      iLep->Tight=iel->mvaTight();
      iLep->Loose=iel->mvaLoose();
    }
    else if(ID=="MVALoose"){
      iLep->Tight=iel->mvaLooseIso();
      iLep->Loose=true;
    }
    else if(ID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }
    else if(ID=="MVATightCC"){
      iLep->Tight=iel->mvaTightCCIso();
      iLep->Loose=iel->mvaLooseCCIso();
    }
    else if(ID=="MVATightCCNoIso"){
      iLep->Tight=iel->mvaTightCC();
      iLep->Loose=iel->mvaLooseCC();
    }
    else if(ID=="MVALooseCC"){
      iLep->Tight=iel->mvaLooseCCIso();
      iLep->Loose=true;
    }
    else if(ID=="MVALooseCCNoIso"){
      iLep->Tight=iel->mvaLooseCC();
      iLep->Loose=true;
    }
    else if(ID=="MVATightRC"){
      iLep->Tight=iel->mvaTightRC();
      iLep->Loose=iel->mvaLooseRCIso();
    }
    else if(ID=="MVA2016TightRC"){
      iLep->Tight=iel->mva2016TightRC();
      iLep->Loose=iel->mvaJulieLooseRCIso();
    }
    else if(ID=="MVA80XTightRC"){
      iLep->Tight=iel->mva80XTightRC();
      iLep->Loose=iel->mva80XLooseRCIso();
    }
    else if(ID=="MVAJulieTightRC"){
      iLep->Tight=iel->mvaJulieTightRC();
      iLep->Loose=iel->mvaJulieLooseRCIso();
    }
    else if(ID=="MVAJulieNewTightRC"){
      iLep->Tight=iel->mvaJulieNewTightRC();
      iLep->Loose=iel->mvaJulieLooseRCIso();
    }
    else if(ID=="MVALooseRC"){
      iLep->Tight=iel->mvaLooseRCIso();
      iLep->Loose=true;
    }
    else if(ID=="SUSYTight"){
      iLep->Tight=iel->susyTight();
      iLep->Loose=iel->susyLoose();
    }
    else if(ID=="SUSYLoose"){
      iLep->Tight=iel->susyLoose();
      iLep->Loose=true;
    }
    else if(ID=="SUSYTightRC"){
      iLep->Tight=iel->susyTightRC();
      iLep->Loose=iel->susyLooseRC();
    }      
    
    iLep->isMu = false;
    iLep->isEl = true;
    //only save if at least loose
    if(iLep->Tight || iLep->Loose){
      //apply pt cut
      //if(iLep->pt>25 && iLep->pt<35) Leptons.push_back(iLep);
      if(iLep->pt>20){ Leptons.push_back(iLep);}
    }
  }


  return Leptons;

}

bool ZVetoCheck(TLepton* lep, std::vector<TJet*> jets){



  float diff=999;
  for(std::vector<TJet*>::size_type i=0; i< jets.size(); i++){
    TJet* ijet = jets.at(i);
    float tempmass = (lep->lv + ijet->lv).M();
    if( fabs(tempmass-91.1) <diff){
      diff = fabs(tempmass-91.1);

    }
  }

  bool veto=false;
  if(diff<10) veto=true;

  return veto;

}


bool AwayJetCheck(TLepton* lep, std::vector<TJet*> jets){

  bool awayJet=false;

  for(std::vector<TJet*>::size_type i=0; i<jets.size();i++){
    TJet* ijet = jets.at(i);
    float dr = pow( pow(lep->eta - ijet->eta,2) + pow(lep->phi - ijet->phi,2) , 0.5);
    if(ijet->pt>40 && dr>1.0){ awayJet=true; break;}
  }

  return awayJet;
}
