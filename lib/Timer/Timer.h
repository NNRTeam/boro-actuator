#pragma once

#include <Arduino.h>

class Timer
{
public:
    explicit Timer(unsigned long duration);
    void start();
    void stop();
    void reset();
    unsigned long elapsedMicros() const;
    bool isExpired() const;
    void setDuration(unsigned long duration);

private:
    unsigned long m_startMicros;
    bool m_running;
    unsigned long m_duration;
};

