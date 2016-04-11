#include "../ThreadPool/headers/FixedBuffer/FixedBufferHandle.h"
#include "../ThreadPool/headers/Thread/Thread.h"
#include "../ThreadPool/headers/Time/Time.h"

#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define FIXEDBUFFER_SIZE 50

ok::FixedBufferHandle h(FIXEDBUFFER_SIZE);
Time t;

void backGround(void *)
{
    std::cout << "Back Ground Thread run" << std::endl;
    std::cout << "Back Ground Thread run" << std::endl;
    std::cout << "Back Ground Thread run" << std::endl;
    h.doBackGround();
    std::cout << "Back Ground Thread exit" << std::endl;
}

void frontGround()
{
    std::cout << "Perform writting..." << std::endl;
    for(int i = 0; i < 100; i++)
    {
        h.doFrontWrite(t.getLogFmtTime().c_str(), MAX_LOGTIME_LENGTH);
        //h.doFrontWrite("Hello World!", 12);
        //sleep(1);
    }
}

int main()
{
    umask(0);
    int fd = open("log_test_FixedBufferHandle.txt", O_RDWR|O_APPEND
                  |O_CREAT|O_NOCTTY, S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
    
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
