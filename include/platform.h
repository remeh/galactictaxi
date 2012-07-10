#ifndef LD23_PLATFORM_H
#define LD23_PLATFORM_H

#include "meh"
#include "entity.h"

using namespace meh;

class Game;

class Platform : public Entity{
    private:
    protected:
    public:
        Platform(Game& g, Vector2d<float> pos);
        ~Platform();
};

#endif // LD23_PLATFORM_H
