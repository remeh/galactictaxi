#ifndef MEH_DRAWABLE_H
#define MEH_DRAWABLE_H

namespace meh {

class Drawable {
    public:
        typedef enum {
            SPRITE = 0,
            PRIMITIVE = 1
        } DrawableType;

    private:
        /**
         * Is this Sprite visible
         */
        bool disp;

    protected:
        DrawableType type;

    public:
        Drawable() : disp(true) { };
        virtual ~Drawable() {};

        /**
         * Draws the Drawable on the current rendering target.
         */
        virtual void draw() = 0;
        /**
         * Ticks this Drawable in case it needs to be updated.
         */
        virtual void tick() = 0;

        /**
         * Returns whether this Drawable is visible or not.
         */
        bool visible() const {
            return disp;
        }

        /**
         * Toggle the visible state of this Drawable.
         */
        void toggleVisible() {
            disp = !disp;
        }

        /**
         * Sets this Drawable visible.
         */
        void show() {
            disp = true;
        }

        /**
         * Sets this Drawable not visible.
         */
        void hide() {
            disp = false;
        }

        /**
         * Returns the DrawableType of this Drawable, whether it is
         * a Primitive or a Sprite
         */
        DrawableType getType() const {
            return type;
        }
};

}

#endif // MEH_DRAWABLE_H
