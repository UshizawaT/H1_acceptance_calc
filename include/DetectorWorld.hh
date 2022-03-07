#ifndef WORLD_HH
#define WORLD_HH 1

#include <G4Box.hh>
#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"

class DetectorWorld : public BaseConstruct {
 public:
  DetectorWorld(TString _name, int _id, TString _material_name,
                G4ThreeVector _size, G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
  void SetGeometry();
  G4LogicalVolume *GetLogicalVol() { return logvol; };
};
#endif  // !WORLD_HH