#include <cmath>
#include <cmath>
#include "player.h"
#include "entity.h"
#include "game.h"
#include "defines.h"

Player::Player(Game& g):
    Entity(g,Rect<float>(128,196,64,32)),
    dir(0),
    dmage(0) {
    setPosition(128,196);
        
    spdX = 0.0f;
    spdY = 0.0f;

    // Sprite
    s = g.creaturesView()->addSprite(Vector2d<float>(298,208), box.size(), "bonzommes", Rect<float>(0,32,64,32));

    // Animation
    const unsigned int duration[] = { 1000 };
    Rect<float> texCoords[] = { Rect<float>(0,32,64,32) };
    s->addAnimation("flyleft", 1, duration, texCoords);
    texCoords[0] = Rect<float>(128,32,64,32);
    s->addAnimation("flyright", 1, duration, texCoords);
    s->setAnimation("flyleft");
    s->startAnimation();
}

Player::~Player() {

}

void Player::tick() {
    double ttl = 100;
    double ang = 0;
    double velocity = 1.0;
    Vector2d<float> particulePos(0,0);

    if (dir & LEFT) {
            particulePos.setXY(s->position().x()+56, s->position().y()+11+System::rnd(2));
            ttl = 180 + System::rnd(50);
            ang = 0;
            velocity = 1.4 + System::rnd(1000)/1000.0;
            g.creaturesView()->particlesManager().addParticle(particulePos,ttl,ang,velocity,0.01, Game::orange);
    }
    if (dir & RIGHT) {
            particulePos.setXY(s->position().x()-5, s->position().y()+10+System::rnd(2));
            ttl = 180 + System::rnd(50);
            ang = 180;
            velocity = 1.4 + System::rnd(1000)/1000.0;
            g.creaturesView()->particlesManager().addParticle(particulePos,ttl,ang,velocity,0.01, Game::orange);
    }
    if (!(dir & DOWN)) {
        for (int i = 0; i < 3; i++) {
            particulePos.setXY(s->position().x()+2+System::rnd(43), s->position().y()+20);
            ttl = (dir == UP ? 100 : 0) + 100 + System::rnd(50);
            ang = 90;
            velocity = 1.0 + System::rnd(1000)/1000.0;
            g.creaturesView()->particlesManager().addParticle(particulePos,ttl,ang,velocity,0.01, Game::orange);
        }
    }

    setPosition(position().x()+spdX,position().y()+spdY);
    rect().set(position().x(),position().y(), rect().size().x(), rect().size().y());

    s->tick();
}

void Player::setDirection(int dir) {
    this->dir = dir;
}

void Player::left() {
    spdX -= 0.1f;
    s->setAnimation("flyleft");
    checkMaxSpeed();
}

void Player::right() {
    spdX += 0.1f;
    s->setAnimation("flyright");
    checkMaxSpeed();
}

void Player::down() {
    spdY += 0.1f;
    checkMaxSpeed();
}

void Player::up() {
    spdY -= 0.1f;
    checkMaxSpeed();
}

void Player::checkMaxSpeed() {
    if (spdX > PLAYER_MAX_SPEED) {
        spdX = PLAYER_MAX_SPEED;
    }
    if (spdX < -PLAYER_MAX_SPEED) {
        spdX = -PLAYER_MAX_SPEED;
    }
    if (spdY > PLAYER_MAX_SPEED) {
        spdY = PLAYER_MAX_SPEED;
    }
    if (spdY < -PLAYER_MAX_SPEED) {
        spdY = -PLAYER_MAX_SPEED;
    }
}

void Player::bounce() {
    float o = 0.0f;
    float oy = 0.0f;
    if (spdX > 0.0f) {
        o = -0.1f;
    } else {
        o = 0.1f;
    }
    if (spdY > 0.0f) {
        oy = -0.1f;
    } else {
        oy = 0.1f;
    }
    spdX = -spdX + o;
    spdY = -spdY + oy;
    g.hurtPlayer();
}

void Player::incDamage(int i) {
    dmage += i;
    if (dmage < 0) {
        dmage = 0;
    }
}

