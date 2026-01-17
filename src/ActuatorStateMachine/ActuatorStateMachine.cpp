#include "ActuatorStateMachine/ActuatorStateMachine.h"
#include <Config.h>

void ActuatorStateMachine::StateOpen::_enter()
{
    auto stateMachine = machineAs<ActuatorStateMachine>();
    stateMachine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_OPEN_ANGLE);
    stateMachine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_OPEN_ANGLE);
    m_timer.start();
}

void ActuatorStateMachine::StateOpen::_execute()
{
    if (m_timer.isExpired())
    {
        auto stateMachine = machineAs<ActuatorStateMachine>();
        stateMachine->setNextState(&stateMachine->m_stateColorMesure);
    }
}

void ActuatorStateMachine::StateOpen::_exit()
{
    m_timer.stop();
}

void ActuatorStateMachine::StateColorMesure::_enter()
{
    auto stateMachine = machineAs<ActuatorStateMachine>();
    stateMachine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_HOME_ANGLE);
    stateMachine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_HOME_ANGLE);
}

void ActuatorStateMachine::StateColorMesure::_execute()
{
    // Code to execute while in the ColorMesure state
}

void ActuatorStateMachine::StateColorMesure::_exit()
{
    // Code to execute when exiting the ColorMesure state
}

void ActuatorStateMachine::StateRevert::_enter()
{
    // Code to execute when entering the Revert state
}

void ActuatorStateMachine::StateRevert::_execute()
{
    // Code to execute while in the Revert state
}

void ActuatorStateMachine::StateRevert::_exit()
{
    // Code to execute when exiting the Revert state
}