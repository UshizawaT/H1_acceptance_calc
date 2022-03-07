#ifndef BEAM_HH
#define BEAM_HH 1

#include <TString.h>

#include <G4ThreeVector.hh>

class Beam {
 public:
  Beam() {}
  Beam(TString btype, double bhsize, double bvsize, double angle)
      : b_type(btype),
        b_h_size(bhsize),
        b_v_size(bvsize),
        spread_angle(angle) {}
  TString GetBeamType() const { return b_type; }
  double GetBeamHSize() const { return b_h_size; }
  double GetBeamVSize() const { return b_v_size; }
  double GetBeamSpreadAngle() const { return spread_angle; }
  void SetBeamType(TString _btype) { b_type = _btype; }
  void SetBeamHSize(double _hsize) { b_h_size = _hsize; }
  void SetBeamVSize(double _vsize) { b_v_size = _vsize; }
  void SetBeamSpreadAngle(double _ang) { spread_angle = _ang; }

 private:
  TString b_type;
  double b_h_size;
  double b_v_size;
  double spread_angle;
};

#endif  // !BEAM_HH