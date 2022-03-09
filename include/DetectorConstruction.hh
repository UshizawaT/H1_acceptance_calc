#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include <G4ThreeVector.hh>
#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

#include "BaseConstruct.hh"
#include "Material.hh"
#include "VisAttributes.hh"
#include "XMLParamParser.hh"

class G4VPhysicalVolume;
class Scintillator;

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:
  DetectorConstruction(XMLParamParser* _xmlobj);
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

 private:
  G4VPhysicalVolume* world;
  Material* material;
  VisAttributes* visatt;
  XMLParamParser* xmlobj;
};

#endif
