#ifndef __TIMER_H__
#define __TIMER_H__
#include <sys/timerfd.h>
#include <functional>
namespace TIMER {
using TimerFucCallBack = std::function<void()>;

class Timer {
public:
    Timer(TimerFucCallBack cb, int initSec, int intervalSec);
    ~Timer();

    // void createTimerFd();
    // void setTimerFd(int initSec, int intervalSec);
    void readTimerFd();
    void startTimerFd();
    void stopTimerFd();

private:
    int _timerFd;
    bool _start;
    TimerFucCallBack _cb;
};
} // namespace TIMER
#endif