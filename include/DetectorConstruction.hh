#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include <G4ThreeVector.hh>
#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

#include "LeadBlock.hh"
#include "Material.hh"
#include "ScintillatorObject.hh"
#include "VisAttributes.hh"

class G4VPhysicalVolume;
class Scintillator;

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:
  DetectorConstruction(Scintillator*);
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

 private:
  Scintillator* scinti;
  G4VPhysicalVolume* world;
  Material *material;
  VisAttributes* visatt;
  G4String tgt_material;
  G4double tgt_thickness, tgt_angle, tgt_hsize, tgt_vsize;
  G4String mesh_material;
  G4double wire_dia, wire_len, mesh_pitch;
  std::vector<G4double> scintis_angle;
  std::vector<G4ThreeVector> scintis_pos, scintis_size, pbblocks_pos,
      pbblocks_size;
};

#endif
