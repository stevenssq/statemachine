#ifndef STATE_GET_JOB
#define STATE_GET_JOB

#include "State.h"

class StateGetJob : public State
{
public:
    StateGetJob(State *parent = 0);
    virtual ~StateGetJob();

    virtual void onEntry(std::string paraP);
    virtual void onLoop();
    virtual void onExit();
};

#endif
