#include <ActuatorStateMachine/State/ServoAction/Pick.h>
#include <ActuatorStateMachine/State/ServoAction/Unpick.h>
#include <ActuatorStateMachine/State/ServoAction/Lock.h>
#include <ActuatorStateMachine/State/ServoAction/Unlock.h>
#include <ActuatorStateMachine/State/ServoAction/Turn.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

void Pick::_exit()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->keepItem();
    }
}

void Unpick::_exit()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->releaseKeptItem();
    }
}

void Lock::_exit()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->lockStock();
    }
}

void Unlock::_exit()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->unlockStock();
    }
}

void Turn::_exit()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        auto mission = machine->currentMission();
        if (mission.has_value()) {
            mission->should_turn = false;
        }
    }
}
