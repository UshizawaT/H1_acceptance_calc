#include "BaseBox.hh"

BaseBox::BaseBox(TString _name, int _id, TString _material_name,
                 G4ThreeVector _size, G4ThreeVector _position, double _ang,
                 TString _color)
    : BaseConstruct(_name, _id, _material_name, _size, _position, _ang,
                    _color) {
  sdflag = false;
}

BaseBox::BaseBox(G4LogicalVolume *_parent, TString _name, int _id,
                 TString _material_name, G4ThreeVector _size,
                 G4ThreeVector _position, double _ang, TString _color)
    : BaseConstruct(_parent, _name, _id, _material_name, _size, _position, _ang,
                    _color) {
    sdflag = false;
}

BaseBox::BaseBox(G4LogicalVolume *_parent, Scintillator *_scinti, TString _name,
                 int _id, int _groupid, TString _material_name,
                 G4ThreeVector _size, G4ThreeVector _position, double _ang,
                 TString _color)
    : BaseConstruct(_parent, _name, _id, _material_name, _size, _position, _ang,
                    _color),
      scinti(_scinti),
      groupid(_groupid) {
  sdflag = true;
}

void BaseBox::SetGeometry() {
  indivisual_name += vol_id;
  solid = new G4Box(indivisual_name, physical_size.x() / 2. * mm,
                    physical_size.y() / 2. * mm, physical_size.z() / 2. * mm);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
  if (sdflag) {
    logvol->SetSensitiveDetector(scinti);
  }
  if (color.contains("none")) {
    logvol->SetVisAttributes(_visattributes->GetInvisible());
  } else {
    logvol->SetVisAttributes(_visattributes->GetVisAttributes(color));
  }

  G4RotationMatrix rotation_matrix;
  rotation_matrix.rotateY(-(90 - angle) * deg);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, parent,
                              false, 0, true);
}
