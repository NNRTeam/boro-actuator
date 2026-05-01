#pragma once

#include <StateMachine.h>
#include <Timer.h>

class GoToIdleState : public State
{
public:
    GoToIdleState(StateMachine* stateMachine) : State(stateMachine, "GoToIdle") {}

protected:
    void _enter() override;
    void _execute() override;
    void _exit() override;

private:
    Timer m_timer{700000};
    unsigned long m_timeout = 0;
};
