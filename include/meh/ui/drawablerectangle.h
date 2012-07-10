#ifndef MEH_DRAWABLE_RECTANGLE_H
#define MEH_DRAWABLE_RECTANGLE_H

#include "core/rect.h"
#include "core/color.h"
#include "ui/drawable.h"

namespace meh {

class DrawableRectangle : public Drawable {
    private:
        /**
         * The Rectangle coordinates.
         */
        Rect<float> r;
        /**
         * The color of this Rectangle.
         */
        Color c;
        /**
         * Thickness.
         */
        float t;
        /**
         * Is filled ?
         */
        bool f;

    protected:
    public:
        /**
         * To draw a rectangle on a view. The drawing of this rectangle 
         * is, when possible, hardware accelerated.
         * Only the outline of the rectangle will be drawn, see
         * the constructor DrawableRectangle(Rect,Color,bool)
         * for a filled rectangle.
         *
         * @param rect the coordinates of this rectangle
         * @param color the color to use to draw the outline
         * @param thickness the thickness of the outline
         */
        DrawableRectangle(Rect<float> rect, Color color, float thickness);

        /**
         * To draw a rectangle on a view. The drawing of this rectangle 
         * is, when possible, hardware accelerated.
         * The rectangle will be filled with the provided color, see
         * the constructor DrawableRectangle(Rect,Color,float)
         * to draw only the outline of the rectangle.
         *
         * @param rect the coordinates of the rectangle 
         * @param color the color to use to draw the outline
         * @param filled whether this rectangle is filled with color, if not, the thickness will be 1.0 
         */
        DrawableRectangle(Rect<float> rect, Color color, bool filled);

        /**
         * Returns a referencet to the Rect used for this DrawableRectangle
         * in order to be able to move/resize it.
         */
        Rect<float>& rect() { return r; }

        /**
         * Sets the width.
         *
         * @param width new width
         */
        void setWidth(float width) { r.size().setX(width); }

        /**
         * Sets the height.
         *
         * @param height the new height
         */
        void setHeight(float height) { r.size().setY(height); }

        /**
         * Sets the position of this Drawable.
         *
         * @param x position on the x axis
         * @param y position on the y axis
         */
        void setXY(float x, float y) { r.position().setXY(x,y); }

        /**
         * Returns the Color of this DrawableRectangle.
         */
        Color& color() { return c; }

        void draw();
        void tick();
};

}

#endif // MEH_DRAWABLE_RECTANGLE_H
