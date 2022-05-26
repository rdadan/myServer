#include "../../include/time/Timer.h"
#include <poll.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

using std::cout;
using std::endl;

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

namespace TIMER
{
    inline int createTimerFd()
    {
        int ret = timerfd_create(CLOCK_REALTIME, 0);
        if (ret == -1)
        {
            perror("timerfd_create");
        }
        return ret;
    }

    inline void setTimerFd(int fd, int initSec, int intervalSec)
    {
        struct itimerspec ts;
        ts.it_value.tv_sec = initSec;
        ts.it_value.tv_nsec = 0;
        ts.it_interval.tv_sec = intervalSec;
        ts.it_interval.tv_nsec = 0;

        int ret = timerfd_settime(fd, 0, &ts, nullptr);
        if (ret == -1)
        {
            perror("timerfd_settime");
            exit(EXIT_FAILURE);
        }
    }
    Timer::Timer(TimerFucCallBack cb, int initSec, int intervalSec)
        : _timerFd(createTimerFd()),
          _cb(cb),
          _start(false)
    {
        setTimerFd(_timerFd, initSec, intervalSec);
    }
    Timer::~Timer()
    {
        stopTimerFd();
    }
    void Timer::startTimerFd()
    {
        _start = true;
        struct pollfd pfd;
        pfd.fd = _timerFd;
        pfd.events = POLLIN; // 监听读事件
        while (_start)
        {
            int ret = poll(&pfd, 1, -1); // -1 设为阻塞
            if (ret == 0)
            {
                cout << "> poll time out " << endl;
            }
            else if (ret < 0)
            {
                if (errno == EINTR) // Interrupted system call
                {
                    continue;
                }
                else
                {
                    perror("poll");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                if (pfd.events == POLLIN)
                {
                    readTimerFd();
                    if (_cb)
                        _cb();
                }
            }
        }
    }

    void Timer::readTimerFd()
    {
        uint64_t exp;
        int ret = read(_timerFd, &exp, sizeof(exp));
        if (ret != sizeof(exp))
        {
            handle_error("read timer fd error");
        }
    }
    void Timer::stopTimerFd()
    {
        if (_start)
        {
            setTimerFd(_timerFd, 0, 0);
            _start = false;
        }
    }

} // TIMER