#include "ActuatorStateMachine/ActuatorStateMachine.h"
#include <Config.h>

void ActuatorStateMachine::run() {
    StateMachine::run();
    if (Serial.available() > 0)
        serialParser();
}

void ActuatorStateMachine::sendMissionState(int missionId, MissionStatus status) {
    String msg = "A" + String(missionId) + ";" + String(static_cast<int>(status)) + "F";
    Serial.print(msg);
}

void ActuatorStateMachine::serialParser() {
    String input = "";
    while (Serial.available() > 0 && (input.length() == 0 || input[input.length() - 1] != 'F')) {
        input += (char)Serial.read();
    }
    if (input.length() > 0 && input[0] == 'M'){
        int firstSemicolon = input.indexOf(';');
        int secondSemicolon = input.indexOf(';', firstSemicolon + 1);

        if (firstSemicolon > 0 && secondSemicolon > 0) {
            int id = input.substring(1, firstSemicolon).toInt();
            int type = input.substring(firstSemicolon + 1, secondSemicolon).toInt();
            int shouldTurn = input.substring(secondSemicolon + 1, input.length() - 1).toInt();

            Mission::Type missionType = static_cast<Mission::Type>(type);
            bool shouldTurnBool = shouldTurn != 0;
            addMission({id, missionType, shouldTurnBool});
        }
    }
}

void ActuatorStateMachine::GoToIdleState::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_BASE_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_BASE_POSITION);
        machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
        machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_HOME_ANGLE);
        machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_HOME_ANGLE);
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
        auto mission = machine->currentMission();
        if (mission.has_value()) {
            machine->sendMissionState(mission.value().id, MissionStatus::FINISHED);
            machine->finishCurrentMission();
        }
    }
}
void ActuatorStateMachine::IdleState::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (!machine) return;

    auto missionOpt = machine->currentMission();
    if (!missionOpt.has_value()) return;

    const Mission& mission = missionOpt.value();
    machine->sendMissionState(mission.id, MissionStatus::STARTED);

    if (mission.type != Mission::Type::PUT_IN_STOCK) {
        m_stateMachine->setNextState(&machine->m_openArm);
        return;
    }

    if (!mission.should_turn && !machine->isStockEmpty()) {
        m_stateMachine->setNextState(&machine->m_goToTopNutBox);
        return;
    }

    m_stateMachine->setNextState(&machine->m_closeArm);
}
void ActuatorStateMachine::IdleState::_exit() {
}

void ActuatorStateMachine::GoToRotation::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_TURN_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_TURN_POSITION);
    }
}
void ActuatorStateMachine::GoToRotation::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_turnToColor);
        }
    }
}
void ActuatorStateMachine::GoToRotation::_exit() {}

void ActuatorStateMachine::TurnToColor::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        m_timer.start();
        machine->m_srv_bottom_1.write(config::SERVO_BOTTOM_1_REVERT_ANGLE);
        machine->m_srv_bottom_2.write(config::SERVO_BOTTOM_2_REVERT_ANGLE);
    }
}
void ActuatorStateMachine::TurnToColor::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        if (!machine->m_isGateOpen) {
            m_stateMachine->setNextState(&machine->m_goToOpenGate);
        } else {
            m_stateMachine->setNextState(&machine->m_goToCloseGate);
        }
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
            if (machine->isStockEmpty()) {
                m_stateMachine->setNextState(&machine->m_openGate);
            } else {
                m_stateMachine->setNextState(&machine->m_uncontrolBottomNutBox);
            }
        }
    }
}
void ActuatorStateMachine::GoToOpenGate::_exit() {}


void ActuatorStateMachine::UncontrolBottomNutBox::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::UncontrolBottomNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_goToTopNutBox);
    }
}
void ActuatorStateMachine::UncontrolBottomNutBox::_exit() {
    m_timer.stop();
    m_timer.reset();
}

// GoToTopNutBox Implementation
void ActuatorStateMachine::GoToTopNutBox::_enter() {
    // Move to top nut box position
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_GATE_CLOSE_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_GATE_CLOSE_POSITION);
    }
}
void ActuatorStateMachine::GoToTopNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_getTopNutBox);
        }
    }
}
void ActuatorStateMachine::GoToTopNutBox::_exit() {}

void ActuatorStateMachine::GetTopNutBox::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_HOME_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_HOME_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::GetTopNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_openGate);
    }
}
void ActuatorStateMachine::GetTopNutBox::_exit() {
    m_timer.stop();
    m_timer.reset();
}

void ActuatorStateMachine::OpenGate::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_gripper_1.write(config::SERVO_GRIPPER_1_HOME_ANGLE);
        machine->m_srv_gripper_2.write(config::SERVO_GRIPPER_2_HOME_ANGLE);
        machine->m_isGateOpen = true;
        m_timer.start();
    }
}
void ActuatorStateMachine::OpenGate::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        if (machine->isStockEmpty()) {
            m_stateMachine->setNextState(&machine->m_goToCloseGate);
        } else {
            m_stateMachine->setNextState(&machine->m_goToTopNutBoxLeftPoint);
        }
    }
}
void ActuatorStateMachine::OpenGate::_exit() {
    m_timer.stop();
    m_timer.reset();
}


// GoToTopNutBox Implementation
void ActuatorStateMachine::GoToTopNutBoxLeftPoint::_enter() {
    // Move to top nut box position
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_GATE_TOP_OPEN_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_GATE_TOP_OPEN_POSITION);
    }
}
void ActuatorStateMachine::GoToTopNutBoxLeftPoint::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_uncontrolTopNutBox);
        }
    }
}
void ActuatorStateMachine::GoToTopNutBoxLeftPoint::_exit() {}

void ActuatorStateMachine::UncontrolTopNutBox::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_OPEN_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_OPEN_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::UncontrolTopNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_goToBottomNutBox);
    }
}
void ActuatorStateMachine::UncontrolTopNutBox::_exit() {
    m_timer.stop();
    m_timer.reset();
}

void ActuatorStateMachine::GoToBottomNutBox::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.setObjective(config::MOTOR1_GATE_OPEN_POSITION);
        machine->m_motor_2.setObjective(config::MOTOR2_GATE_OPEN_POSITION);
    }
}
void ActuatorStateMachine::GoToBottomNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_motor_1.run();
        machine->m_motor_2.run();
        if (machine->m_motor_1.isAtObjective() && machine->m_motor_2.isAtObjective()) {
            m_stateMachine->setNextState(&machine->m_getBottomNutBox);
        }
    }
}
void ActuatorStateMachine::GoToBottomNutBox::_exit() {}

void ActuatorStateMachine::GetBottomNutBox::_enter() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->m_srv_top_1.write(config::SERVO_TOP_1_HOME_ANGLE);
        machine->m_srv_top_2.write(config::SERVO_TOP_2_HOME_ANGLE);
        m_timer.start();
    }
}
void ActuatorStateMachine::GetBottomNutBox::_execute() {
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine && m_timer.isExpired()) {
        m_stateMachine->setNextState(&machine->m_goToCloseGate);
    }
}
void ActuatorStateMachine::GetBottomNutBox::_exit() {
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
        machine->m_isGateOpen = false;
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
    auto* machine = machineAs<ActuatorStateMachine>();
    if (machine) {
        machine->addItemToStock();
    }
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
                if (machine->currentMission().value().should_turn) {
                    m_stateMachine->setNextState(&machine->m_goToRotation);
                } else if (machine->m_isGateOpen == false){
                    m_stateMachine->setNextState(&machine->m_goToOpenGate);
                } else {
                    m_stateMachine->setNextState(&machine->m_goToCloseGate);
                }
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