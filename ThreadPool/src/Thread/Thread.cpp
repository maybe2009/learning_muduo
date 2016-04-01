#include "../../headers/Thread/Thread.h"

namespace ok
{

namespace ThreadLocal 
{
__thread pid_t threadID = 0;
};

Thread::
Thread(RoutineFunction                      &fun,
       std::unique_ptr<void, VoidDeleter>              &&args,
       std::unique_ptr<pthread_attr_t>    &&attr,
       std::string                          name)
    : args_         (args.release()),
      isRunning_    (false),
      isJoined_     (false),
      func_         (fun),
      attribute_    (attr.release()),
      name_   (name)
{}


Thread::
Thread(RoutineFunction &fun)
    : args_         (std::unique_ptr<void, VoidDeleter>()),
      isRunning_    (false),
      isJoined_     (false),
      func_         (fun),
      attribute_    (std::unique_ptr<pthread_attr_t>()),
      name_   ("DEFAULT THREAD NAME")
{}

Thread::
~Thread()
{
    if (isRunning_ && !isJoined_) {
        pthread_detach(id_);
        
        isRunning_ = false;
        isJoined_  = true;
    }
}

void Thread::
run()
{
    /*
     * The launcher must be destoried either after the routine is excuted
     * successful or before the routine is going to be excuted. Or the thread
     * the routine runs on may crashed for the resource is freed at the time
     * launcher's desctructor excuted.
     * 
     * So, we have to use "new" here for the reason that our launcher 
     * is constructed in one thread but living in another, we have to control
     * the resource deletion on ourselves.
     */
    RoutineLauncher *launcher = new RoutineLauncher(func_, std::move(args_));
    
    if (pthread_create(&id_, attribute_.get(), coverFunction, launcher) != 0) 
    {
        delete launcher;
        perror("[ERROR]pthread_create :");
    }
    else
    {
        isRunning_ = true;
    }
}

void Thread::
join(void **_rval_ptr)
{
    if (isRunning_ && !isJoined_) {
        if (pthread_join(id_, _rval_ptr) != 0) {
            perror("[ERROR]pthread_join: ");
        
        } else {
            isJoined_  = true;
            isRunning_ = false;
        }
    
    } else {
            perror("[WARING]Thread is not running or joinable: ");
    }
    return;
}

void Thread::
printName()
{
    std::cout << "Thread: " << name_
        << " pid: " << id_ <<  std::endl;
}

void Thread::
cancel(pthread_t id_)
{
    if (pthread_cancel(id_) != 0) {
        perror("[ERROR]pthread_cancel: ");
    }
    return;
}

void *
coverFunction(void *launcher)
{
    //ThreadLocal::threadID = syscall(__NR_gettid);
    RoutineLauncher *ptr  = static_cast<RoutineLauncher*>(launcher);    
    ptr->Launch();    
    delete ptr;
    
    return nullptr;
}

RoutineLauncher::
RoutineLauncher(const RoutineFunction func, std::unique_ptr<void, VoidDeleter> &&args)
    : args_(args.release()), 
      func_(func)
{}

void RoutineLauncher::
Launch()
{
    std::cout << "Launch" << std::endl;
    func_(args_.get());
}

};//namespace ok
