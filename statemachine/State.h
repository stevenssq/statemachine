#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include <map>
#include <unistd.h>

typedef struct
{
    std::string nextState;
    std::string para;
} S_EVENT;

class State
{
public:
    State(State *parent = 0);
    virtual ~State();

public:
    virtual void onEntry(std::string paraP);
    virtual void onExit();
    virtual void onLoop();
    void postEvent(std::string eventP, std::string paraP = "");
    void stateEntry();
    void stateExit();
    void executeState();
    void setInitState(std::string initState);
    void addState(std::string transEvent, State *nextState);

private:
    S_EVENT getNextEvent();
    void stateInit();

protected:
    State *parentM;
    State *initStateM;
    State *currentStateM;
    State *lastStateM;
    S_EVENT currentEventM;
    S_EVENT lastEventM;
    std::list<S_EVENT> eventListM;
    std::map <std::string, State *> stateMapM;
};

#endif
