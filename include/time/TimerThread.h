#ifndef __TIEMRTHREAD_H__
#define __TIEMRTHREAD_H__
#include "../../include/threadpool/Thread.h"
#include "Timer.h"
namespace TIMER {
class TimerThread : public THREADPOOL::Thread {
public:
    // using TimerFucCallBacka = std::function<void()>;

    TimerThread(TIMER::TimerFucCallBack cb, int initSec, int intervalSec);
    ~TimerThread();

    void run() override;

private:
    Timer _timer;
};
} // namespace TIMER
#endif