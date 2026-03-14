#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

void ServoAction::_enter()
{
    m_srv1.write(m_srv1Pos);
    m_srv2.write(m_srv2Pos);
    m_timer.start();
}

void ServoAction::_execute()
{
    if (m_timer.isExpired()) {
        State* nextState = machineAs<ActuatorStateMachine>()->computeNextState(this);
        if (nextState != nullptr) {
            m_stateMachine->setNextState(nextState);
        }
    }
}

void ServoAction::_exit()
{
    m_timer.stop();
    m_timer.reset();
}
