#ifndef MEH_VIEW_H
#define MEH_VIEW_H

#include <string>
#include <deque>

#include "core/vector2d.h"
#include "core/rect.h"
#include "core/resourcesmanager.h"
#include "core/sample.h"
#include "core/keyboardhandler.h"
#include "ui/particlesmanager.h"

using namespace std;

namespace meh {

class Drawable;
class Sprite;

class View {
    private:
        deque<Drawable*> listDrawables;
        ResourcesManager rm;
        View* prnt;
        View* ch;
        ParticlesManager pm;

        /**
         * In order to try to hold the bitmap into the GPU
         * memory, we need to know whether the last one used
         * is the same or not.
         */
        string lastUsedBitmapId;

    protected:
    public:
        View(View* parent = nullptr);
        ~View();

        deque<Drawable*>& drawables() {
            return listDrawables;
        }

        View* child() {
            return ch;
        }

        View* parent() {
            return prnt;
        }

        void setChild(View* child);

        void setParent(View* parent);

        ResourcesManager& resourcesManager() {
            return rm;
        }

        ParticlesManager& particlesManager() {
            return pm;
        }

        /**
         * Returns a bitmap loaded in this view by its uniqueId.
         *
         * Used by the sprite when they need their Bitmap.
         * If the bitmap isn't found in the current view
         * ResourcesManager, it calls the parent RM if
         * this view is a child.
         */
        Bitmap* getBitmap(string uniqueId);

        /**
         * Returns a sample loaded in this view by its uniqueId.
         *
         * If the sample isn't found in the current view
         * ResourcesManager, it calls the parent RM if
         * this view is a child.
         */
        Sample* getSample(string uniqueId);

        /**
         * Returns a font loaded in this view by its uniqueId.
         *
         * If the font isn't found in the current view
         * ResourcesManager, it calls the parent RM if
         * this view is a child.
         */
        Font* getFont(string uniqueId);

        Sprite* addSprite(Vector2d<float> position, Vector2d<float> size, string bitmapId, Rect<float> texCoord);

        Sprite* addSprite(Sprite* sprite);

        Drawable* addDrawable(Drawable* drawable);

        /**
         * Removes a drawable from the managed drawables
         * but doesn't delete its memory.
         *
         * WARNING: 
         *  * the drawable still has an inconsistent link to the view.
         *  * do not forget to clear the memory !
         *
         * \return true whether a Drawable has been removed
         */
        bool remDrawable(Drawable* drawable);

        void draw();

        /**
         * Ticks every sprites of the View
         */
        void tick();
};

} // namespace meh

#endif // MEH_VIEW_H
