#include "ColorSensor.h"

ColorSensor::ColorSensor()
    :  m_refRed(1), m_refGreen(1), m_refBlue(1), m_refClear(1), m_calibrated(false) {}

void ColorSensor::begin()
{
    Wire1.begin();

    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(BH1745_SYSTEM_CONTROL);
    Wire1.write(0x01);
    Wire1.endTransmission();

    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(BH1745_MODE_CONTROL1);
    Wire1.write(0x00);
    Wire1.endTransmission();

    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(BH1745_MODE_CONTROL2);
    Wire1.write(0x11);
    Wire1.endTransmission();

    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(BH1745_MODE_CONTROL3);
    Wire1.write(0x02);
    Wire1.endTransmission();
    delay(200);
}

RGBData ColorSensor::readRGB()
{
    RGBData data = {0, 0, 0, 0};
    if (_isDataValid())
    {
        data.red = _readColor(BH1745_RED_DATA_LSB, BH1745_RED_DATA_MSB);
        data.green = _readColor(BH1745_GREEN_DATA_LSB, BH1745_GREEN_DATA_MSB);
        data.blue = _readColor(BH1745_BLUE_DATA_LSB, BH1745_BLUE_DATA_MSB);
        data.clear = _readColor(BH1745_CLEAR_DATA_LSB, BH1745_CLEAR_DATA_MSB);
    }
    return data;
}

RGBData ColorSensor::readCalibratedRGB()
{
    RGBData rawData = readRGB();
    RGBData calibratedData;
    if (m_calibrated)
    {
        calibratedData.red = (float)rawData.red /  m_refRed * 100.0;
        calibratedData.green = (float)rawData.green / m_refGreen * 100.0;
        calibratedData.blue = (float)rawData.blue / m_refBlue * 100.0;
        calibratedData.clear = (float)rawData.clear / m_refClear * 100.0;
    }
    else
    {
        calibratedData = rawData;
    }

    return calibratedData;
}

void ColorSensor::calibrateWithWhitePaper()
{
    if (_isDataValid())
    {
        m_refRed = _readColor(BH1745_RED_DATA_LSB, BH1745_RED_DATA_MSB);
        m_refGreen = _readColor(BH1745_GREEN_DATA_LSB, BH1745_GREEN_DATA_MSB);
        m_refBlue = _readColor(BH1745_BLUE_DATA_LSB, BH1745_BLUE_DATA_MSB);
        m_refClear = _readColor(BH1745_CLEAR_DATA_LSB, BH1745_CLEAR_DATA_MSB);
        m_calibrated = true;
    }
}

bool ColorSensor::isCalibrated() const
{
    return m_calibrated;
}

void ColorSensor::resetCalibration()
{
    m_refRed = 1;
    m_refGreen = 1;
    m_refBlue = 1;
    m_refClear = 1;
    m_calibrated = false;
}

uint16_t ColorSensor::_readColor(byte const& lsbReg, byte const& msbReg) const
{
    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(lsbReg);
    Wire1.endTransmission(false);
    Wire1.requestFrom(BH1745_ADDRESS, 2);

    uint16_t lsb = Wire1.read();
    uint16_t msb = Wire1.read();
    return (msb << 8) | lsb;
}

bool ColorSensor::_isDataValid() const
{
    Wire1.beginTransmission(BH1745_ADDRESS);
    Wire1.write(BH1745_MODE_CONTROL2);
    Wire1.endTransmission(false);
    Wire1.requestFrom(BH1745_ADDRESS, 1);
    byte modeControl2 = Wire1.read();
    return (modeControl2 & 0x80);
}
