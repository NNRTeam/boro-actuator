#include "Motor.h"
#include <Config.h>

Motor::Motor(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t homePin, bool inverted)
    : m_stepPin(stepPin), m_dirPin(dirPin), m_enablePin(enablePin), m_homePin(homePin), m_currentPosition(0),
      m_objectivePosition(0), m_enabled(false), m_inverted(inverted)
{
}

void Motor::begin()
{
    pinMode(m_stepPin, OUTPUT);
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_enablePin, OUTPUT);
    pinMode(m_homePin, INPUT);
    _enable(false);
}

void Motor::setPosition(int32_t position)
{
    m_currentPosition = position;
}

int32_t Motor::getPosition() const
{
    return m_currentPosition;
}

void Motor::setObjective(int32_t objective)
{
    m_objectivePosition = objective;
}

int32_t Motor::getObjective() const
{
    return m_objectivePosition;
}

void Motor::run()
{
    if (m_currentPosition == m_objectivePosition)
        return; // Already at objective, do nothing

    if (!m_enabled)
        _enable(true);

    if (m_timer.isExpired() == false)
        return;

    bool direction = m_objectivePosition > m_currentPosition;
    _step(direction);
    m_currentPosition += direction ? 1 : -1;
    m_timer.start();
}

void Motor::homing(int32_t homePosition)
{
    _enable(true);
    while (!isAtHome())
    {
        _step(true); // assume homing is in the positive direction
        delayMicroseconds(config::MOTOR_STEP_DELAY_US);
    }
    m_currentPosition = homePosition;
    m_objectivePosition = homePosition;
    _enable(false);
}

bool Motor::isAtHome() const
{
    return digitalRead(m_homePin) == HIGH;
}

bool Motor::isAtObjective() const
{
    return m_currentPosition == m_objectivePosition;
}

void Motor::setStepDelay(unsigned long delayUs)
{
    m_timer.setDuration(delayUs);
}

void Motor::_step(bool direction)
{
    bool dirLevel = m_inverted ? !direction : direction;
    digitalWrite(m_dirPin, dirLevel ? HIGH : LOW);

    digitalWrite(m_stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_stepPin, LOW);
}

void Motor::_enable(bool enable)
{
    m_enabled = enable;
    digitalWrite(m_enablePin, enable ? LOW : HIGH);
    if (enable)
        m_timer.start();
    else
        m_timer.stop();
}