#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <allegro5/transformations.h>


#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono> 
#include <iostream>
#include <memory>
#include <numbers>
#include <ranges>
#include <string>
#include <vector>
#include <fstream>

#include "view/draw.hpp"
#include "model/vaus.hpp"
#include "model/struct.hpp"
#include "model/game.hpp"
#include "model/brick.hpp"
#include "model/ball.hpp"
#include "controller/controller.hpp"
#include "model/common.hpp"

#include "varaibles_globales.hpp"

using namespace std;

int main(int /* argc */, char** /* argv */) {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / refreshPerSecond);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(windowWidth, windowHeight);
    must_init(disp, "display");

    must_init(al_init_ttf_addon(), "TTF addon");
    font = al_create_builtin_font();
    font = al_load_ttf_font("SourceCodePro-Regular.ttf", FONT_SIZE, 0);
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool draw = false;

    ALLEGRO_EVENT event;

    string newLifeTxt, newScoreTxt, finalScoreTxt;

    vector<Ball> balls;
    vector<Brick> bricks, silverBricks;

    Coordinate ballCenter{BALL_CENTER_X, BALL_CENTER_Y};
    int radius = 10;
    Speed ballSpeed{BALL_SPEED_X, BALL_SPEED_Y};
    Ball ball = Ball(ballCenter, radius, ballSpeed);

    balls.push_back(ball);

    Coordinate vausCenter{VAUS_CENTER_X, VAUS_CENTER_Y};
    int vausLenght = 200;
    int vausWidth = 20;
    Speed vausSpeed{VAUS_SPEED_X, VAUS_SPEED_Y};
    Vaus vaus = Vaus(vausCenter, vausLenght, vausWidth, vausSpeed);

    int highScore = 0;
    int score = 0;
    int life = 3;
    Coordinate powerUpCenter{POWER_UP_CENTER_X, POWER_UP_CENTER_Y};
    Speed powerUpSpeed{POWER_UP_SPEED_X, POWER_UP_SPEED_Y};
    PowerUp powerUp{powerUpCenter, powerUpSpeed, EXTEND_VAUS_SIZE}; 

    shared_ptr<Game> game = make_shared<Game>(vector<TypePower>(), balls, bricks, silverBricks, highScore, vaus, life, score, powerUp);

    Draw toDraw{};

    Controller controller{true, game};

    al_start_timer(timer);
    while (!done) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (controller.getIsMouse()) controller.mouseUpdate();
                controller.update();

                draw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (!controller.getIsMouse()) controller.keyboardUpdate(event.keyboard.keycode);
                controller.getInput(event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            default: {}
        }
        if (draw) {
            al_clear_to_color(COLOR_BLACK); 
            toDraw.draw(game);
            draw = false;
            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}