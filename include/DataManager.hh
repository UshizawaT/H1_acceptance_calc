#ifndef DataManager_h
#define DataManager_h 1

#include <globals.hh>
#include <vector>

#include "GlobalVariables.hh"

namespace DataManager {

inline void Clear() {
  event_id = 0;
  pid_in = 0;
  ekin_in = 0;
  posX_in = 0;
  posY_in = 0;
  posZ_in = 0;

  v_pid_sec->clear();
  v_ekin_sec->clear();
  v_dirX_sec->clear();
  v_dirY_sec->clear();
  v_dirZ_sec->clear();

  vid_stop = 0;
  pid_stop = 0;
  ekin_stop = 0;
  posX_stop = 0;
  posY_stop = 0;
  posZ_stop = 0;

  pid_hit = 0;
  ekin_hit = 0;
  posX_hit = 0;
  posY_hit = 0;
  posZ_hit = 0;
  dirX_hit = 0;
  dirY_hit = 0;
  dirZ_hit = 0;
  hitted = false;

  for (int i = 0; i < _scinti_num; ++i) edep_scinti[i] = 0.0;
}

inline void Initialize() {
  event_id = 0;
  pid_in = 0;
  ekin_in = 0;
  posX_in = 0;
  posY_in = 0;
  posZ_in = 0;

  vid_stop = 0;
  pid_stop = 0;
  ekin_stop = 0;
  posX_stop = 0;
  posY_stop = 0;
  posZ_stop = 0;

  pid_hit = 0;
  ekin_hit = 0;
  posX_hit = 0;
  posY_hit = 0;
  posZ_hit = 0;
  dirX_hit = 0;
  dirY_hit = 0;
  dirZ_hit = 0;
  hitted = false;

  start_particle_num = 0;
  stop_kapton_particle_num = 0;
  stop_mesh_particle_num = 0;
  stop_air_particle_num = 0;
  end_particle_num = 0;
  hit_particle_num = 0;
}

inline void DeleteVar() {
  delete _beam;
  delete _stopping_tgt;
  delete _scintillators;
  delete _pb_blocks;
  delete v_pid_sec;
  delete v_ekin_sec;
  delete v_dirX_sec;
  delete v_dirY_sec;
  delete v_dirZ_sec;
}

inline void ClearInfo() {
  start_particle_num = 0;
  stop_kapton_particle_num = 0;
  stop_mesh_particle_num = 0;
  stop_air_particle_num = 0;
  end_particle_num = 0;
  hit_particle_num = 0;
};

}  // namespace DataManager

#endif
