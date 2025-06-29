#pragma once

#include "../model/game.hpp"

#include <memory>

class Controller {
    protected:
        bool isMouse_;
        int level = -1;
        shared_ptr<Game> game_;
        bool levelIsChange = false;
        bool isLoose = false, isWin = false;
    public:
        /**
         * @brief constructeur
         * @param isMouse Indique si la souris est utilisée comme méthode de contrôle
         * @param game Utilise une instance de game
         */
        Controller(bool isMouse, shared_ptr<Game> game);
        ~Controller() = default;

        // Définit si la souris est utilisée
        inline void setIsMouse(bool isMouse) { isMouse_ = isMouse; }

        // Vérifie si la souris est utilisée
        inline bool getIsMouse() { return isMouse_; }

        // Mise à jour liée à la souris
        void mouseUpdate();

        // Mise à jour liée au clavier avec une touche donnée
        void keyboardUpdate(int key);

        bool getIsLoose() { return isLoose; }
        bool getIsWin() { return isWin; }

        // Gère les entrées clavier pour effectuer des actions
        void getInput(int key);

        // Mise à jour principale du contrôleur (appelée chaque frame)
        void update();
};
