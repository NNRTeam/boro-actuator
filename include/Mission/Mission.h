#pragma once

#include <optional>

enum class MissionStatus
{
    NOT_STARTED = 0,
    STARTED = 1,
    FINISHED = 2,
    FAILED = 3,
    CANCELED = 4,
};

class Mission
{
public:
    Mission() = default;

    enum class Type
    {
        PUT_IN_STOCK,
        DROP,
        IDLE,
        IDLE_TOP
    };

    int id;
    Type type;
    bool should_turn;
    bool should_keep;
};