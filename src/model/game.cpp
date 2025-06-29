#include "game.hpp"
#include "ball.hpp"
#include "vaus.hpp"
#include "struct.hpp"
#include "text.hpp"
#include "brick.hpp"
#include "level.hpp"
#include "../varaibles_globales.hpp"
#include "common.hpp"

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Game::fileToHighScore() {
    ifstream file("highScore.txt");
    string stringRead;
    if (getline(file, stringRead)) {
        stringstream ss(stringRead);
        ss >> highScore_;
    } else {
        cerr << "Error reading from the highScore file!" << endl;
        exit(1);
    }
    file.close();
}

Game::Game(vector<TypePower> vectorPowers, vector<Ball> balls, vector<Brick> bricks, 
vector<Brick> goldBricks, int highScore, Vaus vaus, int life, int score, PowerUp powerUp)
    : balls_{balls}, bricks_{bricks}, goldBricks_{goldBricks}, score_{score}, life_{life}, highScore_{highScore}, vaus_{vaus}, powerUp_{powerUp}, vectorPowers_{vectorPowers} {
        // création des niveaux
        shared_ptr<Level> level1 = make_shared<Level1>();
        shared_ptr<Level> level2 = make_shared<Level2>();
        shared_ptr<Level> level3 = make_shared<Level3>();
        shared_ptr<Level> level4 = make_shared<Level4>();
        shared_ptr<Level> level5 = make_shared<Level5>();
        shared_ptr<Level> level6 = make_shared<Level6>();
        shared_ptr<Level> level7 = make_shared<Level7>();
        shared_ptr<Level> level8 = make_shared<Level8>();
        shared_ptr<Level> level9 = make_shared<Level9>();

        // ajout des niveaux dans le vecteur levels
        levels.push_back(level1);
        levels.push_back(level2);
        levels.push_back(level3);
        levels.push_back(level4);
        levels.push_back(level5);
        levels.push_back(level6);
        levels.push_back(level7);
        levels.push_back(level8);
        levels.push_back(level9);

        // récupération des brick depuis les niveaux
        bricks_ = levels[current_level]->getBricks();
        goldBricks_ = levels[current_level]->getGoldBricks();

        // récpération du meilleur score à partir du fichier "highScore.txt"
        fileToHighScore();
    }

void Game::includeHighScore(int newHighScore) {
    ofstream file("highScore.txt");
    // verifie si le fichier est ouvert
    if (!file) {
        cerr << "Error writing from the highScore file!" << std::endl;
        exit(1);
    }
    highScore_ = newHighScore; // met à jour le meilleur score
    file << to_string(highScore_); // place le meilleur score dans le fichier
    file.close();
}

bool Game::isWin() {
    // verifie si il n'y a plus de briques
    if (bricks_.size() == NO_BRICKS_LEFT) return true;
    return false;
}

bool Game::isLoose() {
    // verifie si le joueur n'a plus de vie
    if (life_ == 0) return true;
    return false;
}

bool Game::checkBalls() {
    int deadZone = 200;
    Coordinate vausCenter = vaus_.getCenter();
    for (unsigned long i = 0; i < balls_.size(); ++i) { 
        Coordinate ballCenter = balls_[i].getCenter();
        if (ballCenter.y + balls_[i].getRadius() >= vausCenter.y + deadZone) {
            // verifie s'il existe plus d'une balle
            if (balls_.size() > 1) { 
                balls_.erase(balls_.begin() + i); // enleve la balle
                vaus_.setTypePowerUp(TypePowerUp::None); // enleve le pouvoir
                return true; // renvoie vrai car on a encore 1 ou plus d'une balle
            }
            // verifie s'il reste une seule balle
            else if (balls_.size() == 1) { return false; }
        }
    }
    return true;
}

void Game::checkBrick() {
    for (auto& ball : balls_) {
        // verifie les collisions avec les briques
        ball.touchBrick(bricks_, goldBricks_, isPowerUp_, powerUpBrickCenter, newPower, score_, balls_.size());
        // si un power-up a été généré par la brique et n'est pas déjà ajouté
        if (newPower.power != TypePowerUp::None) {
            vectorPowers_.push_back(newPower); // ajoute le power-up à la liste des power-ups
            newPower.power = TypePowerUp::None; // réinitialise le power-up généré
        }
    }
}

void Game::powerUpUpdate() { 
    for (auto& power: vectorPowers_) {
        Speed powerSpeed = powerUp_.getSpeed();
        // fait tomber les power-ups
        power.powerUpCenter = Coordinate(power.powerUpCenter.x+powerSpeed.x, power.powerUpCenter.y+powerSpeed.y);
    }
}

