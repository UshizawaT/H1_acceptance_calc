#include "DetectorConstruction.hh"

#include <TString.h>

#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4LogicalVolume.hh>
#include <G4Orb.hh>
#include <G4PVPlacement.hh>
#include <G4Para.hh>
#include <G4RotationMatrix.hh>
#include <G4RunManager.hh>
#include <G4Sphere.hh>
#include <G4SubtractionSolid.hh>
#include <G4SystemOfUnits.hh>
#include <G4Transform3D.hh>
#include <G4Trd.hh>
#include <G4Tubs.hh>
#include <G4UnionSolid.hh>

#include "GlobalVariables.hh"
#include "Material.hh"
#include "Scintillator.hh"
#include "VisAttributes.hh"

using namespace CLHEP;

DetectorConstruction::DetectorConstruction(Scintillator* _scinti)
    : scinti(_scinti) {
  if (_exist_target) {
    tgt_material = _stopping_tgt->GetTargetMaterial();
    tgt_thickness = _stopping_tgt->GetTargetThickness();
    tgt_hsize = _stopping_tgt->GetTargetHSize();
    tgt_vsize = _stopping_tgt->GetTargetVSize();
    tgt_angle = _stopping_tgt->GetTargetAngle();
    if (_n_target > 1) {
      tgt2_material = _stopping_tgt2->GetTargetMaterial();
      tgt2_thickness = _stopping_tgt2->GetTargetThickness();
      tgt2_hsize = _stopping_tgt2->GetTargetHSize();
      tgt2_vsize = _stopping_tgt2->GetTargetVSize();
      tgt2_angle = _stopping_tgt2->GetTargetAngle();
    }
  }
  if (_exist_mesh) {
    mesh_material = _mesh->GetMeshMaterial();
    wire_dia = _mesh->GetWireDiameter();
    wire_len = _mesh->GetWireLength();
    mesh_pitch = _mesh->GetMeshPitch();
  }
  if (_exist_pbblocks) {
    pbblocks_pos.resize(_pb_block_num);
    pbblocks_size.resize(_pb_block_num);
    LeadBlock* itr_pbblock = 0;
    TIter nextb(_pb_blocks);
    int pbb_index = 0;
    while (itr_pbblock = (LeadBlock*)nextb()) {
      pbb_index = itr_pbblock->GetBlockId() - 1;
      pbblocks_pos[pbb_index] = itr_pbblock->GetBlockPos();
      pbblocks_size[pbb_index] = itr_pbblock->GetBlockSize();
    }
  }

  scintis_size.resize(_scinti_num);
  scintis_pos.resize(_scinti_num);
  scintis_angle.resize(_scinti_num);
  XMLScintillator* itr_scinti = 0;
  TIter next(_scintillators);
  int scinti_index = 0;
  while ((itr_scinti = (XMLScintillator*)next())) {
    scinti_index = itr_scinti->GetScintiId() - 1;
    scintis_size[scinti_index] = itr_scinti->GetScintiSize();
    scintis_angle[scinti_index] = itr_scinti->GetScintiAngle();
    scintis_pos[scinti_index] = itr_scinti->GetScintiPosition();
  }
  G4cerr << "constractor of detector constructor" << G4endl;
}

