#include "star.h"
#include "game.h"

Star::Star(Game& g, Vector2d<float> position) :
    Entity(g,Rect<float>(position.x(),position.y(), 4+System::rnd(16), 4+System::rnd(16))) {
    s = g.backgroundView()->addSprite(position, box.size(), "world", Rect<float>(0,0,16,16));
    if (System::rnd(2)) {
        Color tint(255-System::rnd(40),255-System::rnd(40),0);
        s->setTintColor(tint);
    }
}

Star::~Star() {

}

