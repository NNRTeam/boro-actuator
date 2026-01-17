#include <Arduino.h>
#include <Config.h>
#include <Logger.h>
#include <ColorSensor.h>
#include <Deployer/ActuatorDeployer.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

Logger logger(Logger::Level::DEBUG);
ActuatorDeployer actuatorDeployer;
ActuatorStateMachine* actuatorStateMachine;

void setup() {
    Serial.begin(config::SERIAL_BAUDRATE);
    actuatorStateMachine = actuatorDeployer.deployActuators();
}

void loop() {
    actuatorStateMachine->run();
}