#pragma once

#include <StateMachine.h>

class GoToBase : public State
{
public:
    GoToBase(StateMachine* stateMachine, const String& name, int posMotor1, int posMotor2)
        : State(stateMachine, name)
        , m_posMotor1(posMotor1)
        , m_posMotor2(posMotor2)
        , m_timeout(0)
    {
    }

protected:
    void _enter() override;
    void _execute() override;
    void _exit() override;

private:
    int m_posMotor1;
    int m_posMotor2;
    unsigned long m_timeout;
};
