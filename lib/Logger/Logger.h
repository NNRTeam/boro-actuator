#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <Config.h>

class Logger
{
public:
    enum class Level {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        NONE = 4
    };

    Logger(Level level = Level::INFO, String prefix = "") : logLevel(level), logPrefix(prefix) {}

    void setLogLevel(Level level) {
        logLevel = level;
    }

    void debug(const String &message) {
        log(Level::DEBUG, "DEBUG: " + message);
    }

    void info(const String &message) {
        log(Level::INFO, "INFO: " + message);
    }

    void warn(const String &message) {
        log(Level::WARN, "WARN: " + message);
    }

    void error(const String &message) {
        log(Level::ERROR, "ERROR: " + message);
    }

    void setPrefix(const String &prefix) {
        logPrefix = prefix;
    }
private:
    Level logLevel;
    String logPrefix;

    void log(Level level, const String &message) {
        if (config::ENABLE_SERIAL_DEBUG && level >= logLevel) {
            if (!logPrefix.isEmpty())
                Serial.print("[" + logPrefix + "] ");
            Serial.println(message);
        }
    }
};

#endif // LOGGER_H