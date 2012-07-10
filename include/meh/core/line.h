#ifndef MEH_LINE_H
#define MEH_LINE_H

#include "core/vector2d.h"

namespace meh {

class Line {
    private:
        Vector2d<float> s;
        Vector2d<float> e;
    protected:
    public:
        Line(int startx, int starty, int endx, int endy) {
            s.setXY(startx,starty);
            e.setXY(endx,endy);
        }

        Line(Vector2d<float> start, Vector2d<float> end) {
            s = start;
            e = end;
        }

        Vector2d<float>& start() { return s; }
        Vector2d<float>& end() { return e; }
};

} // namespace meh

#endif 
