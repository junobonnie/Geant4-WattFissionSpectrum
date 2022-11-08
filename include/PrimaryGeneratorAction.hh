#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction() override;

    virtual void GeneratePrimaries(G4Event *) override;

private:
    G4ParticleGun *fPrimary;
};

#endif
