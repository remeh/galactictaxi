#ifndef MEH_COLOR_H
#define MEH_COLOR_H

#include <allegro5/allegro.h>

namespace meh {
        
class Color {
    private:
        ALLEGRO_COLOR aColor;
    protected:
    public:
        Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) {
            setRGBA(r,g,b,a);
        }

        void setRGB(float r, float g, float b) {
            setRGBA(r,g,b,1.0f);
        }

        void setRGBA(float r, float g, float b, float a = 1.0f) {
            aColor.r = r;
            aColor.g = g;
            aColor.b = b;
            aColor.a = a;
        }

        float r() const { return aColor.r; }
        float g() const { return aColor.g; }
        float b() const { return aColor.b; }
        float a() const { return aColor.a; }

        ALLEGRO_COLOR& color() {
            return aColor;
        }
};
} // namespace meh

#endif // MEH_COLOR_H
