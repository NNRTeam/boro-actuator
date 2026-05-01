#include <ActuatorStateMachine/State/GoTo/GoToBase.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Config.h>

void GoToBase::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(m_posMotor1);
        machine->m_motor_2.setObjective(m_posMotor2);
        m_timeout = millis();
    }
}

void GoToBase::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        // Check timeout
        unsigned long elapsed = millis() - m_timeout;
        if (elapsed > config::STATE_MOVEMENT_TIMEOUT_MS)
        {
            m_logger.error("Movement timeout! Motors did not reach objective.");
            State* nextState = machine->computeNextState(this);
            if (nextState != nullptr)
            {
                m_stateMachine->setNextState(nextState);
            }
            return;
        }

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
