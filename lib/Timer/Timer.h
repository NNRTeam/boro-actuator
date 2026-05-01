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
    void setDurationMillis(unsigned long durationMs);
    bool isExpiredMillis() const;

private:
    unsigned long m_startMicros;
    unsigned long m_startMillis;
    bool m_running;
    unsigned long m_duration;
    unsigned long m_durationMillis;
};

