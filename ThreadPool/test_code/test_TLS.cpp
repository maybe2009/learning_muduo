#include <iostream>

#include "Thread.h"
#include "Mutex.h"
#include "Condition.h"
#include "ThreadLocalStorge.h"

class test{
public:
    test(int v = 0) : a(v) { std::cout << "Construction run" << std::endl; };
    ~test(){ std::cout << "Destructor run "<< a << std::endl; };
    int get(){return a;};
    void set(int v){ a = v;};
public:
    int a;
};

ok::ThreadLocalStorge<test> tls;
ok::Mutex m;
ok::Condition c(m);

void pro(void* args)
{
    m.lock();
    std::cout << "PRO run" << std::endl; 
    
    test& my_copy = tls.get();
    my_copy.set(*static_cast<int*>(args));
    
    std::cout << "PRO: " << my_copy.get() << std::endl;

    c.wait(); 
    
    m.unlock();
}


int main(int argc, char *argv[])
{
    ok::ThreadFunc fun0; 
    fun0 = pro;
    
    int X = 1, Y = 2, Z = 3;
    ok::Thread t0(fun0, &X), t1(fun0, &Y), t2(fun0, &Z); 
    
    t0.run();
    t1.run();
    t2.run();

    sleep(3);
    c.broadcast();

    t0.join();
    t1.join();
    t2.join();
    return 0;
}

