#pragma once

#include "struct.hpp"
#include "../varaibles_globales.hpp"
#include <allegro5/color.h>

#include <string>

using namespace std;

class Vaus {
    int lenght_, height_;
    Coordinate center_;
    TypePower power_;
    ALLEGRO_COLOR color_;
    Speed speed_;
    int baseLenght;
    bool ballIsCatch_ = false, isCatch_ = false;
    public:
        /** @brief contructeur
         *  @param center_ Indique la position initial de la vaus
         *  @param lenght Indique la longueur de la vaus
         *  @param height_ Indique la hauteur de la vaus
         *  @param speed Indique la vitesse de la vaus
         *  @param power Indique le pouvoir de la vaus
         *  @param color Indique la couleur de la vaus
         */
        Vaus(Coordinate center_, int lenght, int height_,Speed speed, TypePower power = TypePower(false, TypePowerUp::None, Coordinate(-50,-50)), ALLEGRO_COLOR color = COLOR_WHITE);
        ~Vaus() = default;

        void setCenter(Coordinate newPosition);
        Coordinate getCenter();

        inline void setBallIsCatch(bool ballIsCatch) { ballIsCatch_ = ballIsCatch; }
        inline bool getBallIsCatch() { return ballIsCatch_; }

        inline void setIsCatch(bool isCatch) { isCatch_ = isCatch; }
        inline bool getIsCatch() { return isCatch_; }

        void setLenght(int size);
        int getLenght();

        Speed getSpeed() { return speed_; }

        inline int getBaseLenght() { return baseLenght; }

        inline void setColor(ALLEGRO_COLOR newColor) { color_ = newColor; }
        inline ALLEGRO_COLOR getColor() { return color_; }

        void setheight(int size);
        int getHeight();

        inline TypePower getTypePower() { return power_; }

        inline void setHasPowerUp(bool newHasPowerUp) { power_.hasPowerUp = newHasPowerUp; }
        inline void setTypePowerUp(TypePowerUp newType) { power_.power = newType; }
        inline void setPowerUpCenter(Coordinate newPowerUpCenter) { power_.powerUpCenter = newPowerUpCenter; }
};