#pragma once

#include <StateMachine.h>
#include <Timer.h>

class IdleState : public State
{
public:
    IdleState(StateMachine* stateMachine)
        : State(stateMachine, "IDLE")
    {
    }

protected:
    void _enter() override;
    void _execute() override;
    void _exit() override;

private:
    Timer m_timer{3000000};
};
