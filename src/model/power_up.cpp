#include "struct.hpp"
#include "ball.hpp"
#include "vaus.hpp"
#include "power_up.hpp"
#include "common.hpp"
#include "../varaibles_globales.hpp"

#include <vector>
#include <iostream>

using namespace std;

void PowerUp::powerReset(TypePower& power, vector<Ball>& balls, Vaus& vaus) {
    Speed baseBallSpeed = balls[0].getSpeed();
    // si l'ancien pouvoir était ballCatch et que la balle est attrapée alors on la relâche
    if (vaus.getTypePower().power == TypePowerUp::ballCatch && vaus.getBallIsCatch()) {
        balls[0].setSpeed(balls[0].getTouchVaus());
        balls[0].setCenter(Coordinate(balls[0].getCenter().x, balls[0].getCenter().y - 10));
        balls[0].calculSpeed(vaus);
        vaus.setIsCatch(false);
    }
    // si l'ancien pouvoir était slowDown alors on réinitialise la vitesse de la balle
    if (vaus.getTypePower().power == TypePowerUp::slowDown) {
        for (int i = 0; i <= slowDownCount; ++i) {
            baseBallSpeed.x *= 2;
            baseBallSpeed.y *= 2;
            balls[0].setSpeed(baseBallSpeed);
            decreaseSLowDownCount();
        }
    } else { slowDownCount = 0; }
    // si l'ancien pouvoir était agrandir alors on remet la vaus à sa taille de base
    if (power.power == TypePowerUp::expend) {
        vaus.setLenght(vaus.getBaseLenght());
    // si l'a ancien pouvoir était laser alors on supprime les lasers
    } else if (power.power == TypePowerUp::laser) {
        lasers_ = {};
    }
    vaus.setTypePowerUp(TypePowerUp::None);
}

PowerUp::PowerUp(Coordinate powerUpCenter, Speed powerUpSpeed, int newVausWidth)
    : powerUpCenter_{powerUpCenter}, powerUpSpeed_{powerUpSpeed}, newVausWidth_{newVausWidth} {}

void PowerUp::update() {
    powerUpCenter_.y += powerUpSpeed_.y;
}

void PowerUp::newLaser(Vaus vaus) {
    Coordinate vausCenter = vaus.getCenter();
    Laser newLaser;

    // initialise la positiom du laser
    newLaser.center.y = vausCenter.y - widthBrick/2;
    newLaser.center.x = vausCenter.x;

    // initialise la vitesse du laser
    newLaser.speed = Speed(LASER_SPEED_X, LASER_SPEED_Y);

    //initialise la taille du laser
    newLaser.width = 20;
    newLaser.height = 40;

    // ajoute le laser au vecteur des lasers
    lasers_.push_back(newLaser);
}

void PowerUp::laser(vector<Brick>& bricks, vector<Brick>& goldBricks, int& score, 
bool& isPowerUp, Coordinate& powerUpBrickCenter, TypePower& newPower) {
    // vérifie si un laser touche une brique
    if (lasers_.size() > 0) {
        bool laserIsDestroy = false;
        for (unsigned long j=0; j < lasers_.size(); ++j) {
            for (unsigned long i=0; i < bricks.size(); ++i) {
                // verifie si le laser touche une brique
                if (inBrick(lasers_[j], bricks[i])) {
                    // verifie si la brique a un pouvoir
                    if (bricks[i].powerUp != TypePowerUp::None) {
                        isPowerUp = true;
                        powerUpBrickCenter = bricks[i].coordinate;

                        newPower.power = bricks[i].powerUp;
                        newPower.powerUpCenter = Coordinate(bricks[i].coordinate.x, bricks[i].coordinate.y);
                    }
                    // Détruit une brique
                    if (bricks[i].life == 1) {
                        bricks.erase(bricks.begin() + i);
                        score += bricks[i].worth;
                    // Réduit la vie d'une brique
                    } else { 
                        --bricks[i].life; 
                        bricks[i].frameColor = COLOR_RED; 
                    }
                    // enleve le laser du vecteur des lasers
                    lasers_.erase(lasers_.begin() + j);
                    laserIsDestroy = true;
                    
                }
            } 
            // verifie si le laser touche une brique en or
            for (unsigned long i = 0; i < goldBricks.size(); i++) {
                // verifie si le laser touche une brique en or si un laser touche une brique en or alors elle ne fait que s'elver du vecteur lasers
                if (inBrick(lasers_[j], goldBricks[i])) {
                    lasers_.erase(lasers_.begin() + j);
                    laserIsDestroy = true;
                }
            }
            // si le laser n'a pas touché de brique alors il continue de monter
            if (!laserIsDestroy) {
                lasers_[j].center.y += lasers_[j].speed.y;
                laserIsDestroy = false;
            }
        }
    }
}

