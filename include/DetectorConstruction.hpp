#ifndef DETECTOR_GUARD
#define DETECTOR_GUARD

#include <G4VUserDetectorConstruction.hh>
#include <CLHEP/Units/SystemOfUnits.h>

class DetectorConstruction : public G4VUserDetectorConstruction
 {
  public:
    DetectorConstruction (const G4String &materialName="G4_Pb", G4double thickness=200*CLHEP::um);
    ~DetectorConstruction ();
    virtual G4VPhysicalVolume *Construct();

  private:
    G4String fMaterialName;
    G4double fThickness;
 };

#endif
