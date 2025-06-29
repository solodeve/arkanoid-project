#pragma once

#include "brick.hpp"
#include "../varaibles_globales.hpp"

#include <vector>
#include <string>

using namespace std;

class Level {
    protected:
        vector<Brick> bricks_;
        vector<Brick> goldBricks_;

        // convertit une couleur en ALLEGRO_COLOR
        ALLEGRO_COLOR convertToAllegroColor(string color);

        // convertit un type de power en TypePowerUp
        TypePowerUp convertToTypePower(string power);

        // convertit une valeur en int
        int convertWorthToInt(string color);

    public:
        Level() {}
        ~Level() = default;

        vector<Brick> getBricks();
        vector<Brick> getGoldBricks();

        // lit le fichier de niveau et crée les briques
        void readFileForBricks(string levelFile);
};

class Level1: public Level {
    public:
        Level1() {
            string level1File = "level/level1.txt";
            readFileForBricks(level1File);
        }
        ~Level1() = default;
};

class Level2: public Level {
    public:
        Level2() {
            string level1File = "level/level2.txt";
            readFileForBricks(level1File);
        }   
        ~Level2() = default;
};

class Level3: public Level {
    public:
        Level3() {
            string level1File = "level/level3.txt";
            readFileForBricks(level1File);
        }
        ~Level3() = default;
};

class Level4: public Level {
    public:
        Level4() {
            string level1File = "level/level4.txt";
            readFileForBricks(level1File);
        }
        ~Level4() = default;
};

class Level5: public Level {
    public:
        Level5() {
            string level1File = "level/level5.txt";
            readFileForBricks(level1File);
        }
        ~Level5() = default;
};

class Level6: public Level {
    public:
        Level6() {
            string level1File = "level/level6.txt";
            readFileForBricks(level1File);
        }
        ~Level6() = default;
};

class Level7: public Level {
    public:
        Level7() {
            string level1File = "level/level7.txt";
            readFileForBricks(level1File);
        }
        ~Level7() = default;
};

class Level8: public Level {
    public:
        Level8() {
            string level1File = "level/level8.txt";
            readFileForBricks(level1File);
        }
        ~Level8() = default;
};

class Level9: public Level {
    public:
        Level9() {
            string level1File = "level/level9.txt";
            readFileForBricks(level1File);
        }
        ~Level9() = default;
};