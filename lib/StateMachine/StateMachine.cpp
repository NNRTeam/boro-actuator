#include "StateMachine.h"

State::State(StateMachine* stateMachine, const String& name) : m_stateMachine(stateMachine), m_name(name)
{
    m_logger.setPrefix("State: " + name);
}

void State::enter()
{
    m_logger.debug("Entering state: " + m_name);
    _enter();
}

void State::execute()
{
    _execute();
}

void State::exit()
{
    m_logger.debug("Exiting state: " + m_name);
    _exit();
}

void StateMachine::run()
{
    if (m_nextState != nullptr)
    {
        if (m_currentState != nullptr)
        {
            m_currentState->exit();
        }
        m_currentState = m_nextState;
        m_nextState = nullptr;
        m_currentState->enter();
    }

    if (m_currentState != nullptr)
    {
        m_currentState->execute();
    }
}