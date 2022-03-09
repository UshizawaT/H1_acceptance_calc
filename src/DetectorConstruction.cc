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

DetectorConstruction::DetectorConstruction(XMLParamParser* _xmlobj)
    : xmlobj(_xmlobj) {
  material = new Material();
  visatt = new VisAttributes();
  G4cerr << "constractor of detector constructor" << G4endl;
}

DetectorConstruction::~DetectorConstruction() {
  G4cerr << "destractor of detector construct" << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  // Option to switch on/off checking of volumes overlaps
  int n_con = xmlobj->GetConstNumber();
  BaseConstruct *construct, *world;
  for (int i = 0; i < n_con; ++i) {
    construct = xmlobj->GetConstruct(i);
    construct->Initialize(material, visatt);
    construct->SetGeometry();
  }
  world = xmlobj->GetWorld();
  G4VPhysicalVolume* physWorld = world->GetVolume();

  // always return the physical World
  return physWorld;
}
