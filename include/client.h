#ifndef LD23_CLIENT_H
#define LD23_CLIENT_H

#include "meh"
#include "entity.h"
#include "platform.h"
#include "defines.h"

using namespace meh;

class Client : public Entity {
    private:
        Platform* pltform; 
        Platform* dst;

        int walkingDirection;

    protected:
    public:
        Client(Game& g, Vector2d<float> pos);
        ~Client();

        void tick();

        void setPlatform(Platform* platform);
        void setDestination(Platform* dest);

        Platform* platform() { return pltform; }
        Platform* destination() { return dst; }
};

#endif // LD23_CLIENT_H
