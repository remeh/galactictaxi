#ifndef LD23_ENTITY_H
#define LD23_ENTITY_H

#include "meh"

using namespace meh;

class Game;

class Entity {
    private:
    protected:
        Game& g;
        Rect<float> box;
        Sprite* s;

    public:
        Entity(Game &g, Rect<float> box);
        ~Entity();

        Vector2d<float>& position() { return box.position(); }
        void setPosition(float x, float y) { box.position().setXY(x,y); }
        
        Game& game() { return g; }
        
        Sprite* sprite() { return s; }

        Rect<float>& rect() { return box; }
};

#endif // LD23_ENTITY_H
