#pragma once

#include "vaus.hpp"
#include "laser.hpp"
#include "brick.hpp"

#include <allegro5/color.h>
#include <allegro5/drawing.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>


using namespace std;

// Initialise la librearie Allegro
void must_init(bool test, const char* description);

// Permet de choisir un niveau
int chooseLevel(int keyCode);

// Vérifie si un point est dans le rectangle de la vaus
bool inVaus(Vaus vaus, Coordinate toTouch, int width, int height);

// Vérifie si un point est dans le rectangle d'une brique
bool inBrick(Laser laser, Brick brick);