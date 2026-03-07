#pragma once

#include <Arduino.h>
#include <Logger.h>

// Forward declaration
class StateMachine;

class State
{
public:
    State(StateMachine* stateMachine, const String& name);
    StateMachine* machine() const { return m_stateMachine; }
    template<typename T>
    T* machineAs() const { return static_cast<T*>(m_stateMachine); }
    void enter();
    void execute();
    void exit();
    virtual ~State() {}

protected:
    virtual void _enter() = 0;
    virtual void _execute() = 0;
    virtual void _exit() = 0;

    String m_name;
    Logger m_logger = Logger(Logger::Level::INFO, "State");
    StateMachine* m_stateMachine;
};

class StateMachine
{
public:
    StateMachine(State* InitialState) : m_nextState(InitialState) {};
    virtual ~StateMachine() = default;
    void run();
    void setNextState(State* state) { m_nextState = state; };

private:
    State* m_currentState = nullptr;
    State* m_nextState = nullptr;
};