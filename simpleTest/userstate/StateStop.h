#ifndef STATE_STOP
#define STATE_STOP

#include "State.h"

class StateStop : public State
{
public:
    StateStop(State *parent = 0);
    virtual ~StateStop();

    virtual void onEntry(std::string paraP);
    virtual void onExit();
};


#endif
