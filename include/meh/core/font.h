#ifndef MEH_FONT_H
#define MEH_FONT_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "core/vector2d.h"
#include "core/color.h"

using namespace std;

namespace meh {

class Font {
    public:
        typedef enum {
            LEFT = ALLEGRO_ALIGN_LEFT,
            CENTER = ALLEGRO_ALIGN_CENTRE,
            RIGHT = ALLEGRO_ALIGN_RIGHT
        } TextAlignement;

    private:
        ALLEGRO_FONT* aFont;
        int pt;
    protected:
    public:
        /**
         * Loads a font from a file.
         *
         * @param filename the filename of the font
         * @param ptSize the point size of the font
         */
        Font(string filename, int ptSize);
        ~Font();

        /**
         * Returns the pointer to the ALLEGRO_FONT.
         */
        ALLEGRO_FONT* font() {
            return aFont;
        }

        /**
         * Draws the provided text on the current target bitmap.
         *
         * @param position at which position the text must be drawn
         * @param color in which color the text must be drawn
         * @param text the text to render
         * @param alignement the alignement use to render the text
         */
        void draw(Vector2d<float> position, Color color, string text, Font::TextAlignement alignement = Font::LEFT);
};

} // namespace meh

#endif // MEH_FONT_H
