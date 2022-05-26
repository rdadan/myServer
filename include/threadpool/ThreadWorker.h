#ifndef __THREADWORKER_H__
#define __THREADWORKER_H__
#include "Thread.h"
#include "ThreadPool.h"

// 线程局部存储
// 用__thread声明这个变量， 每个线程访问同一个变量，但是不同每个线程都保留一个自己的值
// 也就是threadName变量在每个线程中都独占一个栈空间
namespace CurrentThread
{
    extern __thread int threadName;
} // CurrentThread

namespace THREADPOOL
{
    class ThreadWorker : public Thread
    {
    public:
        ThreadWorker(ThreadPool &_threadPool, int threadName);
        ~ThreadWorker();

    private:
        virtual void run() override;

    private:
        ThreadPool &_threadPool;
        int _threadName; // 线程名称
    };

} //
#endif