#ifndef RootManager_h
#define RootManager_h 1

#include <globals.hh>

#include "DataManager.hh"
#include "GlobalVariables.hh"

namespace RootManager {

inline void SetFileName(G4String name) { write_file_name = name; }
inline G4String GetFileName() { return write_file_name; }
inline void SetTreeName(G4String name) { main_tree_name = name; }
inline G4String GetTreeName() { return main_tree_name; }
inline void SetInfoTreeName(G4String name) { info_tree_name = name; }
inline G4String GetInfoTreeName() { return info_tree_name; }
inline void CreateFile() {
  ofile = new TFile(write_file_name, "recreate", write_file_name, 505);
}
inline void CreateTree() {
  main_tree = new TTree(main_tree_name, main_tree_name);
}
inline void CreateInfoTree() {
  info_tree = new TTree(info_tree_name, info_tree_name);
}
inline void SetTree() {
  // G4cerr << "start set tree" << G4endl;
  //  ---- for final results ----
  info_tree->Branch("start_particle_num", &(start_particle_num),
                    "start_particle_num/I");
  info_tree->Branch("stop_kapton_particle_num", &(stop_kapton_particle_num),
                    "stop_kapton_particle_num/I");
  info_tree->Branch("stop_mesh_particle_num", &(stop_mesh_particle_num),
                    "stop_mesh_particle_num/I");
  info_tree->Branch("stop_air_particle_num", &(stop_air_particle_num),
                    "stop_air_particle_num/I");
  info_tree->Branch("end_particle_num", &(end_particle_num),
                    "end_particle_num/I");
  info_tree->Branch("hit_particle_num", &(hit_particle_num),
                    "hit_particle_num/I");

  ///////////////////////////////////////////
  // ----- event ID -----
  main_tree->Branch("event_id", &(event_id), "event_id/I");
  // ----- primary particle -----
  main_tree->Branch("pid_in", &(pid_in), "pid_in/I");
  main_tree->Branch("ekin_in", &(ekin_in), "ekin_in/D");
  main_tree->Branch("posX_in", &(posX_in), "posX_in/D");
  main_tree->Branch("posY_in", &(posY_in), "posY_in/D");
  main_tree->Branch("posZ_in", &(posZ_in), "posZ_in/D");
  // ----- secondary particle -----
  main_tree->Branch("v_pid_sec", "vector<int>", &(v_pid_sec));

  main_tree->Branch("v_ekin_sec", "vector<double>", &(v_ekin_sec));
  main_tree->Branch("v_dirX_sec", "vector<double>", &(v_dirX_sec));
  main_tree->Branch("v_dirY_sec", "vector<double>", &(v_dirY_sec));
  main_tree->Branch("v_dirZ_sec", "vector<double>", &(v_dirZ_sec));
  // ---- stopped volume id ----
  // 1 : air, 2 : kapton winndow, 3 : stopping target
  main_tree->Branch("vid_stop", &(vid_stop), "vid_stop/I");
  main_tree->Branch("pid_stop", &(pid_stop), "pid_stop/I");
  main_tree->Branch("posX_stop", &(posX_stop), "posX_stop/D");
  main_tree->Branch("posY_stop", &(posY_stop), "posY_stop/D");
  main_tree->Branch("posZ_stop", &(posZ_stop), "posZ_stop/D");
  // ---- hit scinti. ----
  main_tree->Branch("pid_hit", &(pid_hit), "pid_hit/I");
  main_tree->Branch("ekin_hit", &(ekin_hit), "ekin_hit/D");
  main_tree->Branch("posX_hit", &(posX_hit), "posX_hit/D");
  main_tree->Branch("posY_hit", &(posY_hit), "posY_hit/D");
  main_tree->Branch("posZ_hit", &(posZ_hit), "posZ_hit/D");
  main_tree->Branch("hitted", &(hitted), "hitted/O");
  main_tree->Branch("edep_scinti", &(edep_scinti));
  // G4cerr << "success set tree" << G4endl;
}
inline void rootFinalize() {
  main_tree->Write();
  std::cout << "Success write main tree" << std::endl;
  info_tree->Fill();
  DataManager::ClearInfo();
  info_tree->Write();
  std::cout << "Success write info tree" << std::endl;
  ofile->Write();
  std::cout << "Success write file" << std::endl;
  ofile->Delete("*;1");
  ofile->Close();
  std::cout << "Success close file" << std::endl;
}

}  // namespace RootManager

#endif
