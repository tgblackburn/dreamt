#include <PrimaryGeneratorAction.hpp>

#include <G4ParticleGun.hh>
#include <G4ParticleDefinition.hh>
#include <G4Electron.hh>
#include <CLHEP/Units/SystemOfUnits.h>

PrimaryGeneratorAction::PrimaryGeneratorAction (G4double energy)
 {
  gun = new G4ParticleGun();
  G4ParticleDefinition *particle = G4Electron::ElectronDefinition();
  gun->SetParticleDefinition (particle);
  gun->SetParticleEnergy (energy);
  gun->SetParticleMomentumDirection (G4ThreeVector (1.0, 0.0, 0.0));
  gun->SetParticlePosition (G4ThreeVector (-0.05*CLHEP::m, 0, 0));
 }

PrimaryGeneratorAction::~PrimaryGeneratorAction()
 {
  delete gun;
 }

void PrimaryGeneratorAction::GeneratePrimaries (G4Event *event)
 {
  // kinE = G4RandGauss::shoot (mean, sigma); // include "Randomize.hh"
  // gun->SetParticleEnergy (kinE);
  // angle = G4UniformRand();
  // gun->SetParticleMomentumDirection (G4ThreeVector(sin(angle), 0, cos(angle)));
  gun->GeneratePrimaryVertex (event);
 }
