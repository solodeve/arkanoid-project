#include "draw.hpp"
#include "../controller/controller.hpp"
#include "../model/ball.hpp"
#include "../model/brick.hpp"
// #include "../model/common.hpp"
#include "allegro_draw.hpp"
#include "../model/text.hpp"
#include "../model/struct.hpp"

#include <allegro5/color.h>
#include <allegro5/drawing.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <string>

Draw::Draw() {}

using namespace std;

Text Draw::getLetter(TypePowerUp power, Coordinate powerCenter, ALLEGRO_COLOR& powerUpColor) {
    switch (power) {
        case TypePowerUp::laser:
            powerUpColor = COLOR_RED;
            L.setCenter(powerCenter);
            return L;
        case TypePowerUp::ballCatch:
            powerUpColor = COLOR_GREEN;
            At.setCenter(powerCenter);
            return At;
        case TypePowerUp::expend:
            powerUpColor = COLOR_BLUE;
            A.setCenter(powerCenter);
            return A;
        case TypePowerUp::slowDown:
            powerUpColor = COLOR_ORANGE;
            R.setCenter(powerCenter);
            return R;
        case TypePowerUp::player:
            powerUpColor = COLOR_GREY;
            J.setCenter(powerCenter);
            return J;
        case TypePowerUp::interruption:
            powerUpColor = COLOR_CYAN;
            I.setCenter(powerCenter);
            return I;
        default: {}
    }
    Coordinate Q_center{LETTRE_CENTER_X, LETTRE_CENTER_Y};
    Text Q{"Q", Q_center, COLOR_BLACK};
    return Q;
}

void Draw::drawVaus(shared_ptr<Game> game) {
    Vaus vaus = game->getVaus();

    Coordinate vausCenter = vaus.getCenter();
    RectDraw(vausCenter.x - vaus.getLenght()/2, vausCenter.y - vaus.getHeight()/2, vausCenter.x + vaus.getLenght()/2, 
    vausCenter.y + vaus.getHeight()/2, vaus.getColor(), vaus.getColor());
}

void Draw::drawPowerUps(shared_ptr<Game> game){
    ALLEGRO_COLOR powerUpColor = COLOR_WHITE;

    vector<Laser> lasers = game->getLasers();
    vector<TypePower> powers = game->getVectorPowers();

    for (auto& power: powers) {
        Coordinate PowerUpCenter = power.powerUpCenter;
        Text letterToDraw = getLetter(power.power, PowerUpCenter, powerUpColor);
        RectDraw(PowerUpCenter.x - widthPowerUp/2, PowerUpCenter.y - heightPowerUp/2, PowerUpCenter.x + widthPowerUp/2, PowerUpCenter.y + heightPowerUp/2, powerUpColor, powerUpColor);
        if (letterToDraw.getString() != "Q") letterToDraw.draw();
    }

    for (auto& laser: lasers) {
        Coordinate laserCenter = laser.center;
        RectDraw(laserCenter.x - laser.width/2, laserCenter.y - laser.height/2, laserCenter.x + laser.width/2, laserCenter.y + laser.height/2, COLOR_RED, COLOR_RED);
    }
}

void Draw::drawBricks(shared_ptr<Game> game) {
    vector<Brick> bricks = game->getBricks(), goldBricks = game->getGoldBricks();

    Coordinate brickCenter;
    for (auto& brick: bricks) {
        brickCenter = brick.coordinate;
        RectDraw(brickCenter.x - widthBrick/2, brickCenter.y - heightBrick/2, brickCenter.x + widthBrick/2, brickCenter.y + heightBrick/2, brick.color, brick.frameColor);
    }
    for (auto& goldBrick: goldBricks) {
        brickCenter = goldBrick.coordinate;
        RectDraw(brickCenter.x - widthBrick/2, brickCenter.y - heightBrick/2, brickCenter.x + widthBrick/2, brickCenter.y + heightBrick/2, goldBrick.color, goldBrick.frameColor);
    }
}

void Draw::drawBalls(shared_ptr<Game> game) {
    vector<Ball> balls = game->getBalls();

    Coordinate ballCenter;

    for (auto& ball: balls) {
        ballCenter = ball.getCenter();
        CircleDraw(ballCenter.x, ballCenter.y, ball.getRadius(), ball.getColor());
    }
}

void Draw::draw(shared_ptr<Game> game) {
    bool isWin = game->isWin();
    bool isLoose = game->isLoose();
    int score = game->getScore();
    int life = game->getLife();
    string newLifeString = "life: " + to_string(life), newScoreString = "score: " + to_string(score);
    lifeTxt_.setString(newLifeString);
    scoreTxt_.setString(newScoreString);

    if (!isWin && !isLoose) {
        drawBricks(game);
        drawPowerUps(game);
        drawBalls(game);
        drawVaus(game);

        lifeTxt_.draw();
        scoreTxt_.draw();
    } else {
        if (isWin || isLoose) {
            if (isWin) winText_.draw(); 
            else looseText_.draw();

            string finalScoreTxt = "final score: " + to_string(game->getScore());
            finalScore_.setString(finalScoreTxt);
            finalScore_.draw();

            if (game->getScore() >= game->getHighScore()) {
                newHighScoreTxt_.draw();
            }
        }
    }
};
