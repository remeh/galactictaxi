#ifndef MEH_KEYBOARD_HANDLER_H
#define MEH_KEYBOARD_HANDLER_H

#include <allegro5/allegro.h>

namespace meh {

class KeyboardHandler {
    private:
        ALLEGRO_KEYBOARD_STATE state;
    protected:
    public:
        /**
         * Default constructor.
         */
        KeyboardHandler();
        ~KeyboardHandler();

        /**
         * Refresh the snapshot represeting
         * the current state of the keyboard.
         */
        void refreshState();
        
        /**
         * Returns whether the provided key
         * is pushed or not.
         */
        bool keydown(int keycode);
};

} // namespace meh

#endif // MEH_KEYBOARD_HANDLE_H

