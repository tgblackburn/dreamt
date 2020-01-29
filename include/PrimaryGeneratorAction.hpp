#ifndef PRIMARY_GUARD
#define PRIMARY_GUARD

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
 {
  public:
    PrimaryGeneratorAction (G4double energy);
    ~PrimaryGeneratorAction();
    void GeneratePrimaries (G4Event *event);

  private:
    G4ParticleGun *gun;
 };

#endif
