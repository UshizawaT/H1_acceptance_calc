#ifndef BASEBOX_HH
#define BASEBOX_HH

#include <TObject.h>
#include <TString.h>

#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4Transform3D.hh>

#include "BaseConstruct.hh"

using namespace CLHEP;

class BaseBox : public BaseConstruct {
 public:
  BaseBox(TString _name, int _id, TString _material_name, G4ThreeVector _size,
          G4ThreeVector _position, double _angle, TString _color);
  BaseBox(G4LogicalVolume *_parent, TString _name, int _id,
          TString _material_name, G4ThreeVector _size, G4ThreeVector _position,
          double _angle, TString _color);
  BaseBox(G4LogicalVolume *_parent, Scintillator *_scinti, TString _name,
          int _id, int _groupid, TString _material_name, G4ThreeVector _size,
          G4ThreeVector _position, double _angle, TString _color);
  virtual void SetGeometry();
  // virtual void SetGeometry(Scintillator *_scinti);
  G4int GetGroupID();
  ~BaseBox();

 private:
  G4int groupid;
  Scintillator *scinti;
  bool sdflag;
};

inline BaseBox::BaseBox(TString _name, int _id, TString _material_name,
                        G4ThreeVector _size, G4ThreeVector _position,
                        double _ang, TString _color)
    : BaseConstruct(_name, _id, _material_name, _size, _position, _ang,
                    _color) {
  sdflag = false;
}

inline BaseBox::BaseBox(G4LogicalVolume *_parent, TString _name, int _id,
                        TString _material_name, G4ThreeVector _size,
                        G4ThreeVector _position, double _ang, TString _color)
    : BaseConstruct(_parent, _name, _id, _material_name, _size, _position, _ang,
                    _color) {
  sdflag = false;
}

inline BaseBox::BaseBox(G4LogicalVolume *_parent, Scintillator *_scinti,
                        TString _name, int _id, int _groupid,
                        TString _material_name, G4ThreeVector _size,
                        G4ThreeVector _position, double _ang, TString _color)
    : BaseConstruct(_parent, _name, _id, _material_name, _size, _position, _ang,
                    _color),
      scinti(_scinti),
      groupid(_groupid) {
  sdflag = true;
}

inline G4int BaseBox::GetGroupID() { return groupid; }

inline BaseBox::~BaseBox() { delete scinti; }

#endif  // !BASEBOX_HH