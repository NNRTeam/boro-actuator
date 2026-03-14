#include <ActuatorStateMachine/State/IdleState/IdleState.h>
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
    if (!machine)
        return;

    auto missionOpt = machine->currentMission();
    if (!missionOpt.has_value())
        return;

    machine->sendMissionState(missionOpt->id, MissionStatus::STARTED);
    State* nextState = machine->computeNextState(this);
    if (nextState != nullptr) {
        m_stateMachine->setNextState(nextState);
    }
}

void IdleState::_exit()
{
}
