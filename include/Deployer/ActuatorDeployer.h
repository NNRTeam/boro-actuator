#pragma once

#include <Logger.h>
#include <Servo.h>
#include <ColorSensor.h>

class ActuatorStateMachine;

class ActuatorDeployer
{
public:
    ActuatorDeployer(){};
    ActuatorStateMachine* deployActuators();

private:
    void _deployServos();
    void _deployColorSensor();

    Logger m_logger = Logger(Logger::Level::INFO, "ActuatorDeployer");

    Servo m_srv_top_1;
    Servo m_srv_top_2;
    Servo m_srv_bottom_1;
    Servo m_srv_bottom_2;
    Servo m_srv_gripper_1;
    Servo m_srv_gripper_2;

    ColorSensor m_colorSensor;
};