#include "controller.hpp"
#include "../model/game.hpp"
#include "../model/common.hpp"

#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

#include <vector>
#include <string>
#include <memory>

using namespace std;

Controller::Controller(bool isMouse, shared_ptr<Game> game)
    : isMouse_{isMouse}, game_{game} {}

void Controller::getInput(int key) {
    level = chooseLevel(key); // Détermine si une touche correspond à un changement de niveau
    if (level != -1) {
        game_->changeLevel(level);
        game_->reset(); 
    }

    // Réinitialisation en cas de victoire ou défaite
    if (isLoose || isWin) {
        isLoose = false; isWin = false;
        game_->reset(); // Réinitialise l'état du jeu
        levelIsChange = false; // qd isWin = true
    }

    // Gère les actions en fonction des touches
    switch (key) {
        case ALLEGRO_KEY_SPACE:
            game_->spaceTouch(); // permet l'utilisation des pouvoirs laser et attrapé
            break;
        case ALLEGRO_KEY_S:
            isMouse_ = !isMouse_;
            break;
        case ALLEGRO_KEY_R:
            game_->resetHighScore();
        default: {}
    }
}

void Controller::update() {
    isWin = game_->isWin();
    isLoose = game_->isLoose();
    if (!isWin && !isLoose) {
        game_->update(); // Met à jour l'état du jeu si la partie est en cours
    } else if (isWin || isLoose) {
        game_->endGameLogic(levelIsChange); // Gère la fin de partie
    }
}

void Controller::mouseUpdate() {
    al_get_mouse_state(&mouseState); // Récupère l'état actuel de la souris
    float mouseX = static_cast<float>(mouseState.x); // Position X de la souris
    game_->mouseUpdate(mouseX); // Passe la position au jeu pour mise à jour
}

void Controller::keyboardUpdate(int key) {
    switch (key) {
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_Q: // Déplacement à gauche
            game_->keyboardUpdate("left");
            break;
        case ALLEGRO_KEY_D:
        case ALLEGRO_KEY_P: // Déplacement à droite
            game_->keyboardUpdate("right");
            break;
        default: {}
    }
}
