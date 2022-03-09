#ifndef BEAM_HH
#define BEAM_HH 1

#include <TString.h>

#include <G4ThreeVector.hh>
#include <G4TwoVector.hh>

class Beam {
 public:
  Beam() {}
  Beam(TString _btype, G4TwoVector _sizev, G4double _angle,
       G4TwoVector _momentum)
      : b_type(_btype),
        size(_sizev),
        spread_angle(_angle),
        momentum(_momentum) {}
  TString GetBeamType() const { return b_type; }
  G4TwoVector GetBeamSize() const { return size; }
  G4double GetBeamSpreadAngle() const { return spread_angle; }
  G4TwoVector GetMomentum() const { return momentum; }
  void SetBeamType(TString _btype) { b_type = _btype; }
  void SetBeamSize(G4double _hsize, G4double _vsize) {
    size = G4TwoVector(_hsize, _vsize);
  }
  void SetBeamSpreadAngle(G4double _ang) { spread_angle = _ang; }
  void SetBeamMomentum(G4double _mean, G4double _sigma) {
    momentum = G4TwoVector(_mean, _sigma);
  }

 private:
  TString b_type;
  G4TwoVector size, momentum;
  G4double spread_angle;
};

#endif  // !BEAM_HH