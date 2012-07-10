#ifndef LD23_PLAYER_H
#define LD23_PLAYER_H

#include "meh"
#include "entity.h"

using namespace meh;

class Game;

class Player : public Entity {
    private:
        /** direction */
        int dir;
        /** speed */
        float spdX;
        float spdY;
        /** accel */
        float accel;

        /** damage */
        int dmage;

    protected:
        void particles();

    public:
        Player(Game& g);
        ~Player();

        void tick();

        void up();
        void down();
        void left();
        void right();

        void setDirection(int dir);
        int direction() { return dir; }

        float speedX() { return spdX; }
        float speedY() { return spdY; }

        void setSpeed(Vector2d<float> p) { spdX = p.x(); spdY = p.y(); }

        void bounce();

        void checkMaxSpeed();

        int damage() { return dmage; }
        void setDamage(int i) { dmage = i; }
        void incDamage(int i);
};

#endif // LD23_PLAYER_H
