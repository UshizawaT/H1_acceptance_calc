#include "BaseTubs.hh"

void BaseTubs::SetGeometry() {
  indivisual_name += vol_id;
  solid = new G4Tubs(indivisual_name, 0., physical_size.x() / 2. * mm,
                     physical_size.y() / 2. * mm, 0, twopi);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
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

void BaseTubs::SetWGeometry() {
  indivisual_name += vol_id;
  solid = new G4Tubs(indivisual_name, 0., physical_size.x() / 2. * mm,
                     physical_size.y() / 2. * mm, 0, twopi);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
  if (color.contains("none")) {
    logvol->SetVisAttributes(_visattributes->GetInvisible());
  } else {
    logvol->SetVisAttributes(_visattributes->GetVisAttributes(color, "w"));
  }
  G4RotationMatrix rotation_matrix;
  rotation_matrix.rotateY(-(90 - angle) * deg);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, parent,
                              false, 0, true);
}