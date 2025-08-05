#include "StateDoJob.h"

StateDoJob::StateDoJob(State *parent) :
    State(parent)
{

}

StateDoJob::~StateDoJob()
{

}

void StateDoJob::onEntry(std::string paraP)
{
    std::cout << "StateDoJob::onEntry()" << std::endl;
    parentM->postEvent("do job");
    sleep(1);
}

void StateDoJob::onLoop()
{
    std::cout << "StateDoJob::onLoop()" << std::endl;
    sleep(1);
    parentM->postEvent("job finish", "success");
}

void StateDoJob::onExit()
{
    std::cout << "StateDoJob::onExit()" << std::endl;
}
