#include "RunAction.hh"

#include "DataManager.hh"
#include "G4Run.hh"
#include "GlobalVariables.hh"
#include "RootManager.hh"

RunAction::RunAction() { G4cerr << "constractor of run action" << G4endl; }

RunAction::~RunAction() { G4cerr << "destractor of run action" << G4endl; }

void RunAction::BeginOfRunAction(const G4Run*) {
  // G4cerr << "Run initialized" << G4endl;
  DataManager::Initialize();
  RootManager::CreateFile();
  RootManager::CreateTree();
  RootManager::CreateInfoTree();
  RootManager::SetTree();
}

void RunAction::EndOfRunAction(const G4Run*) { RootManager::rootFinalize(); }
