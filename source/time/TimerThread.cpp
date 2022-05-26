#include "../../include/time/TimerThread.h"
namespace TIMER
{
    TimerThread::TimerThread(TIMER::TimerFucCallBack cb, int initSec, int intervalSec)
        : _timer(cb, initSec, intervalSec),
          Thread()
    {
        startThread();
    }

    void TimerThread::run()
    {
        _timer.startTimerFd();
    }

    TimerThread::~TimerThread()
    {
        _timer.stopTimerFd();
    }
}
