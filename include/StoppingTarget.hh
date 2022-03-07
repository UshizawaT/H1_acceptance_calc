#ifndef STOPPTGT_HH
#define STOPPTGT_HH 1

#include <TString.h>

#include <G4Box.hh>
#include <G4PVPlacement.hh>

#include "BaseConstruct.hh"

class StoppingTarget : public BaseConstruct {
 public:
  StoppingTarget(TString _name, int _id, TString _material_name,
                 G4ThreeVector _size, G4ThreeVector _position, double _angle)
      : BaseConstruct(_name, _id, _material_name, _size, _position, _angle) {}
};

#endif  // !STOPPTGT_HH