void Game::determinePowerUp() {
    // récupère le type de power-up actuellement activé par le Vaus
    TypePowerUp type = vaus_.getTypePower().power;
    if (vaus_.getTypePower().hasPowerUp) {
        switch (type) {
            case TypePowerUp::slowDown:
                powerUp_.slowDown(balls_[0]);
                break;
            case TypePowerUp::player:
                powerUp_.player(life_);
                break;
            case TypePowerUp::expend:
                powerUp_.expend(vaus_);
                break;
            case TypePowerUp::interruption:
                powerUp_.interruption(balls_);
                break;
            case TypePowerUp::ballCatch:
                powerUp_.ballCatch(balls_, vaus_);
                break;
            case TypePowerUp::laser:
                powerUp_.laser(bricks_, goldBricks_, score_, isPowerUp_, powerUpBrickCenter, newPower);
                break;
            default: {} // ne fait rien si le type de power-up n'est pas reconnu
        }
    }
}

void Game::spaceTouch() {
    // si le joueur a attrapé la balle et que le pouvoir attraper est actif
    if (vaus_.getIsCatch()) {
        balls_[0].setSpeed(balls_[0].getTouchVaus()); // la balle prend la vitesse de la vaus
        balls_[0].setCenter(Coordinate(balls_[0].getCenter().x, balls_[0].getCenter().y - 10)); 
        balls_[0].calculSpeed(vaus_); // calcule la nouvelle vitesse de la balle
        vaus_.setIsCatch(false); // réinitialise l'état du Vaus (le Vaus n'est plus dans un état "attraper")
        timer = 300;
    // si le pouvoir laser est actif
    } else if (TypePowerUp::laser == vaus_.getTypePower().power && vaus_.getTypePower().hasPowerUp) {
        powerUp_.newLaser(vaus_); // lance un nouveau laser
    }
}

void Game::handlePowerUps() {
    for (unsigned long i = 0; i < vectorPowers_.size(); ++i) {
        // vérifie si un power-up entre en collision avec le Vaus
        if (inVaus(vaus_, vectorPowers_[i].powerUpCenter, widthPowerUp, heightPowerUp)) { 
            TypePower vausPower = vaus_.getTypePower();
            // si le pouvoir actuel du Vaus est différent du pouvoir du power-up ou si le pouvoir du power-up est ralentir
            if (vausPower.power != vectorPowers_[i].power || vectorPowers_[i].power == TypePowerUp::slowDown) { 
                // si le pouvoir du power-up est ralentir et que le pouvoir actuel du Vaus n'est pas ralentir
                if (vectorPowers_[i].power == TypePowerUp::slowDown && vausPower.power != TypePowerUp::slowDown) { powerUp_.powerReset(vausPower, balls_, vaus_); timer = 300; }
                else if (vectorPowers_[i].power != TypePowerUp::slowDown) { powerUp_.powerReset(vausPower, balls_, vaus_); timer = 300; } // vausPower.power != TypePowerUp::slowDown || 
                vaus_.setHasPowerUp(true); // marque que le Vaus a maintenant un power-up
            }
            else { 
                if (!(vausPower.power == TypePowerUp::ballCatch) && !(vausPower.power == TypePowerUp::laser)) { 
                    vaus_.setHasPowerUp(false); // marque que le Vaus n'a plus de power-up pour que le pouvoir (dans le case autre que laser et ballCatch) ne soit pas actif qu'une fois
                } 
            }

            isPowerUp_ = false; // marque que le power-up n'est plus actif
            vaus_.setTypePowerUp(vectorPowers_[i].power); // met à jour le pouvoir du Vaus
            vectorPowers_.erase(vectorPowers_.begin() + i); // enleve le power-up de la liste des power-ups
            // si le pouvoir est attraper alors lorsque la balle touche vaus alors la balle est attrapée (et reste sur le vaus)
            if (vaus_.getTypePower().power == TypePowerUp::ballCatch) {
                vaus_.setBallIsCatch(true);
            }
        }
    }
}

void Game::handleTimer() {
    // verifie si le pouvoir attraper est actif
    if (vaus_.getIsCatch()) {
        --timer; // décrémente le timer
        int releaseOffset = 10;
        // si le timer est à 0 alors on renvoi la balle
        if ((timer <= 0)) {
            timer = 300;
            balls_[0].setSpeed(balls_[0].getTouchVaus());
            balls_[0].setCenter(Coordinate(balls_[0].getCenter().x, balls_[0].getCenter().y - releaseOffset));
            balls_[0].calculSpeed(vaus_);
            vaus_.setIsCatch(false);
        }
    // verifie si le pouvoir ralentir est actif
    } else if (vaus_.getTypePower().power == TypePowerUp::slowDown) {
        --timer; // décrémente le timer
        // si le timer est à 0 alors on réinitialise la vitesse de la balle
        if (timer < 0) {
            timer = 300;
            if (powerUp_.getSlowDownCount() > 0) {
                powerUp_.decreaseSLowDownCount();
                powerUp_.resetBallSpeed(balls_, vaus_);
            }
        }
    }
}

