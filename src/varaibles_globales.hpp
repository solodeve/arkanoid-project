#pragma once

#include <allegro5/color.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_font.h>

extern ALLEGRO_FONT *font;
extern const int     FONT_SIZE;
extern ALLEGRO_MOUSE_STATE mouseState;

extern const float BALL_SPEED_X;
extern const float BALL_SPEED_Y;

extern const float BALL_CENTER_X;
extern const float BALL_CENTER_Y;

extern const float VAUS_CENTER_X;
extern const float VAUS_CENTER_Y;

extern const float VAUS_SPEED_X;
extern const float VAUS_SPEED_Y;

extern const float LASER_SPEED_X;
extern const float LASER_SPEED_Y;

extern const float POWER_UP_CENTER_X;
extern const float POWER_UP_CENTER_Y;

extern const float POWER_UP_SPEED_X;
extern const float POWER_UP_SPEED_Y;

extern const float POWER_UP_BRICK_CENTER_X;
extern const float POWER_UP_BRICK_CENTER_Y;

extern const float POWER_UP_BRICK_SPEED_X;
extern const float POWER_UP_BRICK_SPEED_Y;

extern const float SCORE_CENTER_X;
extern const float SCORE_CENTER_Y;

extern const float WIN_LOOSE_CENTER_X;
extern const float WIN_LOOSE_CENTER_Y;

extern const float LIFE_CENTER_X;
extern const float LIFE_CENTER_Y;

extern const float NEW_HIGHSCORE_CENTER_X;
extern const float NEW_HIGHSCORE_CENTER_Y;

extern const float COORDINATE_OUTSIDE_POWER_X;
extern const float COORDINATE_OUTSIDE_POWER_Y;

extern const float LETTRE_CENTER_X;
extern const float LETTRE_CENTER_Y;

extern const unsigned long NO_BRICKS_LEFT;

extern const int EXTEND_VAUS_SIZE;

extern const int    windowWidth;
extern const int    windowHeight;
extern const double refreshPerSecond;

extern const float LEFT_WALL;
extern const float UP_WALL;

extern const int widthBrick;
extern const int heightBrick;

extern const int widthPowerUp;
extern const int heightPowerUp;

extern const ALLEGRO_COLOR COLOR_RED;
extern const ALLEGRO_COLOR COLOR_GREY;
extern const ALLEGRO_COLOR COLOR_GREEN;
extern const ALLEGRO_COLOR COLOR_YELLOW;
extern const ALLEGRO_COLOR COLOR_BLACK;
extern const ALLEGRO_COLOR COLOR_WHITE;
extern const ALLEGRO_COLOR COLOR_PINK;
extern const ALLEGRO_COLOR COLOR_MAGENTA;
extern const ALLEGRO_COLOR COLOR_ORANGE;
extern const ALLEGRO_COLOR COLOR_CYAN;
extern const ALLEGRO_COLOR COLOR_BLUE;
extern const ALLEGRO_COLOR COLOR_GOLD;
