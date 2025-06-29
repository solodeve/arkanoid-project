#pragma once

#include "ball.hpp"
#include "vaus.hpp"
#include "struct.hpp"
#include "text.hpp"
#include "brick.hpp"
#include "level.hpp"
#include "power_up.hpp"
#include "laser.hpp"
#include "../varaibles_globales.hpp"

#include <vector>
#include <string>
#include <memory>

using namespace std;

class Game {
    vector<Ball> balls_;
    // int ballCount_ = 1;
    vector<Brick> bricks_;
    vector<Brick> goldBricks_;
    int score_;
    int life_;
    int highScore_;
    Vaus vaus_;
    vector< shared_ptr<Level> > levels;
    int current_level = 0;
    PowerUp powerUp_;
    bool isPowerUp_ = false;
    Coordinate powerUpBrickCenter{POWER_UP_BRICK_CENTER_X, POWER_UP_BRICK_CENTER_Y};
    TypePower newPower = TypePower(false, TypePowerUp::None, Coordinate{COORDINATE_OUTSIDE_POWER_X, COORDINATE_OUTSIDE_POWER_Y});
    vector<TypePower> vectorPowers_;
    int timer = 300;
    bool ballOnVaus = false;

    void fileToHighScore();

    void handlePowerUps();

    void handleTimer();

    public:
        /** @brief Constructeur
         *  @param vectorPowers Indique les pouvoirs déjà acquis par le joueur
         *  @param balls Indique les balles du jeu 
         *  @param bricks Indique les briques du jeu
         *  @param goldBricks Indique les briques en or du jeu
         *  @param highScore Indique le score le plus élevé du jeu
         *  @param vaus Indique le vaus du jeu
         *  @param life Indique le nombre de vie du joueur
         *  @param score Indique le score du joueur
         *  @param powerUp Indique le powerUp du joueur
         */
        Game(vector<TypePower> powers, vector<Ball> balls, vector<Brick> bricks, 
        vector<Brick> goldBricks, int highScore, Vaus vaus, int life, int score, PowerUp powerUp);
        ~Game() = default;

        inline int getScore() { return score_; }
        inline void setScore(int score) { score_ = score; }

        inline int getCurrentLevel() { return current_level; }

        inline int getLife() { return life_; }
        inline void setLife(int life) { life_ = life; }

        inline bool getIsPowerUp() { return isPowerUp_; }

        inline PowerUp getPowerUp() { return powerUp_; }
        inline void setPowerUp(PowerUp newPowerUp) { powerUp_ = newPowerUp; }

        inline int getHighScore() { return highScore_; }
        inline void setHighScore(int highScore) { highScore_ = highScore; }

        inline vector<Brick> getBricks() { return bricks_; }
        inline void setBricks(vector<Brick> newBricks) { bricks_ = newBricks; }

        inline vector<Brick> getGoldBricks() { return goldBricks_; }
        inline void setGoldBricks(vector<Brick> newBricks) { goldBricks_ = newBricks; }

        inline vector<Ball> getBalls() { return balls_; }
        inline void setBalls(vector<Ball> newBalls) { balls_ = newBalls; }

        inline Vaus getVaus() { return vaus_; }
        inline void setVaus(Vaus newVaus) { vaus_ = newVaus; }

        inline vector<Laser> getLasers() { return powerUp_.getLasers(); }

        inline vector<TypePower> getVectorPowers() { return vectorPowers_; }

        bool isWin();
        bool isLoose();
        bool checkBalls();

        // verifie les collisions avec les briques
        void checkBrick();

        // determine le pouvoir du joueur
        void determinePowerUp();

        // met à jour les pouvoirs
        void spaceTouch();

        // met à jour le jeu (à chaque frame)
        void update();

        // reset le jeu
        void reset(); 

        void changeLevel(unsigned long level);

        // Fait tomber les capsules de pouvoirs
        void powerUpUpdate();

        // permet de mettre le le meilleur score dans le fichier "highScore.txt"
        void includeHighScore(int newHighScore);

        // permet de bouger la vaus grâce à la souris
        void mouseUpdate(float mouseX);

        // permet de bouger la vaus grâce au clavier
        void keyboardUpdate(string side);

        // permet de remmetre le meilleur score à 0
        void resetHighScore();

        // permet de gérer la fin d'une partie
        void endGameLogic(bool& levelIsChange);
};