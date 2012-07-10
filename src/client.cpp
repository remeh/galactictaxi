#include <cmath>
#include "meh"
#include "client.h"
#include "entity.h"
#include "game.h"
#include "player.h"
#include "platform.h"
#include "defines.h"

using namespace meh;

Client::Client(Game& g, Vector2d<float> pos) :
    Entity(g, Rect<float>(pos.x(),pos.y(),32,32)),
    walkingDirection(RIGHT) {
    // TODO randomize model
   
    int model = System::rnd(3);
    // Animation
    if (model == 0) {
        s = g.creaturesView()->addSprite(pos, box.size(), "bonzommes", Rect<float>(0,0,32,32));
        const unsigned int duration[] = { 250, 250 };
        Rect<float> texCoords[] = { Rect<float>(32,0,32,32), Rect<float>(64,0,32,32) };
        s->addAnimation("right", 2, duration, texCoords);
        texCoords[0] = Rect<float>(96,0,32,32);
        texCoords[1] = Rect<float>(128,0,32,32);
        s->addAnimation("left", 2, duration, texCoords);
        s->setAnimation("left");
        s->startAnimation();    
    } else if (model == 1) {
        s = g.creaturesView()->addSprite(pos, box.size(), "bonzommes", Rect<float>(0,129,32,32));
        const unsigned int duration[] = { 250, 250 };
        Rect<float> texCoords[] = { Rect<float>(32,129,32,32), Rect<float>(64,129,32,32) };
        s->addAnimation("right", 2, duration, texCoords);
        texCoords[0] = Rect<float>(96,129,32,32);
        texCoords[1] = Rect<float>(128,129,32,32);
        s->addAnimation("left", 2, duration, texCoords);
        s->setAnimation("left");
        s->startAnimation();    
    } else {
        s = g.creaturesView()->addSprite(pos, box.size(), "bonzommes", Rect<float>(0,161,32,32));
        const unsigned int duration[] = { 250, 250 };
        Rect<float> texCoords[] = { Rect<float>(32,161,32,32), Rect<float>(64,161,32,32) };
        s->addAnimation("right", 2, duration, texCoords);
        texCoords[0] = Rect<float>(96,161,32,32);
        texCoords[1] = Rect<float>(128,161,32,32);
        s->addAnimation("left", 2, duration, texCoords);
        s->setAnimation("left");
        s->startAnimation();    
    }
}

Client::~Client() {

}

void Client::setPlatform(Platform* platform) {
    pltform = platform;
}

void Client::setDestination(Platform* destination) {
    dst = destination;
}

void Client::tick() {
    if (!System::rnd(100)) {
        walkingDirection = System::rnd(1) ? LEFT : RIGHT;
        switch (walkingDirection) {
            case LEFT:
                s->setAnimation("left");
                break;
            case RIGHT:
                s->setAnimation("right");
                break;
        }
    }
    switch (walkingDirection) {
        case LEFT:
            if (position().x()-CLIENT_SPEED >= pltform->position().x()) {
                position().setX(position().x()-CLIENT_SPEED); 
            } else {
                walkingDirection = RIGHT;
                s->setAnimation("right");
            }
            break;
        case RIGHT:
        default:
            if (position().x()+CLIENT_SPEED <= pltform->position().x()+pltform->rect().size().x()-32) {
                position().setX(position().x()+CLIENT_SPEED); 
            } else {
                walkingDirection = LEFT;
                s->setAnimation("left");
            }
            break;
    }

    if (!g.customerLoaded()) {
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

        if (g.player()->rect().intersects(rect())) {
            if (abs(g.player()->speedX()) < 1.5f && abs(g.player()->speedY()) < 1.5f) {
                g.loadCustomer(); 
                g.soundNewClient();
                g.newDestination();
                s->hide();
            } else {
                g.bloodExplosion(position());
                g.murderCustomer();
                g.addPoints(-150);
                g.newClient();
            }
        }
    }
}