DetectorConstruction::~DetectorConstruction() {
  G4cerr << "destractor of detector construct" << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  Material* material = new Material();
  VisAttributes* visAtt = new VisAttributes();

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //------------------------------------
  // World
  //------------------------------------
  G4double xWorld = 5 * m;
  G4double yWorld = 2 * m;
  G4double zWorld = 5 * m;

  G4Box* solidWorld = new G4Box("World", xWorld, yWorld, zWorld);

  G4LogicalVolume* logicWorld =
      new G4LogicalVolume(solidWorld, material->GetMaterial("air"), "World");

  G4VPhysicalVolume* physWorld =
      new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "World", 0,
                        false, 0, checkOverlaps);

  ///
  // Vacuum volume
  ///
  G4double vacuum_length = 1. * m - _thick_kapton * m;
  G4Tubs* solid_vacuum_v =
      new G4Tubs("vacuum_vol", 0, 1. / 2. * m, vacuum_length / 2., 0, twopi);
  G4LogicalVolume* logic_vacuum_v = new G4LogicalVolume(
      solid_vacuum_v, material->GetMaterial("vacuum"), "vacuum_vol");
  G4VPhysicalVolume* phys_vacuum_v =
      new G4PVPlacement(0, G4ThreeVector(0., 0., -0.5 * m), logic_vacuum_v,
                        "vacuum_vol", logicWorld, false, 0, checkOverlaps);
  // visualization /////////////////////
  logic_vacuum_v->SetVisAttributes(visAtt->GetVisAttributes("white", "w"));

  ///
  // Kapton window
  ///
  G4Tubs* solid_kapton = new G4Tubs("Kapton_window", 0, _dia_kapton * m / 2.,
                                    _thick_kapton * m / 2., 0, twopi);
  G4LogicalVolume* logic_kapton = new G4LogicalVolume(
      solid_kapton, material->GetMaterial(_kapton_mat), "Kapton_window");
  G4VPhysicalVolume* phys_kapton =
      new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logic_kapton,
                        "Kapton_window", logicWorld, false, 0, checkOverlaps);
  // visualization /////////////////////
  logic_kapton->SetVisAttributes(visAtt->GetVisAttributes("yellow"));

  ///
  // SUS mesh
  ///
  if (_exist_mesh) {
    G4double r_wire = wire_dia / 2. * mm;
    G4double half_pitch = mesh_pitch / 2. * mm;
    G4Tubs* solid_sus_wire =
        new G4Tubs("sus_wire", 0, r_wire, wire_len * mm / 2., 0, twopi);
    G4LogicalVolume* logic_sus_wire = new G4LogicalVolume(
        solid_sus_wire, material->GetMaterial(mesh_material), "SUS_wire");
    G4RotationMatrix rm_wire_v, rm_wire_h;
    G4Transform3D tr_wire_v, tr_wire_h;
    G4ThreeVector pos_wire_v, pos_wire_h;
    G4VPhysicalVolume *phys_wire_v[20], *phys_wire_h[21];
    rm_wire_v.rotateX(halfpi);
    rm_wire_h = rm_wire_v;
    rm_wire_h.rotateZ(halfpi);
    for (int i = 0; i < 20; i++) {
      pos_wire_v = G4ThreeVector{
          pow(-1, i) * (half_pitch + (int)(i / 2) * mesh_pitch * mm), 0.,
          vacuum_length / 2. - r_wire};
      tr_wire_v = G4Transform3D{rm_wire_v, pos_wire_v};
      phys_wire_v[i] = new G4PVPlacement(
          tr_wire_v, logic_sus_wire, TString::Format("VWire_%d", i).Data(),
          logic_vacuum_v, false, 0, checkOverlaps);
    }
    pos_wire_h = G4ThreeVector{0., 0., vacuum_length / 2. - r_wire * 3};
    tr_wire_h = G4Transform3D{rm_wire_h, pos_wire_h};
    phys_wire_h[0] = new G4PVPlacement(tr_wire_h, logic_sus_wire, "HWire_0",
                                       logic_vacuum_v, false, 0, checkOverlaps);
    for (int j = 1; j < 21; j++) {
      pos_wire_h =
          G4ThreeVector{0., pow(-1, j) * ((int)((j + 1) / 2) * mesh_pitch * mm),
                        vacuum_length / 2. - r_wire * 3};
      tr_wire_h = G4Transform3D{rm_wire_h, pos_wire_h};
      phys_wire_h[j] = new G4PVPlacement(
          tr_wire_h, logic_sus_wire, TString::Format("HWire_%d", j).Data(),
          logic_vacuum_v, false, 0, checkOverlaps);
    }
    logic_sus_wire->SetVisAttributes(visAtt->GetVisAttributes("magenta"));
  }
  ///
  // Mu stompping target
  ///
  if (_exist_target) {
    G4Box* solid_target =
        new G4Box("Muon_stopping_target", tgt_vsize * mm / 2.,
                  tgt_hsize * mm / 2., tgt_thickness * mm / 2.);
    G4LogicalVolume* logic_target =
        new G4LogicalVolume(solid_target, material->GetMaterial(tgt_material),
                            "Muon_stopping_target");
    G4RotationMatrix rm_target;
    G4ThreeVector pos_target(0., 0., 0.2 * m);
    rm_target.rotateY(-(90 - tgt_angle) * deg);
    G4Transform3D tr_target(rm_target, pos_target);
    G4VPhysicalVolume* phys_target =
        new G4PVPlacement(tr_target, logic_target, "Muon_stopping_target",
                          logicWorld, false, 0, checkOverlaps);
    // visualization /////////////////////
    logic_target->SetVisAttributes(visAtt->GetVisAttributes("green"));
    if (_n_target > 1) {
      G4Box* solid_target2 =
          new G4Box("Muon_stopping_target2", tgt2_vsize * mm / 2.,
                    tgt2_hsize * mm / 2., tgt2_thickness * mm / 2.);
      G4LogicalVolume* logic_target2 = new G4LogicalVolume(
          solid_target2, material->GetMaterial(tgt2_material),
          "Muon_stopping_target2");
      G4RotationMatrix rm_target2;
      G4double tgt_zpos = tgt_thickness / 2. + tgt2_thickness / 2.;
      G4ThreeVector pos_target2(0., 0., 0.2 * m + tgt_zpos * mm);
      rm_target2.rotateY(-(90 - tgt2_angle) * deg);
      G4Transform3D tr_target2(rm_target2, pos_target2);
      G4VPhysicalVolume* phys_target2 =
          new G4PVPlacement(tr_target2, logic_target2, "Muon_stopping_target2",
                            logicWorld, false, 0, checkOverlaps);
      logic_target2->SetVisAttributes(visAtt->GetVisAttributes("bgreen"));
    }
  }

  ///
  // Concrete block
  ///
  G4Box* solid_shield =
      new G4Box("Shield", 1600 / 2. * mm, 1600 / 2. * mm, 1400 / 2. * mm);
  G4LogicalVolume* logic_shield = new G4LogicalVolume(
      solid_shield, material->GetMaterial("concrete"), "Shield");
  G4RotationMatrix rm_shield;
  G4ThreeVector pos_shield(200 * mm, 0., 1890 * mm);
  // rm_target.rotateY(-angle_target);
  G4Transform3D tr_shield(rm_shield, pos_shield);
  G4VPhysicalVolume* phys_shield = new G4PVPlacement(
      tr_shield, logic_shield, "Shield", logicWorld, false, 0, checkOverlaps);
  // visualization /////////////////////
  logic_shield->SetVisAttributes(visAtt->GetVisAttributes("light_gray"));

  ///
  // Pb block
  ///
  if (_exist_pbblocks) {
    G4Box* solid_pbblocks[_pb_block_num];
    G4LogicalVolume* logic_pbblocks[_pb_block_num];
    G4RotationMatrix rm_pbblock[_pb_block_num];
    G4Transform3D tr_pbblock[_pb_block_num];
    G4VPhysicalVolume* phys_pbblock[_pb_block_num];

    for (int i = 0; i < _pb_block_num; ++i) {
      solid_pbblocks[i] = new G4Box("Pb_block", pbblocks_size[i].x() / 2. * mm,
                                    pbblocks_size[i].y() / 2. * mm,
                                    pbblocks_size[i].z() / 2. * mm);
      logic_pbblocks[i] =
          new G4LogicalVolume(solid_pbblocks[i], material->GetMaterial("Pb"),
                              TString::Format("log_pbblock_%d", i).Data());
      tr_pbblock[i] = G4Transform3D{rm_pbblock[i], pbblocks_pos[i]};
      phys_pbblock[i] =
          new G4PVPlacement(tr_pbblock[i], logic_pbblocks[i],
                            TString::Format("PbBlock_%d", i).Data(), logicWorld,
                            false, 0, checkOverlaps);
      logic_pbblocks[i]->SetVisAttributes(visAtt->GetVisAttributes("blue"));
    }
  }

  ///
  // scinti
  ///
  G4Box* solid_scinti[_scinti_num];
  G4LogicalVolume* logic_scinti[_scinti_num];
  G4RotationMatrix rm_scinti[_scinti_num];
  G4Transform3D tr_scinti[_scinti_num];
  G4VPhysicalVolume* phys_scinti[_scinti_num];
  // G4double scinti_int = 37e-3 * m;
  for (G4int i = 0; i < _scinti_num; i++) {
    /*
    solid_scinti[i] =
        new G4Box("Scitillator", scintis_thick[i] * mm / 2.,
                  scintis_vsize[i] * mm / 2., scintis_hsize[i] * mm / 2.);**/
    solid_scinti[i] =
        new G4Box("Scintillator", scintis_size[i].x() / 2. * mm,
                  scintis_size[i].y() / 2. * mm, scintis_size[i].z() / 2. * mm);
    logic_scinti[i] =
        new G4LogicalVolume(solid_scinti[i], material->GetMaterial(_sciti_mat),
                            TString::Format("log_scinti_%d", i).Data());
    logic_scinti[i]->SetSensitiveDetector(scinti);
    rm_scinti[i].rotateY(-(90 - scintis_angle[i]) * deg);
    tr_scinti[i] = G4Transform3D{rm_scinti[i], scintis_pos[i]};
    phys_scinti[i] = new G4PVPlacement(tr_scinti[i], logic_scinti[i],
                                       TString::Format("Scinti_%d", i).Data(),
                                       logicWorld, false, 0, checkOverlaps);
    logic_scinti[i]->SetVisAttributes(visAtt->GetVisAttributes("cyan"));
  }
  logicWorld->SetVisAttributes(visAtt->GetInvisible());

  // always return the physical World
  return physWorld;
}
