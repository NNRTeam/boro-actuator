#pragma once

#include <StateMachine.h>
#include <Servo.h>
#include <ColorSensor.h>
#include <Timer.h>
#include <Motor.h>

class ActuatorStateMachine : public StateMachine
{
public:
    ActuatorStateMachine(Servo srv_top_1, Servo srv_top_2,
                        Servo srv_bottom_1, Servo srv_bottom_2,
                        Servo srv_gripper_1, Servo srv_gripper_2,
                        ColorSensor colorSensor, Motor motor_1, Motor motor_2) : StateMachine(&m_stateOpen),
                                                  m_srv_top_1(srv_top_1),
                                                  m_srv_top_2(srv_top_2),
                                                  m_srv_bottom_1(srv_bottom_1),
                                                  m_srv_bottom_2(srv_bottom_2),
                                                  m_srv_gripper_1(srv_gripper_1),
                                                  m_srv_gripper_2(srv_gripper_2),
                                                  m_colorSensor(colorSensor),
                                                  m_motor_1(motor_1),
                                                  m_motor_2(motor_2) {};

    class StateOpen : public State
    {
    public:
        StateOpen(StateMachine* stateMachine) : State(stateMachine, "Open") {}
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{1000000}; // 1 second
    };
    StateOpen m_stateOpen{this};

    class StateColorMesure : public State
    {
    public:
        StateColorMesure(StateMachine* stateMachine) : State(stateMachine, "ColorMesure") {}
        void _enter() override;
        void _execute() override;
        void _exit() override;
    };
    StateColorMesure m_stateColorMesure{this};

    class StateRevert : public State
    {
    public:
        StateRevert(StateMachine* stateMachine) : State(stateMachine, "Revert") {}
        void _enter() override;
        void _execute() override;
        void _exit() override;
    };
    StateRevert m_stateRevert{this};

    Servo m_srv_top_1;
    Servo m_srv_top_2;
    Servo m_srv_bottom_1;
    Servo m_srv_bottom_2;
    Servo m_srv_gripper_1;
    Servo m_srv_gripper_2;

    ColorSensor m_colorSensor;

    Motor m_motor_1;
    Motor m_motor_2;
};