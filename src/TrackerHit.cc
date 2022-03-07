#include "TrackerHit.hh"

#include "G4Allocator.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"

using namespace CLHEP;

G4Allocator<TrackerHit> TrackerHitAllocator;

TrackerHit::TrackerHit() {}

TrackerHit::~TrackerHit() {}

TrackerHit::TrackerHit(const TrackerHit& right) : G4VHit() {
  trackID = right.trackID;
  parentID = right.parentID;
  particleName = right.particleName;
  particleID = right.particleID;
  volumeName = right.volumeName;
  trackStatus = right.trackStatus;
  energy = right.energy;
  momentum = right.momentum;
  position = right.position;
  energyDeposit = right.energyDeposit;
  processName = right.processName;
  creatorProcessName = right.creatorProcessName;
}

const TrackerHit& TrackerHit::operator=(const TrackerHit& right) {
  trackID = right.trackID;
  parentID = right.parentID;
  particleName = right.particleName;
  particleID = right.particleID;
  volumeName = right.volumeName;
  trackStatus = right.trackStatus;
  energy = right.energy;
  momentum = right.momentum;
  position = right.position;
  energyDeposit = right.energyDeposit;
  processName = right.processName;
  creatorProcessName = right.creatorProcessName;

  return *this;
}

G4int TrackerHit::operator==(const TrackerHit& right) const {
  return (this == &right) ? 1 : 0;
}

void TrackerHit::Draw() {
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if (pVVisManager) {
    G4Circle circle(position);
    circle.SetScreenSize(5.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.0, 0.0, 1.0);  // magenta
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void TrackerHit::Print() {
  G4cout << "  trackID              : " << trackID << G4endl;
  G4cout << "  parentID             : " << parentID << G4endl;
  G4cout << "  particleName         : " << particleName << G4endl;
  G4cout << "  volumeName           : " << volumeName << G4endl;
  G4cout << "  trackStatus          : " << trackStatus << G4endl;
  G4cout << "  energy               : " << G4BestUnit(energy, "Energy")
         << G4endl;
  G4cout << "  momentum             : " << momentum << G4endl;
  G4cout << "  position             : " << G4BestUnit(position, "Length")
         << G4endl;
  G4cout << "  energyDeposit        : " << G4BestUnit(energyDeposit, "Energy")
         << G4endl;
  G4cout << "  processName          : " << processName << G4endl;
  G4cout << "  creatorProcessName   : " << creatorProcessName << G4endl;
  G4cout << G4endl;
}
