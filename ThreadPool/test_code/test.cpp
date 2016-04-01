//#include "test.h"
//#include "Condition.h"
//extern void oh();
#include <iostream>

#include "Thread.h"
#include "CountDownLatch.h"
#include "BoundedBlockingQueue.h"
#include "Singleton.h"

ok::Mutex m;
ok::Condition c(m);
ok::CountDownLatch l(3);
int i;


class test{
public:
    test() : a(7), b(2), c(3) {};
    int a,b,c;
};

test *t_obj = nullptr;

void fun0(void* args)
{
    m.lock();
    std::cout << "Fun0 bootup! " << *static_cast<int*>(args) << std::endl;
    std::cout << "Thread id: " << ok::ThreadLocal::threadID << std::endl;
    m.unlock();
    
    sleep(3);
    
    m.lock();
    std::cout << "Fun0 Ready!" << *static_cast<int*>(args) <<  std::endl;
    std::cout << "Count: " << l.countDown() << std::endl;
    m.unlock();
}

void fun1(void* )
{
    m.lock();
    std::cout << "Every body ready?"<< ok::ThreadLocal::threadID <<  std::endl;
    l.wait();
    m.unlock();

    m.lock();
    std::cout << "Fun1 return" << std::endl;
    m.unlock();
}

void fun2(void *)
{
    m.lock();
    std::cout << "Ready " << ok::ThreadLocal::threadID << std::endl;
    m.unlock();
    l.countDown();
    l.wait();
    
    m.lock();
    std::cout << "GO " << ok::ThreadLocal::threadID << std::endl;
    m.unlock();
}

void fun3(void *)
{
    m.lock();
    std::cout << "Signal! " << std::endl;
    m.lock();
}

void fun4(void *args)
{
    t_obj = &ok::Singleton<test>::getInstance();
}

int main(int argc, char *argv[])
{
    int x,y,z;

    x = 3;
    y = 5;
    z = 7;

    ok::ThreadFunc f0, f1, f2; 
    f0 = fun2;
    f2 = fun1;
    
    ok::Thread td0(f0, &x), td1(f0, &y),
        td2(f0, &z), td3(f0);

    td3.run();
    td0.run(); 
    td1.run();
    td2.run();
/*
    m.lock();
    sleep(3);
    std::cout << "Signal 1" << std::endl;
    c.signal();
    m.unlock();    
    
    m.lock();
    sleep(3);
    std::cout << "Signal 2" << std::endl;
    c.signal();
    m.unlock();    
    
    m.lock();
    sleep(3);
    std::cout << "Signal 3" << std::endl;
    c.signal();
    m.unlock();    
//    td3.run();
//   l.wait();
*/
    td3.join();
    td0.join();
    td1.join();
    td2.join();
    
    //std::cout << "value " << t_obj->a<< std::endl;
    //std::cout << "value " << t_obj->b<< std::endl;
    //std::cout << "value " << t_obj->c<< std::endl;
    //ok::Singleton<test>::delInstance();
    //    td3.join();
    return 0;
}
