#ifndef CONFIG_H
#define CONFIG_H

namespace config {

    bool constexpr TEST = false; // Enable or disable test mode
    unsigned long int constexpr SERIAL_BAUDRATE = 115200; // Serial communication baudrate
    bool constexpr ENABLE_SERIAL_DEBUG = true; // Enable or disable serial debug messages

    int constexpr I2C_ADD = 0x30; // I2C address for the robot

} // namespace config

#endif // CONFIG_H