#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class Turn : public ServoAction
{
public:
    Turn(StateMachine* stateMachine, const String& name, Servo& srv1, Servo& srv2)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_BOTTOM_1_REVERT_ANGLE,
                      config::SERVO_BOTTOM_2_REVERT_ANGLE,
                      srv1,
                      srv2,
                      Timer(1000000),
                      3)
    {}

protected:
    void _exit() override;
};
