#ifndef MESHPARAM_HH
#define MESHPARAM_HH

#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>

using namespace CLHEP;

class MeshParam : public G4VPVParameterisation {
 public:
  MeshParam(G4ThreeVector _sizev, G4double _parent_zpos);
  virtual ~MeshParam() { ; };
  void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol)
      const;  // position, rotation

 private:
  // G4VPhysicalVolume* physical_volume;
  G4int n_wire_d1, n_wire;
  std::vector<G4double> xpos, ypos, zpos;
  G4RotationMatrix *rotation_x;
  G4RotationMatrix *rotation_y;
};

#endif  // !MESHPARAM_HH