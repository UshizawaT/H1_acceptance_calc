#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4PrimaryParticle.hh>
#include <G4PrimaryVertex.hh>
#include <G4RandomDirection.hh>
#include <G4ThreeVector.hh>
#include <PrimaryGeneratorAction.hh>

#include "DataManager.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "GlobalVariables.hh"
#include "Randomize.hh"
#include "XMLParamParser.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;

using namespace CLHEP;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
 public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

 private:
  // G4ParticleGun* fParticleGun;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4double p_mu;
  G4ThreeVector mom_vec;
  //  direction
  // G4double beam_spread_angle = 30 * mrad;
  G4ThreeVector direction;  // = G4ThreeVector{0., 0., 1.};
  G4PrimaryParticle* primary_particle;

  G4double spangle, theta, phi;
  G4double hsize, vsize, pos_x, pos_y;
  G4ThreeVector position;
  G4double time_zero;
  G4PrimaryVertex* primary_vertex;
  G4int pid;
  G4double ekin;
};

#endif
