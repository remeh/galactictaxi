#ifndef LD23_SPACE_H
#define LD23_SPACE_H

#include <deque>
#include "game.h"
#include "star.h"
#include "building.h"
#include "platform.h"
#include "defines.h"

using namespace std;

class Destination;
class Fragment;
class Client;
class Game;

class Space {
    private:
        deque<Star*> strs;
        deque<Platform*> pltforms;
        deque<Building*> bldings;
        deque<Fragment*> frgments;

        Game &g;
        Client* clnt;
        Destination* dest;

    protected:
    public:
        Space(Game& g);
        ~Space();

        void fillWithStars(int max);
        void fillWithPlatforms(int max);

        void newClient();
        void newDestination();

        void init();
        void deinit();
        void restart();

        void tick();

        Client* client() { return clnt; }
        Destination* destination() { return dest; }
};

#endif // LD23_SPACE_H
