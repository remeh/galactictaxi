#ifndef MEH_DRAWABLE_LINE_H
#define MEH_DRAWABLE_LINE_H

#include "core/vector2d.h"
#include "core/color.h"
#include "ui/drawable.h"

namespace meh {

class DrawableLine : public Drawable {
    private:
        Vector2d<float> s;
        Vector2d<float> e;
        Color c;
        float t;

    protected:
    public:
        /**
         * To draw a line on a view. The drawing of this line
         * is, when possible, hardware accelerated.
         *
         * @param start the starting point of this line
         * @param end the ending point of this line
         * @param color the color to use to draw this line
         * @param thickness the thickness of this point
         */
        DrawableLine(Vector2d<float> start, Vector2d<float> end, Color color, float thickness);

        void draw();
        void tick();
};

}

#endif // MEH_DRAWABLE_LINE_H
