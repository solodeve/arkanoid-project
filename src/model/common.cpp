#include "common.hpp"
#include "vaus.hpp"
#include "laser.hpp"
#include "brick.hpp"

#include <allegro5/color.h>
#include <allegro5/drawing.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>


using namespace std;

void must_init(bool test, const char* description) {
  if (test) return;

  cerr << "couldn't initialize" << description << '\n';
  exit(1);
}

int chooseLevel(int keyCode) {
  int level = -1;
  switch (keyCode) {
    case ALLEGRO_KEY_1:
      level = 0;
      break;
    case ALLEGRO_KEY_2:
      level = 1;
      break;
    case ALLEGRO_KEY_3:
      level = 2;
      break;
    case ALLEGRO_KEY_4:
      level = 3;
      break;
    case ALLEGRO_KEY_5:
      level = 4;
      break;
    case ALLEGRO_KEY_6:
      level = 5;
      break;
    case ALLEGRO_KEY_7:
      level = 6;
      break;
    case ALLEGRO_KEY_8:
      level = 7;
      break;
    case ALLEGRO_KEY_9:
      level = 8;
      break;
    default: {}
  }
  return level;
}

bool inVaus(Vaus vaus, Coordinate toTouch, int width, int height) {
    int vausLenght = vaus.getLenght(), vausHeight = vaus.getHeight();
    Coordinate vausCenter = vaus.getCenter();
    if (toTouch.x + width/2 >= vausCenter.x - vausLenght/2 &&
    toTouch.x - width/2 <= vausCenter.x + vausLenght/2 &&
    toTouch.y - height/2 <= vausCenter.y + vausHeight/2 &&
    toTouch.y + height/2 >= vausCenter.y - vausHeight/2) { 
      return true; 
    }
    return false;
}

bool inBrick(Laser laser, Brick brick) {
  int heightLaser = laser.height;
  int widthLaser = laser.width;
  Coordinate brickCenter = brick.coordinate;
  Coordinate laserCenter = laser.center;
  if (laserCenter.x + widthLaser/2 >= brickCenter.x - widthBrick/2 &&
  laserCenter.x - widthLaser/2 <= brickCenter.x + widthBrick/2 &&
  laserCenter.y - heightLaser/2 <= brickCenter.y + heightBrick/2 &&
  laserCenter.y + heightLaser/2 >= brickCenter.y - heightBrick/2) {
    return true;
  }
  return false;
}
