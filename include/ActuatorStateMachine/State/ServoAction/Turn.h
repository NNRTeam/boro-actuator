#pragma once

#include <State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

class Turn : public ServoAction
{
public:
    Turn(StateMachine* stateMachine, const String& name)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_BOTTOM_1_REVERT_ANGLE,
                      config::SERVO_BOTTOM_2_REVERT_ANGLE,
                      machineAs<ActuatorStateMachine>()->m_srv_bottom_1,
                      machineAs<ActuatorStateMachine>()->m_srv_bottom_2,
                      Timer(500000),
                      3)
    {
    }

protected:
    void _exit() override
    {
        auto* machine = machineAs<ActuatorStateMachine>();
        if (machine) {
            machine->currentMission()->should_turn = false;
        }
    }
};
