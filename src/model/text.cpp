#include <string>
#include "struct.hpp"
#include <allegro5/color.h>
#include "text.hpp"
#include "../varaibles_globales.hpp"

using namespace std;

void Text::draw() {
  auto verticalCenterAdjustment =
      static_cast<float>(al_get_font_line_height(font) / 2.0);
  al_draw_text(font, color_, center_.x, center_.y - verticalCenterAdjustment,
               ALLEGRO_ALIGN_CENTRE, s_.c_str());
}