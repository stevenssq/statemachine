#include "StateGetJob.h"

StateGetJob::StateGetJob(State *parent) :
    State(parent)
{

}

StateGetJob::~StateGetJob()
{

}

void StateGetJob::onEntry(std::string paraP)
{
    std::cout << "StateGetJob::onEntry()" << std::endl;
    parentM->postEvent("get job");
    sleep(1);
}

void StateGetJob::onLoop()
{
    std::cout << "StateGetJob::onLoop()" << std::endl;
    sleep(1);
    parentM->postEvent("do job");
}

void StateGetJob::onExit()
{
    std::cout << "StateGetJob::onExit()" << std::endl;
}
