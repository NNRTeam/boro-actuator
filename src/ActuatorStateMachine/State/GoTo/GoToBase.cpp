#include <ActuatorStateMachine/State/GoTo/GoToBase.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

void GoToBase::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(m_posMotor1);
        machine->m_motor_2.setObjective(m_posMotor2);
    }
}

void GoToBase::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        if (!machine->m_motor_1.isAtObjective()) {
            machine->m_motor_1.run();
        }
        if (!machine->m_motor_2.isAtObjective()) {
            machine->m_motor_2.run();
        }
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            State* nextState = machine->computeNextState(this);
            if (nextState != nullptr) {
                m_stateMachine->setNextState(nextState);
            }
        }
    }
}

void GoToBase::_exit() {}
