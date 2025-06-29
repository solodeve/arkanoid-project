#pragma once

#include "struct.hpp"
#include "vaus.hpp"
#include "struct.hpp"
#include "brick.hpp"
#include "../varaibles_globales.hpp"
#include "power_up.hpp"

#include <vector>

#include <allegro5/color.h>

class Ball {
    Speed speed_;
    Speed firstSpeed_;
    Speed touchVaus_;
    Coordinate firstCoordinate{500, 780};
    Coordinate centre_; 
    int radius_;
    ALLEGRO_COLOR color_; 
    int distanceX_ = 0;

    void checkGoldBricks(vector<Brick>& bricks);

    public:
        /**
         * @brief constructeur
         * @param centre Indique la position initial de la balle 
         * @param radius Indique le rayon de la balle
         * @param speed Indique la vitesse de la balle
         * @param color Indique la couleur de la balle
         */
        Ball(Coordinate centre, int radius, Speed speed, ALLEGRO_COLOR color = COLOR_GREY);
        ~Ball() = default;

        inline int getDistanceX() { return distanceX_; }
        inline void setDistanceX(int distanceX) { distanceX_ = distanceX; }

        inline int getRadius() { return radius_; }
        inline void setRadius(int radius) { radius_ = radius; }

        inline Coordinate getCenter() { return centre_; }
        inline void setCenter(Coordinate centre) {centre_ = centre; }

        inline Coordinate getFirstCoordinate() { return firstCoordinate; }

        inline Speed getTouchVaus() { return touchVaus_; }
        inline void setTouchVaus(Speed newTouchVaus) {touchVaus_ = newTouchVaus; }

        inline Speed getSpeed() { return speed_; }
        inline void setSpeed(Speed speed) {speed_ = speed; }

        inline void setColor(ALLEGRO_COLOR newColor) { color_ = newColor; }
        inline ALLEGRO_COLOR getColor() { return color_; }

        // Gère la collision avec vaus
        void touchVaus(Vaus& vaus);

        // Gère la collision avec les murs
        void touchWall();

        // Gère la collision avec les briques
        void touchBrick(vector<Brick>& bricks, vector<Brick>& goldBricks, 
        bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int ballsSize); 
        
        // Vérifie si la balle touche le bas de l'écran
        bool touchBottom(Vaus vaus);

        void update();
        void reset();

        // Calcule une nouvelle vitesse en fonction de la collision avec Vaus
        void calculSpeed(Vaus vaus);

        // void resetSpeed();

        // Calcule la distance entre la balle et le côté gauche de Vaus
        int DistanceX(Vaus vaus);

        // Vérifie les collisions avec les briques
        void checkBricks(vector<Brick>& bricks, bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int ballsSize);

        // Gère une brique spécifique lors d'une collision
        void handleBrick(vector<Brick>& bricks, bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int index, int ballsSize);
};
