#include "StateMachine.h"

StateMachine::StateMachine():
    finalStateM(NULL),
    machineStateM(INIT)
{
}

StateMachine::~StateMachine()
{

}

void StateMachine::addFinalState(State *pFinalStateP)
{
    finalStateM = pFinalStateP;
}

void StateMachine::setTransEvent(S_TransEvent transEventP)
{
    transVecMutexM.lock();
    transVecM.push_back(transEventP);
    transVecMutexM.unlock();
}

S_TransEvent StateMachine::getTransEvent()
{
    transVecMutexM.lock();
    S_TransEvent transEvent = transVecM.front();
    transVecM.erase(transVecM.begin());
    transVecMutexM.unlock();

    return transEvent;
}

void StateMachine::executeState()
{
    if (NULL == currentStateM)
    {
        std::cout << "null point currentStateM!" << std::endl;
        sleep(1);
        return;
    }

    if (currentStateM != lastStateM)
    {
        if (lastStateM != NULL)
        {
            if (lastStateM == finalStateM)
            {
                lastStateM->onExit();
            }
            else
            {
                lastStateM->stateExit();
            }
        }
        lastStateM = currentStateM;
    }

    currentStateM->executeState();
}

void StateMachine::transferState(std::string transStateP)
{
    std::map<std::string,  State *>::iterator iter;
    iter = stateMapM.find(transStateP);
    if(iter != stateMapM.end())
    {
        S_TransEvent transEvent = {"transfer", iter->second};
        setTransEvent(transEvent);
    }
    else
    {
        S_TransEvent transEvent = {"transfer", NULL};
        setTransEvent(transEvent);
    }
}

void StateMachine::executeFinalState()
{
    if (finalStateM != NULL)
    {
        finalStateM->onEntry("");
        lastStateM = finalStateM;
    }
}

int StateMachine::getMachineState()
{
    return machineStateM;
}

void StateMachine::setMachineState(int stateP)
{
    machineStateM = stateP;
}

void StateMachine::transferOperate()
{
    if (transVecM.empty())
    {
        return;
    }

    S_TransEvent transEvent = getTransEvent();

    if (transEvent.cmd == "start")
    {
        if (RUNNING == getMachineState())
        {
            return;
        }
        autoSetInitState();
        currentStateM = initStateM;
        if (currentStateM != NULL)
        {
            currentStateM->stateEntry();
        }
        setMachineState(RUNNING);
    }
    else if (transEvent.cmd == "stop")
    {
        if (STOPPED == getMachineState())
        {
            return;
        }

        if (lastStateM != NULL)
        {
            lastStateM->stateExit();
        }
        lastStateM = NULL;
        executeFinalState();
        setMachineState(STOPPED);
    }
    else
    {
        if (STOPPED == getMachineState())
        {
            std::cout << "state machine stopped, ignore transfer" << std::endl;
            return;
        }

        if (transEvent.nextState == currentStateM)
        {
            return;
        }

        lastStateM = currentStateM;
        currentStateM = transEvent.nextState;
        if (currentStateM != NULL)
        {
            currentStateM->stateEntry();
        }
    }
}

void StateMachine::runningMachine()
{
    while (true)
    {
        usleep(10);
        transferOperate();

        switch(machineStateM)
        {
            case RUNNING:
                executeState();
                break;
            case STOPPED:
                usleep(100);
                break;
            default:
                break;
        }
    }
}

void StateMachine::start()
{
    S_TransEvent transEvent = {"start", NULL};
    setTransEvent(transEvent);
}

void StateMachine::stop()
{
    S_TransEvent transEvent = {"stop", NULL};
    setTransEvent(transEvent);
}

void StateMachine::autoSetInitState()
{
    if (NULL == initStateM && 1 == stateMapM.size())
    {
        std::map<std::string, State *>::iterator it = stateMapM.begin();
        initStateM = it->second;
    }
}