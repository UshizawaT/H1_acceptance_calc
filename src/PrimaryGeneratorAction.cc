#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction() {  //, fParticleGun(0) {
  // fParticleGun = new G4ParticleGun();
  particleName = _beam->GetBeamType();
  spangle = _beam->GetBeamSpreadAngle();
  size = _beam->GetBeamSize();
  mom_info = _beam->GetMomentum();
  G4cout << "beam constructer!" << G4endl;
  G4cout << "beam type : " << particleName << G4endl;
  G4cout << "beam spread angle : " << spangle << G4endl;
  G4cout << "beam size (x, y) : (" << size[0] << ", " << size[1] << ")"
         << G4endl;
  G4cout << "beam momentum (mean, sigma) : (" << mom_info[0] << ", "
         << mom_info[1] << ")" << G4endl;
  // fParticleGun->SetParticleDefinition(
  //     particleTable->FindParticle(particleName));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  G4cerr << "destractor of primary gen." << G4endl;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  // momentum
  // const G4double Eend = 0.546 * MeV;
  // G4double p_mu = 27.4 * MeV;
  p_mu = (G4RandGauss(*CLHEP::HepRandom::getTheEngine())
              .shoot(mom_info[0], mom_info[1]));
  // fParticleGun->SetParticleMomentum(p_mu);
  phi = G4UniformRand() * twopi;
  direction = G4ThreeVector{sin(spangle) * cos(phi), sin(spangle) * sin(phi),
                            cos(spangle)};
  mom_vec = p_mu * direction;
  // fParticleGun->SetParticleMomentumDirection(direction);
  // primary_particle->SetMomentum(mom_vec.x(), mom_vec.y(), mom_vec.z());
  primary_particle =
      new G4PrimaryParticle(particleTable->FindParticle(particleName),
                            mom_vec.x(), mom_vec.y(), mom_vec.z());
  // position
  theta = twopi * G4UniformRand();
  if (size[0] == 0.) {
    pos_x = 0;
  }
  if (size[1] == 0.) {
    pos_y = 0;
  }
  if (size[0] != 0.) {
    pos_x = (G4RandGauss(*CLHEP::HepRandom::getTheEngine()).shoot(0., size[0]));
  }
  if (size[1] != 0.) {
    pos_y = (G4RandGauss(*CLHEP::HepRandom::getTheEngine()).shoot(0., size[1]));
  }
  // std::cout << pos_x << ", " << pos_y << std::endl;

  position = G4ThreeVector{pos_x, pos_y, -800 * mm};
  // std::cout << position.x() << ", " << position.y() << ", " << position.z()
  //           << std::endl;
  //  std::cout << "success input vector!" << std::endl;
  time_zero = 0.0 * us;
  // std::cout << "success input time" << std::endl;
  //  primary_vertex->SetPosition(position.x(), position.y(), position.z());
  //  primary_vertex->SetT0(time_zero);
  primary_vertex = new G4PrimaryVertex{position, time_zero};
  // std::cout << "success set primary vertex!" << std::endl;
  primary_vertex->SetPrimary(primary_particle);
  // std::cout << "success set primary particle" << std::endl;
  anEvent->AddPrimaryVertex(primary_vertex);
  // std::cout << "success generate events" << std::endl;
  //   fParticleGun->SetParticlePosition(position);
  //   fParticleGun->GeneratePrimaryVertex(anEvent);
  pid = primary_particle->GetParticleDefinition()->GetPDGEncoding();
  // std::cout << "pid : " << pid << std::endl;
  //  pid = fParticleGun->GetParticleDefinition()->GetPDGEncoding();
  ekin = primary_particle->GetKineticEnergy();
  // std::cout << "Ekin : " << ekin << std::endl;
  //  ekin = fParticleGun->GetParticleEnergy();

  pid_in = pid;
  ekin_in = ekin / MeV;
  posX_in = position.x() / mm;
  posY_in = position.y() / mm;
  posZ_in = position.z() / mm;
  start_particle_num += 1;
  // std::cout << "success primary generation" << std::endl;
}
