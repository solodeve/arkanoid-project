#include "ball.hpp"
#include "vaus.hpp"
#include "struct.hpp"
#include "brick.hpp"
#include "../varaibles_globales.hpp"
#include "power_up.hpp"
#include "common.hpp"

#include <vector>
#include <iostream>
#include <cmath>

#include <allegro5/color.h>

using namespace std;

Ball::Ball(Coordinate centre, int radius, Speed speed, ALLEGRO_COLOR color): 
    speed_{speed}, centre_{centre}, radius_{radius}, color_{color} {
        firstSpeed_ = speed;
    }
int Ball::DistanceX(Vaus vaus) {
        Coordinate vausCenter = vaus.getCenter();
        int vausLenght = vaus.getLenght();
        float distanceX;
        distanceX = centre_.x - (vausCenter.x - vausLenght / 2); 
        return distanceX;
    }

void Ball::calculSpeed(Vaus vaus) {
    int vausLenght = vaus.getLenght();
    float alpha, alphaRad, speed, distenceX;
    Coordinate vausCenter = vaus.getCenter();
    distenceX = centre_.x - (vausCenter.x - vausLenght / 2); 

    // Calcul de l'angle en fonction de la position de l'impact
    alpha = 30 + 120 * (1 - (distenceX / vausLenght));
    alphaRad = alpha * (M_PI / 180);

    speed = sqrt(speed_.x * speed_.x + speed_.y * speed_.y);

    // Mise à jour de la direction de la vitesse
    speed_.x = speed * cos(alphaRad);
    speed_.y = -speed * sin(alphaRad);
}

void Ball::touchVaus(Vaus& vaus) { 
    Coordinate vausCenter = vaus.getCenter();
    int vausLenght = vaus.getLenght();
    int vausHeight = vaus.getHeight();
    float left, right, bottom, up;

    if (inVaus(vaus, centre_, radius_, radius_)) {
        left = centre_.x + radius_ - (vausCenter.x - vausLenght/2);
        right = vausCenter.x + vausLenght/2 - (centre_.x - radius_);
        up = centre_.y + radius_ - (vausCenter.y - vausHeight/2);
        bottom = vausCenter.y + vausHeight/2 - (centre_.y - radius_);

        float minOverlapX = min(abs(left), abs(right));
        float minOverlapY = min(abs(up), abs(bottom));

        if (abs(minOverlapX) < abs(minOverlapY)) {
            if (!(abs(left) < abs(right))) { 
                speed_.y = -speed_.y;
            }
        }
        else if (abs(minOverlapX) >= abs(minOverlapY)) {
            if (!(abs(up) > abs(bottom))) { 
                calculSpeed(vaus); // Mise à jour de la vitesse si la balle touche vaus
            }
        }
    }
}

void Ball::touchWall() {
    if (((centre_.x + radius_ >= windowWidth) || (centre_.x - radius_ <= LEFT_WALL)) && (centre_.y - radius_ <= UP_WALL)) {
        speed_.x = -speed_.x;
        speed_.y = -speed_.y;
    }
    else if ((centre_.x + radius_ >= windowWidth) || (centre_.x - radius_ <= LEFT_WALL)) {
        speed_.x = -speed_.x;
    }
    else if (centre_.y - radius_ <= UP_WALL) {
        speed_.y = -speed_.y;
    }
}

bool Ball::touchBottom(Vaus vaus) {
    int tolerance = 50;
    Coordinate vausCenter = vaus.getCenter();
    if (centre_.y >= vausCenter.y + tolerance) return true;
    return false;
}

void Ball::reset() {
    centre_.x = firstCoordinate.x;
    centre_.y = firstCoordinate.y;

    speed_.x = firstSpeed_.x;
    speed_.y = firstSpeed_.y;
}

void Ball::update() {
    centre_.x += speed_.x;
    centre_.y += speed_.y;
}

