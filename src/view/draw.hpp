#pragma once

#include "../model/text.hpp"
#include "../model/struct.hpp"
#include "../controller/controller.hpp"
// #include "../model/common.hpp"

class Draw {
    // initialisation tous les textes utiles
    Coordinate win_loose_coordinate{WIN_LOOSE_CENTER_X, WIN_LOOSE_CENTER_Y};
    Text winText_{"You win!", win_loose_coordinate, COLOR_GREEN};
    Text looseText_{"You loose!", win_loose_coordinate, COLOR_RED};

    Coordinate scoreTxtCoordinate{SCORE_CENTER_X, SCORE_CENTER_Y};
    Coordinate lifeTxtCoordinate{LIFE_CENTER_X, LIFE_CENTER_Y};
    Coordinate newHighScoreTxtCoordinate{NEW_HIGHSCORE_CENTER_X, NEW_HIGHSCORE_CENTER_Y};

    Text finalScore_{"score: 0", scoreTxtCoordinate, COLOR_WHITE};
    Text scoreTxt_{"score: " + to_string(0), scoreTxtCoordinate, COLOR_WHITE};
    Text lifeTxt_{"life: " + to_string(3), lifeTxtCoordinate, COLOR_WHITE};
    Text newHighScoreTxt_{"New high score", newHighScoreTxtCoordinate, COLOR_ORANGE};

    Coordinate letterCenter{LETTRE_CENTER_X, LETTRE_CENTER_Y};
    Text L{"L", letterCenter, COLOR_WHITE};
    Text A{"A", letterCenter, COLOR_WHITE};
    Text At{"At", letterCenter, COLOR_WHITE};
    Text R{"R", letterCenter, COLOR_WHITE};
    Text I{"I", letterCenter, COLOR_WHITE};
    Text J{"J", letterCenter, COLOR_WHITE};

    // permet de récupérer la lettre correspondant au pouvoir
    Text getLetter(TypePowerUp power, Coordinate powerCenter, ALLEGRO_COLOR& powerUpColor); 

    public:
        Draw();
        ~Draw() = default;

        // affiche le jeu
        void draw(shared_ptr<Game> game);

        // dessine les pouvoirs
        void drawPowerUps(shared_ptr<Game> game);

        // dessine les briques
        void drawBricks(shared_ptr<Game> game);

        // dessine les balles
        void drawBalls(shared_ptr<Game> game);

        // dessine vaus
        void drawVaus(shared_ptr<Game> game);
};