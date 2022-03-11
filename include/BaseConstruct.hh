#ifndef BASECONST_HH
#define BASECONST_HH 1

#include <TObject.h>
#include <TString.h>

#include <G4LogicalVolume.hh>
#include <G4ThreeVector.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>

#include "Material.hh"
#include "Scintillator.hh"
#include "VisAttributes.hh"

using namespace CLHEP;

class BaseConstruct : public TObject {
 public:
  BaseConstruct(TString _name, int _id, TString _material_name,
                G4ThreeVector _size, G4ThreeVector _position, double _angle,
                TString _color);
  BaseConstruct(G4LogicalVolume *_parent, TString _name, int _id,
                TString _material_name, G4ThreeVector _size,
                G4ThreeVector _position, double _angle, TString _color);
  ~BaseConstruct();
  void Initialize(Material *_mat, VisAttributes *_visatt);
  virtual void SetGeometry() = 0;
  G4VPhysicalVolume *GetVolume();
  G4LogicalVolume *GetLogicalVol();
  G4int GetID();

 protected:
  G4String indivisual_name, material_name;
  G4ThreeVector position, physical_size;
  G4double angle;
  G4int vol_id;
  G4String color;
  G4VSolid *solid;
  G4LogicalVolume *logvol, *parent;
  G4VPhysicalVolume *physvol;
  Material *_material;
  VisAttributes *_visattributes;
};

inline BaseConstruct::BaseConstruct(TString _name, int _id,
                                    TString _material_name, G4ThreeVector _size,
                                    G4ThreeVector _position, double _angle,
                                    TString _color) {
  indivisual_name = _name;
  vol_id = _id;
  material_name = _material_name;
  physical_size = _size;
  position = _position * mm;
  angle = _angle;
  color = _color;
  parent = 0;
}

inline BaseConstruct::BaseConstruct(G4LogicalVolume *_parent, TString _name,
                                    int _id, TString _material_name,
                                    G4ThreeVector _size,
                                    G4ThreeVector _position, double _angle,
                                    TString _color) {
  parent = _parent;
  indivisual_name = _name;
  vol_id = _id;
  material_name = _material_name;
  physical_size = _size;
  position = _position * mm;
  angle = _angle;
  color = _color;
}

inline void BaseConstruct::Initialize(Material *mat, VisAttributes *vis) {
  _material = mat;
  _visattributes = vis;
}

inline G4VPhysicalVolume *BaseConstruct::GetVolume() { return physvol; }
inline G4LogicalVolume *BaseConstruct::GetLogicalVol() { return logvol; }
inline G4int BaseConstruct::GetID() { return vol_id; }

inline BaseConstruct::~BaseConstruct() {
  delete logvol;
  delete physvol;
}

#endif  // !BASECONST_HH