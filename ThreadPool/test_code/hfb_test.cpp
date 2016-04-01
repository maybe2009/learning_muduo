#include "FixedBufferHandle.h"
#include "Thread.h"
#include "Mutex.h"

using namespace ok;

FixedBufferHandle h(4, 32 ,4);

void p0(void*)
{
    h.doFrontWrite("He", 2);
     
    sleep(2); 
    
    h.doFrontWrite(" Wei", 4);
     
    sleep(2);
    
    h.doFrontWrite("Dong", 4);
    
}

void p1(void*)
{
    std::cout << "p1 Go!" << std::endl;
    h.doBackGround();
}

int main()
{
    ThreadFunc fun0, fun1;
    
    fun0 = p0;
    fun1 = p1;

    Thread t0(fun0), t1(fun1);
    t0.run();
    t1.run();

    t0.join();
    t1.join();
 
    return 0;

}
