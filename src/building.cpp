#include "building.h"
#include "game.h"

Building::Building(Game& g, Vector2d<float> pos) :
    Entity(g,Rect<float>(pos.x(),pos.y(),64,64)) {
    Rect<float> r(0,32,32,32);
    switch (System::rnd(4)) {
        case 1:
            r = Rect<float>(32,32,32,32);
            break;
        case 2:
            r = Rect<float>(32,65,32,31);
            break;
        case 3:
            r = Rect<float>(0,65,32,31);
            break;
        case 0:
        default:
            break;
    }
    s = g.platformsView()->addSprite(pos, box.size(), "world", r); 
}

Building::~Building() {
}
