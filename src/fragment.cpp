#include "meh"
#include "fragment.h"
#include "game.h"
#include "player.h"
#include "defines.h"

using namespace meh;

Fragment::Fragment(Game& g, Vector2d<float> pos) :
    Entity(g,Rect<float>(pos.x(),pos.y(),32,32)) {
    int a = System::rnd(3);
    int b = System::rnd(3);
    dir = 0;
    switch (a) {
        case 0:
            dir |= DOWN;
            break;
        case 1:
            dir |= UP;
            break;
        default:
            break;
    }
    switch (b) {
        case 0:
            dir |= LEFT;
            break;
        case 1:
            dir |= RIGHT;
            break;
        default:
            break;
    }
    if (dir == 0) {
        dir = LEFT | DOWN;
    }
    if (dir & DOWN) {
        pos.setY(-500 + System::rnd(400));
    } else if (dir & UP) {
        pos.setY(SPACE_HEIGHT+500 - System::rnd(400));
    }
    if (dir & LEFT) {
        pos.setX(SPACE_WIDTH+500 - System::rnd(400));
    } else if (dir & RIGHT) {
        pos.setX(-500 + System::rnd(400));
    }

    position() = pos;

    s = g.creaturesView()->addSprite(pos, rect().size(), "bonzommes", Rect<float>(0,96,32,32)); 
    speed = 1.0;
    speed += System::rnd(10)/10.0;

    alive = true;
}

void Fragment::tick() {
    if (dir & LEFT) {
        position().setX(position().x()-speed);
    } else if (dir & RIGHT) {
        position().setX(position().x()+speed);
    }
    if (dir & UP) {
        position().setY(position().y()-speed);
    } else if (dir & DOWN) {
        position().setY(position().y()+speed);
    }
    if (position().x() < -1000 || position().x() > SPACE_WIDTH+1000 || position().y() < -1000 || position().y() > SPACE_HEIGHT+1000) {
        alive = false;
    }
    if ((rot += 0.03)> 360) {
        rot = 0;
    }

    if (rect().intersects(g.player()->rect())) {
        sprite()->setTintColor(Game::orange);
        g.hurtPlayer();
        g.fragmentExplosion(position());
        alive = false;
        sprite()->hide();
    } else {
        sprite()->setTintColor(Game::white);
    }
}
