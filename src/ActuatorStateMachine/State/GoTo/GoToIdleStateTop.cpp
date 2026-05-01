#include <ActuatorStateMachine/State/GoTo/GoToIdleStateTop.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Config.h>

void GoToIdleStateTop::_enter()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_HOME_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_HOME_POSITION);
        if (!machine->isItemKept()) {
            machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_HOME_ANGLE);
            machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_HOME_ANGLE);
            machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
            machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
        }
        if (machine->isStockEmpty()) {
            machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_HOME_ANGLE);
            machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_HOME_ANGLE);
            machine->m_isGateOpen = true;
        } else {
            machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_OPEN_ANGLE);
            machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_OPEN_ANGLE);
            machine->m_isGateOpen = false;
        }
        m_timer.start();
    }
}

void GoToIdleStateTop::_execute()
{
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        if (!machine->m_motor_1.isAtObjective())
            machine->m_motor_1.run();
        if (!machine->m_motor_2.isAtObjective())
            machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective() && m_timer.isExpired()) {
            m_stateMachine->setNextState(&machine->m_idleState);
        }
    }
}

void GoToIdleStateTop::_exit()
{
    m_timer.stop();
    m_timer.reset();
}
