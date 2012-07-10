#include "platform.h"
#include "game.h"

Platform::Platform(Game& g, Vector2d<float> pos) :
    Entity(g,Rect<float>(pos.x(),pos.y(),160,64)) {
    // TODO randomize platform texcoord
    s = g.platformsView()->addSprite(pos, box.size(), "world", Rect<float>(96,0,160,64)); 
}

Platform::~Platform() {

}

