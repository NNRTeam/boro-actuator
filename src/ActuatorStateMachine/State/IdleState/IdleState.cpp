#include "IdleState.h"
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Mission/Mission.h>

void IdleState::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        auto mission = machine->currentMission();
        if (mission.has_value()) {
            machine->sendMissionState(mission.value().id, MissionStatus::FINISHED);
            machine->finishCurrentMission();
        }
    }
}

void IdleState::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (!machine) return;

    auto missionOpt = machine->currentMission();
    if (!missionOpt.has_value()) return;

    const Mission& mission = missionOpt.value();
    machine->sendMissionState(mission.id, MissionStatus::STARTED);

    if (mission.type != Mission::Type::PUT_IN_STOCK) {
        m_stateMachine->setNextState(&machine->m_openArm);
        return;
    }

    if (!mission.should_turn && !machine->isStockEmpty()) {
        m_stateMachine->setNextState(&machine->m_goToTopNutBox);
        return;
    }

    m_stateMachine->setNextState(&machine->m_closeArm);
}

void IdleState::_exit()
{
}
