#include <Arduino.h>
#include <Config.h>
#include <Logger.h>
#include <ColorSensor.h>

Logger logger(Logger::Level::DEBUG);
ColorSensor colorSensor;


void setup() {
    Serial.begin(config::SERIAL_BAUDRATE);
    colorSensor.begin();
}

void loop() {
    RGBData colorData = colorSensor.readCalibratedRGB();
    logger.info("Calibrated RGB Values - R: " + String(colorData.red) +
                " G: " + String(colorData.green) +
                " B: " + String(colorData.blue) +
                " C: " + String(colorData.clear));
    delay(1000);
}