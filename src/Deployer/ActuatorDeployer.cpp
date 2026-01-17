#include "Deployer/ActuatorDeployer.h"
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Config.h>

ActuatorStateMachine* ActuatorDeployer::deployActuators()
{
    m_logger.info("Deploying actuators...");
    _deployServos();
    _deployColorSensor();
    return new ActuatorStateMachine(m_srv_top_1, m_srv_top_2,
                                    m_srv_bottom_1, m_srv_bottom_2,
                                    m_srv_gripper_1, m_srv_gripper_2,
                                    m_colorSensor);
}

void ActuatorDeployer::_deployServos()
{
    m_srv_top_1.attach(config::SERVO_TOP_1_PIN);
    m_srv_top_2.attach(config::SERVO_TOP_2_PIN);
    m_srv_bottom_1.attach(config::SERVO_BOTTOM_1_PIN);
    m_srv_bottom_2.attach(config::SERVO_BOTTOM_2_PIN);
    m_srv_gripper_1.attach(config::SERVO_GRIPPER_1_PIN);
    m_srv_gripper_2.attach(config::SERVO_GRIPPER_2_PIN);

    m_srv_top_1.write(config::SERVO_TOP_1_HOME_ANGLE);
    m_srv_top_2.write(config::SERVO_TOP_2_HOME_ANGLE);
    m_srv_bottom_1.write(config::SERVO_BOTTOM_1_HOME_ANGLE);
    m_srv_bottom_2.write(config::SERVO_BOTTOM_2_HOME_ANGLE);
    m_srv_gripper_1.write(config::SERVO_GRIPPER_1_HOME_ANGLE);
    m_srv_gripper_2.write(config::SERVO_GRIPPER_2_HOME_ANGLE);
    m_logger.info("Servo Deployed");
}

void ActuatorDeployer::_deployColorSensor()
{
    m_colorSensor.begin();
    m_logger.info("Color Sensor Deployed");
}