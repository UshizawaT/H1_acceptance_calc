#ifndef TrackerHit_h
#define TrackerHit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TrackStatus.hh"
#include "G4VHit.hh"
#include "globals.hh"

class TrackerHit : public G4VHit {
 public:
  TrackerHit();
  ~TrackerHit();
  TrackerHit(const TrackerHit&);

  const TrackerHit& operator=(const TrackerHit&);
  G4int operator==(const TrackerHit&) const;

  inline void* operator new(size_t);
  inline void operator delete(void*);

  void Draw();
  void Print();

 public:
  void SetTrackID(G4int ti) { trackID = ti; };
  G4int GetTrackID() { return trackID; };

  void SetParentID(G4int pi) { parentID = pi; };
  G4int GetParentID() { return parentID; };

  void SetParticleName(G4String pn) { particleName = pn; };
  G4String GetParticleName() { return particleName; };

  void SetParticleID(G4int parti) { particleID = parti; };
  G4int GetParticleID() { return particleID; };

  void SetVolumeName(G4String vn) { volumeName = vn; };
  G4String GetVolumeName() { return volumeName; };

  void SetTrackStatus(G4TrackStatus ts) { trackStatus = ts; };
  G4TrackStatus GetTrackStatus() { return trackStatus; };

  void SetEnergy(G4double e) { energy = e; };
  G4double GetEnergy() { return energy; };

  void SetMomentum(G4ThreeVector mom) { momentum = mom; };
  G4ThreeVector GetMomentum() { return momentum; };

  void SetPosition(G4ThreeVector pos) { position = pos; };
  G4ThreeVector GetPosition() { return position; };

  void SetEnergyDeposit(G4double ed) { energyDeposit = ed; };
  G4double GetEnergyDeposit() { return energyDeposit; };

  void SetProcessName(G4String pn) { processName = pn; };
  G4String GetProcessName() { return processName; };

  void SetCreatorProcessName(G4String cpn) { creatorProcessName = cpn; };
  G4String GetCreatorProcessName() { return creatorProcessName; };

 private:
  G4int trackID;
  G4int parentID;
  G4int particleID;
  G4String particleName;
  G4String volumeName;
  G4TrackStatus trackStatus;
  G4double energy;  // kinetic energy
  G4ThreeVector momentum;
  G4ThreeVector position;
  G4double energyDeposit;
  G4String processName;
  G4String creatorProcessName;
};

typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

extern G4Allocator<TrackerHit> TrackerHitAllocator;

inline void* TrackerHit::operator new(size_t) {
  void* aHit;
  aHit = (void*)TrackerHitAllocator.MallocSingle();
  return aHit;
}

inline void TrackerHit::operator delete(void* aHit) {
  TrackerHitAllocator.FreeSingle((TrackerHit*)aHit);
}

#endif
