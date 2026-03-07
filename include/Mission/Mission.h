#pragma once

#include <optional>

class Mission
{
public:
    Mission() = default;

    enum class Type
    {
        PUT_IN_STOCK,
        DESTOCK,
    };

    enum class Color
    {
        YELLOW,
        BLUE,
    };

    Type type;
    Color color;
};