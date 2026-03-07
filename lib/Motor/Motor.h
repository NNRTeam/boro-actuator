#pragma once

#include <Arduino.h>
#include <Timer.h>
#include <Config.h>

class Motor
{
public:
    Motor(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t homePin, bool inverted = false);
    void begin();
    void setPosition(int32_t position);
    [[nodiscard]] int32_t getPosition() const;
    void setObjective(int32_t objective);
    [[nodiscard]] int32_t getObjective() const;
    void run();
    void homing(int32_t homePosition);
    [[nodiscard]] bool isAtHome() const;
    [[nodiscard]] bool isAtObjective() const;
    void setStepDelay(unsigned long delayUs);

private:
    void _step(bool direction);
    void _enable(bool enable);

    uint8_t m_stepPin;
    uint8_t m_dirPin;
    uint8_t m_enablePin;
    uint8_t m_homePin;
    int32_t m_currentPosition;
    int32_t m_objectivePosition;
    bool m_enabled;
    bool m_inverted;
    Timer m_timer{config::MOTOR_STEP_DELAY_US};
};