#include "BaseBox.hh"

void BaseBox::SetGeometry() {
  TString str_id;
  str_id.Form("%d", vol_id);
  indivisual_name += str_id;
  G4cout << "Basebox : " << indivisual_name << G4endl;
  solid = new G4Box(indivisual_name, physical_size.x() / 2.,
                    physical_size.y() / 2., physical_size.z() / 2.);
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
  rotation_matrix.rotateY(-angle);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, parent,
                              false, 0, true);
}
