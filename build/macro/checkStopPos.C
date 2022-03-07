int inputs = 0;
int hitnum = 0;
int stopnum = 0;
vector<int> vol_ids;
vector<double> edeps1, edeps2;
// TH1D *stop_vol = new TH1D("stopped_vol", "stopped_vol.", 4, 0., 3.);

void registerHitInfo(TString filename) {
  TFile *rfile = new TFile(filename, "read");
  TTree *rtree = (TTree *)rfile->Get("tree");
  TTree *rinfo = (TTree *)rfile->Get("info");
  // TH1D *edep1 = new TH1D();
  bool hit_;
  int pid_hit_, vid_stop_;
  int input_, stopped_;
  double edeps_[2];
  rinfo->SetBranchAddress("start_particle_num", &input_);
  rinfo->SetBranchAddress("end_particle_num", &stopped_);
  rinfo->GetEntry(0);
  inputs += input_;
  stopnum += stopped_;
  // rtree->SetBranchAddress("hitted", &hit_);
  // rtree->SetBranchAddress("pid_hit", &pid_hit_);
  rtree->SetBranchAddress("vid_stop", &vid_stop_);
  rtree->SetBranchAddress("edep_scinti", edeps_);
  int nentries = rtree->GetEntries();
  for (int i = 0; i < nentries; ++i) {
    rtree->GetEntry(i);
    if (hit_ && pid_hit_ == -11) {  // e+ : -11
      hitnum += 1;
      // cout<<"stopped vol. : "<<vid_stop_<<endl;
      // cout<<"edep_scinti : "<<edeps_[0]<<endl;
      // cout<<"edep_scinti : "<<edeps_[1]<<endl;
      edeps1.push_back(edeps_[0]);
      edeps2.push_back(edeps_[1]);
      vol_ids.push_back(vid_stop_);
    }
  }
}

void loadFiles(int angle, int sigma, int endseed, TString basename) {
  TString filename, seedtxt, angletxt, bsizetxt;
  angletxt.Form("_target-angle%d", angle);
  bsizetxt.Form("_beam-size%d", sigma);
  int seeds = endseed + 1;
  for (int i = 1; i < seeds; ++i) {
    // acceptance_seed9_target-angle45_beam-size0.root
    seedtxt.Form("_seed%d", i);
    filename = basename;
    filename += seedtxt;
    filename += angletxt;
    filename += bsizetxt;
    filename += ".root";
    registerHitInfo(filename);
  }
}

void drawHist() {
  cout << "Hit number / input : " << hitnum << "/" << inputs << endl;
  cout << "Stopped num : " << stopnum << endl;
  TH1I *stop_vol = new TH1I("stopped_vol", "stopped_vol", 8, 0., 4.);
  TH1D *hist_edeps1 = new TH1D("edep1", "edep1", 40, 0, 1000);
  TH1D *hist_edeps2 = new TH1D("edep2", "edep2", 40, 0, 1000);
  int n = vol_ids.size();
  for (int i = 0; i < n; ++i) {
    hist_edeps1->Fill(edeps1[i]);
    hist_edeps2->Fill(edeps2[i]);
    // cout<<"stopped id : "<<vol_ids[i]<<endl;
    stop_vol->Fill(vol_ids[i]);
  }
  stop_vol->SetTitle(
      "Muon Stopped;Stopped volume ID (1:Air, 2:Kapton, 3:Stopping target);Hit "
      "#");
  hist_edeps1->SetTitle("energy deposit;Energy [keV];Hit #");
  TCanvas *tc = new TCanvas("result", "result", 1200, 600);
  tc->Divide(2, 1);
  tc->cd(1);
  stop_vol->Draw();
  tc->cd(2);
  hist_edeps1->Draw();
  hist_edeps2->SetLineColor(2);
  hist_edeps2->Draw("same");
}