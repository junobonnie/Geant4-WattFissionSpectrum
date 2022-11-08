#include "G4ParticleGun.hh"
#include "G4Proton.hh"
#include "G4SystemOfUnits.hh"

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
    fPrimary->SetParticleDefinition(G4Proton::Definition());
    fPrimary->SetParticleEnergy(100.*MeV);
    fPrimary->SetParticlePosition(G4ThreeVector(0., 0., -5.*m));
    fPrimary->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    fPrimary->GeneratePrimaryVertex(anEvent);
}
