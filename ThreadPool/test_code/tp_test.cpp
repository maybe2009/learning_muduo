#include "ThreadPool.h"
#include "Mutex.h"

using namespace ok;

Mutex m;

void fun()
{
    ScopeMutex lock(m);    
    std::cout << "Running on Thread : " << ThreadLocal::threadID << std::endl;

}

int main(int argc, char *argv[])
{
    ThreadPool::Task task = fun;

    ThreadPool pool(5);
    pool.startNThread(5);
    
    //std::cout << "Running: " << pool.numRunning() << std::endl;
    //std::cout << "Waiting: " << pool.numWaiting() << std::endl;
    
    sleep(3);
    
    std::cout << "Add Task" << std::endl;    
    pool.addTask(task);
    sleep(2);
    
    std::cout << "Add Task" << std::endl;    
    pool.addTask(task);
    sleep(2);
    
    std::cout << "Add Task" << std::endl;    
    pool.addTask(task);
    sleep(2);

    pool.stop(); 
    return 0;
}
