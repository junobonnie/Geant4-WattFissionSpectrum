#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "Configure.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    ~EventAction() override;

    virtual void BeginOfEventAction(const G4Event *) override;
    virtual void EndOfEventAction(const G4Event *) override;

private:
	G4int event_num;
	G4int fHCID[particle_num*Maximum_E/E_bin];
	int spectrum[particle_num][Maximum_E/E_bin] = {0,};
};

#endif // EVENTACTION_HH
