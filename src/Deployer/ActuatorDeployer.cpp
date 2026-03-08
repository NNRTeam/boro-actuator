#include "Deployer/ActuatorDeployer.h"
#include <ActuatorStateMachine/ActuatorStateMachine.h>
#include <Config.h>

ActuatorStateMachine* ActuatorDeployer::deployActuators()
{
    delay(2000); // wait for 5 seconds before starting deployment to allow for serial monitor connection
    m_logger.debug("Deploying actuators...");
    _deployServos();
    _deployColorSensor();
    _deployMotorControllers();
    m_logger.debug("All actuators deployed.");
    return new ActuatorStateMachine(m_srv_top_1, m_srv_top_2,
                                    m_srv_bottom_1, m_srv_bottom_2,
                                    m_srv_gripper_1, m_srv_gripper_2,
                                    m_colorSensor, m_motor_1, m_motor_2);
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

    // m_srv_top_1.write(90);
    // m_srv_top_2.write(90);
    // m_srv_bottom_1.write(90);
    // m_srv_bottom_2.write(90);
    // m_srv_gripper_1.write(90);
    // m_srv_gripper_2.write(90);

    m_logger.debug("Servo Deployed");
}

void ActuatorDeployer::_deployColorSensor()
{
    m_colorSensor.begin();
    m_logger.debug("Color Sensor Deployed");
}

void ActuatorDeployer::_deployMotorControllers()
{
    m_motor_1.begin();
    m_motor_2.begin();

    m_motor_1.homing(config::MOTOR1_HOME_POSITION);
    m_motor_2.homing(config::MOTOR2_HOME_POSITION);

    m_logger.debug("Motor Controllers Deployed");
}