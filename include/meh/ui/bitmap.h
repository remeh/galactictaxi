#ifndef MEH_BITMAP_H
#define MEH_BITMAP_H

#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>
#include "core/rect.h"
#include "core/color.h"

using namespace std;

namespace meh {

class Bitmap {
    private:
        ALLEGRO_BITMAP* aBitmap;
        Rect<float> clip;

        /**
         * Fills the background of the Bitmap with the
         * provided Color.
         */
        void clear(Color c);

    protected:
    public:
        /**
         * Creates a Bitmap of size w*h.
         *
         * The flag videoMemory allows to choose whether
         * the bitmap is residing in the video card memory
         * or in the system memory.
         * The video memory will receive the greatest
         * benefit from hardware acceleration whereas the
         * bitmaps in system memory will probably have
         * faster direct pixel access.
         *
         * Note: the video bitmaps will be converted into
         * memory bitmaps when the last display is
         * destroyed.
         * 
         * @param w the width
         * @param h the height
         * @param videoMemory whether the bitmap is residing
         * in the video card memory or in the system memory.
         */
        Bitmap(int w, int h, bool videoMemory = true);

        /**
         * Creates a bitmap from a file on the hard disk.
         *
         * The flag videoMemory allows to choose whether
         * the bitmap is residing in the video card memory
         * or in the system memory.
         * The video memory will receive the greatest
         * benefit from hardware acceleration whereas the
         * bitmaps in system memory will probably have
         * faster direct pixel access.
         *
         * Note: the video bitmaps will be converted into
         * memory bitmaps when the last display is
         * destroyed.
         *
         * @param file the path to the file
         * @param videoMemory whether the bitmap is residing
         * in the video card memory or in the system memory.
         */
        Bitmap(string file, bool videoMemory = true);
        ~Bitmap();

        /**
         * Binds this Bitmap as the rendering target. Every 
         * draw calls will be applied on this Bitmap.
         */
        void bind();

        /**
         * Saves the Bitmap in a file. The file type is determined
         * by the extension.
         *
         * @return true on success, false otherwise.
         */
        bool save(string filename);

        /**
         * Returns the clipping rectangle of this Bitmap.
         */
        Rect<float> clipping() {
            return clip;
        }

        void setClipping(Rect<float> rect) {
            clip = rect;
        }

        /**
         * Returns the width of this Bitmap.
         */
        int width() const {
            return al_get_bitmap_width(aBitmap);
        }

        /**
         * Returns the height of this Bitmap.
         */
        int height() const {
            return al_get_bitmap_height(aBitmap);
        }

        /**
         * Returns true if this Bitmap is in the video memory.
         */
        bool isVideoBitmap() {
            return ((al_get_bitmap_flags(aBitmap) & ALLEGRO_VIDEO_BITMAP) != 0);
        }

        /**
         * Returns true if this Bitmap is in the memory (not in the GPU memory).
         */
        bool isMemoryBitmap() const {
            return ((al_get_bitmap_flags(aBitmap) & ALLEGRO_MEMORY_BITMAP) != 0);
        }

        /**
         * Returns the FBO number (OpenGL-related) used by Allegro to identify
         * the FBO used for this bitmap. Could return 0 whether no FBO is used.
         */
        int getFBO() const {
            return al_get_opengl_fbo(aBitmap);
        }

        /**
         * Returns a pointer to the ALLEGRO_BITMAP used for this Bitmap
         */
        ALLEGRO_BITMAP* bitmap() {
            return aBitmap;
        }
};
}

#endif // MEH_BITMAP_H