void Ball::handleBrick(vector<Brick>& bricks, bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int index, int ballsSize) {
    int brickLife = bricks[index].life;
    Coordinate brickCenter = bricks[index].coordinate;
    if (ballsSize == 1) { // verifie si si interreruption est active, si oui aucun pouvoir ne peut être activé
        // verifie si une brique a un povoir
        if (bricks[index].powerUp != TypePowerUp::None) {
            isPowerUp = true;
            powerUpBrickCenter = brickCenter;
            newPower.power = bricks[index].powerUp;
            newPower.powerUpCenter = Coordinate(brickCenter.x, brickCenter.y);
        }
    }
    // Détruit une brique
    if (brickLife == 1) {
        bricks.erase(bricks.begin() + index);
        score += bricks[index].worth;
    // Réduit la vie d'une brique
    } else if (brickLife > 1) { 
        --bricks[index].life; 
        bricks[index].frameColor = COLOR_RED; 
    } 
}

void Ball::checkBricks(vector<Brick>& bricks, 
bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int ballsSize) {
    Coordinate brickCenter;
    float dx, dy;
    for (unsigned long i = 0; i < bricks.size(); ++i) { 
        brickCenter = bricks[i].coordinate;

        /* 
        * la logique de collision entre la balle et les briques vient du projet : https://github.com/Kielx/Arkanoid/blob/master/main.cpp#L123 
        */
        // Calcul des distances entre le centre de la balle et le centre de la brique
        dx = centre_.x - brickCenter.x;
        dy = centre_.y - brickCenter.y;

        // Calcul du chevauchement potentiel entre la balle et la brique sur les axes X et Y
        float overLapX = radius_ + widthBrick / 2 - abs(dx);
        float overLapY = radius_ + heightBrick / 2 - abs(dy);

        // Si la balle chevauche la brique (collision détectée)
        if (overLapX > 0 && overLapY > 0) {
            // Collision horizontale : inverse la direction X de la balle
            if (overLapX < overLapY) {
                handleBrick(bricks, isPowerUp, powerUpBrickCenter, newPower, score, i, ballsSize);
                speed_.x = -speed_.x;
                break;
            // Collision verticale : inverse la direction Y de la balle
            } else {
                handleBrick(bricks, isPowerUp, powerUpBrickCenter, newPower, score, i, ballsSize);
                speed_.y = -speed_.y;
                break;
            }
        } 
    }
}

void Ball::checkGoldBricks(vector<Brick>& goldBricks) {
    float dx, dy;
    Coordinate brickCenter;
    for (unsigned long i = 0; i < goldBricks.size(); ++i) {
        Brick brick = goldBricks[i];
        brickCenter = brick.coordinate;
        /* 
        * la logique de collision entre la balle et les briques vient du projet : https://github.com/Kielx/Arkanoid/blob/master/main.cpp#L123 
        */
        // Calcul des distances entre le centre de la balle et le centre de la brique
        dx = centre_.x - brickCenter.x;
        dy = centre_.y - brickCenter.y;

        // Calcul du chevauchement potentiel entre la balle et la brique sur les axes X et Y
        double overLapX = radius_ + widthBrick / 2 - abs(dx);
        double overLapY = radius_ + heightBrick / 2 - abs(dy);

        // Si la balle chevauche la brique (collision détectée)
        if (overLapX > 0 && overLapY > 0) {
            // Collision des coins : inverse la direction X et Y de la balle
            if (overLapX == overLapY) {
                speed_.x = -speed_.x;
                speed_.y = -speed_.y;
            }
            // Collision horizontale : inverse la direction X de la balle
            if (overLapX < overLapY) {
                speed_.x = -speed_.x;
                break;
            // Collision verticale : inverse la direction Y de la balle
            } else {
                speed_.y = -speed_.y;
                break;
            }
        } 
    }
}

void Ball::touchBrick(vector<Brick>& bricks, vector<Brick>& goldBricks, 
bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower, int& score, int ballsSize) { 
    // verifie les collisions avec les briques
    checkBricks(bricks, isPowerUp, powerUpBrickCenter, newPower, score, ballsSize);

    // verifie les collisions avec les briques dorées
    checkGoldBricks(goldBricks);
}
