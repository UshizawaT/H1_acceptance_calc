#ifndef BASETUBS_HH
#define BASETUBS_HH 1

#include <G4PVPlacement.hh>
#include <G4Tubs.hh>

#include "BaseConstruct.hh"

class BaseTubs : public BaseConstruct {
 public:
  BaseTubs(TString _name, int _id, TString _material_name, G4ThreeVector _size,
           G4ThreeVector _position, double _angle, TString _color)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle,
                      _color) {}
  BaseTubs(G4LogicalVolume *_parent, TString _name, int _id,
           TString _material_name, G4ThreeVector _size, G4ThreeVector _position,
           double _angle, TString _color)
      : BaseConstruct(_parent, _name, _id, _material_name, _size, _position,
                      _angle, _color) {}
  virtual void SetGeometry();
  virtual void SetWGeometry();
};
#endif  // !BASETUBS_HH