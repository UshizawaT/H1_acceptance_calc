#ifndef KAPTON_HH
#define KAPTON_HH 1

#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"

class Kapton : public BaseConstruct {
 public:
  Kapton(TString _name, int _id, TString _material_name, G4ThreeVector _size,
         G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
  void SetGeometry(G4LogicalVolume *_parent, G4String color_name);
};
#endif  // !KAPTON_HH