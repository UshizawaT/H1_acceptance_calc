#ifndef Scintillator_h
#define Scintillator_h 1
 
#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "TrackerHit.hh"
 
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class Scintillator : public G4VSensitiveDetector
{

  public:

      Scintillator(G4String);
      virtual ~Scintillator();
 
      virtual void Initialize(G4HCofThisEvent*);
      virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      virtual void EndOfEvent(G4HCofThisEvent*);

  private:

      TrackerHitsCollection* hitsCollection;
      G4String sdname;
      G4int HCID;

};

#endif
