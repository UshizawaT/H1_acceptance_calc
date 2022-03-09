#ifndef MESH_HH
#define MESH_HH 1

#include <G4PVParameterised.hh>
#include <G4VPVParameterisation.hh>

#include "BaseConstruct.hh"
#include "G4Tubs.hh"
#include "MeshParam.hh"

class Mesh : public BaseConstruct {
 public:
  Mesh(G4LogicalVolume *_parent, TString _name, int _id, TString _material_name,
       G4ThreeVector _size, G4ThreeVector _position, double _angle,
       TString _color)
      : BaseConstruct(_parent, _name, _id, _material_name, _size, _position,
                      _angle, _color) {}
  void SetGeometry();
};
#endif  // !MESH_HH