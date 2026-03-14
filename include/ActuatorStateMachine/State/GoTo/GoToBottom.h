#pragma once
#include "GoToBase.h"
#include <Config.h>

class StateMachine;

class GoToBottom : public GoToBase
{
public:
    GoToBottom(StateMachine* stateMachine, String name)
        : GoToBase(stateMachine, name, config::MOTOR1_BASE_POSITION, config::MOTOR2_BASE_POSITION)
    {
    }
};