#include <iostream>
#include "./ThreadPool/headers/Thread/Thread.h"
#include "./ThreadPool/headers/Log/LogStream.h"

void foo(void *a)
{
   std::cout<< "Hello" << std::endl;
   return;
}

/*
int main() {
   ok::RoutineFunction fun = foo;
   ok::Thread t(fun);

   t.run();
   std::cout << "HHHHHHHHh" << std::endl;
   sleep(3);
   t.join(nullptr);

   return 0;

}
*/

int main()
{
   ok::LogStream log(10);
   log << 25;
   log << 'a';

   log.show();
}