#include "ActuatorStateMachine/ActuatorStateMachine.h"
#include <Config.h>

void ActuatorStateMachine::run() {
    StateMachine::run();
    if (Serial.available() > 0)
        serialParser();
}

void ActuatorStateMachine::sendMissionState(int missionId, MissionStatus status) {
    String msg = "A" + String(missionId) + ";" + String(static_cast<int>(status)) + "F";
    Serial.print(msg);
}

void ActuatorStateMachine::serialParser() {
    String input = "";
    while (Serial.available() > 0 && (input.length() == 0 || input[input.length() - 1] != 'F')) {
        input += (char)Serial.read();
    }
    if (input.length() > 0 && input[0] == 'M'){
        int firstSemicolon = input.indexOf(';');
        int secondSemicolon = input.indexOf(';', firstSemicolon + 1);
        int thirdSemicolon = input.indexOf(';', secondSemicolon + 1);

        if (firstSemicolon > 0 && secondSemicolon > 0 && thirdSemicolon > 0) {
            int id = input.substring(1, firstSemicolon).toInt();
            int type = input.substring(firstSemicolon + 1, secondSemicolon).toInt();
            int shouldTurn = input.substring(secondSemicolon + 1, thirdSemicolon).toInt();
            int shouldKeep = input.substring(thirdSemicolon + 1, input.length() - 1).toInt();

            Mission::Type missionType = static_cast<Mission::Type>(type);
            bool shouldTurnBool = shouldTurn != 0;
            bool shouldKeepBool = shouldKeep != 0;
            addMission({id, missionType, shouldTurnBool, shouldKeepBool});
        }
    }
}

State* ActuatorStateMachine::computeNextState(State* currentState) const
{
    if (!currentState)
        return nullptr;

    const String& name = currentState->name();
    auto mission = currentMission();
    if (!mission.has_value())
    {
        m_logger.warn("No current mission, cannot compute next state from " + name);
        return nullptr;
    }
    bool shouldTurn = mission ? mission->should_turn : false;
    bool shouldKeep = mission ? mission->should_keep : false;

    // ===== MAIN STATES TRANSITIONS =====
    if (name == "GT_IDLE")
    {
        return &m_idleState;
    }
    else if (name == "IDLE")
    {
        if (mission)
        {
            if (mission->type == Mission::Type::PUT_IN_STOCK && !isItemKept())
            {
                return &m_gotoBot_T0;
            }
            else if (mission->type == Mission::Type::DROP && isItemKept())
            {
                return &m_gotoBot_D0;
            }
            else if (mission->type == Mission::Type::DROP && !isItemKept())
            {
                return &m_gotoTop_D7;
            }
        }
    }
    // ===== TAKE SECTION TRANSITIONS =====
    else if (name == "GT_BOT_T0")
    {
        if (isStockLocked() && !shouldKeep && !shouldTurn)
        {
            return &m_unpick_T10;
        }
        return &m_pick_T1;
    }
    else if (name == "pick_T1")
    {
        addItemToStock();
        if (shouldTurn)
        {
            return &m_gotoTurn_T5;
        }
        else if (shouldKeep)
        {
            return &m_gotoIdleState;
        }
        else
        {
            return &m_gotoTop_T2;
        }
    }
    else if (name == "GT_TOP_T2")
    {
        return &m_lock_T3;
    }
    else if (name == "LOCK_T3")
    {
        return &m_unpick_T4;
    }
    else if (name == "UNPICK_T4")
    {
        return &m_gotoIdleState;
    }
    else if (name == "GT_TURN_T5")
    {
        return &m_turn_T6;
    }
    else if (name == "TURN_T6")
    {
        if (isStockLocked() && !shouldKeep)
        {
            return &m_gotoBot_T7;
        }
        else if (shouldKeep)
        {
            return &m_gotoIdleState;
        }
        else
        {
            return &m_gotoTop_T2;
        }
    }
    else if (name == "GT_BOT_T7")
    {
        return &m_unpick_T10;
    }
    else if (name == "UNPICK_T10")
    {
        return &m_gotoTop_T11;
    }
    else if (name == "GT_TOP_T11")
    {
        return &m_pick_T12;
    }
    else if (name == "PICK_T12")
    {
        return &m_unlock_T13;
    }
    else if (name == "UNLOCK_T13")
    {
        return &m_gotoOver_T14;
    }
    else if (name == "GT_OVER_T14")
    {
        return &m_unpick_T15;
    }
    else if (name == "UNPICK_T15")
    {
        return &m_pick_T1;
    }

    // ===== DROP SECTION TRANSITIONS =====
    else if (name == "GT_BOT_D0")
    {
        return &m_unpick_D1;
    }
    else if (name == "UNPICK_D1")
    {
        removeItemFromStock();
        if (isStockEmpty())
        {
            return &m_gotoIdleState;
        }
        else
        {
            return &m_gotoOver_D2;
        }
    }
    else if (name == "GT_OVER_D2")
    {
        return &m_pick_D3;
    }
    else if (name == "PICK_D3")
    {
        return &m_gotoTop_D4;
    }
    else if (name == "GT_TOP_D4")
    {
        return &m_lock_D5;
    }
    else if (name == "LOCK_D5")
    {
        return &m_unpick_D6;
    }
    else if (name == "UNPICK_D6")
    {
        return &m_gotoTop_D7;
    }
    else if (name == "GT_TOP_D7")
    {
        return &m_pick_D8;
    }
    else if (name == "PICK_D8")
    {
        return &m_unlock_D9;
    }
    else if (name == "UNLOCK_D9")
    {
        return &m_gotoBot_D0;
    }

    return nullptr;
}