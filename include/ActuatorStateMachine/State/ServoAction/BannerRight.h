#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class BannerRight : public ServoAction
{
public:
    BannerRight(StateMachine* stateMachine, const String& name, Servo* srv1)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_BANER_RIGHT_ACTIVATED_ANGLE,
                      -1,
                      srv1,
                      nullptr,
                      Timer(1000000),
                      3)
    {}
};
