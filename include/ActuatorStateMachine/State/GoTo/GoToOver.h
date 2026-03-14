#pragma once
#include "GoToBase.h"
#include <Config.h>

class StateMachine;

class GoToOver : public GoToBase
{
public:
    GoToOver(StateMachine* stateMachine, String name)
        : GoToBase(stateMachine, name, config::MOTOR1_GATE_TOP_OPEN_POSITION, config::MOTOR2_GATE_TOP_OPEN_POSITION)
    {
    }
};