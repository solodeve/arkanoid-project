#include "vaus.hpp"
#include "struct.hpp"
#include <allegro5/color.h>
#include "../varaibles_globales.hpp"

#include <string>
#include <iostream>

using namespace std;

Vaus::Vaus(Coordinate center, int lenght, int height, Speed speed, TypePower power, ALLEGRO_COLOR color): 
    lenght_{lenght}, height_{height}, center_{center}, power_{power}, color_{color}, speed_{speed} {
        baseLenght = lenght;
    }

void Vaus::setCenter(Coordinate newPosition) { center_ = newPosition; }
Coordinate Vaus::getCenter() { return center_; }

int Vaus::getLenght() { return lenght_; }
void Vaus::setLenght(int lenght) { lenght_ = lenght; }

int Vaus::getHeight() { return height_; }
void Vaus::setheight(int height) { height_ = height; }