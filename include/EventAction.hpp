#ifndef EVENT_GUARD
#define EVENT_GUARD

#include <chrono>
#include <G4UserEventAction.hh>

class EventAction : public G4UserEventAction
 {
  public:
    EventAction (G4int numberOfEvents);
    virtual void EndOfEventAction (const G4Event *);

  private:
    G4int num;
    std::chrono::high_resolution_clock::time_point start;
 };

#endif
