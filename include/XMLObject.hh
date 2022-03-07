#ifndef XMLOBJ_HH
#define XMLOBJ_HH 1

#include <TObject.h>
#include <TString.h>

#include <G4ThreeVector.hh>

class Beam {
 public:
  Beam() {}
  Beam(TString btype, double bhsize, double bvsize, double angle, double _mom)
      : b_type(btype),
        b_h_size(bhsize),
        b_v_size(bvsize),
        spread_angle(angle),
        momentum(_mom) {}
  TString GetBeamType() const { return b_type; }
  double GetBeamHSize() const { return b_h_size; }
  double GetBeamVSize() const { return b_v_size; }
  double GetBeamSpreadAngle() const { return spread_angle; }
  double GetBeamMomentum() const { return momentum; }
  void SetBeamType(TString _btype) { b_type = _btype; }
  void SetBeamHSize(double _hsize) { b_h_size = _hsize; }
  void SetBeamVSize(double _vsize) { b_v_size = _vsize; }
  void SetBeamSpreadAngle(double _ang) { spread_angle = _ang; }
  void SetBeamMomentum(double _mom) { momentum = _mom; }

 private:
  TString b_type;
  double b_h_size;
  double b_v_size;
  double spread_angle;
  double momentum;
};

class Mesh {
 public:
  Mesh() {}
  Mesh(TString _mat, double _dia, double _length, double _pitch)
      : material(_mat), diameter(_dia), length(_length), pitch(_pitch) {}
  TString GetMeshMaterial() { return material; }
  double GetWireDiameter() { return diameter; }
  double GetWireLength() { return length; }
  double GetMeshPitch() { return pitch; }
  void SetMeshMaterial(TString _mat) { material = _mat; }
  void SetWireDiameter(double _dia) { diameter = _dia; }
  void SetWireLength(double _len) { length = _len; }
  void SetMeshPitch(double _pitch) { pitch = _pitch; }

 private:
  TString material;
  double diameter, length, pitch;
};

class StoppingTarget {
 public:
  StoppingTarget() {}
  StoppingTarget(TString _mat, double _thickness, double _hsize, double _vsize,
                 double _ang)
      : material(_mat),
        thickness(_thickness),
        hsize(_hsize),
        vsize(_vsize),
        angle(_ang) {}
  TString GetTargetMaterial() const { return material; }
  double GetTargetThickness() const { return thickness; }
  double GetTargetHSize() const { return hsize; }
  double GetTargetVSize() const { return vsize; }
  double GetTargetAngle() const { return angle; }
  void SetTargetMaterial(TString _tmat) { material = _tmat; }
  void SetTargetThickness(double _thick) { thickness = _thick; }
  void SetTargetHSize(double _hsize) { hsize = _hsize; }
  void SetTargetVSize(double _vsize) { vsize = _vsize; }
  void SetTargetAngle(double _ang) { angle = _ang; }

 private:
  TString material;
  double thickness, hsize, vsize, angle;
};

class LeadBlock : public TObject {
 public:
  LeadBlock() {}
  LeadBlock(int _id, double _xsize, double _ysize, double _zsize, double _xpos,
            double _ypos, double _zpos)
      : id(_id) {
    sizev = G4ThreeVector{_xsize, _ysize, _zsize};
    position = G4ThreeVector{_xpos, _ypos, _zpos};
  }
  int GetBlockId() const { return id; }
  G4ThreeVector GetBlockSize() const { return sizev; }
  G4ThreeVector GetBlockPos() const { return position; }
  void SetBlockId(int _id) { id = _id; }
  void SetBlockSize(double _xsize, double _ysize, double _zsize) {
    sizev = G4ThreeVector{_xsize, _ysize, _zsize};
  }
  void SetBlockPos(double _xpos, double _ypos, double _zpos) {
    position = G4ThreeVector{_xpos, _ypos, _zpos};
  }

 private:
  int id;
  G4ThreeVector sizev, position;
};

class XMLScintillator : public TObject {
 public:
  XMLScintillator() {}
  XMLScintillator(int _id, int _groupid, double _hsize, double _vsize,
                  double _thick, double _angle, double _xpos, double _ypos,
                  double _zpos)
      : id(_id), groupid(_groupid), angle(_angle) {
    sizev = G4ThreeVector{_hsize, _vsize, _thick};
    position = G4ThreeVector{_xpos, _ypos, _zpos};
  }
  int GetScintiId() { return id; }
  int GetScintiGroupId() { return groupid; }
  G4ThreeVector GetScintiSize() { return sizev; }
  double GetScintiAngle() { return angle; }
  G4ThreeVector GetScintiPosition() { return position; }
  void SetScintiId(int _id) { id = _id; }
  void SetScintiGroupId(int _groupid) { groupid = _groupid; }
  void SetScintiSize(double _hsize, double _vsize, double _thickness) {
    sizev = G4ThreeVector{_hsize, _vsize, _thickness};
  }
  void SetScintiAngle(double _ang) { angle = _ang; }
  void SetScintiPosition(double _xpos, double _ypos, double _zpos) {
    position = G4ThreeVector{_xpos, _ypos, _zpos};
  }

 private:
  int id, groupid;
  // double hsize, vsize, thickness;
  double angle;
  // double xpos, ypos, zpos;
  G4ThreeVector sizev, position;
};

#endif  // !XMLOBJ_HH