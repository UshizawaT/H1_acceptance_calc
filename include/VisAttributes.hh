#ifndef VisAttributes_h
#define VisAttributes_h 1

#include "G4VisAttributes.hh"
#include "globals.hh"

class VisAttributes {
 public:
  VisAttributes();
  ~VisAttributes();

  G4VisAttributes GetInvisible() const { return invisible; };
  G4VisAttributes* GetVisAttributes(const G4String&,
                                    const G4String& option = "") const;

 private:
  G4VisAttributes invisible;

  G4VisAttributes* white;
  G4VisAttributes* gray;
  G4VisAttributes* light_gray;
  G4VisAttributes* black;
  G4VisAttributes* red;
  G4VisAttributes* green;
  G4VisAttributes* blue;
  G4VisAttributes* cyan;
  G4VisAttributes* magenta;
  G4VisAttributes* yellow;
};

#endif
