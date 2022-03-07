#ifndef LEADBLOCK_HH
#define LEADBLOCK_HH 1

#include <G4Box.hh>
#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"

class LeadBlock : public BaseConstruct {
 public:
  LeadBlock(TString _name, int _id, TString _material_name, G4ThreeVector _size,
            G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
};
#endif  // !LEADBLOCK_HH