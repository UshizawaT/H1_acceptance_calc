#include "Material.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

using namespace CLHEP;

Material::Material() {
  G4NistManager* nistManager = G4NistManager::Instance();

  G4String name, symbol;

  G4int ncomponents, natoms;

  G4int z;
  G4double density, fractionmass;

  G4Element* eH = nistManager->FindOrBuildElement(z = 1);
  // G4Element* eBe = nistManager->FindOrBuildElement(z = 4);
  // G4Element* eB = nistManager->FindOrBuildElement(z = 5);
  G4Element* eC = nistManager->FindOrBuildElement(z = 6);
  // G4Element* eN = nistManager->FindOrBuildElement(z = 7);
  G4Element* eO = nistManager->FindOrBuildElement(z = 8);
  // G4Element* eF = nistManager->FindOrBuildElement(z = 9);
  // G4Element* eNa = nistManager->FindOrBuildElement(z = 11);
  G4Element* eAl = nistManager->FindOrBuildElement(z = 13);
  // G4Element* eSi = nistManager->FindOrBuildElement(z = 14);
  G4Element* eCl = nistManager->FindOrBuildElement(z = 17);
  // G4Element* eTi = nistManager->FindOrBuildElement(z = 22);
  G4Element* eCr = nistManager->FindOrBuildElement(z = 24);
  G4Element* eFe = nistManager->FindOrBuildElement(z = 26);
  G4Element* eNi = nistManager->FindOrBuildElement(z = 28);
  // G4Element* eCu = nistManager->FindOrBuildElement(z = 29);
  // G4Element* eBr = nistManager->FindOrBuildElement(z = 35);
  // G4Element* eY = nistManager->FindOrBuildElement(z = 39);
  // G4Element* eMo = nistManager->FindOrBuildElement(z = 42);
  // G4Element* eI = nistManager->FindOrBuildElement(z = 53);
  // G4Element* eCs = nistManager->FindOrBuildElement(z = 55);
  // G4Element* eLa = nistManager->FindOrBuildElement(z = 57);
  // G4Element* eCe = nistManager->FindOrBuildElement(z = 58);
  // G4Element* eNd = nistManager->FindOrBuildElement(z = 60);
  // G4Element* eDy = nistManager->FindOrBuildElement(z = 66);
  // G4Element* eLu = nistManager->FindOrBuildElement(z = 71);
  G4Element* ePb = nistManager->FindOrBuildElement(z = 82);

  // vacuum
  vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");

  // air
  air = nistManager->FindOrBuildMaterial("G4_AIR");

  // water
  // water = nistManager->FindOrBuildMaterial("G4_WATER");
  /*
    // N2 1atm, 273.15+40K
    N2 = new G4Material(name = "N2",
                        density = 1.25 * 273.15 / (273.15 + 40.) * mg / cm3,
                        ncomponents = 1);  // ideal gas assumption
    N2->AddElement(eN, fractionmass = 100. * perCent);
**/
  // concrete 2.3 kg/cm^3
  concrete = nistManager->FindOrBuildMaterial("G4_CONCRETE");

  // Al
  Al = nistManager->FindOrBuildMaterial("G4_Al");
  /*
      // Be
      Be = nistManager->FindOrBuildMaterial("G4_Be");

      // Cu
      Cu = nistManager->FindOrBuildMaterial("G4_Cu");
    **/
  // Pb
  Pb = nistManager->FindOrBuildMaterial("G4_Pb");

  // Fe
  Fe = nistManager->FindOrBuildMaterial("G4_Fe");
  /*
    // Ti
    Ti = nistManager->FindOrBuildMaterial("G4_Ti");

    // Ni
    Ni = nistManager->FindOrBuildMaterial("G4_Ni");

    // Si
    Si = nistManager->FindOrBuildMaterial("G4_Si");

    // LSO
    LSO = new G4Material(name = "LSO", density = 7.35 * g / cm3, ncomponents =
  3); LSO->AddElement(eLu, natoms = 2); LSO->AddElement(eSi, natoms = 1);
    LSO->AddElement(eO, natoms = 5);

    // YSO
    YSO = new G4Material(name = "YSO", density = 4.45 * g / cm3, ncomponents =
  3); YSO->AddElement(eY, natoms = 2); YSO->AddElement(eSi, natoms = 1);
    YSO->AddElement(eO, natoms = 5);

    // LYSO
    LYSO =
        new G4Material(name = "LYSO", density = 7.25 * g / cm3, ncomponents =
  2); LYSO->AddMaterial(YSO, fractionmass = 10. * perCent);
    LYSO->AddMaterial(LSO, fractionmass = 90. * perCent);

    // YAP
    YAP = new G4Material(name = "YAP", density = 5.37 * g / cm3, ncomponents =
  3); YAP->AddElement(eY, natoms = 1); YAP->AddElement(eAl, natoms = 1);
    YAP->AddElement(eO, natoms = 3);

    // NaI
    NaI = new G4Material(name = "NaI", density = 3.67 * g / cm3, ncomponents =
  2); NaI->AddElement(eNa, natoms = 1); NaI->AddElement(eI, natoms = 1);

    // CsI
    CsI = new G4Material(name = "CsI", density = 4.51 * g / cm3, ncomponents =
  2); CsI->AddElement(eCs, natoms = 1); CsI->AddElement(eI, natoms = 1);

    // LaBr3
    LaBr3 =
        new G4Material(name = "LaBr3", density = 5.06 * g / cm3, ncomponents =
  2); LaBr3->AddElement(eLa, natoms = 1); LaBr3->AddElement(eBr, natoms = 3);

    // CeBr3
    CeBr3 =
        new G4Material(name = "CeBr3", density = 5.18 * g / cm3, ncomponents =
  2); CeBr3->AddElement(eCe, natoms = 1); CeBr3->AddElement(eBr, natoms = 3);

    // LaBr3_Ce
    LaBr3_Ce = new G4Material(name = "LaBr3_Ce", density = 5.08 * g / cm3,
                              ncomponents = 2);
    LaBr3_Ce->AddMaterial(LaBr3, fractionmass = 95. * perCent);
    LaBr3_Ce->AddMaterial(CeBr3, fractionmass = 5. * perCent);

    // aerogel
    aerogel = new G4Material(name = "aerogel", density = 0.11 * g / cm3,
                             ncomponents = 2);
    aerogel->AddElement(eSi, natoms = 1);
    aerogel->AddElement(eO, natoms = 2);
  **/
  // plastic
  plastic = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

  // PMMA
  PMMA =
      new G4Material(name = "PMMA", density = 1.20 * g / cm3, ncomponents = 3);
  PMMA->AddElement(eH, natoms = 8);
  PMMA->AddElement(eC, natoms = 5);
  PMMA->AddElement(eO, natoms = 2);

  // PVC
  // PVC = nistManager->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE ");
  PVC = new G4Material(name = "PVC", density = 1.40 * g / cm3, ncomponents = 3);
  PVC->AddElement(eC, natoms = 2);
  PVC->AddElement(eH, natoms = 3);
  PVC->AddElement(eCl, natoms = 1);
  /*
    // sekiei
    sekiei = new G4Material(name = "sekiei", density = 2.20 * g / cm3,
                            ncomponents = 2);
    sekiei->AddElement(eSi, natoms = 1);
    sekiei->AddElement(eO, natoms = 2);

    // glass (2.4 - 2.6*g/cm3)
    glass =
        new G4Material(name = "glass", density = 2.6 * g / cm3, ncomponents =
  2); glass->AddElement(eSi, natoms = 1); glass->AddElement(eO, natoms = 2);


    // teflon
    teflon =
        new G4Material(name = "teflon", density = 2.2 * g / cm3, ncomponents =
  2); teflon->AddElement(eC, fractionmass = 24.0183 * perCent);
    teflon->AddElement(eF, fractionmass = 75.9817 * perCent);
  **/

  // SUS304
  SUS304 = new G4Material(name = "SUS304", density = 7.93 * g / cm3,
                          ncomponents = 3);
  SUS304->AddElement(eFe, fractionmass = 74. * perCent);
  SUS304->AddElement(eCr, fractionmass = 18. * perCent);
  SUS304->AddElement(eNi, fractionmass = 8. * perCent);

  // kapton
  kapton = nistManager->FindOrBuildMaterial("G4_KAPTON");
  /*
    // mylar
    mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");

    // permalloy
    permalloy = new G4Material(name = "permalloy", density = 8.6 * g / cm3,
                               ncomponents = 4);
    permalloy->AddElement(eCu, fractionmass = 5. * perCent);
    permalloy->AddElement(eMo, fractionmass = 4. * perCent);
    permalloy->AddElement(eNi, fractionmass = 78. * perCent);
    permalloy->AddElement(eFe, fractionmass = 13. * perCent);

    // AlFlame
    AlFlame = new G4Material(name = "AlFlame", density = 1.08 * g / cm3,
                             ncomponents = 1);
    AlFlame->AddElement(eAl, fractionmass = 100. * perCent);
    **/
}

