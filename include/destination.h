#ifndef LD23_DESTINATION_H_
#define LD23_DESTINATION_H

#include "meh"
#include "entity.h"
#include "defines.h"

using namespace meh;

class Platform;
class Game;

class Destination : public Entity {
    private:
        Platform* pltform; 

    protected:
    public:
        Destination(Game& g, Vector2d<float> pos);
        ~Destination();

        void tick();

        void setPlatform(Platform* platform);
};

#endif // LD23_DESTINATION_H
