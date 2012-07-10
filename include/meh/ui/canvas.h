#ifndef MEH_CANVAS_H
#define MEH_CANVAS_H

#include <string>
#include <allegro5/allegro.h>
#include "core/keyboardhandler.h"
#include "core/mousehandler.h"
#include "core/vector2d.h"
#include "core/timer.h"

using namespace std;

namespace meh {

class View;

typedef enum {
    CANVAS_DEFAULT = 0,
    CANVAS_OPENGL = 1,
    CANVAS_DIRECT3D = 2
} CanvasMode;

class Canvas {
    private:
        ALLEGRO_DISPLAY* aCanvas;
        View* v;
        /**
         * Used in the function refresh() to draw
         * only 60 frames per second.
         */
        Timer fpsTimer; 
        ALLEGRO_EVENT_QUEUE* eventQueue;
        ALLEGRO_EVENT event;

        KeyboardHandler keyHandler;
        MouseHandler mousHandler;

        Rect<float> clip; 

    protected:
    public:
        /**
         * Default constructor.
         *
         * @param w width of this canvas
         * @param h height of this canvas
         * @param mode whether this Canvas is hardware accelerated by OpenGL or Direct3D. Default value
         * to CANVAS_DEFAULT, which could be OpenGL on some systems.
         */
        Canvas(int w, int h, CanvasMode mode = CANVAS_DEFAULT);
        virtual ~Canvas();

        /**
         * Returns the pointer to the ALLEGRO_DISPLAY
         */
        ALLEGRO_DISPLAY* canvas() {
            return aCanvas;
        }

        /**
         * Returns the width of this canvas
         */
        int width() const {
            return al_get_display_width(aCanvas);
        }

        /**
         * Returns the height of this canvas.
         */
        int height() const {
            return al_get_display_height(aCanvas);
        }

        /**
         * Returns the position of this canvas in the screen.
         */
        Vector2d<int> position() const;

        /**
         * Sets the position of this Canvas in the screen.
         *
         * @param x position on the x axis
         * @param y position on the y axis
         */
        void setPosition(int x, int y);

        /**
         * Sets the position of this Canvas in the screen.
         *
         * @param p position in the screen
         */
        void setPosition(Vector2d<int>& p);

        /**
         * Sets the title of the window.
         *
         * @param title the new title of the window
         */
        void setTitle(string title);

        /**
         * Flips the buffer of the Canvas.
         *
         * When you draw on the Canvas, you don't actually draw
         * directly on it but in another buffer. When you flip
         * the Canvas, you display the modified buffer.
         */
        void flip();
        
        /**
         * Redraw the Canvas.
         *
         * Sets this Canvas as the current rendering target,
         * then draws every Sprites of the current view and its
         * subviews on it.
         *
         * Note:
         *   - you may want to call flip() if you wan't to see the
         *   result
         *   - contrary to refresh(), it doesn't use an
         *   internal timer to only draw 60 frames per second.
         *
         */
        void draw();

        /**
         * Redraw the Canvas only 60 times per second. To do
         * so, this function is blocking until a redraw should
         * happen.
         * 
         * Sets this Canvas as the current rendering target,
         * then draws every Sprites of the current view on it.
         * This method don't call flip().
         *
         * You should use like this :
         *
         * if (canvas.refresh()) {
         *    // stuff
         *    canvas.flip();
         * }
         *
         * \return whether the screen has been redrawn
         */
        bool refresh();

        /**
         * Returns true whether this Canvas is the current 
         * rendering target.
         */
        bool isCurrentCanvas() const {
            return (al_get_current_display() == aCanvas);
        }

        /**
         * Sets this display as the rendering target.
         */
        void bind();

        /**
         * Set the view to render.
         *
         * @param view the view to render on this Canvas
         */
        void setView(View* view) {
            this->v = view;
        }
    
        /**
         * Returns a pointer to the View binded to this Canvas.
         */
        View* view() {
            return v;
        }

        /**
         * Returns the clipping rectangle of this Canvas.
         *
         * \return the clipping rectangle of this Canvas.
         */
        Rect<float> clipping() const { return clip; }

        /**
         * Sets the clipping of this Canvas.
         */
        void setClipping(Rect<float> rect) {
            clip = rect;
        }

        KeyboardHandler& keyboardHandler() {
            return keyHandler;
        }

        MouseHandler& mouseHandler() {
            return mousHandler;
        }
};

} // namespace meh

#endif // MEH_CANVAS_H
