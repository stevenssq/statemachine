#include "StateStop.h"

StateStop::StateStop(State *parent) :
    State(parent)
{

}

StateStop::~StateStop()
{

}

void StateStop::onEntry(std::string paraP)
{
    std::cout << "StateStop::onEntry()" << std::endl;
}

void StateStop::onExit()
{
    std::cout << "StateStop::onExit()" << std::endl;
}
