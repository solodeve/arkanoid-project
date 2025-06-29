#include "varaibles_globales.hpp"
#include <allegro5/color.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_font.h>

const int     FONT_SIZE = 20;
ALLEGRO_FONT *font;

ALLEGRO_MOUSE_STATE mouseState;

const float BALL_SPEED_X = 7;
const float BALL_SPEED_Y = -7;

const float LASER_SPEED_X = 8;
const float LASER_SPEED_Y = -8;

const float BALL_CENTER_X = 500;
const float BALL_CENTER_Y = 780;

const float VAUS_CENTER_X = 500;
const float VAUS_CENTER_Y = 800;

const float VAUS_SPEED_X = 10;
const float VAUS_SPEED_Y = 0;

const float POWER_UP_CENTER_X = 0;
const float POWER_UP_CENTER_Y = 0;

const float POWER_UP_SPEED_X = 0;
const float POWER_UP_SPEED_Y = 5;

const float POWER_UP_BRICK_CENTER_X = 0;
const float POWER_UP_BRICK_CENTER_Y = 0;

const float LETTRE_CENTER_X = 0;
const float LETTRE_CENTER_Y = 0;

const float SCORE_CENTER_X = 500;
const float SCORE_CENTER_Y = 550;

const float WIN_LOOSE_CENTER_X = 500;
const float WIN_LOOSE_CENTER_Y = 500;

const float LIFE_CENTER_X = 500;
const float LIFE_CENTER_Y = 500;

const float NEW_HIGHSCORE_CENTER_X = 500;
const float NEW_HIGHSCORE_CENTER_Y = 600;

const float COORDINATE_OUTSIDE_POWER_X = -50;
const float COORDINATE_OUTSIDE_POWER_Y = -50;

const int EXTEND_VAUS_SIZE = 300;

const int    windowWidth      = 1000;
const int    windowHeight     = 1000;
const double refreshPerSecond = 60;

const float LEFT_WALL = 0;
const float UP_WALL = 0;

const unsigned long NO_BRICKS_LEFT = 0;

const int widthBrick = 69; 
const int heightBrick = 48; 

const int widthPowerUp = 20;
const int heightPowerUp = 20;

const ALLEGRO_COLOR COLOR_RED     = al_map_rgb(255, 0, 0);
const ALLEGRO_COLOR COLOR_GREY    = al_map_rgb(200, 200, 200);
const ALLEGRO_COLOR COLOR_GREEN   = al_map_rgb(0, 255, 0);
const ALLEGRO_COLOR COLOR_YELLOW  = al_map_rgb(255, 255, 0);
const ALLEGRO_COLOR COLOR_BLACK   = al_map_rgb(0, 0, 0);
const ALLEGRO_COLOR COLOR_WHITE   = al_map_rgb(255, 255, 255);
const ALLEGRO_COLOR COLOR_MAGENTA = al_map_rgb(255, 0, 255);
const ALLEGRO_COLOR COLOR_ORANGE  = al_map_rgb(255,165,0);
const ALLEGRO_COLOR COLOR_CYAN    = al_map_rgb(0,255,255);
const ALLEGRO_COLOR COLOR_BLUE    = al_map_rgb(0,0,255);
const ALLEGRO_COLOR COLOR_GOLD    = al_map_rgb(255,215,0);