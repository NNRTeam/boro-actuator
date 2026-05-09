#pragma once

#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <Config.h>

class HomeBanner : public ServoAction
{
public:
    HomeBanner(StateMachine* stateMachine, const String& name, Servo* srv1, Servo* srv2)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_BANER_LEFT_HOME_ANGLE,
                      config::SERVO_BANER_RIGHT_HOME_ANGLE,
                      srv1,
                      srv2,
                      Timer(1000000),
                      3)
    {}
};
