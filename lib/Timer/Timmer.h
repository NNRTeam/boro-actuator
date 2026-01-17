#pragma once

#include <Arduino.h>

class Timer
{
public:
    explicit Timer(unsigned long duration);
    void start();
    void stop();
    void reset();
    unsigned long elapsedMillis() const;
    bool isExpired() const;

private:
    unsigned long m_startMillis;
    bool m_running;
    unsigned long m_duration;
};

