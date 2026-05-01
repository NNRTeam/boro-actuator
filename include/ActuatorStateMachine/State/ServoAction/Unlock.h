#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class Unlock : public ServoAction
{
public:
    Unlock(StateMachine* stateMachine, const String& name, Servo& srv1, Servo& srv2)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_GRIPPER_1_HOME_ANGLE,
                      config::SERVO_GRIPPER_2_HOME_ANGLE,
                      srv1,
                      srv2,
                      Timer(500000),
                      -2)
    {}

protected:
    void _exit() override;
};
