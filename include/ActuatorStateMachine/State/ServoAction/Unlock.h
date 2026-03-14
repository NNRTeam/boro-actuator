#pragma once

#include <State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

class Unlock : public ServoAction
{
public:
    Unlock(StateMachine* stateMachine, const String& name)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_GRIPPER_1_HOME_ANGLE,
                      config::SERVO_GRIPPER_2_OPEN_ANGLE,
                      machineAs<ActuatorStateMachine>()->m_srv_gripper_1,
                      machineAs<ActuatorStateMachine>()->m_srv_gripper_2,
                      Timer(500000),
                      -2)
    {
    }

protected:
    void _exit() override
    {
        auto* machine = machineAs<ActuatorStateMachine>();
        if (machine) {
            machine->unlockStock();
        }
    }
};
