#ifndef VACUUMV_HH
#define VACUUMV_HH 1

#include <G4Box.hh>
#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"

class VacuumVolume : public BaseConstruct {
 public:
  VacuumVolume(TString _name, int _id, TString _material_name,
               G4ThreeVector _size, G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
  G4LogicalVolume *GetLogicalVol() { return logvol; };
  void SetGeometry(G4LogicalVolume *_parent, G4String color_name);
};
#endif  // !VACUUMV_HH