/*
 * This Code is edited by sun wukong @ 2015.12.18 15:22:12 CST 
 * 
 * Just feel free to use this code as you wish.
 * Any bug and ugly code, please notify me, thanks!
 *
 * Github https://githuc.com/maybe2009
 * Gmail  qtdssunwukong@gmail.com
 * 									-Auto Generated By UltiSnips
 */

#ifndef OK_COUNTDOWNLATCH_INCLUDED
#define OK_COUNTDOWNLATCH_INCLUDED

#include "Condition.h"

/*********************************************************************** 
      class CountDownLatch Declaration
************************************************************************/ 
namespace ok{
class CountDownLatch : boost::noncopyable
{
public:
    inline          CountDownLatch (int count);
    inline int      countDown();    
    inline void     wait();
    inline int      get() const;
    inline void     reset(int count);
private:
    int         count_;
    Mutex       mutex_;
    Condition   cond_; 
};
/*********************************************************************** 
      class CountDownLatch Definition
************************************************************************/ 
inline CountDownLatch::
CountDownLatch(int count) 
    : count_(count),
      mutex_(),
      cond_(mutex_)
{}

inline int CountDownLatch::
countDown()
{
    ScopeMutex lock(mutex_);
    if (--count_ == 0) {
        cond_.broadcast();
        return 0;

    } else {
        return count_;
    }
}

inline void CountDownLatch::
wait()
{
    ScopeMutex lock(mutex_);
    if (count_ != 0) {
        cond_.wait();
    }

    return;
}

inline int CountDownLatch::
get() const
{
    return count_;
}

inline void CountDownLatch::
reset(int count)
{
    count_ = count;
}

};
#endif /* ifndef OK_COUNTDOWNLATCH_INCLUDED */


