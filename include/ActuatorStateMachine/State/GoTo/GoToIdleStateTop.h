#pragma once

#include <StateMachine.h>
#include <Timer.h>

class GoToIdleStateTop : public State
{
public:
    GoToIdleStateTop(StateMachine* stateMachine) : State(stateMachine, "GoToIdleTop") {}

protected:
    void _enter() override;
    void _execute() override;
    void _exit() override;

private:
    Timer m_timer{700000};
};
