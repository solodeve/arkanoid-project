#include "allegro_draw.hpp"

#include <allegro5/color.h>
#include <allegro5/drawing.h>
#include <allegro5/allegro_primitives.h>

void RectDraw(float x, float y, float x2, float y2, ALLEGRO_COLOR color, ALLEGRO_COLOR frameColor) {
    float thickness = 1;
  al_draw_filled_rectangle(x, y, x2, y2, color);
  al_draw_rectangle(x, y, x2, y2, frameColor, thickness);
}

void CircleDraw(float x, float y, int r, ALLEGRO_COLOR fillColor) {
    al_draw_filled_circle(x, y, r, fillColor);
    al_draw_circle(x, y, r, fillColor, 1);
}