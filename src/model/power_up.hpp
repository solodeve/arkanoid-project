#pragma once

#include "struct.hpp"
#include "vaus.hpp"
#include "laser.hpp"

#include <vector>
#include <iostream>

class Ball;

using namespace std;

class PowerUp {
    Coordinate powerUpCenter_;
    Speed powerUpSpeed_;
    int newVausWidth_;
    bool hasPowerUp = false;
    vector<Laser> lasers_;
    int slowDownCount = 0;

    public:
        /** @brief Constructeur
         *  @param powerUpCenter Indique la position des capsules de pouvoir
         *  @param powerUpSpeed Indique la vitesse des capsules de pouvoir
         *  @param newVausWidth Indique la nouvelle longuer de vaus (lorsque le pouvoir est agrandir)
         */
        PowerUp(Coordinate powerUpCenter, Speed powerUpSpeed, int newVausWidth);
        ~PowerUp() = default;

        inline void setCenter(Coordinate newCenter) { powerUpCenter_ = newCenter; }
        inline Coordinate getCenter() { return powerUpCenter_; }

        inline void setHasPowerUp(bool newHasPowerUp) { hasPowerUp = newHasPowerUp; } 
        inline bool getHasPowerUp() { return hasPowerUp; }

        inline Speed getSpeed() { return powerUpSpeed_; }

        inline vector<Laser> getLasers() { return lasers_; }
        inline void setLasers(vector<Laser> lasers) { lasers_ = lasers; }

        inline int getSlowDownCount() { return slowDownCount; }

        // fait tomber les power-ups (à chaque frame)
        void update(); 

        // reset les pouvoirs
        void powerReset(TypePower& power, vector<Ball>& balls, Vaus& vaus);

        // permet la création d'un nouveau laser
        void newLaser(Vaus vaus);

        // vérifie si un laser touche une brique
        void laser(vector<Brick>& bricks, vector<Brick>& goldBricks, int& score, bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower);
        
        // ralentit la balle
        void slowDown(Ball& ball);

        // augmente la vie du joueur de 1
        void player(int& life);

        // divise la balle en 3
        void interruption(vector<Ball>& balls);

        // agrandit la vaus
        void expend(Vaus& vaus);

        // permet de rattraper la balle
        void ballCatch(vector<Ball>& balls, Vaus& vaus);

        // reset la vitesse de la balle petit à petit ds le cas ou slowDownCount est > 0
        void resetBallSpeed(vector<Ball>& balls, Vaus& vaus);

        void decreaseSLowDownCount(); 
        void increaseSLowDownCount();
};