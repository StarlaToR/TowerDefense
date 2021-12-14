#include "timeCounter.hpp"

TimeCounter::TimeCounter()
{
    startTime = 0;
    totalTime = 0;
}

TimeCounter::~TimeCounter() {}

size_t TimeCounter::getTime()
{
    if (!isRunning()) return totalTime;
    double tmp = difftime(time(NULL), startTime);
    return static_cast<size_t>(tmp) + totalTime;
}

void TimeCounter::start()
{
    if (!isRunning()) startTime = time(NULL);
}

void TimeCounter::stop()
{
    if (isRunning())
    {
        double tmp = difftime(time(NULL), startTime);
        if (tmp > 0) totalTime += static_cast<size_t>(tmp);
        startTime = 0;
    }
}

void TimeCounter::setTime(size_t timeV)
{
    if (startTime > 0) startTime = time(NULL);
    totalTime = timeV;
}

bool TimeCounter::isRunning()
{
    return startTime != 0;
}