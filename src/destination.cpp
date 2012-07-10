#include "meh"
#include "destination.h"
#include "space.h"
#include "client.h"
#include "entity.h"
#include "game.h"
#include "player.h"
#include "platform.h"
#include "defines.h"

using namespace meh;

Destination::Destination(Game& g, Vector2d<float> pos) :
    Entity(g, Rect<float>(pos.x(),pos.y(),64,64)) {
    s = g.creaturesView()->addSprite(pos, box.size(), "bonzommes", Rect<float>(0,64,32,32));
    
    // Animation
    const unsigned int duration[] = { 1000, 50,50,50 };
    Rect<float> texCoords[] = { Rect<float>(0,65,32,31), Rect<float>(32,65,32,31), Rect<float>(64,65,32,31), Rect<float>(32,65,32,31) };
    s->addAnimation("bounce", 4, duration, texCoords);
    s->setAnimation("bounce");
    s->startAnimation();    
}

Destination::~Destination() {
}

void Destination::tick() {
    if (g.customerLoaded()) {
        g.hideArrows();
        if (position().x() < g.player()->rect().x()) {
            g.displayArrow(LEFT);
        } else {
            g.displayArrow(RIGHT);
        }
        if (position().y() < g.player()->rect().y()) {
            g.displayArrow(UP);
        } else {
            g.displayArrow(DOWN);
        }

        // should be done in Game::dropCustomer() ...
        if (g.player()->rect().intersects(rect())) {
            g.addPoints(100);
            s->hide();
            g.space()->client()->sprite()->show();
            g.dropCustomer();
            g.player()->incDamage(-5);
            g.newClient();
            g.dring();
        }
    }
}

