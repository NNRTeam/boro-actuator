#pragma once
#include "GoToBase.h"
#include <Config.h>

class StateMachine;

class GoToTop : public GoToBase
{
public:
    GoToTop(StateMachine* stateMachine, String name)
        : GoToBase(stateMachine, name, config::MOTOR1_HOME_POSITION, config::MOTOR2_HOME_POSITION)
    {
    }
};