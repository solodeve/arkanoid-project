#include "level.hpp"
#include "brick.hpp"
#include "struct.hpp"
#include "common.hpp"

#include <vector>
#include <string>
#include <allegro5/color.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Brick> Level::getBricks() { return bricks_; }
vector<Brick> Level::getGoldBricks() { return goldBricks_; }

ALLEGRO_COLOR Level::convertToAllegroColor(string color) {
    // initialisation des couleurs
    ALLEGRO_COLOR red     = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR grey    = al_map_rgb(200, 200, 200);
    ALLEGRO_COLOR green   = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR yellow  = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR white   = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR magenta = al_map_rgb(255, 0, 255);
    ALLEGRO_COLOR orange  = al_map_rgb(255,165,0);
    ALLEGRO_COLOR cyan    = al_map_rgb(0,255,255);
    ALLEGRO_COLOR blue    = al_map_rgb(0,0,255);
    ALLEGRO_COLOR gold    = al_map_rgb(255,215,0);

    // retourne la couleur correspondante
    if (color == "COLOR_RED") return red;
    if (color == "COLOR_GREY") return grey;
    else if (color == "COLOR_GREEN") return green;
    else if (color == "COLOR_YELLOW") return yellow;
    else if (color == "COLOR_WHITE") return white;
    else if (color == "COLOR_MAGENTA") return magenta;
    else if (color == "COLOR_ORANGE") return orange;
    else if (color == "COLOR_CYAN") return cyan;
    else if (color == "COLOR_BLUE") return blue;
    return gold; // retourn la couleur gold
}

int Level::convertWorthToInt(string color) {
    // initialisation des valeurs
    int red_worth     = 90;
    int grey_worth    = 200;
    int green_worth   = 80;
    int yellow_worth  = 120;
    int white_worth   = 50;
    int magenta_worth = 110;
    int orange_worth  = 60;
    int cyan_worth    = 70;
    int blue_worth    = 100;

    // retourne la valeur correspondante
    if (color == "COLOR_RED") return red_worth;
    if (color == "COLOR_GREY") return grey_worth;
    else if (color == "COLOR_GREEN") return green_worth;
    else if (color == "COLOR_YELLOW") return yellow_worth;
    else if (color == "COLOR_WHITE") return white_worth;
    else if (color == "COLOR_MAGENTA") return magenta_worth;
    else if (color == "COLOR_ORANGE") return orange_worth;
    else if (color == "COLOR_CYAN") return cyan_worth;
    return blue_worth; // retourn la valeur de la couleur blue
}

TypePowerUp Level::convertToTypePower(string power) {
    TypePowerUp none = TypePowerUp::None;

    // retourne le type de power correspondant
    if (power == "laser") return TypePowerUp::laser;
    else if (power == "expend") return TypePowerUp::expend;
    else if (power == "ballCatch") return TypePowerUp::ballCatch;
    else if (power == "slowDown") return TypePowerUp::slowDown;
    else if (power == "interruption") return TypePowerUp::interruption;
    else if (power == "player") return TypePowerUp::player;
    return none; // retourne le type de pouvoir none 
}

void Level::readFileForBricks(string levelFile) { 
    string line, character; 
    int x, y, life, worth;
    TypePowerUp power;
    Coordinate brickCoordinate;
    ALLEGRO_COLOR color;
    vector<string> lineData;
    string str_color, str_x, str_y, str_power;

    char del = ',';

    ifstream file(levelFile);
    if (!file) { // verifie si le fichier est ouvert
        cerr << "Error reading from the level file!" << endl;
        exit(1);
    } else {
        while (getline(file, line)) { // lit chaque ligne du fichier
            stringstream ss(line);
            while (getline(ss, character, del)) { // lit chaque caractère de la ligne
                lineData.push_back(character);
            }

            str_x = lineData[0];
            str_y = lineData[1];
            str_color = lineData[2];
            str_power = lineData[3];
                
            x = stoi(str_x);
            y = stoi(str_y);
            brickCoordinate = Coordinate(x, y);
            color = convertToAllegroColor(str_color);
            power = convertToTypePower(str_power);

            if (str_color != "COLOR_GOLD") worth = convertWorthToInt(str_color);
            else worth = -1;

            if ("COLOR_GREY" == str_color) life = 2;
            else if ("COLOR_GREY" == str_color) life = -1;
            else life = 1;

            Brick brick{color, worth, power, brickCoordinate, life};

            if (str_color != "COLOR_GOLD") bricks_.push_back(brick);
            else goldBricks_.push_back(brick);

            lineData = {};
        }
    file.close();
    }
}