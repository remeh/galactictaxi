#ifndef MEH_DRAWABLE_TRIANGLE_H
#define MEH_DRAWABLE_TRIANGLE_H

#include "core/vector2d.h"
#include "core/color.h"
#include "ui/drawable.h"

namespace meh {

class DrawableTriangle : public Drawable {
    private:
        Vector2d<float> p1;
        Vector2d<float> p2;
        Vector2d<float> p3;
        Color c;
        float t;
        bool f;

    protected:
    public:
        /**
         * To draw a triangle on a view. The drawing of this triangle 
         * is, when possible, hardware accelerated.
         * Only the outline of the triangle will be drawn, see
         * the constructor DrawableTriangle(Vector2d<float>,Vector2d<float>,Vector2d<float>,Color,bool)
         * for a filled triangle.
         *
         * @param p1 the first point of the triangle
         * @param p2 the second point of the triangle
         * @param p3 the third point of the triangle
         * @param color the color to use to draw the outline
         * @param thickness the thickness of the outline
         */
        DrawableTriangle(Vector2d<float> p1, Vector2d<float> p2, Vector2d<float> p3, Color color, float thickness);

        /**
         * To draw a triangle on a view. The drawing of this triangle
         * is, when possible, hardware accelerated.
         * The triangle will be filled with the provided color, see
         * the constructor DrawableTriangle(Vector2d<float>,Vector2d<float>,Vector2d<float>,Color,float)
         * to draw only the outline of the triangle.
         *
         * @param p1 the first point of the triangle
         * @param p2 the second point of the triangle
         * @param p3 the third point of the triangle
         * @param color the color to use to draw the outline
         * @param filled whether this triangle is filled with color. If not, the thickness will be 1.0
         */
        DrawableTriangle(Vector2d<float> p1, Vector2d<float> p2, Vector2d<float> p3, Color color, bool filled);

        void draw();
        void tick();
};

}

#endif // MEH_DRAWABLE_TRIANGLE_H
