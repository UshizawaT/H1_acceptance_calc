#include "EventAction.hh"

#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4TrackStatus.hh>

#include "DataManager.hh"
#include "GlobalVariables.hh"
#include "RootManager.hh"
#include "TrackerHit.hh"

using namespace CLHEP;

EventAction::EventAction() {
  hitflag.resize(_scinti_group_num);
  coinciflag.resize(_scinti_group_num);
  G4int gid_1;
  scintis_gid = _scinti_group_ids;
  edep_scinti.resize(_scinti_num);
  for (int i = 0; i < _scinti_num; ++i) {
    gid_1 = scintis_gid[i];
    edep_scinti[i] = 0.0;
    coinciflag[gid_1] |= (1 << i);
  }
  G4cerr << "constractor of event act." << G4endl;
}

EventAction::~EventAction() {
  G4cerr << "destractor of event action" << G4endl;
}

void EventAction::BeginOfEventAction(const G4Event* anEvent) {}

void EventAction::EndOfEventAction(const G4Event* anEvent) {
  event_id = anEvent->GetEventID();
  writeflag = false;
  for (int i = 0; i < _scinti_group_num; ++i) {
    hitflag[i] = 0;
  }

  static G4int ScintiHCID = -1;
  if (ScintiHCID < 0)
    ScintiHCID =
        G4SDManager::GetSDMpointer()->GetCollectionID("ScintiHitsCollection");

  G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();
  TrackerHitsCollection* ScintiHC = 0;

  if (HCE) {
    ScintiHC = (TrackerHitsCollection*)(HCE->GetHC(ScintiHCID));
  }

  if (ScintiHC) {
    G4int NbHits = ScintiHC->entries();

    for (G4int i = 0; i < NbHits; i++) {
      TrackerHit* hit = (*ScintiHC)[i];
      G4String volumeName = hit->GetVolumeName();
      G4double edep = hit->GetEnergyDeposit();
      G4String particleName = hit->GetParticleName();
      G4int trackID = hit->GetTrackID();
      G4int parentID = hit->GetParentID();
      G4int pID = hit->GetParticleID();
      G4TrackStatus trackStatus = hit->GetTrackStatus();
      G4String processName = hit->GetProcessName();
      G4String creatorProcessName = hit->GetCreatorProcessName();
      G4ThreeVector position = hit->GetPosition();
      G4ThreeVector momentum = hit->GetMomentum();
      G4double ekin = hit->GetEnergy();

      for (G4int j = 0; j < _scinti_num; j++) {
        char s_tmp[100];
        sprintf(s_tmp, "Scinti_%d", j);
        if (volumeName.find(s_tmp) != G4String::npos) {
          edep_scinti[j] += edep / keV;
          scintigid = scintis_gid[j];
          ekin_hit = ekin / MeV;
          posX_hit = (position.getX());
          posY_hit = (position.getY());
          posZ_hit = (position.getZ());
          pid_hit = (pID);
          if (abs(edep) > 0) {
            hitflag[scintigid - 1] |= (1 << j);
          }
          particle_name = particleName;
        }
      }
    }
  }

  for (int i = 0; i < _scinti_group_num; ++i) {
    if ((hitflag[i] & coinciflag[i]) == coinciflag[i]) {
      G4cerr << "hitflag : " << hitflag[i] << G4endl;
      G4cerr << "Hit : " << particle_name << G4endl;
      hitted = true;
      hit_particle_num += 1;
      writeflag = true;
    }
  }

  if ((event_id + 1) % 1000 == 0) {
    writeflag = true;
  }
  if (writeflag) {
    main_tree->Fill();
  }

  // event_id
  // G4cerr << "Event_id : " << event_id << G4endl;
  if ((event_id + 1) % 1000000 == 0) {
    G4cerr << "Event_id : " << event_id << G4endl;
  }
  //  rootManager->tree->Fill();
  DataManager::Clear();
}
