#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSPopulation.hh"
#include "G4SDParticleWithEnergyFilter.hh"

#include "DetectorConstruction.hh"
#include "Configure.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // materials
    auto nist = G4NistManager::Instance();
    auto mat_Vaccum = nist->FindOrBuildMaterial("G4_Galactic");
    auto mat_Al = nist->FindOrBuildMaterial("G4_Al");
    //auto mat_Si = nist->FindOrBuildMaterial("G4_Si");
    
    // World
    auto world_size = 10.*m;
    auto world_sol = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
    auto world_log = new G4LogicalVolume(world_sol, mat_Vaccum, "World");
    auto world_phy = new G4PVPlacement(nullptr, G4ThreeVector(), world_log, "World", nullptr, false, 0);
    
    // Shield
    auto shield_depth = 10.*cm;
    auto shield_size = 2.*m;
    auto shield_pos = G4ThreeVector(0., 0., 0.);
    auto shield_sol = new G4Box("Shield", 0.5*shield_size, 0.5*shield_size, 0.5*shield_depth);
    auto shield_log = new G4LogicalVolume(shield_sol, mat_Al, "Shield");
    new G4PVPlacement(nullptr, shield_pos, shield_log, "Shield", world_log, false, 0);
    
    // Detector
    auto detector_depth = 10.*cm;
    auto detector_size = 2.*m;
    auto detector_pos = G4ThreeVector(0., 0., (shield_depth + detector_depth)/2);
    auto detector_sol = new G4Box("Detector", 0.5*detector_size, 0.5*detector_size, 0.5*detector_depth);
    auto detector_log = new G4LogicalVolume(detector_sol, mat_Vaccum, "Detector");
    new G4PVPlacement(nullptr, detector_pos, detector_log, "Detector", world_log, false, 0);
    
    return world_phy;
}
void DetectorConstruction::ConstructSDandField()
{
	auto mfd = new G4MultiFunctionalDetector("Detector");
	G4SDManager::GetSDMpointer()->AddNewDetector(mfd);
	
	char name[particle_num*Maximum_E/E_bin];
	
	for(G4int k = 0; k < particle_num; k++){
		for(G4int i =0; i < Maximum_E; i = i+E_bin){
		// Filter
		G4String results = particle[k];
		std::sprintf(name, " %dMeV",i);
		G4String psName(name);
		results += psName;
		auto psPop = new G4PSPopulation(results);
		auto filter = new G4SDParticleWithEnergyFilter("filter");
		filter->add(particle[k]);
		filter->SetKineticEnergy(i*MeV, (i+E_bin)*MeV);
		psPop->SetFilter(filter);
		
		mfd->RegisterPrimitive(psPop);
		}
	}
	SetSensitiveDetector("Detector", mfd);
}
