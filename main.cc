//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * This product includes software developed by Members of the       *
// * Geant4 Collaboration ( http://cern.ch/geant4 ).                  *
// *                                                                  *
// * This product is a template code for Geant4 provided by Y. Kim.   *
// * Author: Young-su Kim (Evan Kim)                                  *
// * E-mail: evandde@gmail.com                                        *
// * homepage: https://evandde.github.io/                             *
// * Tested with Geant4 version 10.7.p01 at 2021.06.06.               *
// *                                                                  *
// ********************************************************************
//

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char **argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive *ui = nullptr;
    if (argc == 1)
        ui = new G4UIExecutive(argc, argv);

    // Set random seed number
    G4Random::setTheSeed(time(nullptr));

    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization);

    // Initialize G4 kernel
    runManager->Initialize();

    // Initialize visualization
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    if (ui)
    {
        // interactive mode
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else
    {
        // batch mode
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command + filename);
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !
    delete visManager;
    delete runManager;

    return 0;
}
