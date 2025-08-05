#include <iostream>
#include <thread>
#include <functional>
#include <StateMachine.h>
#include "userstate/StateStop.h"
#include "userstate/StateGetJob.h"
#include "userstate/StateDoJob.h"
#include "userstate/StateFinish.h"

StateMachine *pStateMachine;
void initStateMachine();

int main(int argc, char *argv[])
{
    //初始化状态机
    initStateMachine();

    //启动状态机
    std::cout << "*******start machine*******" << std::endl;
    pStateMachine->start();
    sleep(7);

    //停止状态机
    std::cout << "*******stop machine*******" << std::endl;
    pStateMachine->stop();
    sleep(2);

    //再次启动状态机
    std::cout << "*******start machine*******" << std::endl;
    pStateMachine->start();

    while(1)
    {
        sleep(1);
    }

    return 0;
}

void initStateMachine()
{
    pStateMachine = new StateMachine();

    //创建父状态
    State *pWorkState = new State(pStateMachine);
    //创建stop状态，这是一个特殊的状态，当停止状态机时会进入该状态
    StateStop *pStateStop = new StateStop(pStateMachine);

    //创建3个子状态，并设置父状态为work父状态
    StateGetJob *pStateGetJob = new StateGetJob(pWorkState);
    StateDoJob *pStateDoJob = new StateDoJob(pWorkState);
    StateFinish *pStateFinish = new StateFinish(pWorkState);

    //向work父状态注册子状态，并设置子状态的标签，标签是子状态之间切换的标记
    pWorkState->addState("get job", pStateGetJob);
    pWorkState->addState("do job", pStateDoJob);
    pWorkState->addState("job finish", pStateFinish);
    //初始化work父状态运行时的第一个子状态
    pWorkState->setInitState("get job");

    //向状态机注册父状态与stop状态
    pStateMachine->addState("work state", pWorkState);
    pStateMachine->addFinalState(pStateStop);
    //初始化状态机启动时进入work父状态，当只有一个父状态时，该行可以省略
    //pStateMachine->setInitState("work state");

    //启动状态机运行时的内部线程
    std::thread tmpThread(std::bind(&StateMachine::runningMachine, pStateMachine));
    tmpThread.detach();
}
