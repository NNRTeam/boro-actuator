#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long duration) : m_startMicros(0), m_running(false), m_duration(duration) {}

void Timer::start()
{
    m_startMicros = micros();
    m_running = true;
}

void Timer::stop()
{
    m_running = false;
}

unsigned long Timer::elapsedMicros() const
{
    return m_running ? micros() - m_startMicros : 0;
}

bool Timer::isExpired() const
{
    return m_running && (micros() - m_startMicros) >= m_duration;
}

void Timer::setDuration(unsigned long duration)
{
    m_duration = duration;
}