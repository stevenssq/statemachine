#ifndef STATE_FINISH_CHARGE
#define STATE_FINISH_CHARGE

#include "State.h"

class StateFinishCharge : public State
{
public:
    StateFinishCharge(State *parent = 0);
    virtual ~StateFinishCharge();

    virtual void onEntry(std::string paraP);
    virtual void onLoop();
    virtual void onExit();
};

#endif
