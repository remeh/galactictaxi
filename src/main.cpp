#include "meh"
#include "game.h"

using namespace meh;

int main(int argc, char* argv[]) {
    System::init();

    Game g;
    g.mainLoop();

    return 0;
}
