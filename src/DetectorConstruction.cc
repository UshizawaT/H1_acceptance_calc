#include "DetectorConstruction.hh"

#include <TString.h>

#include <G4Box.hh>
#include <G4Cons.hh>
#include <G4LogicalVolume.hh>
#include <G4MultiUnion.hh>
#include <G4Orb.hh>
#include <G4PVPlacement.hh>
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
  material = new Material();
  visatt = new VisAttributes();
  G4cerr << "constractor of detector constructor" << G4endl;
}

DetectorConstruction::~DetectorConstruction() {
  G4cerr << "destractor of detector construct" << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //------------------------------------
  // World
  //------------------------------------
  G4cout << "prepare world" << G4endl;
  _world->Initialize(material, visatt);
  G4cout << "initialized world" << G4endl;
  _world->SetGeometry();
  G4cout << " world geomm. set" << G4endl;
  G4LogicalVolume* logicWorld = _world->GetLogicalVol();
  G4VPhysicalVolume* physWorld = _world->GetVolume();

  ///
  // Vacuum volume
  ///
  G4cout << "prepare vacuum vol." << G4endl;
  _vacuum_volume->Initialize(material, visatt);
  G4cout << "initialized vacuum vol." << G4endl;
  _vacuum_volume->SetGeometry(logicWorld, "white");
  G4cout << "set geom. of vacuum vol." << G4endl;
  G4LogicalVolume* logic_vacuum_v = _vacuum_volume->GetLogicalVol();
  G4VPhysicalVolume* phys_vacuum_v = _vacuum_volume->GetVolume();
  // G4double vacuum_length = 1. * m - _thick_kapton * m;
  // G4Tubs* solid_vacuum_v =
  //     new G4Tubs("vacuum_vol", 0, 1. / 2. * m, vacuum_length / 2., 0,
  //     twopi);
  // G4LogicalVolume* logic_vacuum_v = new G4LogicalVolume(
  //     solid_vacuum_v, material->GetMaterial("vacuum"), "vacuum_vol");
  // G4VPhysicalVolume* phys_vacuum_v =
  //     new G4PVPlacement(0, G4ThreeVector(0., 0., -0.5 * m),
  //     logic_vacuum_v,
  //                       "vacuum_vol", logicWorld, false, 0,
  //                       checkOverlaps);
  //  visualization /////////////////////
  // logic_vacuum_v->SetVisAttributes(visatt->GetVisAttributes("white",
  // "w"));

  ///
  // Kapton window
  ///
  G4cout << "prepare kapton window" << G4endl;
  _kapton_window->Initialize(material, visatt);
  G4cout << "initialized kapton window" << G4endl;
  _kapton_window->SetGeometry(logicWorld, "yellow");
  G4cout << "set geom of kapton window" << G4endl;
  G4VPhysicalVolume* phys_kapton = _kapton_window->GetVolume();
  // G4Tubs* solid_kapton = new G4Tubs("Kapton_window", 0, _dia_kapton * m
  // / 2.,
  //                                   _thick_kapton * m / 2., 0, twopi);
  // G4LogicalVolume* logic_kapton = new G4LogicalVolume(
  //     solid_kapton, material->GetMaterial(_kapton_mat), "Kapton_window");
  // G4VPhysicalVolume* phys_kapton =
  //     new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logic_kapton,
  //                       "Kapton_window", logicWorld, false, 0,
  //                       checkOverlaps);
  //  visualization /////////////////////
  // logic_kapton->SetVisAttributes(visatt->GetVisAttributes("yellow"));

  ///
  // SUS mesh
  ///
  if (_exist_mesh) {
    G4cout << "prepare mesh" << G4endl;
    _mesh->Initialize(material, visatt);
    G4cout << "initialized mesh" << G4endl;
    _mesh->SetGeometry(logic_vacuum_v, "magenta");
    G4cout << "set geom. of mesh" << G4endl;
    G4VPhysicalVolume* mesh_volume = _mesh->GetVolume();
  }

  ///
  // Mu stompping target
  ///
  if (_exist_target) {
    G4cout << "prepare target" << G4endl;
    _stopping_tgt->Initialize(material, visatt);
    G4cout << "initialized target" << G4endl;
    _stopping_tgt->SetGeometry(logicWorld, "green");
    G4cout << "set geom. of target" << G4endl;
    G4VPhysicalVolume* mu_stopping_tgt = _stopping_tgt->GetVolume();
  }

  ///
  // Concrete block
  ///
  G4cout << "prepare shield" << G4endl;
  _concrete_block->Initialize(material, visatt);
  G4cout << "initialized shield" << G4endl;
  _concrete_block->SetGeometry(logicWorld, "light_gray");
  G4cout << "set geom. of shield" << G4endl;
  G4VPhysicalVolume* phys_shield = _concrete_block->GetVolume();
  // G4Box* solid_shield =
  //     new G4Box("Shield", 1600 / 2. * mm, 1600 / 2. * mm, 1400 / 2. *
  //     mm);
  // G4LogicalVolume* logic_shield = new G4LogicalVolume(
  //     solid_shield, material->GetMaterial("concrete"), "Shield");
  // G4RotationMatrix rm_shield;
  // G4ThreeVector pos_shield(200 * mm, 0., 1890 * mm);
  //// rm_target.rotateY(-angle_target);
  // G4Transform3D tr_shield(rm_shield, pos_shield);
  // G4VPhysicalVolume* phys_shield = new G4PVPlacement(
  //     tr_shield, logic_shield, "Shield", logicWorld, false, 0,
  //     checkOverlaps);
  //  visualization /////////////////////
  // logic_shield->SetVisAttributes(visatt->GetVisAttributes("light_gray"));

  ///
  // Pb block
  ///
  if (_exist_pbblocks) {
    G4VPhysicalVolume* phys_pbblock[_pb_block_num];
    LeadBlock* itr_pbb;
    TIter nextpbb(_pb_blocks);
    G4int i = 0;
    while (itr_pbb = (LeadBlock*)nextpbb()) {
      G4cout << "prepare pb block : " << i << G4endl;
      itr_pbb->Initialize(material, visatt);
      G4cout << "initialized pb block : " << i << G4endl;
      itr_pbb->SetGeometry(logicWorld, "blue");
      G4cout << "set geom. of pb block : " << i << G4endl;
      phys_pbblock[i] = itr_pbb->GetVolume();
      i++;
    }
  }

  ///
  // scinti
  ///
  G4VPhysicalVolume* phys_scinti[_scinti_num];
  // G4double scinti_int = 37e-3 * m;
  ScintillatorObject* itr_scinti;
  TIter nextscinti(_scintillators);
  G4int i = 0;
  while (itr_scinti = (ScintillatorObject*)nextscinti()) {
    itr_scinti->Initialize(material, visatt);
    itr_scinti->SetGeometry(logicWorld, scinti, "cyan");
    phys_scinti[i] = itr_scinti->GetVolume();
    i++;
  }

  logicWorld->SetVisAttributes(visatt->GetInvisible());

  // always return the physical World
  return physWorld;
}