void Game::update() {
    Coordinate ballCenter;
    
    handleTimer(); 

    // vérifie les collisions avec des balles avec la vaus et les murs
    for (unsigned long i = 0; i < balls_.size(); ++i) {
        ballCenter = balls_[i].getCenter();

        balls_[i].touchVaus(vaus_); 
        balls_[i].touchWall();  
    }
    for (auto& ball: balls_) {
        ball.update();
    }

    checkBrick(); 

    handlePowerUps();

    // verifie si vaus contient un power-up
    if (vaus_.getTypePower().hasPowerUp) {
        determinePowerUp(); // active le pouvoir de vaus
        if (!(vaus_.getTypePower().power == TypePowerUp::ballCatch) && !(vaus_.getTypePower().power == TypePowerUp::laser)) { 
            vaus_.setHasPowerUp(false); // desactive le pouvoir de vaus si le pouvoir n'est pas attraper ou laser
        }
    }
    powerUpUpdate();

    // verifie s'il reste plus d'une balle
    bool cdt = checkBalls();
    // si le joueur n'a plus de balle alors on réinitialise le jeu
    if ((!cdt)) {
        balls_[0].reset();
        --life_;
        vaus_.setTypePowerUp(TypePowerUp::None);
        powerUp_.setLasers({});
    } 
}

void Game::reset() { 
    vaus_.setLenght(vaus_.getBaseLenght()); // réinitialise la longueur de la vaus

    Speed baseBallSpeed{BALL_SPEED_X, BALL_SPEED_Y};
    Coordinate ballCenter{BALL_CENTER_X, BALL_CENTER_Y};
    int radius = 10;
    Ball ball = Ball(ballCenter, radius, baseBallSpeed, COLOR_WHITE); // crée une nouvelle balle
    balls_ = {ball}; // réinitialise le vecteur des balles

    Coordinate baseVausCordinate{VAUS_CENTER_X, VAUS_CENTER_Y};
    vaus_.setCenter(baseVausCordinate); // réinitialise la position de la vaus

    // récupère les briques du niveau
    bricks_ = levels[current_level]->getBricks();
    goldBricks_ = levels[current_level]->getGoldBricks(); 

    score_ = 0; // réinitialise le score à 0
    life_ = 3; // réinitialise le nombre de vie à 3

    vaus_.setTypePowerUp(TypePowerUp::None); // réinitialise le pouvoir de la vaus
    powerUp_.setLasers({}); // réinitialise les lasers
    vectorPowers_ = {};
}

void Game::changeLevel(unsigned long level) {
    balls_ = {balls_[0]}; // réinitialise les balles
    if (level < levels.size()) { // verifie si le niveau est valide
        current_level = level; // met à jour le niveau actuel
    } else {
        current_level = 0;
    }
}

void Game::mouseUpdate(float mouseX) {
    Coordinate vausCenter = vaus_.getCenter();
    Coordinate newVausCenter{mouseX, vausCenter.y}; // nouvelle position de la vaus grâce à la souris
    if (mouseX - vaus_.getLenght()/2 > LEFT_WALL && mouseX + vaus_.getLenght()/2 < windowWidth) { // verifie si la vaus ne dépasse pas les murs
        vaus_.setCenter(newVausCenter); 
    }
}

void Game::keyboardUpdate(string side) { 
    float boundaryCheck;
    Speed vausSpeed = vaus_.getSpeed();
    Coordinate vausCenter = vaus_.getCenter();
    int vausLenght = vaus_.getLenght();
    if (side == "left") { // si la touche A/Q est appuyée
        boundaryCheck = (vausCenter.x - vausSpeed.x - vausLenght/2); // verifie si la vaus ne dépasse pas les murs
        if (boundaryCheck > 0) {
            vausCenter.x -= vausSpeed.x;
        }
    }
    else if (side == "right") { // si la touche D/P est appuyée
        boundaryCheck = (vausCenter.x + vausSpeed.x + vausLenght/2); // verifie si la vaus ne dépasse pas les murs
        if (boundaryCheck < windowWidth) {
            vausCenter.x += vausSpeed.x;
        }
    }
    vaus_.setCenter(vausCenter);
}

void Game::resetHighScore() {
    highScore_ = 0;
    includeHighScore(highScore_);
}

void Game::endGameLogic(bool& levelIsChange) {
    // Met à jour le meilleur score si nécessaire
    if (score_ > highScore_) {
        setHighScore(score_);
        includeHighScore(score_);
    // Passe au niveau suivant si le joueur a gagné
    } if (isWin() && !levelIsChange) {
        changeLevel(current_level + 1);
        levelIsChange = true;
    } 
}