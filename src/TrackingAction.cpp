#include <RunAction.hpp>
#include <TrackingAction.hpp>

#include <G4Track.hh>
#include <G4Electron.hh>
#include <G4Gamma.hh>
#include <G4Positron.hh>
#include <CLHEP/Units/SystemOfUnits.h>

void TrackingAction::PostUserTrackingAction (const G4Track *track)
 {
  auto am = G4AnalysisManager::Instance();

  auto energy = track->GetKineticEnergy();
  auto def = track->GetDefinition();
  auto pos = track->GetPosition(); // current position
  auto start = track->GetVertexPosition(); // where track started

  if (pos.x() < 0.05 * CLHEP::m)
    return;

  if (def == G4Electron::Electron())
    am->FillH1 (0, energy);
  else if (def == G4Positron::Positron())
   {
    auto dir = track->GetMomentumDirection();
    G4double angle = atan2 (hypot (dir.y(), dir.z()), dir.x());
    am->FillH1 (1, energy);
    am->FillH2 (1, energy, angle);
   }
  else if (def == G4Gamma::Gamma())
   {
    auto dir = track->GetMomentumDirection();
    G4double angle = atan2 (hypot (dir.y(), dir.z()), dir.x());    
    am->FillH1 (2, energy);
    am->FillH2 (0, energy, angle);
   }

  /*
  if (def == G4Positron::Positron() || def == G4Gamma::Gamma())
   {
  G4cout << "Binned " << def->GetParticleName() << " with energy " << energy / CLHEP::MeV << " MeV at x = " << pos.x() / CLHEP::mm << " mm, which started at x = " << start.x() / CLHEP::um << " um" << G4endl;
   }
  */
 }
