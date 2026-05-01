#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long duration)
    : m_startMicros(0)
    , m_startMillis(0)
    , m_running(false)
    , m_duration(duration)
    , m_durationMillis(0)
{
}

void Timer::start()
{
    m_startMicros = micros();
    m_startMillis = millis();
    m_running = true;
}

void Timer::stop()
{
    m_running = false;
}

unsigned long Timer::elapsedMicros() const
{
    if (!m_running)
        return 0;
    // Handle micros() overflow (wraps every ~71 minutes)
    unsigned long currentMicros = micros();
    if (currentMicros >= m_startMicros)
    {
        return currentMicros - m_startMicros;
    }
    else
    {
        // Overflow occurred
        return (ULONG_MAX - m_startMicros) + currentMicros + 1;
    }
}

bool Timer::isExpired() const
{
    return m_running && elapsedMicros() >= m_duration;
}

bool Timer::isExpiredMillis() const
{
    if (!m_running)
        return false;
    return (millis() - m_startMillis) >= m_durationMillis;
}

void Timer::reset()
{
    m_startMicros = 0;
    m_startMillis = 0;
    m_running = false;
}

void Timer::setDuration(unsigned long duration)
{
    m_duration = duration;
}

void Timer::setDurationMillis(unsigned long durationMs)
{
    m_durationMillis = durationMs;
}