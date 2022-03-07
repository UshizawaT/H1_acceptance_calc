#include "GlobalVariables.hh"

// using namespace CLHEP;

Beam *_beam;
StoppingTarget *_stopping_tgt;
StoppingTarget *_stopping_tgt2;
Mesh *_mesh;
TList *_pb_blocks;
TList *_scintillators;

G4String _kapton_mat = "kapton";
G4String _sciti_mat = "plastic";

G4double _dia_kapton = 0.4;
G4double _thick_kapton = 75e-6;

G4int _pb_block_num = 2;
bool _exist_mesh = false;
bool _exist_target = false;

bool _exist_pbblocks = false;
G4int _scinti_num = 2;
G4int _scinti_group_num = 1;
G4int _n_target = 0;

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
