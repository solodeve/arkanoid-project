#pragma once

#include "../varaibles_globales.hpp"

struct Speed {
    float x;
    float y;
};

struct Coordinate {
    float x;
    float y;
};
enum class TypePowerUp {
    laser,
    expend,
    ballCatch,
    slowDown,
    interruption,
    player,
    None,
};

struct TypePower {
    bool hasPowerUp;
    TypePowerUp power;
    Coordinate powerUpCenter{COORDINATE_OUTSIDE_POWER_X, COORDINATE_OUTSIDE_POWER_Y};
};