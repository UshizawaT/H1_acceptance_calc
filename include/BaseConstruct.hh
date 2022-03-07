#ifndef BASECONST_HH
#define BASECONST_HH

#include <TObject.h>
#include <TString.h>

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Transform3D.hh>
#include <G4Tubs.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>

#include "Material.hh"
#include "Scintillator.hh"
#include "VisAttributes.hh"

using namespace CLHEP;

class BaseConstruct : public TObject {
 public:
  BaseConstruct(TString _name, int _id, TString _material_name,
                G4ThreeVector _size, G4ThreeVector _position, double _angle);
  ~BaseConstruct();
  void Initialize(Material *_mat, VisAttributes *_visatt);
  virtual void SetGeometry(G4LogicalVolume *_parent, G4String color_name);
  virtual void SetGeometry(G4LogicalVolume *_parent, Scintillator *_scinti,
                           G4String color_name);
  G4VPhysicalVolume *GetVolume();
  G4int GetID();

 protected:
  G4String indivisual_name, material_name;
  G4ThreeVector position, physical_size;
  G4double angle;
  G4int vol_id;
  G4VSolid *solid;
  G4LogicalVolume *logvol;
  G4VPhysicalVolume *physvol;
  Material *_material;
  VisAttributes *_visattributes;
};

inline G4VPhysicalVolume *BaseConstruct::GetVolume() { return physvol; }
inline G4int BaseConstruct::GetID() { return vol_id; }

#endif  // !BASECONST_HH