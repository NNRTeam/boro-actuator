#pragma once

#include <StateMachine.h>
#include <Servo.h>
#include <ColorSensor.h>
#include <Timer.h>
#include <Motor.h>
#include <Mission/Mission.h>
#include <vector>

class ActuatorStateMachine : public StateMachine
{
public:
    ActuatorStateMachine(Servo srv_top_1, Servo srv_top_2,
                        Servo srv_bottom_1, Servo srv_bottom_2,
                        Servo srv_gripper_1, Servo srv_gripper_2,
                        ColorSensor colorSensor, Motor motor_1, Motor motor_2) : StateMachine(&m_goToIdleState),
                                                  m_srv_top_1(srv_top_1),
                                                  m_srv_top_2(srv_top_2),
                                                  m_srv_bottom_1(srv_bottom_1),
                                                  m_srv_bottom_2(srv_bottom_2),
                                                  m_srv_gripper_1(srv_gripper_1),
                                                  m_srv_gripper_2(srv_gripper_2),
                                                  m_colorSensor(colorSensor),
                                                  m_motor_1(motor_1),
                                                  m_motor_2(motor_2) {};


    class GoToIdleState: public State
    {
    public:
        GoToIdleState(StateMachine* stateMachine) : State(stateMachine, "GoToIdle") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{1000000};
    } m_goToIdleState{this};

    class IdleState: public State
    {
    public:
        IdleState(StateMachine* stateMachine) : State(stateMachine, "Idle") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{3000000};
    } m_idleState{this};

    class GoToMesure: public State
    {
    public:
        GoToMesure(StateMachine* stateMachine) : State(stateMachine, "GoToMesure") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_goToMesure{this};

    class Mesure: public State
    {
    public:
        Mesure(StateMachine* stateMachine) : State(stateMachine, "Mesure") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_mesure{this};

    class TurnToColor: public State
    {
    public:
        TurnToColor(StateMachine* stateMachine) : State(stateMachine, "TurnToColor") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{700000};
    } m_turnToColor{this};

    class GoToOpenGate: public State
    {
    public:
        GoToOpenGate(StateMachine* stateMachine) : State(stateMachine, "GoToOpenGate") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    } m_goToOpenGate{this};

    class OpenGate: public State
    {
    public:
        OpenGate(StateMachine* stateMachine) : State(stateMachine, "OpenGate") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{700000};
    } m_openGate{this};

    class GoToCloseGate: public State
    {
    public:
        GoToCloseGate(StateMachine* stateMachine) : State(stateMachine, "GoToCloseGate") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    } m_goToCloseGate{this};

    class CloseGate: public State
    {
    public:
        CloseGate(StateMachine* stateMachine) : State(stateMachine, "CloseGate") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{700000};
    } m_closeGate{this};

    class OpenArm: public State
    {
    public:
        OpenArm(StateMachine* stateMachine) : State(stateMachine, "OpenArm") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_openArm{this};

    class CloseArm: public State
    {
    public:
        CloseArm(StateMachine* stateMachine) : State(stateMachine, "CloseArm") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_closeArm{this};


    Servo m_srv_top_1;
    Servo m_srv_top_2;
    Servo m_srv_bottom_1;
    Servo m_srv_bottom_2;
    Servo m_srv_gripper_1;
    Servo m_srv_gripper_2;

    ColorSensor m_colorSensor;

    Motor m_motor_1;
    Motor m_motor_2;

    [[nodiscard]] std::optional<Mission> currentMission() const
        { return m_missions.empty() ? std::nullopt : std::make_optional(m_missions.front()); }

    [[nodiscard]] std::optional<Mission> nextMission() const
        { return m_missions.size() < 2 ? std::nullopt : std::make_optional(m_missions[1]); }

    void finishCurrentMission() { if (!m_missions.empty()) m_missions.erase(m_missions.begin()); }

    void addMission(const Mission& mission) { m_missions.push_back(mission); }

protected:
    std::vector<Mission> m_missions;
};