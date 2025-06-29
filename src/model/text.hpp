#pragma once

#include <string>
#include "struct.hpp"
#include <allegro5/color.h>
#include "../varaibles_globales.hpp"
#include <allegro5/allegro_font.h>

using namespace std;

class Text {
  string        s_;
  Coordinate         center_;
  ALLEGRO_COLOR color_;

 public:
  // Constructor
  Text(string text, Coordinate center, ALLEGRO_COLOR color = COLOR_WHITE)
      : s_{text}, center_{center}, color_{color} {}
  ~Text() = default;

  // Draw
  void draw();

  // Setters and getters
  inline string getString() { return s_; }
  inline void   setString(const string &newString) { s_ = newString; }
  inline Coordinate  getCenter() { return center_; }
  inline void   setCenter(Coordinate newCenter) { center_ = newCenter; }
};