void PowerUp::slowDown(Ball& ball) {
    increaseSLowDownCount();
    Speed ballSpeed = ball.getSpeed();
    ballSpeed.x /= 2;
    ballSpeed.y /= 2;
    ball.setSpeed(ballSpeed);
}

void PowerUp::ballCatch(vector<Ball>& balls, Vaus& vaus) {
    Coordinate vausCenter = vaus.getCenter();
    Speed ballSpeed;
    Coordinate ballCenter = balls[0].getCenter();
    int vausLenght = vaus.getLenght();
    float newBallX;
    // verifie si la balle est attrapée (si la ballse touche vaus)
    if (vaus.getIsCatch()) { 
        // si la balle est attrapée alors elle suit vaus
        newBallX = balls[0].getDistanceX() + (vausCenter.x - vausLenght/2);
        balls[0].setCenter(Coordinate{newBallX, balls[0].getCenter().y});
    }
    // verifie si la balle touche vaus et que la balle n'est pas attrapée
    else if (inVaus(vaus, ballCenter, widthPowerUp, heightPowerUp)) {
        // met la balle en mode attrapée
        ballSpeed = balls[0].getSpeed();
        balls[0].setTouchVaus(ballSpeed);
        balls[0].setSpeed(Speed{0,0}); // la balle s'arrête
        vaus.setIsCatch(true);
        balls[0].setDistanceX(balls[0].DistanceX(vaus));
    }
}

void PowerUp::expend(Vaus& vaus) {
    int vausLenght = vaus.getLenght();
    vausLenght = newVausWidth_;
    vaus.setLenght(vausLenght);
}

void PowerUp::player(int& life) {
    ++life;
}

void PowerUp::interruption(vector<Ball>& balls) {
    // crée 2 nouvelles balles avec des vitesses en X différentes
    Coordinate ballCenter{balls[0].getCenter().x+20, balls[0].getCenter().y+20};
    int radius = 10;
    Speed ballSpeed{BALL_SPEED_X, BALL_SPEED_Y};
    Ball ball = Ball(ballCenter, radius, ballSpeed);
    balls.push_back(ball);

    ballCenter = Coordinate{balls[0].getCenter().x-20, balls[0].getCenter().y-20};
    ballSpeed = Speed{-BALL_SPEED_X, BALL_SPEED_Y};
    ball = Ball(ballCenter, radius, ballSpeed);
    balls.push_back(ball);
}

void PowerUp::resetBallSpeed(vector<Ball>& balls, Vaus& vaus) {
    if (vaus.getTypePower().power == TypePowerUp::slowDown) {
        Speed baseBallSpeed = balls[0].getSpeed();
        baseBallSpeed.x *= 2;
        baseBallSpeed.y *= 2;
        balls[0].setSpeed(baseBallSpeed);
    }
}

void PowerUp::decreaseSLowDownCount() { --slowDownCount; } 
void PowerUp::increaseSLowDownCount() { ++slowDownCount; }