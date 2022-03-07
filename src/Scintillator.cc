#include "Scintillator.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

Scintillator::Scintillator(G4String name) : G4VSensitiveDetector(name) {
  sdname = name;
  collectionName.insert("ScintiHitsCollection");
  HCID = -1;
}

Scintillator::~Scintillator() {
  G4cerr << "destractor of scintillator" << G4endl;
}

void Scintillator::Initialize(G4HCofThisEvent* HCE) {
  if (HCID < 0) HCID = GetCollectionID(0);

  hitsCollection = new TrackerHitsCollection(sdname, collectionName[0]);

  HCE->AddHitsCollection(HCID, hitsCollection);
}

G4bool Scintillator::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
  G4Track* aTrack = aStep->GetTrack();

  TrackerHit* newHit = new TrackerHit();

  newHit->SetTrackID(aTrack->GetTrackID());
  newHit->SetParentID(aTrack->GetParentID());
  newHit->SetParticleName((aTrack->GetDefinition())
                              ? (aTrack->GetDefinition()->GetParticleName())
                              : ("NONE"));
  newHit->SetParticleID(aTrack->GetDynamicParticle()->GetPDGcode());
  newHit->SetVolumeName((aTrack->GetVolume()) ? (aTrack->GetVolume()->GetName())
                                              : ("NONE"));
  newHit->SetTrackStatus(aTrack->GetTrackStatus());
  newHit->SetEnergy(aTrack->GetKineticEnergy());
  newHit->SetMomentum(aTrack->GetMomentum());
  newHit->SetPosition(aTrack->GetPosition());
  newHit->SetEnergyDeposit(aStep->GetTotalEnergyDeposit());

  newHit->SetProcessName("NONE");
  if (G4StepPoint* postStepPoint = aStep->GetPostStepPoint()) {
    if (const G4VProcess* process = postStepPoint->GetProcessDefinedStep()) {
      if (G4String processName = process->GetProcessName()) {
        newHit->SetProcessName(processName);
      }
    }
  }

  newHit->SetCreatorProcessName("NONE");
  if (const G4VProcess* creatorProcess = aTrack->GetCreatorProcess()) {
    if (G4String creatorProcessName = creatorProcess->GetProcessName()) {
      newHit->SetCreatorProcessName(creatorProcessName);
    }
  }

  hitsCollection->insert(newHit);

  // newHit->Print();
  // newHit->Draw();

  return true;
}

void Scintillator::EndOfEvent(G4HCofThisEvent*) {}
