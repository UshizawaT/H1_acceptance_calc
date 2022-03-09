#include "GlobalVariables.hh"

// using namespace CLHEP;

Beam *_beam;

std::vector<G4int> _scinti_group_ids;
G4int _scinti_num = 0;
G4int _scinti_group_num = 0;

/////////////////////////////////////////////////////////////////////
/// Global ttree
/////////////////////////////////////////////////////////////////////
TFile *ofile;
TTree *main_tree;
TTree *info_tree;
G4String main_tree_name;
G4String info_tree_name;
G4String write_file_name;

//////////////////////////////////////////////////////////////////////
/// TTree variables
//////////////////////////////////////////////////////////////////////

// ----- event ID -----
G4int event_id;

// ----- primary particle -----
G4int pid_in;
G4double ekin_in;                    // [GeV]
G4double posX_in, posY_in, posZ_in;  // [mm]
G4int vid_stop;

G4int start_particle_num;
G4int stop_kapton_particle_num;
G4int stop_mesh_particle_num;
G4int stop_air_particle_num;
G4int end_particle_num;
G4int hit_particle_num;

G4int pid_stop;
G4double ekin_stop;                        // [MeV]
G4double posX_stop, posY_stop, posZ_stop;  // [mm]

std::vector<G4int> *v_pid_sec;
std::vector<G4double> *v_ekin_sec;                            // [MeV]
std::vector<G4double> *v_dirX_sec, *v_dirY_sec, *v_dirZ_sec;  // [mm]

G4int pid_hit;
G4double ekin_hit;                      // [MeV]
G4double posX_hit, posY_hit, posZ_hit;  // [mm]
G4double dirX_hit, dirY_hit, dirZ_hit;  // [mm]
G4bool hitted;

// ----- energy deposit @ sensitive detector-----
std::vector<G4double> edep_scinti;
