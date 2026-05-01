#pragma once

#include <StateMachine.h>
#include <Servo.h>
#include <Timer.h>

class ServoAction : public State
{
public:
    ServoAction(StateMachine* stateMachine,
                const String& name,
                int srv1Pos,
                int srv2Pos,
                Servo& srv1,
                Servo& srv2,
                Timer timer,
                u_int64_t id)
        : State(stateMachine, name)
        , m_srv1Pos(srv1Pos)
        , m_srv2Pos(srv2Pos)
        , m_srv1(srv1)
        , m_srv2(srv2)
        , m_timer(timer)
        , m_id(id)
        , m_startTime(0)
    {
    }

protected:
    void _enter() override;
    void _execute() override;
    void _exit() override;

private:
    int m_srv1Pos;
    int m_srv2Pos;
    Servo& m_srv1;
    Servo& m_srv2;
    Timer m_timer;
    u_int64_t m_id;
    unsigned long m_startTime;
};
