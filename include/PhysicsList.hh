#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics_option4
/// - G4EmStandardPhysics
/// - G4IonBinaryCascadePhysics
/// - G4HadronPhysicsQGSP_BIC_HP

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
