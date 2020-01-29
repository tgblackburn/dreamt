#include <G4Event.hh>
#include <EventAction.hpp>

struct timer {double s; int min, hr;};

EventAction::EventAction (G4int numberOfEvents)
 {
  num = numberOfEvents;
  start = std::chrono::high_resolution_clock::now();
 }

void EventAction::EndOfEventAction (const G4Event *event)
 {
  G4int current = event->GetEventID();
  G4int every = num / 20;
  struct timer rt, ettc;
  
  if (current > 0 && ((current % every) == 0))
   {
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);

    rt.s   = elapsed.count();
    rt.hr  = rt.s / 3600.0;
    rt.s  -= 3600 * rt.hr;
    rt.min = rt.s / 60.0;
    rt.s   -= 60 * rt.min;

    ettc.s   = elapsed.count() * (num - current) / (double)current;
    ettc.hr  = ettc.s / 3600.0;
    ettc.s  -= 3600 * ettc.hr;
    ettc.min = ettc.s / 60.0;
    ettc.s  -= 60 * ettc.min;

    fprintf (stdout,
	     "Completed event %10d of %10d, RT = %02d:%02d:%04.1lf, ETTC = %02d:%02d:%04.1lf.\n",
	    current, num, rt.hr, rt.min, rt.s, ettc.hr, ettc.min, ettc.s);
    fflush (stdout);
   }
 }
