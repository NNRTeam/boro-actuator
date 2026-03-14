#pragma once
#include "GoToBase.h"

class StateMachine;

class GoToTurn : public GoToBase
{
public:
    GoToTurn(StateMachine* stateMachine, String name)
        : GoToBase(stateMachine, name, config::MOTOR1_TURN_POSITION, config::MOTOR2_TURN_POSITION)
    {
    }
};