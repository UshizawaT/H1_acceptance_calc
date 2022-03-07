#include "SteppingAction.hh"

#include "DataManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "GlobalVariables.hh"

using namespace CLHEP;

SteppingAction::SteppingAction() : G4UserSteppingAction() {
  btype = _beam->GetBeamType();
  G4cerr << "constractor of stepping action" << G4endl;
}

SteppingAction::~SteppingAction() {
  G4cerr << "destractor of stepping action" << G4endl;
}

void SteppingAction::UserSteppingAction(const G4Step* theStep) {
  // DetectorConstruction *detectorconstruct =
  // DetectorConstruction::DetectorConstruction();

  G4Track* theTrack = theStep->GetTrack();

  G4ThreeVector position = theTrack->GetPosition();
  G4ThreeVector direction = theTrack->GetMomentumDirection();
  G4String volume_name = theTrack->GetVolume()->GetName();
  G4int _pid = theTrack->GetDynamicParticle()->GetPDGcode();
  G4StepPoint* pre_step_point = theStep->GetPreStepPoint();
  G4StepPoint* post_step_point = theStep->GetPostStepPoint();
  G4int parentid = theTrack->GetParentID();
  G4ParticleDefinition* particleDefinition = theTrack->GetDefinition();
  if (particleDefinition->GetParticleName() == btype) {
    if (theTrack->GetTrackStatus() == fStopButAlive) {
      if (volume_name.find("Kapton_window") != G4String::npos) {
        vid_stop = 2;
        stop_kapton_particle_num += 1;
      } else if (volume_name.find("Muon_stopping_target") != G4String::npos) {
        vid_stop = 3;
        end_particle_num += 1;
      } else if (volume_name.find("VWire_") != G4String::npos ||
                 volume_name.find("HWire_") != G4String::npos) {
        vid_stop = 4;
        stop_mesh_particle_num += 1;
      } else if (volume_name.find("World") != G4String::npos) {
        vid_stop = 1;
        stop_air_particle_num += 1;
      }
      pid_stop = _pid;
      ekin_stop = theTrack->GetKineticEnergy() / MeV;
      posX_stop = position.getX();
      posY_stop = position.getY();
      posZ_stop = position.getZ();
    }

    if (post_step_point->GetProcessDefinedStep()->GetProcessName() == "Decay") {
      const G4TrackVector* track_sec = theStep->GetSecondary();
      G4int track_n, s_pid;
      G4Track* secTrack;
      G4ThreeVector s_position;
      G4ThreeVector s_direction;
      track_n = track_sec->size();
      for (int i = 0; i < track_n; ++i) {
        secTrack = track_sec->at(i);
        s_position = secTrack->GetPosition();
        s_direction = secTrack->GetMomentumDirection();
        s_pid = secTrack->GetDynamicParticle()->GetPDGcode();
        v_pid_sec->emplace_back(s_pid);
        v_ekin_sec->emplace_back(secTrack->GetKineticEnergy() / MeV);
        v_dirX_sec->emplace_back(s_direction.getX());
        v_dirY_sec->emplace_back(s_direction.getY());
        v_dirZ_sec->emplace_back(s_direction.getZ());
      }
    }
  }
}
