#include <ActuatorStateMachine/State/IdleState/IdleState.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Mission/Mission.h>

void IdleState::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        auto mission = machine->currentMission();
        if (mission.has_value()) {
            m_logger.info("Mission " + String(mission->id) + " completed.");
            machine->sendMissionState(mission.value().id, MissionStatus::FINISHED);
            machine->finishCurrentMission();
        }
    }
}

void IdleState::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (!machine)
        return;

    auto missionOpt = machine->currentMission();
    if (!missionOpt.has_value())
    {
        // No mission available, stay idle
        return;
    }

    m_logger.info("Starting mission " + String(missionOpt->id));
    machine->sendMissionState(missionOpt->id, MissionStatus::STARTED);
    State* nextState = machine->computeNextState(this);
    if (nextState != nullptr) {
        m_stateMachine->setNextState(nextState);
    }
    else
    {
        m_logger.error("No valid next state for mission " + String(missionOpt->id));
        // Finish the mission to prevent infinite loop
        machine->sendMissionState(missionOpt->id, MissionStatus::FAILED);
        machine->finishCurrentMission();
    }
}

void IdleState::_exit()
{
}
