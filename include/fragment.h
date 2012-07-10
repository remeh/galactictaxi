#ifndef LD23_FRAGMENT_H
#define LD23_FRAGMENT_H

#include "meh"
#include "entity.h"

class Fragment : public Entity {
    private:
        int dir;
        double speed;
        bool alive;
        float rot;

    protected:
    public:
        Fragment(Game& g, Vector2d<float> pos);

        void tick();
        
        bool dead() { return !alive; }
};

#endif // LD23_FRAGMENT_H
