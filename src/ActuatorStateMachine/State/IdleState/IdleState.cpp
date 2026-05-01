#include <ActuatorStateMachine/State/IdleState/IdleState.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Mission/Mission.h>

void IdleState::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        const Mission* mission = machine->currentMissionPtr();
        if (mission)
        {
            machine->sendMissionState(mission->id, MissionStatus::FINISHED);
            machine->finishCurrentMission();
        }
    }
}

void IdleState::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (!machine)
        return;

    const Mission* mission = machine->currentMissionPtr();
    if (!mission)
    {
        // No mission available, stay idle
        return;
    }

    machine->sendMissionState(mission->id, MissionStatus::STARTED);
    State* nextState = machine->computeNextState(this);
    if (nextState != nullptr) {
        m_stateMachine->setNextState(nextState);
    }
    else
    {
        m_logger.error("No valid next state for mission");
        // Finish the mission to prevent infinite loop
        machine->sendMissionState(mission->id, MissionStatus::FAILED);
        machine->finishCurrentMission();
    }
}

void IdleState::_exit()
{
}