Material::~Material() { G4cerr << "destractor of Material" << G4endl; }

G4Material* Material::GetMaterial(const G4String& name) const {
  if (name == "vacuum") return vacuum;
  if (name == "air") return air;
  // if (name == "water") return water;
  // if (name == "N2") return N2;
  if (name == "concrete") return concrete;

  // if (name == "Be") return Be;
  if (name == "Al") return Al;
  // if (name == "Cu") return Cu;
  if (name == "Pb") return Pb;
  if (name == "Fe") return Fe;
  // if (name == "Ti") return Ti;
  // if (name == "Ni") return Ni;
  // if (name == "Si") return Si;

  // if (name == "LSO") return LSO;
  // if (name == "YSO") return YSO;
  // if (name == "LYSO") return LYSO;
  // if (name == "YAP") return YAP;
  // if (name == "NaI") return NaI;
  // if (name == "CsI") return CsI;
  // if (name == "LaBr3") return LaBr3;
  // if (name == "CeBr3") return CeBr3;
  // if (name == "LaBr3_Ce") return LaBr3_Ce;

  // if (name == "aerogel") return aerogel;
  if (name == "plastic") return plastic;
  if (name == "PMMA") return PMMA;
  if (name == "PVC") return PVC;
  // if (name == "sekiei") return sekiei;
  // if (name == "glass") return glass;
  if (name == "SUS304") return SUS304;
  // if (name == "teflon") return teflon;
  if (name == "kapton") return kapton;
  // if (name == "mylar") return mylar;
  // if (name == "permalloy") return permalloy;
  // if (name == "AlFlame") return AlFlame;

  G4cout << "ERROR :: material " << name << " is not implemented" << G4endl;

  return 0;
}
