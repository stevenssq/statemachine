一款纯C++编写的状态机，模拟Qt状态机的功能，支持linux与windows下运行，旨在解决某些场景下无法使用Qt的问题。

状态机支持父状态与子状态，父状态下可以注册多个子状态，子状态之间可以互相跳转，但不同父状态下的子状态是隔离的，
无法从某个父状态的子状态跳转到另一个父状态的子状态。

statemachine目录下是状态机的核心代码，simpleTest目录下演示了一个简单例子，该示例只包含一个父状态，fullTest目录下演示了
2个父状态的例子，以及父状态之间如何实现跳转。

**1.simpleTest**

编译运行方法：

 cd simpleTest && mkdir build

 cd build && cmake ../

 make && ./simplefsm
 
 该示例的状态机框架如下图所示：

 <img width="1510" height="745" alt="image" src="https://github.com/user-attachments/assets/55c7f3fc-9023-4b85-8ec1-80eb8b2e2052" />
simpleTest目录下main.cpp中有完整的代码注释，这里对每个用户的状态做下解释：
**用户的子状态类需要继承State基类，并覆盖基类中的3个方法：**
void onEntry(std::string paraP);  //该方法会在进入该状态时被调用，即从其他状态跳转到该状态，可以做一些初始化操作，paraP是从上一个状态传递过来的信息
void onLoop();                    //该方法是该状态的自循环函数，可以被执行多次
void onExit();                    //该方法是退出该状态时被调用，可以做一些清理操作
从一个子状态跳转到另一个子状态时，需要调用父状态的postEvent方法，该方法原型如下：
void postEvent(std::string eventP, std::string paraP = "")
其中eventP参数是跳转到目标状态的“标签”, paraP参数是需要给下一个状态传递的自定义信息，默认为空

