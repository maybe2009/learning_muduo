#include "../ThreadPool/headers/FixedBuffer/FixedBufferHandle.h"
#include "../ThreadPool/headers/Thread/Thread.h"

#include <fcntl.h>
#include <errno.h>

#define FIXEDBUFFER_SIZE 20 

ok::FixedBufferHandle h(FIXEDBUFFER_SIZE);

void backGround(void *)
{
    std::cout << "Back Ground Thread run" << std::endl;
    h.doBackGround();
    std::cout << "Back Ground Thread exit" << std::endl;
}

void frontGround()
{
    std::cout << "Perform writting..." << std::endl;
    for(int i = 0; i < 10; i++)
    {
        h.doFrontWrite("Hello World!", 12);
        sleep(1);
    }
}

int main()
{
    int fd = open("log_test_FixedBufferHandle.txt", O_WRONLY|O_APPEND
                  |O_CREAT|O_NOCTTY);
    
    ok::RoutineFunction fun = backGround;
    ok::Thread trd(fun);

    if(fd != -1)
    {
        std::cout << "Open file on : "<< fd << std::endl;
        h.setFileDescriptor(fd);
        trd.run();
        frontGround();

    }
    else
    {
        perror("Open file fail: ");
    }

    std::cout << "Main return ..." << std::endl;
    trd.join();

    close(fd);

    return 0;
}
