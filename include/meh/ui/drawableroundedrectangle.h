#ifndef MEH_DRAWABLE_ROUNDED_RECTANGLE_H
#define MEH_DRAWABLE_ROUNDED_RECTANGLE_H

#include "core/rect.h"
#include "core/color.h"
#include "ui/drawable.h"

namespace meh {

class DrawableRoundedRectangle : public Drawable {
    private:
        Rect<float> r;
        Color c;
        float t;
        bool f;
        float rx;
        float ry;

    protected:
    public:
        /**
         * To draw a rectangle with rounded angles on a view. The drawing of
         * this rectangle is, when possible, hardware accelerated.
         * Only the outline of the rectangle will be drawn, see
         * the constructor DrawableRoundedRectangle(Rect,Color,bool)
         * for a filled rectangle.
         *
         * @param rect the coordinates of this rectangle
         * @param color the color to use to draw the outline
         * @param rx radii on x of the round
         * @param ry radii on y of the round
         * @param thickness the thickness of the outline
         */
        DrawableRoundedRectangle(Rect<float> rect, float rx, float ry, Color color, float thickness);

        /**
         * To draw a rectangle on a view. The drawing of this rectangle 
         * is, when possible, hardware accelerated.
         * The rectangle will be filled with the provided color, see
         * the constructor DrawableRoundedRectangle(Rect,Color,float)
         * to draw only the outline of the rectangle.
         *
         * @param rect the coordinates of the rectangle 
         * @param color the color to use to draw the outline
         * @param rx radii on x of the round
         * @param ry radii on y of the round
         * @param filled whether this rectangle is filled with color, if not, the thickness will be 1.0 
         */
        DrawableRoundedRectangle(Rect<float> rect, float rx, float ry, Color color, bool filled);

        void draw();
        void tick();
};

}

#endif // MEH_DRAWABLE_ROUNDED_RECTANGLE_H
