#ifndef LD23_BUILDING_H
#define LD23_BUILDING_H

#include "meh"
#include "entity.h"

using namespace meh;

class Building : public Entity {
    private:
    protected:
    public:
        Building(Game& g, Vector2d<float> pos);
        ~Building();

};

#endif // LD23_BUILDING_H
