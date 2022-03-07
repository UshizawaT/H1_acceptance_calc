int inputs=0;
int hitnum=0;
int stopnum=0;
int kapton_stop = 0;
vector<int> vol_ids;
vector<double> edeps1, edeps2;
TH1D *hist_eP = new TH1D("kinetic_energy", "kinetic_ebergy", 100, 0, 100);
TString outputname;
TFile *output;

void registerHitInfo(TString filename){
  TFile *rfile = new TFile(filename, "read");
  TTree *rtree = (TTree*)rfile->Get("tree");
  TTree *rstree = (TTree*)rfile->Get("positron");
  TTree *rinfo = (TTree*)rfile->Get("info");
  //TH1D *edep1 = new TH1D();
  bool hit_;
  int pid_hit_, vid_stop_;
  int input_, stopped_, kstop_;
  double edeps_[2];
  vector<int> *epid=0;
  vector<double> *ePx=0, *ePy=0, *ePz=0, *eE=0;
  rinfo->SetBranchAddress("start_particle_num", &input_);
  rinfo->SetBranchAddress("transient_particle_num", &kstop_);
  rinfo->SetBranchAddress("end_particle_num", &stopped_); 
  rinfo->GetEntry(0);
  inputs+=input_;
  kapton_stop += kstop_;
  stopnum+=stopped_;
  rtree->SetBranchAddress("hitted", &hit_);
  rtree->SetBranchAddress("pid_hit", &pid_hit_);
  rtree->SetBranchAddress("vid_stop", &vid_stop_);
  rtree->SetBranchAddress("edep_scinti", edeps_);
  rtree->SetBranchAddress("v_pid_sec", &epid);
  rtree->SetBranchAddress("v_ekin_sec", &eE);
  int nentries = rtree->GetEntries();
  int sec_num;
  for(int i=0;i<nentries;++i){
    rtree->GetEntry(i);
    if(hit_ && pid_hit_==-11){//e+ : -11
      hitnum+=1;
      //cout<<"stopped vol. : "<<vid_stop_<<endl;
      //cout<<"edep_scinti : "<<edeps_[0]<<endl;
      //cout<<"edep_scinti : "<<edeps_[1]<<endl;
      edeps1.push_back(edeps_[0]);
      edeps2.push_back(edeps_[1]); 
      vol_ids.push_back(vid_stop_);
    }
    sec_num = epid->size();
    for(int j=0; j<sec_num; ++j){
       if(epid->at(j) == -11){
        hist_eP->Fill(eE->at(j));
      }
    }
  }
}

void loadFiles(int angle, int sigma, TString source, TString mat, int startseed, int endseed, TString basename){
  TString filename, seedtxt, angletxt, bsizetxt;
  angletxt.Form("_target-angle%d", angle);
  bsizetxt.Form("_beam-size%d", sigma);
  int seeds = endseed+1;
  for(int i=startseed;i<seeds;++i){
//acceptance_seed9_target-angle45_beam-size0.root
    seedtxt.Form("_seed%d", i);
    filename = basename;
    filename += seedtxt;
    filename += angletxt;
    filename += bsizetxt;
    filename += "_beam-type_";
    filename += source;
    filename += "_stptgt_";
    filename += mat;
    filename += ".root";
    registerHitInfo(filename);
  }
  outputname = (basename + angletxt + bsizetxt +"_"+source+"_"+mat+ "_ana.root");
}

void drawHist(TFile *wfile){
  cout<<"Hit number / input : "<<hitnum<<"/"<<inputs<<endl;
  cout<<"Stopped kapton, Final stopped num : "<<kapton_stop<<", "<<stopnum<<endl;
  TH1I *stop_vol = new TH1I("stopped_vol", "stopped_vol", 8, 0., 4.);
  TH1D *hist_edeps1 = new TH1D("edep1","edep1", 40, 0, 1000);
  TH1D *hist_edeps2 = new TH1D("edep2","edep2", 40, 0, 1000);
  int n = vol_ids.size();
  for(int i=0; i<n; ++i){
    hist_edeps1->Fill(edeps1[i]);
    hist_edeps2->Fill(edeps2[i]);
    //cout<<"stopped id : "<<vol_ids[i]<<endl;
    stop_vol->Fill(vol_ids[i]);
  }
  stop_vol->SetTitle("Muon Stopped;Stopped volume ID (1:Air, 2:Kapton, 3:Stopping target);Hit #");
  hist_edeps1->SetTitle("energy deposit;Energy [keV];Hit #");
  TCanvas *tc = new TCanvas("result","result",1800, 600);
  tc->Divide(3,1);
  tc->cd(1);
  stop_vol->Draw();
  tc->cd(2);
  hist_edeps1->Draw();
  hist_edeps2->SetLineColor(2);
  hist_edeps2->Draw("same");
  tc->cd(3);
  hist_eP->SetTitle("Decay positron;Kinetic energy [GeV];positron #");
  hist_eP->Draw();
  wfile->cd();
  stop_vol->Write();
  hist_edeps1->Write();
  hist_edeps2->Write();
  hist_eP->Write();
  tc->Write();
}

void analysis_simu(int angle, int sigma, TString source, TString mat, int startseed, int endseed, TString basename){
  loadFiles(angle, sigma, source, mat, startseed, endseed, basename);
  output = new TFile(outputname, "recreate");
  drawHist(output);
}
