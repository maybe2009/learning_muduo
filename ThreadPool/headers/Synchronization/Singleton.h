/*
 * This Code is edited by sun wukong @ 2015.12.19 17:17:44 CST 
 * 
 * Just feel free to use this code as you wish.
 * Any bug and ugly code, please notify me, thanks!
 *
 * Github https://githuc.com/maybe2009
 * Gmail  qtdssunwukong@gmail.com
 * 									-Auto Generated By UltiSnips
 */


#ifndef OK_SINGLETON_INCLUDED
#define OK_SINGLETON_INCLUDED

#include <pthread.h>
#include <boost/noncopyable.hpp>
#include "Mutex.h"

namespace ok{
template<typename T>
class Singleton : public boost::noncopyable
{
public:
    static T& getInstance()
    {
        pthread_once(&once_control_, createInstance);
        return *object_; 
    }
    
    static void delInstance()
    {
        ScopeMutex lock(mutex_);
        delete object_;
    } 
private:
    Singleton();
    ~Singleton();
    
    static void createInstance()
    {
        object_ = new T();
    }

private:
    static T*               object_;
    static pthread_once_t   once_control_;
    static Mutex            mutex_;
};

template<typename T>
pthread_once_t Singleton<T>::once_control_ = PTHREAD_ONCE_INIT;
template<typename T>
T* Singleton<T>::object_ = NULL;
template<typename T>
Mutex Singleton<T>::mutex_;
};
#endif /* ifndef OK_SINGLETON_INCLUDED */
