#include "StateBeginCharge.h"

StateBeginCharge::StateBeginCharge(State *parent) :
    State(parent)
{

}

StateBeginCharge::~StateBeginCharge()
{

}

void StateBeginCharge::onEntry(std::string paraP)
{
    std::cout << "StateBeginCharge::onEntry()" << std::endl;
    parentM->postEvent("begin charge");
    sleep(1);
}

void StateBeginCharge::onLoop()
{
    std::cout << "StateBeginCharge::onLoop()" << std::endl;
    parentM->postEvent("finish charge");
    sleep(1);
}

void StateBeginCharge::onExit()
{
    std::cout << "StateBeginCharge::onExit()" << std::endl;
}
