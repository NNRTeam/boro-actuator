#pragma once

#include <StateMachine.h>
#include <Servo.h>
#include <ColorSensor.h>
#include <Timer.h>
#include <Motor.h>
#include <Mission/Mission.h>
#include <vector>
#include <optional>

#include <ActuatorStateMachine/State/GoTo/GoToIdleState.h>
#include <ActuatorStateMachine/State/GoTo/GoToBottom.h>
#include <ActuatorStateMachine/State/GoTo/GoToTop.h>
#include <ActuatorStateMachine/State/GoTo/GoToTurn.h>
#include <ActuatorStateMachine/State/GoTo/GoToOver.h>
#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/State/IdleState/IdleState.h>
#include <ActuatorStateMachine/State/ServoAction/Pick.h>
#include <ActuatorStateMachine/State/ServoAction/Unpick.h>
#include <ActuatorStateMachine/State/ServoAction/Lock.h>
#include <ActuatorStateMachine/State/ServoAction/Unlock.h>
#include <ActuatorStateMachine/State/ServoAction/Turn.h>

class ActuatorStateMachine : public StateMachine
{
public:
    ActuatorStateMachine(Servo srv_top_1,
                         Servo srv_top_2,
                         Servo srv_bottom_1,
                         Servo srv_bottom_2,
                         Servo srv_gripper_1,
                         Servo srv_gripper_2,
                         ColorSensor colorSensor,
                         Motor motor_1,
                         Motor motor_2)
        : StateMachine(&m_gotoIdleState)
        , m_srv_top_1(srv_top_1)
        , m_srv_top_2(srv_top_2)
        , m_srv_bottom_1(srv_bottom_1)
        , m_srv_bottom_2(srv_bottom_2)
        , m_srv_gripper_1(srv_gripper_1)
        , m_srv_gripper_2(srv_gripper_2)
        , m_colorSensor(colorSensor)
        , m_motor_1(motor_1)
        , m_motor_2(motor_2)
        ,
        // Main states
        m_gotoIdleState(this)
        , m_idleState(this, "IDLE")
        , m_gotoIdleStateTop(this)
        , m_idleStateTop(this, "IDLE_TOP")
        ,
        // TAKE section states
        m_gotoBot_T0(this, "GT_BOT_T0")
        , m_pick_T1(this, "PICK_T1", m_srv_top_1, m_srv_top_2)
        , m_gotoTop_T2(this, "GT_TOP_T2")
        , m_lock_T3(this, "LOCK_T3", m_srv_gripper_1, m_srv_gripper_2)
        , m_unpick_T4(this, "UNPICK_T4", m_srv_top_1, m_srv_top_2)
        , m_gotoTurn_T5(this, "GT_TURN_T5")
        , m_turn_T6(this, "TURN_T6", m_srv_bottom_1, m_srv_bottom_2)
        , m_gotoBot_T7(this, "GT_BOT_T7")
        , m_gotoBot_T8(this, "GT_BOT_T8")
        , m_gotoBot_T9(this, "GT_BOT_T9")
        , m_unpick_T10(this, "UNPICK_T10", m_srv_top_1, m_srv_top_2)
        , m_gotoTop_T11(this, "GT_TOP_T11")
        , m_pick_T12(this, "PICK_T12", m_srv_top_1, m_srv_top_2)
        , m_unlock_T13(this, "UNLOCK_T13", m_srv_gripper_1, m_srv_gripper_2)
        , m_gotoOver_T14(this, "GT_OVER_T14")
        , m_unpick_T15(this, "UNPICK_T15", m_srv_top_1, m_srv_top_2)
        ,
        // DROP section states
        m_gotoBot_D0(this, "GT_BOT_D0")
        , m_unpick_D1(this, "UNPICK_D1", m_srv_top_1, m_srv_top_2)
        , m_gotoOver_D2(this, "GT_OVER_D2")
        , m_pick_D3(this, "PICK_D3", m_srv_top_1, m_srv_top_2)
        , m_gotoTop_D4(this, "GT_TOP_D4")
        , m_lock_D5(this, "LOCK_D5", m_srv_gripper_1, m_srv_gripper_2)
        , m_unpick_D6(this, "UNPICK_D6", m_srv_top_1, m_srv_top_2)
        , m_gotoTop_D7(this, "GT_TOP_D7")
        , m_pick_D8(this, "PICK_D8", m_srv_top_1, m_srv_top_2)
        , m_unlock_D9(this, "UNLOCK_D9", m_srv_gripper_1, m_srv_gripper_2){};

    void run() override;
    void serialParser();
    void sendMissionState(int missionId, MissionStatus status);

    State* computeNextState(State* currentState);

    friend class GoToIdleState;
    friend class GoToBase;
    friend class GoToBottom;
    friend class GoToTop;
    friend class GoToTurn;
    friend class GoToOver;
    friend class ServoAction;
    friend class IdleState;
    friend class Pick;
    friend class Unpick;
    friend class Lock;
    friend class Unlock;
    friend class Turn;


protected:
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
    {
        return m_missions.empty() ? std::nullopt : std::make_optional(m_missions.front());
    }

    [[nodiscard]] std::optional<Mission> nextMission() const
        { return m_missions.size() < 2 ? std::nullopt : std::make_optional(m_missions[1]); }

    void finishCurrentMission() { if (!m_missions.empty()) m_missions.erase(m_missions.begin()); }

    void addMission(const Mission& mission) { m_missions.push_back(mission); }

    [[nodiscard]] int getCurrentStock() const { return m_currentStock; }
    void addItemToStock() { m_currentStock++; }
    void removeItemFromStock() { if (m_currentStock > 0) m_currentStock--; }
    [[nodiscard]] bool isStockEmpty() const { return m_currentStock == 0; }

    void lockStock() { m_isLocked = true; }
    void unlockStock() { m_isLocked = false; }
    [[nodiscard]] bool isStockLocked() const { return m_isLocked; }

    void keepItem() { m_isKept = true; }
    void releaseKeptItem() { m_isKept = false; }
    [[nodiscard]] bool isItemKept() const { return m_isKept; }

protected:
    std::vector<Mission> m_missions;
    int m_currentStock = 0;
    bool m_isGateOpen = true;
    bool m_isKept = false;
    bool m_isLocked = false;

    // Main state instances
    GoToIdleState m_gotoIdleState;
    GoToIdleStateTop m_gotoIdleStateTop;
    IdleState m_idleState;
    IdleState m_idleStateTop;

    // TAKE section state instances
    GoToBottom m_gotoBot_T0;
    Pick m_pick_T1;
    GoToTop m_gotoTop_T2;
    Lock m_lock_T3;
    Unpick m_unpick_T4;
    GoToTurn m_gotoTurn_T5;
    Turn m_turn_T6;
    GoToBottom m_gotoBot_T7;
    GoToBottom m_gotoBot_T8;
    GoToBottom m_gotoBot_T9;
    Unpick m_unpick_T10;
    GoToTop m_gotoTop_T11;
    Pick m_pick_T12;
    Unlock m_unlock_T13;
    GoToOver m_gotoOver_T14;
    Unpick m_unpick_T15;

    // DROP section state instances
    GoToBottom m_gotoBot_D0;
    Unpick m_unpick_D1;
    GoToOver m_gotoOver_D2;
    Pick m_pick_D3;
    GoToTop m_gotoTop_D4;
    Lock m_lock_D5;
    Unpick m_unpick_D6;
    GoToTop m_gotoTop_D7;
    Pick m_pick_D8;
    Unlock m_unlock_D9;
};
