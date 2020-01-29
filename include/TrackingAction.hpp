#ifndef TRACKING_GUARD
#define TRACKING_GUARD

#include <G4UserTrackingAction.hh>

class TrackingAction : public G4UserTrackingAction
 {
  public:
    virtual void PostUserTrackingAction (const G4Track *);
 };

#endif
