#include "../../include/threadpool/ThreadWorker.h"

namespace CurrentThread
{
    __thread int threadName = -1;
} // CurrentThread

namespace THREADPOOL
{
    ThreadWorker::ThreadWorker(ThreadPool &threadPool, int threadName)
        : _threadPool(threadPool),
          _threadName(threadName)
    {
    }
    ThreadWorker::~ThreadWorker()
    {
    }
    void ThreadWorker::run()
    {
        // ThreadWorker类外访问ThreadPool的私有成员函数，
        // 需要将ThreadWorker设为ThreadPool的友元类
        // cout << "ThreadWorker::run()::_threadPool.processTask()" << endl;
        CurrentThread::threadName = _threadName == -1 ? -1 : _threadName;
        _threadPool.processTask();
    }
} //