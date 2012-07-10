#ifndef MEH_DRAWABLE_ELLIPSE_H
#define MEH_DRAWABLE_ELLIPSE_H

#include "core/vector2d.h"
#include "core/color.h"
#include "ui/drawable.h"

namespace meh {

class DrawableEllipse : public Drawable {
    private:
        Vector2d<float> p;
        Vector2d<float> r;
        Color c;
        float t;
        bool f;

    protected:
    public:
        /**
         * To draw an ellipse on a view. The drawing of this ellipse 
         * is, when possible, hardware accelerated.
         * Only the outline of the ellipse will be drawn, see
         * the constructor DrawableEllipse(Vector2d<float>,float,float,Color,bool)
         * for a filled ellipse.
         *
         * @param center the center of the ellipse
         * @param rx the radii on x
         * @param ry the radii on y
         * @param color the color to use to draw the outline
         * @param thickness the thickness of the outline
         */
        DrawableEllipse(Vector2d<float> center, float rx, float ry, Color color, float thickness);

        /**
         * To draw a ellipse on a view. The drawing of this ellipse
         * is, when possible, hardware accelerated.
         * The ellipse will be filled with the provided color, see
         * the constructor DrawableRectangle(Vector2d<float>,float,float,Color,float)
         * to draw only the outline of the ellipse.
         *
         * @param center the center of the ellipse
         * @param rx the radii on x
         * @param ry the radii on y
         * @param color the color to use to draw the outline
         * @param filled whether this ellipse is filled with color, if not, the thickness will be 1.0 
         */
        DrawableEllipse(Vector2d<float> center, float rx, float ry, Color color, bool filled);

        /**
         * To draw a circle on a view. The drawing of this circle is, when
         * possible, hardware accelerated.
         * Only the outline of the circle will be drawn, see the
         * constructor DrawableEllipse(Vector2d<float>,float,Color,bool) for
         * a filled circle.
         *
         * @param center the center of the circle
         * @param r the radii of the circle
         * @param color the color of the outline
         * @param thickness the thickness of the outline
         */
        DrawableEllipse(Vector2d<float> center, float r, Color color, float thickness);

        /**
         * To draw a circle on a view. The drawing of this circle is, when
         * possible, hardware accelerated.
         * The circle will be filled with the provided color, see the
         * constructor DrawableEllipse(Vector2d<float>,float,Color,float) to
         * draw only the outline of the circle.
         *
         * @param center the center of the circle
         * @param r the radii of the circle
         * @param color the color of the outline
         * @param filled whether this ellipse is filled with color, if not, the thickness will be 1.0
         */ 
        DrawableEllipse(Vector2d<float> center, float r, Color color, bool filled);

        void draw();
        void tick();
};

}

#endif // MEH_DRAWABLE_ELLIPSE_H

