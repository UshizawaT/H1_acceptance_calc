#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class EventAction : public G4UserEventAction {
 public:
  EventAction();
  virtual ~EventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

 private:
  // G4int* hitflag;
  // G4int* coinciflag;
  G4bool writeflag = false;
  G4int scintigid = 0;
  G4String particle_name;
  std::vector<G4int> hitflag, coinciflag, scintis_gid;
};

#endif
