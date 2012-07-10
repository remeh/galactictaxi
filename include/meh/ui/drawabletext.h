#ifndef MEH_DRAWABLE_TEXT_H
#define MEH_DRAWABLE_TEXT_H

#include <string>
#include "core/font.h"
#include "core/vector2d.h"
#include "core/color.h"
#include "ui/view.h"
#include "ui/drawable.h"

using namespace std;

namespace meh {

class DrawableText : public Drawable {
    private:
        Vector2d<float> pos;
        Color c;
        string t;
        View& v;
        string id;
        Font::TextAlignement align;

    protected:
    public:
        DrawableText(Vector2d<float> position, Color color, string text, View& view, string fontUniqueId, Font::TextAlignement alignement = Font::LEFT);

        /** Returns the position of this DrawableText. */
        Vector2d<float>& position() { return pos; }

        string& text() { return t; }

        Color& color() { return c; }

        Font::TextAlignement& alignement() { return align; }

        void draw();

        void tick() {};

};

} // namespace meh

#endif // MEH_DRAWABLE_TEXT_H
