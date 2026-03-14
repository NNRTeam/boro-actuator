#pragma once

#include <State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

class Lock : public ServoAction
{
public:
    Lock(StateMachine* stateMachine, const String& name)
        : ServoAction(stateMachine,
                      name,
                      config::SERVO_GRIPPER_1_OPEN_ANGLE,
                      config::SERVO_GRIPPER_2_HOME_ANGLE,
                      machineAs<ActuatorStateMachine>()->m_srv_gripper_1,
                      machineAs<ActuatorStateMachine>()->m_srv_gripper_2,
                      Timer(500000),
                      2)
    {
    }

protected:
    void _exit() override
    {
        auto* machine = machineAs<ActuatorStateMachine>();
        if (machine) {
            machine->lockStock();
        }
    }
};
