#ifndef Material_h
#define Material_h 1

#include "globals.hh"

class G4Material;

class Material {
 public:
  Material();
  ~Material();

  G4Material* GetMaterial(const G4String&) const;

 private:
  G4Material* vacuum;
  G4Material* air;
  // G4Material* water;
  // G4Material* N2;
  G4Material* concrete;
  G4Material* PVC;

  // G4Material* Be;
  G4Material* Al;
  // G4Material* Cu;
  G4Material* Pb;
  G4Material* Fe;
  // G4Material* Ti;
  // G4Material* Ni;
  // G4Material* Si;

  // G4Material* LSO;
  // G4Material* YSO;
  // G4Material* LYSO;
  // G4Material* YAP;
  // G4Material* NaI;
  // G4Material* CsI;
  // G4Material* LaBr3;
  // G4Material* CeBr3;
  // G4Material* LaBr3_Ce;

  // G4Material* aerogel;
  G4Material* plastic;
  G4Material* PMMA;
  // G4Material* sekiei;
  // G4Material* glass;
  G4Material* SUS304;
  // G4Material* teflon;
  G4Material* kapton;
  // G4Material* mylar;
  // G4Material* permalloy;
  // G4Material* AlFlame;
};

#endif
