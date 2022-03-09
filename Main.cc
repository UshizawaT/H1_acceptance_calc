#include <TString.h>
#include <time.h>

#include <G4AllocatorList.hh>
#include <G4PhysListFactory.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>

#include "ActionInitialization.hh"
#include "BaseConstruct.hh"
#include "DataManager.hh"
#include "DetectorConstruction.hh"
#include "GlobalVariables.hh"
#include "Material.hh"
#include "RootManager.hh"
#include "Scintillator.hh"
#include "VisAttributes.hh"
#include "XMLParamParser.hh"

using namespace CLHEP;

int main(int argc, char* argv[]) {
  clock_t start_time = clock();
  if (argc < 3 || argc > 4) {
    G4cerr << argv[0] << " seed setting_xml_basename [macroFile]" << G4endl;
    return 1;
  }

  G4UIExecutive* ui = 0;
  // if(argc==5){
  if (argc == 3) {
    ui = new G4UIExecutive(argc, argv);
  }
  G4long seed = atoi(argv[1]);
  G4String xmlfname = argv[2];

  // G4cerr << "prepared root file" << G4endl;
  //   Sensitive Detector
  G4cout << "prepare SD" << G4endl;
  G4SDManager* SDManager = G4SDManager::GetSDMpointer();
  Scintillator* plastic_scinti = new Scintillator("Plastic_scinti");
  SDManager->AddNewDetector(plastic_scinti);
  XMLParamParser* xmlsetting =
      new XMLParamParser(TString(xmlfname), plastic_scinti);
  G4String basename = G4String(xmlsetting->GetFileBaseName());
  G4String xmlbasename = G4String(xmlsetting->GetXMLBaseName());
  G4String rootFileName;  // = "data/";
  rootFileName = "data/" + basename + "_seed" + G4String(argv[1]) + "_" +
                 xmlbasename + ".root";
  G4cerr << "filename : " << rootFileName << G4endl;
  // G4cerr << "beam type, tgt. material : " << _beam->GetBeamType() << ", "
  //        << _stopping_tgt->GetTargetMaterial() << G4endl;

  // choose the random engine
  RanluxEngine theRanluxEngine(seed, 4);
  HepRandom::setTheEngine(&theRanluxEngine);
  HepRandom::setTheSeed(seed);
  // G4cerr << "set user var" << G4endl;

  G4cout << "prepare run manager" << G4endl;
  // construct the default run manager
  G4RunManager* runManager = new G4RunManager;
  // std::unique_ptr<G4RunManager> runManager;

  // construct the ROOT manager
  G4cout << "prepare ROOT" << G4endl;
  RootManager::SetFileName(rootFileName);
  RootManager::SetTreeName("tree");
  RootManager::SetInfoTreeName("info");

  // G4cerr << "prepared SD" << G4endl;

  // set mandatory initialization classes
  G4cout << "prepare Geom." << G4endl;
  runManager->SetUserInitialization(new DetectorConstruction(xmlsetting));

  G4cout << "prepare physics list" << G4endl;
  G4PhysListFactory factory;
  G4VModularPhysicsList* physicsList =
      factory.GetReferencePhysList("FTFP_BERT_EMV");  // fast
  physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);

  G4cerr << "prepare action init." << G4endl;
  runManager->SetUserInitialization(new ActionInitialization);
  // G4cerr << "Action initialized" << G4endl;

  // initialize visualization
  G4cout << "initialize vis." << G4endl;
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // G4cerr << "Visualization initialized" << G4endl;

  // get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    // batch mode
    std::cerr << "batch mode!" << std::endl;
    G4String command = "/control/execute ";
    G4String fileName = argv[3];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }
  // G4cerr << "complete simulation!" << G4endl;
  //  job termination
  delete visManager;

  // G4cerr << "exist ui manager? :" << (UImanager) << G4endl;
  DataManager::DeleteVar();
  delete runManager;
  // runManager.reset();
  // G4cerr << "Success disalocate memory" << G4endl;
  clock_t end_time = clock();
  double lapse_time =
      static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1.;
  G4cerr << "Simulation time : " << lapse_time << G4endl;

  return 0;
}
