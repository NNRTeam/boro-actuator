#include "ActuatorStateMachine/ActuatorStateMachine.h"
#include <Config.h>

void ActuatorStateMachine::GoToIdleState::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_BASE_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_BASE_POSITION);
        machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
        machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_HOME_ANGLE);
        machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_HOME_ANGLE);
        machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_OPEN_ANGLE);
        machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_OPEN_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::GoToIdleState::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective() && m_timer.isExpired()) {
            m_stateMachine->setNextState(&machine->m_idleState);
        }
    }
}
void ActuatorStateMachine::GoToIdleState::_exit() {
    m_timer.stop();
    m_timer.reset();
}

void ActuatorStateMachine::IdleState::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->finishCurrentMission();
        Serial.println("IDLE");
    }
}
void ActuatorStateMachine::IdleState::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        if (machine->currentMission().has_value()) {
            if(machine->currentMission().value().type == Mission::Type::PUT_IN_STOCK) {
                m_stateMachine->setNextState(&machine->m_closeArm);
            } else {
                m_stateMachine->setNextState(&machine->m_openArm);
            }
        }
        else {
            String input = "";
            while(Serial.available() > 0 && input[-1] != 'F') {
                input += (char)Serial.read();
            }
            if (input[0] == 'M'){
                m_logger.info("Received command to start mission");
                int type = input[1] - '0';
                int color = input[2] - '0';
                Mission::Type missionType = static_cast<Mission::Type>(type);
                Mission::Color missionColor = static_cast<Mission::Color>(color);
                machine->addMission({missionType, missionColor});
            }
        }
    }
}
void ActuatorStateMachine::IdleState::_exit() {
}

void ActuatorStateMachine::GoToMesure::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_TURN_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_TURN_POSITION);
    }
}
void ActuatorStateMachine::GoToMesure::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_mesure);
        }
    }
}
void ActuatorStateMachine::GoToMesure::_exit() {}

void ActuatorStateMachine::Mesure::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_COLOR_MEASURE_ANGLE);
        machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_COLOR_MEASURE_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::Mesure::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_turnToColor);
    }
}
void ActuatorStateMachine::Mesure::_exit() {
    m_timer.stop();
    m_timer.reset();
}

void ActuatorStateMachine::TurnToColor::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {

        auto color = machine->m_colorSensor.readRGB();

        m_logger.info("Measured color - R: " + String(color.red) + " G: " + String(color.green) + " B: " + String(color.blue));

        m_timer.start();
        machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_REVERT_ANGLE);
        machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_REVERT_ANGLE);
    }
}
void ActuatorStateMachine::TurnToColor::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_goToOpenGate);
    }
}
void ActuatorStateMachine::TurnToColor::_exit() {
    m_timer.stop();
    m_timer.reset();
}

void ActuatorStateMachine::GoToOpenGate::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_GATE_OPEN_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_GATE_OPEN_POSITION);
    }
}
void ActuatorStateMachine::GoToOpenGate::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_openGate);
        }
    }
}
void ActuatorStateMachine::GoToOpenGate::_exit() {}


void ActuatorStateMachine::OpenGate::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_HOME_ANGLE);
        machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_HOME_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::OpenGate::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_goToCloseGate);
    }
}
void ActuatorStateMachine::OpenGate::_exit() {
    m_timer.stop();
    m_timer.reset();
}

// GoToCloseGate Implementation
void ActuatorStateMachine::GoToCloseGate::_enter() {
    // Move to gate close position
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_GATE_CLOSE_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_GATE_CLOSE_POSITION);
    }
}

void ActuatorStateMachine::GoToCloseGate::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_closeGate);
        }
    }
}

void ActuatorStateMachine::GoToCloseGate::_exit() {
}

// CloseGate Implementation
void ActuatorStateMachine::CloseGate::_enter() {
    // Close the gate using servos
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        m_timer.start();
        machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_OPEN_ANGLE);
        machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_OPEN_ANGLE);
    }
}

void ActuatorStateMachine::CloseGate::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        // Wait for gate to fully close, then go back to idle
        m_stateMachine->setNextState(&machine->m_goToIdleState);
    }
}

void ActuatorStateMachine::CloseGate::_exit() {
    m_timer.stop();
    m_timer.reset();
}

// OpenArm Implementation
void ActuatorStateMachine::OpenArm::_enter() {
    // Open the gripper arm
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
    }
}

void ActuatorStateMachine::OpenArm::_execute() {
    // Wait for gripper to open
}

void ActuatorStateMachine::OpenArm::_exit() {
    // Nothing to do on exit
}

// CloseArm Implementation
void ActuatorStateMachine::CloseArm::_enter() {
    // Close the gripper arm
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_HOME_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_HOME_ANGLE);
        m_timer.start();
    }
}

void ActuatorStateMachine::CloseArm::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        if(machine->currentMission().has_value() && m_timer.isExpired()) {
            if(machine->currentMission().value().type == Mission::Type::PUT_IN_STOCK) {
                m_stateMachine->setNextState(&machine->m_goToMesure);
            } else {
                m_stateMachine->setNextState(&machine->m_goToIdleState);
            }
        }
    }
}

void ActuatorStateMachine::CloseArm::_exit() {
    m_timer.stop();
    m_timer.reset();
}