#ifndef MEH_MOUSE_HANDLER_H
#define MEH_MOUSE_HANDLER_H

#include <allegro5/allegro.h>
#include "core/vector2d.h"

namespace meh {

class MouseHandler {
    private:
        ALLEGRO_MOUSE_STATE state;
    protected:
    public:
        /**
         * Default constructor.
         */
        MouseHandler();
        ~MouseHandler();

        /**
         * Refresh the snapshot represeting
         * the current state of the mouse.
         */
        void refreshState();

        /**
         * Returns whether the left button is pressed.
         */
        bool left();

        /**
         * Returns whether the middle button is pressed.
         */
        bool middle();
        
        /**
         * Returns whether the right button is pressed.
         */
        bool right();

        /**
         * Returns the position of the wheel (when the user
         * roll the wheel up, the position increase and when
         * the user roll the wheel down, this value decrease.
         */
        int wheel();

        /**
         * Alias of method wheel().
         */
        int z();

        /**
         * Returns the position of the mouse.
         */
        Vector2d<float> position();

        /**
         * Returns the x position of the mouse.
         */
        float x();

        /**
         * Returns the y position of the mouse.
         */
        float y();
};

} // namespace meh

#endif // MEH_MOUSE_HANDLE_H


