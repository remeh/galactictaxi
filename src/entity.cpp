#include "entity.h"
#include "game.h"

Entity::Entity(Game& g, Rect<float> box) :
    g(g),
    box(box) {
}

Entity::~Entity() {
}

