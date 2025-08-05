#ifndef STATE_DO_JOB
#define STATE_DO_JOB

#include "State.h"

class StateDoJob : public State
{
public:
    StateDoJob(State *parent = 0);
    virtual ~StateDoJob();

    virtual void onEntry(std::string paraP);
    virtual void onLoop();
    virtual void onExit();
};

#endif
