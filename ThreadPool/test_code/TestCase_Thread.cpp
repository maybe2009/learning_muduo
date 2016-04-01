#include "Thread.h"
void fun(void* ptr)
{
    std::cout << "........@@@@Hello New Thread" << std::endl;
}

int main()
{
   
    ok::RoutineFunction fun1 = fun;
    fun1(nullptr);
    ok::Thread thread(fun1, std::unique_ptr<void>(), std::unique_ptr<pthread_attr_t>(), "Test Robot");
    std::cout << "Start" << std::endl;
    thread.run();
    sleep(3);
    thread.join();

    return 0;

}
