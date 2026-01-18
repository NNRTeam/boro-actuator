#pragma once

#include <Logger.h>
#include <Servo.h>
#include <ColorSensor.h>
#include <Motor.h>

class ActuatorStateMachine;

class ActuatorDeployer
{
public:
    ActuatorDeployer(){};
    ActuatorStateMachine* deployActuators();

private:
    void _deployServos();
    void _deployColorSensor();
    void _deployMotorControllers();

    Logger m_logger = Logger(Logger::Level::INFO, "ActuatorDeployer");

    Servo m_srv_top_1;
    Servo m_srv_top_2;
    Servo m_srv_bottom_1;
    Servo m_srv_bottom_2;
    Servo m_srv_gripper_1;
    Servo m_srv_gripper_2;

    ColorSensor m_colorSensor;

    Motor m_motor_1{config::MOTOR1_STEP_PIN, config::MOTOR1_DIR_PIN, config::MOTOR_ENABLE_PIN, config::MOTOR1_HOME_PIN, config::MOTOR1_INVERTED};
    Motor m_motor_2{config::MOTOR2_STEP_PIN, config::MOTOR2_DIR_PIN, config::MOTOR_ENABLE_PIN, config::MOTOR2_HOME_PIN, config::MOTOR2_INVERTED};
};