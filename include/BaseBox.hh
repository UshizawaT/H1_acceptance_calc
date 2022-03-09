#ifndef BASEBOX_HH
#define BASEBOX_HH

#include <TObject.h>
#include <TString.h>

#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
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

 private:
  G4int groupid;
  Scintillator *scinti;
  bool sdflag;
};

inline G4int BaseBox::GetGroupID() { return groupid; }

#endif  // !BASEBOX_HH