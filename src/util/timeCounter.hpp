#pragma once

#include <ctime>

class TimeCounter
{
    private:
    time_t startTime;
    size_t totalTime;
    public:
    TimeCounter();
    ~TimeCounter();

    void start();
    void stop();
    void setTime(size_t timeV);
    bool isRunning();
    size_t getTime();
};