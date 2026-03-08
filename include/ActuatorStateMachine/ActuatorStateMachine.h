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

    void run() override;
    void serialParser();
    void sendMissionState(int missionId, MissionStatus status);

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

    class GoToRotation: public State
    {
    public:
        GoToRotation(StateMachine* stateMachine) : State(stateMachine, "GoToRotation") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_goToRotation{this};

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

    class UncontrolBottomNutBox: public State
    {
    public:
        UncontrolBottomNutBox(StateMachine* stateMachine) : State(stateMachine, "UncontrolBottomNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_uncontrolBottomNutBox{this};

    class GoToTopNutBox: public State
    {
    public:
        GoToTopNutBox(StateMachine* stateMachine) : State(stateMachine, "GoToTopNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    } m_goToTopNutBox{this};

    class GetTopNutBox: public State
    {
    public:
        GetTopNutBox(StateMachine* stateMachine) : State(stateMachine, "GetTopNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_getTopNutBox{this};

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

    class GoToTopNutBoxLeftPoint: public State
    {
    public:
        GoToTopNutBoxLeftPoint(StateMachine* stateMachine) : State(stateMachine, "GoToTopNutBoxLeftPoint") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    } m_goToTopNutBoxLeftPoint{this};

    class UncontrolTopNutBox: public State
    {
    public:
        UncontrolTopNutBox(StateMachine* stateMachine) : State(stateMachine, "UncontrolTopNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_uncontrolTopNutBox{this};

    class GoToBottomNutBox: public State
    {
    public:
        GoToBottomNutBox(StateMachine* stateMachine) : State(stateMachine, "GoToBottomNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    } m_goToBottomNutBox{this};

    class GetBottomNutBox: public State
    {
    public:
        GetBottomNutBox(StateMachine* stateMachine) : State(stateMachine, "GetBottomNutBox") {}
    protected:
        void _enter() override;
        void _execute() override;
        void _exit() override;
    private:
        Timer m_timer{500000};
    } m_getBottomNutBox{this};

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

    [[nodiscard]] int getCurrentStock() const { return m_currentStock; }
    void addItemToStock() { m_currentStock++; }
    void removeItemFromStock() { if (m_currentStock > 0) m_currentStock--; }
    [[nodiscard]] bool isStockEmpty() const { return m_currentStock == 0; }
protected:
    std::vector<Mission> m_missions;
    int m_currentStock = 0;
    bool m_isGateOpen = true;
};