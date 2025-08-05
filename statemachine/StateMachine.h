#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>
#include <mutex>
#include "State.h"

typedef struct
{
    std::string cmd;
    State *nextState;
} S_TransEvent;

class StateMachine : public State
{
public:
    StateMachine();
    virtual ~StateMachine();

    void start();
    void stop();
    void transferState(std::string transStateP);
    void addFinalState(State *pFinalStateP);
    void runningMachine();

private:
    void executeState();
    void executeFinalState();
    void transferOperate();
    void setTransEvent(S_TransEvent transEventP);
    S_TransEvent getTransEvent();
    int getMachineState();
    void setMachineState(int stateP);
    void autoSetInitState();

private:
    enum {
        INIT = 0,
        RUNNING = 1,
        STOPPED = 2,
    };

private:
    State *finalStateM;
    int machineStateM;
    std::vector<S_TransEvent> transVecM;
    std::mutex transVecMutexM;
};

#endif
