#ifndef SCINTIOBJ_HH
#define SCINTIOBJ_HH 1

#include <G4Box.hh>
#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"
#include "Scintillator.hh"

class ScintillatorObject : public BaseConstruct {
 public:
  ScintillatorObject(TString _name, int _id, int _gid, TString _material_name,
                     G4ThreeVector _size, G4ThreeVector _position,
                     double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle),
        groupid(_gid) {}
  G4int GetScintiId() { return vol_id; }
  G4int GetScintiGroupId() { return groupid; }

 private:
  G4Box *scinti_solid;
  G4int groupid;
};
#endif  // !SCINTIOBJ_HH