#ifndef LD23_STAR_H
#define LD23_STAR_H

#include "meh"
#include "entity.h"

using namespace meh;

class Game;

class Star : public Entity {
    private:
    protected:
    public:
        Star(Game& g, Vector2d<float> position);
        ~Star();
};

#endif // LD23_STAR_H
