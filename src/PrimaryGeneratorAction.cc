#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction() {  //, fParticleGun(0) {
  // fParticleGun = new G4ParticleGun();
  particleName = _beam->GetBeamType();
  spangle = _beam->GetBeamSpreadAngle();
  hsize = _beam->GetBeamHSize();
  vsize = _beam->GetBeamVSize();
  mean_mom = _beam->GetBeamMomentum();
  sigma_mom = mean_mom * _beam->GetBeamPPercent() * 0.01;
  G4cerr << "constractor of primary gen." << G4endl;
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
  // p_mu = (G4RandGauss(*CLHEP::HepRandom::getTheEngine())
  //            .shoot(27.4 * MeV, 0.274 * MeV));
  p_mu = (G4RandGauss(*CLHEP::HepRandom::getTheEngine())
              .shoot(mean_mom * MeV, sigma_mom * MeV));
  // fParticleGun->SetParticleMomentum(p_mu);
  phi = G4UniformRand() * twopi;
  direction = G4ThreeVector{sin(spangle * deg) * cos(phi),
                            sin(spangle * deg) * sin(phi), cos(spangle * deg)};
  mom_vec = p_mu * direction;
  // fParticleGun->SetParticleMomentumDirection(direction);
  // primary_particle->SetMomentum(mom_vec.x(), mom_vec.y(), mom_vec.z());
  primary_particle =
      new G4PrimaryParticle(particleTable->FindParticle(particleName),
                            mom_vec.x(), mom_vec.y(), mom_vec.z());
  // position
  theta = twopi * G4UniformRand();
  if (hsize == 0.) {
    pos_x = 0;
  }
  if (vsize == 0.) {
    pos_y = 0;
  }
  if (hsize != 0.) {
    pos_x = (G4RandGauss(*CLHEP::HepRandom::getTheEngine()).shoot(0., hsize));
  }
  if (vsize != 0.) {
    pos_y = (G4RandGauss(*CLHEP::HepRandom::getTheEngine()).shoot(0., vsize));
  }
  // std::cout << pos_x << ", " << pos_y << std::endl;

  position = G4ThreeVector{pos_x * mm, pos_y * mm, -800 * mm};
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
