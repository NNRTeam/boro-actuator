#ifndef CONFIG_H
#define CONFIG_H

namespace config {

    // HARDWARE CONFIGURATION
    int constexpr MOTOR_ENABLE_PIN = 2;

    int constexpr MOTOR1_STEP_PIN = 4;
    int constexpr MOTOR1_DIR_PIN = 7;
    int constexpr MOTOR2_STEP_PIN = 8;
    int constexpr MOTOR2_DIR_PIN = 12;
    int constexpr MOTOR1_HOME_PIN = 15;
    int constexpr MOTOR2_HOME_PIN = 14;

    int constexpr SERVO_TOP_1_PIN = 3;
    int constexpr SERVO_TOP_2_PIN = 5;
    int constexpr SERVO_BOTTOM_1_PIN = 6;
    int constexpr SERVO_BOTTOM_2_PIN = 9;
    int constexpr SERVO_GRIPPER_1_PIN = 10;
    int constexpr SERVO_GRIPPER_2_PIN = 11;

    // MOTOR PARAMETERS
    float constexpr MOTOR_STEPS_PER_REVOLUTION = 200.0; // Steps per revolution for the stepper motors
    float constexpr MOTOR_MICROSTEPPING = 1.0; // Microstepping setting for the stepper drivers

    int constexpr MOTOR1_HOME_POSITION = 470; // Home position for motor 1
    int constexpr MOTOR2_HOME_POSITION = 470; // Home position for motor 2

    int constexpr MOTOR1_BASE_POSITION = 0; // Base position for motor 1
    int constexpr MOTOR2_BASE_POSITION = 0; // Base position for motor 2

    int constexpr MOTOR1_TURN_POSITION = 100; // Turn position for motor 1
    int constexpr MOTOR2_TURN_POSITION = 100; // Turn position_ç for motor 2

    int constexpr MOTOR1_GATE_OPEN_POSITION = 0; // Gate open position for motor 1
    int constexpr MOTOR2_GATE_OPEN_POSITION = 0; // Gate open position for motor 2

    int constexpr MOTOR1_GATE_TOP_OPEN_POSITION = 150; // Gate top open position for motor 1
    int constexpr MOTOR2_GATE_TOP_OPEN_POSITION = 150; // Gate top open position for motor 2

    int constexpr MOTOR1_GATE_CLOSE_POSITION = 460; // Gate close position for motor 1
    int constexpr MOTOR2_GATE_CLOSE_POSITION = 460; // Gate close position for motor 2

    bool constexpr MOTOR1_INVERTED = false; // Inversion setting for motor 1
    bool constexpr MOTOR2_INVERTED = true;  // Inversion setting for motor 2

    int constexpr SERVO_TOP_1_HOME_ANGLE = 85; // Home angle for top servo 1
    int constexpr SERVO_TOP_2_HOME_ANGLE = 85; // Home angle for top servo 2
    int constexpr SERVO_BOTTOM_1_HOME_ANGLE = 0; // Home angle for bottom servo 1
    int constexpr SERVO_BOTTOM_2_HOME_ANGLE = 180; // Home angle for bottom servo 2
    int constexpr SERVO_GRIPPER_1_HOME_ANGLE = 0; // Home angle for gripper servo 1
    int constexpr SERVO_GRIPPER_2_HOME_ANGLE = 180; // Home angle for gripper servo 2

    int constexpr SERVO_TOP_1_OPEN_ANGLE = 110; // Open angle for top servo 1
    int constexpr SERVO_TOP_2_OPEN_ANGLE =  55; // Open angle for top servo 2

    int constexpr SERVO_BOTTOM_1_COLOR_MEASURE_ANGLE = 90; // Angle for bottom servo 1 to measure color
    int constexpr SERVO_BOTTOM_2_COLOR_MEASURE_ANGLE = 90; // Angle for bottom servo 2 to measure color
    int constexpr SERVO_BOTTOM_1_REVERT_ANGLE = 180; // revert angle for bottom servo 1
    int constexpr SERVO_BOTTOM_2_REVERT_ANGLE = 0; // revert angle for bottom servo 2

    int constexpr SERVO_GRIPPER_1_OPEN_ANGLE = 95; // Open angle for gripper servo 1
    int constexpr SERVO_GRIPPER_2_OPEN_ANGLE = 85; // Open angle for gripper servo 2

    // SOFTWARE CONFIGURATION

    bool constexpr TEST = false; // Enable or disable test mode
    unsigned long int constexpr SERIAL_BAUDRATE = 115200; // Serial communication baudrate
    bool constexpr ENABLE_SERIAL_DEBUG = true; // Enable or disable serial debug messages

    unsigned long int constexpr MOTOR_STEP_DELAY_US = 2000; // Delay between motor steps in microseconds

    int constexpr I2C_ADD = 0x30; // I2C address for the robot

} // namespace config

#endif // CONFIG_H