#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class Unpick : public ServoAction
{
public:
    Unpick(StateMachine* stateMachine, const String& name, Servo& srv1, Servo& srv2)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_TOP_1_OPEN_ANGLE,
                      config::SERVO_TOP_2_OPEN_ANGLE,
                      srv1,
                      srv2,
                      Timer(1000000),
                      -1)
    {}

protected:
    void _exit() override;
};
