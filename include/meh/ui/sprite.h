#ifndef MEH_SPRITE_H
#define MEH_SPRITE_H

#include <string>
#include <map>

#include "core/vector2d.h"
#include "core/rect.h"
#include "core/color.h"
#include "ui/drawable.h"
#include "ui/view.h"
#include "ui/spriteanimation.h"

using namespace std;

namespace meh {

/**
 * A Sprite is attached to a View and is an image drawn on a Canvas.
 * The image used is the part of a Bitmap read in the ResourcesManager of
 * the View.
 *
 * It could be rotated : use setRotationAngle(), rotationAngle(), setRotationCenter()
 * and rotationCenter().
 * it could also be tinted : see setTintColor() and tintColor();
 *
 * It could be animated, see addAnimation(), startAnimation(), stopAnimation()
 * and animated(). By default, if there is an animation provided, the Sprite
 * is animated.
 *
 */
class Sprite : public Drawable {
    private:
        string bitmap;
        Vector2d<float> pos;
        Vector2d<float> s;
        View& view;
        map<string, SpriteAnimation*> anims;
        SpriteAnimation* currAnimation;
        bool animHasChangedSinceLastRotation;

        /**
         * For non-animated sprites.
         */
        Rect<float> texCoord;

        /**
         * Whether this animation is started or not.
         */
        bool strted;

        // The center of rotation
        Vector2d<float> rotCenter;
        // The rotation angle in radian
        float rotAngle;

        // Sub-bitmap used to rotate/tint the Sprite
        ALLEGRO_BITMAP* bmp;

        // Tint color
        Color tColor;

        bool isTinted;

    protected:
    public:
        /**
         * Static sprite
         *
         * <b>WARNING</b> : You should never use this constructor but use the addSprite method of View
         * instead, but if you do, always use this constructors with a 'new' and never delete the memory
         * as this is the view who takes care of it.
         */
        Sprite(Vector2d<float> position, Vector2d<float> size, View& view, string bitmapId, Rect<float> texCoord);
        ~Sprite();

        /**
         * Draw the Sprite on the current rendering target.
         */
        void draw();
        
        /**
         * Tick used to animate the sprite
         */
        void tick();

        /**
         * Adds an animation to this sprite.
         *
         * @param name the name of this animation
         * @param nbFrames the number of frame of this animation
         * @param durations the duration of each frame of this animation
         * @param texCoords the texture coordinates of each frame of this animation
         */
        void addAnimation(string name, unsigned int nbFrames, const unsigned int* durations, const Rect<float>* texCoords);

        /**
         * Sets the current animation of this frame.
         * 
         * NOTE: could reset the frame to the frame number 0 whether the
         * current frame number was too high due to the previous animation.
         */
        void setAnimation(string animation);

        /**
         * Returns wheter this animation is started or not.
         * See : startAnimation() and stopAnimation()
         */
        bool animated() { return strted; }

        /**
         * Stops the animation. Could be restarted by using startAnimation().
         */
        void stopAnimation();

        /**
         * Starts the animation. Could be stopped by using stopAnimation().
         */
        void startAnimation();

        /**
         * Returns a pointer to the current SpriteAnimation.
         *
         * \return a pointer to the current SpriteAnimation.
         */
        SpriteAnimation* currentAnimation() {
            return currAnimation;
        }

        /**
         * Sets the size of this Sprite in the View.
         *
         * @param x size on the x axis
         * @param y size on the y axis
         */
        void setSize(float x, float y) {
            s.setXY(x,y);
        }

        /**
         * Returns the size of this Sprite in the View.
         *
         * \return the size of this Sprite in the View
         */
        Vector2d<float>& size() {
            return s;
        }

        /**
         * Sets the position of this Sprite in the View.
         *
         * @param x position on the x axis
         * @param y position on the y axis
         */
        void setPosition(float x, float y) {
            pos.setXY(x,y);
        }

        /**
         * Returns the position of this Sprite in the View.
         *
         * \return the position of this Sprite in the View
         */
        Vector2d<float>& position() {
            return pos;
        }

        /**
         * Returns the uniqueId of the Bitmap used for this Sprite.
         *
         * \return the uniqueId of the Bitmap used for this Sprite.
         */
        string& bitmapId() {
            return bitmap;
        }

        /**
         * Sets the rotation angle of this Sprite. (unit: rad, the rotation is clockwise)
         */
        void setRotationAngle(float rot) {
            rotAngle = rot;
        }

        /**
         * Returns the rotation angle of this Sprite. (unit: rad, the rotation is clockwise)
         */
        float rotationAngle() const {
            return rotAngle;
        }

        /**
         * Sets the rotation center of this Sprite.
         * @param rotationCenter the rotation center of this Sprite.
         */
        void setRotationCenter(Vector2d<float>& rotationCenter) {
            rotCenter.setXY(rotationCenter.x(),rotationCenter.y()); 
        }

        /**
         * Returns the rotation center of this Sprite.
         */
        Vector2d<float>& rotationCenter() {
            return rotCenter;
        }

        /**
         * Sets the tint color of this Sprite.
         *
         * @param color the tint color to use to color this Sprite.
         */
        void setTintColor(Color& color) {
            tColor.color() = color.color();
            // TODO use a constant
            if (tColor.r() == 1.0f && tColor.g() == 1.0f && tColor.b() == 1.0f && tColor.a() == 1.0f) {
                isTinted = false;
            }
            isTinted = true;
        }

        /**
         * Returns whether this Sprite is tinted or not.
         */
        bool tinted() { return isTinted; }

        /**
         * Returns the Color used to tint this Sprite.
         */
        Color& tintColor() {
            return tColor;
        }
};

} // namespace meh

#endif // MEH_SPRITE_H
