#include "MeshParam.hh"

MeshParam::MeshParam(G4ThreeVector _sizev, G4double _parent_zpos) {
  G4double d_wire = _sizev.x() * mm;
  G4double r_wire = d_wire / 2.;
  G4double l_wire = _sizev.y() * mm;
  G4double pitch = _sizev.z() * mm;
  G4double half_pitch = pitch / 2.;
  n_wire_d1 = (int)(l_wire / pitch);
  n_wire = n_wire_d1 * 2 + 1;
  // G4cerr << "wire num : " << n_wire << G4endl;
  xpos.resize(n_wire);
  ypos.resize(n_wire);
  zpos.resize(n_wire);
  rotation_x = new G4RotationMatrix();
  rotation_y = new G4RotationMatrix();
  rotation_x->rotateX(halfpi);  // make vertical wire
  rotation_y->rotateY(halfpi);  // make horizontal wire
  // wire assemble
  for (int copyNo = 0; copyNo < n_wire; ++copyNo) {
    // assemble x direction
    if (copyNo < n_wire_d1) {
      xpos[copyNo] =
          pow(-1, copyNo) * (half_pitch + (int)(copyNo / 2) * pitch * mm);
      ypos[copyNo] = 0.;
      zpos[copyNo] = _parent_zpos - r_wire;
      // assemble y direction
    } else if (copyNo < n_wire) {
      xpos[copyNo] = 0.;
      ypos[copyNo] = pow(-1, copyNo - n_wire_d1) *
                     ((int)((copyNo - n_wire_d1) / 2) * pitch * mm);
      zpos[copyNo] = _parent_zpos - r_wire * 3;
    }
  }
}

void MeshParam::ComputeTransformation(const G4int copyNo,
                                      G4VPhysicalVolume* physVol) const {
  // G4Tranform3D tr_mesh(rm_wire, wire_pos);
  physVol->SetTranslation(
      G4ThreeVector(xpos[copyNo], ypos[copyNo], zpos[copyNo]));
  if (copyNo < n_wire_d1) {
    physVol->SetRotation(rotation_x);
  } else if (copyNo < n_wire) {
    // G4cerr << "horizontal wire" << G4endl;
    physVol->SetRotation(rotation_y);
  }
}