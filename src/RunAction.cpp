#include <iomanip>
#include <G4Run.hh>
#include <RunAction.hpp>

#include <CLHEP/Units/SystemOfUnits.h>

RunAction::RunAction (G4String material, G4String thickness, G4double energy, G4int num)
 {
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel (2);

  std::string pre("G4_");
  std::string::size_type i = material.find(pre);
  if (i != std::string::npos)
    material.erase (i, pre.length()); // remove leading "G4_" if it exists

  filename = material + "x" + thickness;

  weight = 1.0 / num;
  max_energy = energy;
  /* Avg (RMS) angle = 19.2 MeV * sqrt (L/X0) / E0 */
  max_angle = 3.0 * 20 * CLHEP::MeV / max_energy;
 }

RunAction::~RunAction()
 {
  delete G4AnalysisManager::Instance();
 }

void RunAction::BeginOfRunAction (const G4Run *run)
 {
  //G4int total = run->GetNumberOfEvent();
  //G4int current = run->GetNumberOfEventToBeProcessed();
  //G4cout << current << " of " << total << G4endl;
   
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile (filename);
  analysisManager->CreateH1 ("electron", "e- energy spectrum",
			     200, 0, max_energy, "MeV");
  analysisManager->CreateH1 ("positron", "e+ energy spectrum",
			     200, 0, max_energy, "MeV");
  analysisManager->CreateH1 ("photon", "ph energy spectrum",
			     200, 0, max_energy, "MeV");
  analysisManager->CreateH2 ("photon", "ph energy-angle spectrum",
			     200, 0, max_energy,
			     100, 0, max_angle,
			     "MeV", "rad");
  analysisManager->CreateH2 ("positron", "e+ energy-angle spectrum",
			     200, 0, max_energy,
			     100, 0, max_angle,
			     "MeV", "rad");
  //analysisManager->SetH2Plotting (0, true);
 }

/* Histograms are populated in TrackingAction class, specifically
   in PostUserTrackingAction(), to get energy spectra at exit. */

void RunAction::EndOfRunAction (const G4Run *run)
 {
  auto analysisManager = G4AnalysisManager::Instance();

  for (int i = 0; i < 3; i++)
    analysisManager->ScaleH1 (i, weight / (max_energy / 200));

  for (int i = 0; i < 2; i++)
    analysisManager->ScaleH2 (i, weight / (max_energy * max_angle / (200 * 100)));
  
  analysisManager->Write();
  analysisManager->CloseFile();
 }
