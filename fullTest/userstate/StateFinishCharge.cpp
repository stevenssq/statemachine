#include "StateFinishCharge.h"

StateFinishCharge::StateFinishCharge(State *parent) :
    State(parent)
{

}

StateFinishCharge::~StateFinishCharge()
{

}

void StateFinishCharge::onEntry(std::string paraP)
{
    std::cout << "StateFinishCharge::onEntry()" << std::endl;
    parentM->postEvent("finish charge");
    sleep(1);
}

void StateFinishCharge::onLoop()
{
    std::cout << "StateFinishCharge::onLoop()" << std::endl;
    parentM->postEvent("finish charge");
    sleep(1);
}

void StateFinishCharge::onExit()
{
    std::cout << "StateFinishCharge::onExit()" << std::endl;
}
