#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Wire.h>
#include <stdint.h>

// Adresse I2C du BH1745
#define BH1745_ADDRESS 0x38

// Registres du BH1745
#define BH1745_SYSTEM_CONTROL 0x40
#define BH1745_MODE_CONTROL1 0x41
#define BH1745_MODE_CONTROL2 0x42
#define BH1745_MODE_CONTROL3 0x44
#define BH1745_RED_DATA_LSB 0x50
#define BH1745_RED_DATA_MSB 0x51
#define BH1745_GREEN_DATA_LSB 0x52
#define BH1745_GREEN_DATA_MSB 0x53
#define BH1745_BLUE_DATA_LSB 0x54
#define BH1745_BLUE_DATA_MSB 0x55
#define BH1745_CLEAR_DATA_LSB 0x56
#define BH1745_CLEAR_DATA_MSB 0x57

// Structure pour stocker les données RGB
struct RGBData
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;
};

class ColorSensor
{
public:
    ColorSensor();

    void begin();

    RGBData readRGB();
    RGBData readCalibratedRGB();

    void calibrateWithWhitePaper();
    bool isCalibrated() const;
    void resetCalibration();

private:
    uint16_t    m_refRed;
    uint16_t m_refGreen;
    uint16_t m_refBlue;
    uint16_t m_refClear;
    bool m_calibrated;

    uint16_t _readColor(byte const& lsbReg, byte const& msbReg) const;

    bool _isDataValid() const;
};

#endif
