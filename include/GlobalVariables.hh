#ifndef GlobalVariables_h
#define GlobalVariables_h 1

#include <TFile.h>
#include <TTree.h>

#include <globals.hh>

#include "XMLObject.hh"

extern Beam *_beam;
extern StoppingTarget *_stopping_tgt;
extern StoppingTarget *_stopping_tgt2;
extern Mesh *_mesh;
extern TList *_scintillators;
extern TList *_pb_blocks;
// G4String _target_mat = "PMMA";
extern G4String _kapton_mat;  // = "kapton";
extern G4String _sciti_mat;   // = "plastic";

extern G4double _dia_kapton;    // = 0.4;
extern G4double _thick_kapton;  // = 75e-6;
// G4double _thick_target = 3.6e-3;
extern bool _exist_mesh;
extern bool _exist_target;

extern bool _exist_pbblocks;
extern G4int _pb_block_num;
extern G4int _scinti_num;
extern G4int _scinti_group_num;
extern G4int _n_target;

/////////////////////////////////////////////////////////////////////
/// Global ttree and tfiles
/////////////////////////////////////////////////////////////////////
extern TFile *ofile;
extern TTree *main_tree;
extern TTree *info_tree;
extern G4String main_tree_name;
extern G4String info_tree_name;
extern G4String write_file_name;
///////////////////////////////////////////////////////////////////////
/// TTree variables
///////////////////////////////////////////////////////////////////////

// ----- event ID -----
extern G4int event_id;

// ----- primary particle -----
extern G4int pid_in;
extern G4double ekin_in;                    // [GeV]
extern G4double posX_in, posY_in, posZ_in;  // [mm]
extern G4int vid_stop;

extern G4int start_particle_num;
extern G4int stop_kapton_particle_num;
extern G4int stop_mesh_particle_num;
extern G4int stop_air_particle_num;
extern G4int end_particle_num;
extern G4int hit_particle_num;

extern G4int pid_stop;
extern G4double ekin_stop;                        // [MeV]
extern G4double posX_stop, posY_stop, posZ_stop;  // [mm]

extern std::vector<G4int> *v_pid_sec;
extern std::vector<G4double> *v_ekin_sec;                            // [MeV]
extern std::vector<G4double> *v_dirX_sec, *v_dirY_sec, *v_dirZ_sec;  // [mm]

extern G4int pid_hit;
extern G4double ekin_hit;                      // [MeV]
extern G4double posX_hit, posY_hit, posZ_hit;  // [mm]
extern G4double dirX_hit, dirY_hit, dirZ_hit;  // [mm]
extern G4bool hitted;

// ----- energy deposit @ sensitive detector-----
extern std::vector<G4double> edep_scinti;

#endif
