#include "Mesh.hh"

void Mesh::SetGeometry(G4LogicalVolume *_parent, G4String color_name) {
  G4double d_wire = physical_size.x() * mm;
  G4double r_wire = d_wire / 2.;
  G4double l_wire = physical_size.y() * mm;
  G4double pitch = physical_size.z() * mm;
  wire_solid = new G4Tubs("wire", 0, r_wire, l_wire / 2., 0, twopi);
  logvol = new G4LogicalVolume(wire_solid,
                               _material->GetMaterial(material_name), "wire");
  logvol->SetVisAttributes(_visattributes->GetVisAttributes(color_name));
  const G4int n_wire = (G4int)(l_wire / pitch) * 2 + 1;
  G4Tubs *vac_tub = (G4Tubs *)_parent->GetSolid();
  G4double l_vac = vac_tub->GetZHalfLength();
  G4VPVParameterisation *meshparm = new MeshParam(physical_size, l_vac);
  physvol = new G4PVParameterised(indivisual_name, logvol, _parent, kUndefined,
                                  n_wire, meshparm, false);
}