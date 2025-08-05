#ifndef STATE_FINISH
#define STATE_FINISH

#include "State.h"

class StateFinish : public State
{
public:
    StateFinish(State *parent = 0);
    virtual ~StateFinish();

    virtual void onEntry(std::string paraP);
    virtual void onLoop();
    virtual void onExit();
};


#endif
