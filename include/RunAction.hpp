#ifndef RUN_GUARD
#define RUN_GUARD

#include <G4UserRunAction.hh>

//#include "g4root.hh" // ROOT style output
//#include "g4xml.hh"
#include <g4csv.hh>

class RunAction : public G4UserRunAction
 {
  public:
    RunAction (G4String materialName, G4String thickness, G4double energy, G4int num);
    ~RunAction();
    virtual void BeginOfRunAction (const G4Run *);
    virtual void EndOfRunAction (const G4Run *);

  private:
    G4String filename;
    G4double weight, max_energy, max_angle;
 };

#endif
