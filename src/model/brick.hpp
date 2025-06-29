#pragma once

#include <allegro5/color.h>

#include "struct.hpp"

struct Brick {
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR frameColor;
    int worth;
    TypePowerUp powerUp;
    Coordinate coordinate;
    int life;

    /** @brief Constructeur
     *  @param color Couleur de la brique
     *  @param worth Valeur de la brique
     *  @param powerUp Type de power up de la brique
     *  @param coordinate Coordonnées de la brique
     *  @param life Vie de la brique
    */
    Brick(ALLEGRO_COLOR color, int worth, TypePowerUp powerUp, Coordinate coordinate, int life = 1)
        : color(color), worth(worth), powerUp(powerUp), coordinate(coordinate), life(life) { frameColor = color; }
};
