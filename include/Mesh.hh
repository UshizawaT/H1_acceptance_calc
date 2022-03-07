#ifndef MESH_HH
#define MESH_HH 1

#include <G4PVParameterised.hh>
#include <G4VPVParameterisation.hh>

#include "BaseConstruct.hh"
#include "G4Tubs.hh"
#include "MeshParam.hh"

class Mesh : public BaseConstruct {
 public:
  Mesh(TString _name, int _id, TString _material_name, G4ThreeVector _size,
       G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
  void SetGeometry(G4LogicalVolume *_parent, G4String color_name);

 private:
  G4Tubs *wire_solid;
};
#endif  // !MESH_HH