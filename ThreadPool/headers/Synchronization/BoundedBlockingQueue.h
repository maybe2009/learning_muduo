/*
 * This Code is edited by sun wukong @ 2015.12.19 15:17:10 CST 
 * 
 * Just feel free to use this code as you wish.
 * Any bug and ugly code, please notify me, thanks!
 *
 * Github https://githuc.com/maybe2009
 * Gmail  qtdssunwukong@gmail.com
 * 									-Auto Generated By UltiSnips
 */

#ifndef OK_BOUNDEDBLOCKINGQUEUE_INCLUDED
#define OK_BOUNDEDBLOCKINGQUEUE_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/circular_buffer.hpp>

#include "Mutex.h"
#include "Condition.h"

namespace ok{
template <typename T>
class BoundedBlockingQueue
{
public:
    BoundedBlockingQueue (int size)
        : mutex_(),
          notFull_(mutex_),
          notEmpty_(mutex_),
          queue_(size)
    {}

    void put(T product)
    {
        ScopeMutex lock(mutex_);
        while (queue_.full()) {
            notFull_.wait();
        }

        queue_.push_back(product);
        notEmpty_.signal();
    }
    
    T get()
    {
        ScopeMutex lock(mutex_);
        while(queue_.empty()) {
            notEmpty_.wait();
        }
        
        T ret(queue_.front());
        queue_.pop_front();
        notEmpty_.signal();
    }
    
    bool isEmpty() const
    {
        ScopeMutex lock(mutex_);
        return queue_.empty();
    }
    
    bool isFull() const
    {
        ScopeMutex lock(mutex_);
        return queue_.full();
    }

    bool size() const
    {
        ScopeMutex lock(mutex_);
        return queue_.size();
    }
    
    bool capacity() const
    {
        ScopeMutex lock(mutex_);
        return queue_.capacity();
    }

private: 
    mutable Mutex               mutex_;
    Condition                   notFull_;
    Condition                   notEmpty_;
    boost::circular_buffer<T>   queue_;

};
};
#endif /* ifndef OK_BOUNDEDBLOCKINGQUEUE_INCLUDED */
