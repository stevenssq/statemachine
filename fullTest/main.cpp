#include <iostream>
#include <thread>
#include <functional>
#include <StateMachine.h>
#include "userstate/StateStop.h"
#include "userstate/StateGetJob.h"
#include "userstate/StateDoJob.h"
#include "userstate/StateFinish.h"
#include "userstate/StateBeginCharge.h"
#include "userstate/StateFinishCharge.h"

StateMachine *pStateMachine;
void initStateMachine();

int main(int argc, char *argv[])
{
    //初始化状态机
    initStateMachine();

    //启动状态机，会进入work父状态，并运行其中的子状态
    std::cout << "*******start machine,in work state*******" << std::endl;
    pStateMachine->start();
    sleep(7);

    //当需要充电时，切换到charge父状态，并运行其中的子状态
    std::cout << "*******switch to charge state*******" << std::endl;
    pStateMachine->transferState("charge state");
    sleep(7);

    //当充电结束时，再切回work父状态
    std::cout << "*******switch to work state*******" << std::endl;
    pStateMachine->transferState("work state");
    sleep(7);

    //停止状态机
    std::cout << "*******stop machine*******" << std::endl;
    pStateMachine->stop();

    while(1)
    {
        sleep(1);
    }

    return 0;
}

void initStateMachine()
{
    pStateMachine = new StateMachine();

    //创建2个父状态，work父状态与charge父状态
    State *pWorkState = new State(pStateMachine);
    State *pChargeState = new State(pStateMachine);

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

    //创建2个子状态，并设置父状态为charge父状态
    StateBeginCharge *pStateBeginCharge = new StateBeginCharge(pChargeState);
    StateFinishCharge *pStateFinishCharge = new StateFinishCharge(pChargeState);

    //向charge父状态注册子状态，并设置子状态的标签
    pChargeState->addState("begin charge", pStateBeginCharge);
    pChargeState->addState("finish charge", pStateFinishCharge);
    //初始化charge父状态运行时的第一个子状态
    pChargeState->setInitState("begin charge");

    //向状态机注册2个父状态，并设置父状态标签，标签用于控制状态机在父状态之间切换
    pStateMachine->addState("work state", pWorkState);
    pStateMachine->addState("charge state", pChargeState);
    //向状态机注册stop状态，状态机停止时会进入该状态
    pStateMachine->addFinalState(pStateStop);
    //设置状态机启动时进入哪个父状态
    pStateMachine->setInitState("work state");

    //启动状态机运行时的内部线程
    std::thread tmpThread(std::bind(&StateMachine::runningMachine, pStateMachine));
    tmpThread.detach();
}
