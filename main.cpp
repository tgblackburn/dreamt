#include <G4RunManager.hh> // single-threaded
#include <G4HadronicProcessStore.hh>
#include <QGSP_BERT.hh> // <FTFP_BERT.hh>

#include <DetectorConstruction.hpp>
#include <PrimaryGeneratorAction.hpp>
#include <RunAction.hpp>
#include <TrackingAction.hpp>
#include <EventAction.hpp>

int main (int argc, char **argv)
 {   
  if (!(argc == 4 || argc == 5))
   {
    G4cout << "Usage: ./dreamt material L_micron E_MeV [num]" << G4endl;
    return 0;
   }

  G4String material = argv[1];
  G4double thickness = std::stod (argv[2]);
  G4double energy = std::stod (argv[3]);
  G4int num = (argc == 5) ? std::stoi (argv[4]) : 100000000;

  G4RunManager *runManager = new G4RunManager;

  // Experimental setup, solid targets and so on
  auto detector = new DetectorConstruction (material, thickness * CLHEP::um);
  runManager->SetUserInitialization (detector);

  // What processes are included?
  auto physics = new QGSP_BERT(0); // FTFP_BERT
  runManager->SetUserInitialization (physics);
  G4HadronicProcessStore::Instance()->SetVerbose(0); // stop "Hadronic Processes Summary" getting printed

  // How to load primary particle beam
  auto primary = new PrimaryGeneratorAction (energy * CLHEP::MeV);
  runManager->SetUserAction (primary);

  // Actions per run (histogram init and print)
  auto runAction = new RunAction (argv[1], argv[2], energy * CLHEP::MeV, num);
  runManager->SetUserAction (runAction);

  // Actions per track (binning)
  auto trackAction = new TrackingAction();
  runManager->SetUserAction (trackAction);

  // Actions per event (progress report)
  auto eventAction = new EventAction (num);
  runManager->SetUserAction (eventAction);

  //G4UImanager *ui = G4UImanager::GetUIpointer();
  //ui->ApplyCommand("/process/verbose 0");

  runManager->Initialize();

  G4cout << num << " primary electrons with energy " << energy / CLHEP::MeV << " MeV. Beam on." << G4endl;

  runManager->BeamOn (num);

  G4cout << "Beam off." << G4endl;

  delete runManager;
  return 0;
 }
