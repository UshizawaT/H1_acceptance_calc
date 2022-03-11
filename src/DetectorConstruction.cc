#include "DetectorConstruction.hh"

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
  G4cout << "N constructs : " << n_con << G4endl;
  BaseConstruct* world;
  std::vector<BaseConstruct*> constructs = xmlobj->GetConstructsList();
  G4cout << "N constructs from vector : " << constructs.size() << G4endl;
  /*
  for (int i = 0; i < n_con; ++i) {
    constructs[i]->Initialize(material, visatt);
    G4cout << "construct Initialized!" << G4endl;
    constructs[i]->SetGeometry();
    G4cout << "Set Geom.!" << G4endl;
  }**/
  world = xmlobj->GetWorld();
  G4VPhysicalVolume* physWorld = world->GetVolume();

  // always return the physical World
  return physWorld;
}
