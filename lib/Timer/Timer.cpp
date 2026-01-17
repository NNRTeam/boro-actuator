#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long duration) : m_startMillis(0), m_running(false), m_duration(duration) {}

void Timer::start()
{
    m_startMillis = millis();
    m_running = true;
}

void Timer::stop()
{
    m_running = false;
}

void Timer::reset()
{
    m_startMillis = millis();
}

unsigned long Timer::elapsedMillis() const
{
    return m_running ? millis() - m_startMillis : 0;
}

bool Timer::isExpired() const
{
    return m_running && (millis() - m_startMillis) >= m_duration;
}
