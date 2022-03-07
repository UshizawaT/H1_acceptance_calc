#include "DetectorWorld.hh"

void DetectorWorld::SetGeometry() {
  indivisual_name += vol_id;
  solid = new G4Box(indivisual_name, physical_size.x() / 2. * mm,
                    physical_size.y() / 2. * mm, physical_size.z() / 2. * mm);
  logvol = new G4LogicalVolume(solid, _material->GetMaterial(material_name),
                               indivisual_name);
  logvol->SetVisAttributes(_visattributes->GetInvisible());
  G4RotationMatrix rotation_matrix;
  rotation_matrix.rotateY(-(90 - angle) * deg);
  G4Transform3D transform_3d(rotation_matrix, position);
  physvol = new G4PVPlacement(transform_3d, logvol, indivisual_name, 0, false,
                              0, true);
}