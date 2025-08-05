#include "StateFinish.h"

StateFinish::StateFinish(State *parent) :
    State(parent)
{

}

StateFinish::~StateFinish()
{

}

void StateFinish::onEntry(std::string paraP)
{
    std::cout << "StateFinish::onEntry()" << std::endl;
    std::cout << "job result:" << paraP << std::endl;
    parentM->postEvent("get job");
    sleep(1);
}

void StateFinish::onLoop()
{
    std::cout << "StateFinish::onLoop()" << std::endl;
}

void StateFinish::onExit()
{
    std::cout << "StateFinish::onExit()" << std::endl;
}
