#include "BaseConstruct.hh"

BaseConstruct::BaseConstruct(TString _name, int _id, TString _material_name,
                             G4ThreeVector _size, G4ThreeVector _position,
                             double _ang) {
  indivisual_name = _name;
  vol_id = _id;
  material_name = _material_name;
  physical_size = _size;
  position = _position * mm;
  angle = _ang;
}

void BaseConstruct::Initialize(Material *mat, VisAttributes *vis) {
  _material = mat;
  _visattributes = vis;
}

void BaseConstruct::SetGeometry(G4LogicalVolume *_parent, G4String color_name) {
  indivisual_name += vol_id;
  solid = new G4Box(indivisual_name, physical_size.x() / 2. * mm,
                    physical_size.y() / 2. * mm, physical_size.z() / 2. * mm);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
  logvol->SetVisAttributes(_visattributes->GetVisAttributes(color_name));
  G4RotationMatrix rotation_matrix;
  rotation_matrix.rotateY(-(90 - angle) * deg);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, _parent,
                              false, 0, true);
}

void BaseConstruct::SetGeometry(G4LogicalVolume *_parent, Scintillator *_scinti,
                                G4String color_name) {
  indivisual_name += vol_id;
  solid = new G4Box(indivisual_name, physical_size.x() / 2. * mm,
                    physical_size.y() / 2. * mm, physical_size.z() / 2. * mm);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
  logvol->SetSensitiveDetector(_scinti);
  logvol->SetVisAttributes(_visattributes->GetVisAttributes(color_name));
  G4RotationMatrix rotation_matrix;
  rotation_matrix.rotateY(-(90 - angle) * deg);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, _parent,
                              false, 0, true);
}

BaseConstruct::~BaseConstruct() {
  delete logvol;
  delete physvol;
}