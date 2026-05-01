#include <ActuatorStateMachine/State/ServoAction/ServoAction.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Config.h>

void ServoAction::_enter()
{
    m_srv1.write(m_srv1Pos);
    m_srv2.write(m_srv2Pos);
    m_timer.start();
    m_startTime = millis();
}

void ServoAction::_execute()
{
    // Check timeout
    unsigned long elapsed = millis() - m_startTime;
    if (elapsed > config::STATE_ACTION_TIMEOUT_MS)
    {
        m_logger.error("Servo action timeout!");
        State* nextState = machineAs<ActuatorStateMachine>()->computeNextState(this);
        if (nextState != nullptr)
        {
            m_stateMachine->setNextState(nextState);
        }
        return;
    }

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
