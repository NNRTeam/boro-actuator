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
        if (shouldLog(Level::DEBUG))
            log(Level::DEBUG, "DEBUG: " + message);
    }

    void info(const String &message) {
        if (shouldLog(Level::INFO))
            log(Level::INFO, "INFO: " + message);
    }

    void warn(const String &message) {
        if (shouldLog(Level::WARN))
            log(Level::WARN, "WARN: " + message);
    }

    void error(const String &message) {
        if (shouldLog(Level::ERROR))
            log(Level::ERROR, "ERROR: " + message);
    }

    // Overloads with const char* to avoid String construction when not needed
    void debug(const char* message) {
        if (shouldLog(Level::DEBUG))
            logRaw("DEBUG: ", message);
    }

    void info(const char* message) {
        if (shouldLog(Level::INFO))
            logRaw("INFO: ", message);
    }

    void warn(const char* message) {
        if (shouldLog(Level::WARN))
            logRaw("WARN: ", message);
    }

    void error(const char* message) {
        if (shouldLog(Level::ERROR))
            logRaw("ERROR: ", message);
    }

    void setPrefix(const String &prefix) {
        logPrefix = prefix;
    }

private:
    Level logLevel;
    String logPrefix;

    bool shouldLog(Level level) const {
        return config::ENABLE_SERIAL_DEBUG && level >= logLevel;
    }

    void log(Level level, const String &message) {
        if (!logPrefix.isEmpty())
            Serial.print("[" + logPrefix + "] ");
        Serial.println(message);
    }

    void logRaw(const char* levelStr, const char* message) {
        if (!logPrefix.isEmpty()) {
            Serial.print('[');
            Serial.print(logPrefix);
            Serial.print("] ");
        }
        Serial.print(levelStr);
        Serial.println(message);
    }
};

#endif // LOGGER_H