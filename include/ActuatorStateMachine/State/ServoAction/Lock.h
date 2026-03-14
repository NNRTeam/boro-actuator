#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class Lock : public ServoAction
{
public:
    Lock(StateMachine* stateMachine, const String& name, Servo& srv1, Servo& srv2)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_GRIPPER_1_OPEN_ANGLE,
                      config::SERVO_GRIPPER_2_OPEN_ANGLE,
                      srv1,
                      srv2,
                      Timer(1000000),
                      2)
    {}

protected:
    void _exit() override;
};
