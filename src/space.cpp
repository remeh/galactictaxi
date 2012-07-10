#include "game.h"
#include "client.h"
#include "space.h"
#include "star.h"
#include "destination.h"
#include "building.h"
#include "player.h"
#include "fragment.h"
#include "defines.h"

Space::Space(Game& g) :
    g(g) {
    clnt = nullptr;
    dest = nullptr;
    init();
}

Space::~Space() {
    deinit();
}

void Space::deinit() {
    for (auto it = strs.begin(); it != strs.end(); it++) {
        if (g.backgroundView()->remDrawable((*it)->sprite())) {
            delete (*it)->sprite();
            //delete reinterpret_cast<Star*>((*it)->sprite());
        }
        delete *it;
    }
    strs.clear();
    for (auto it = pltforms.begin(); it != pltforms.end(); it++) {
        if (g.platformsView()->remDrawable((*it)->sprite())) {
            delete (*it)->sprite();
            //delete reinterpret_cast<Sprite*>((*it)->sprite());
        }
        delete *it;
    }
    pltforms.clear();
    for (auto it = bldings.begin(); it != bldings.end(); it++) {
        if (g.platformsView()->remDrawable((*it)->sprite())) {
            delete (*it)->sprite();
        }
        delete *it;
    }
    bldings.clear();
    for (auto it = frgments.begin(); it != frgments.end(); it++) {
        if (g.creaturesView()->remDrawable((*it)->sprite())) {
            delete (*it)->sprite();
        }
        delete *it;
    }
    frgments.clear();

    if (g.creaturesView()->remDrawable(clnt->sprite())) {
        delete clnt->sprite();       
    }
    delete clnt;
    clnt = nullptr;
    if (g.creaturesView()->remDrawable(dest->sprite())) {
        delete dest->sprite();
    }
    delete dest;
    dest = nullptr;
}

void Space::init() {
    fillWithStars(STAR_COUNT);
    fillWithPlatforms(10);
    newClient();
    dest = new Destination(g,Vector2d<float>(0,0));
    newDestination();
    dest->sprite()->hide();
}

void Space::restart() {
    deinit();
    init();
}

void Space::fillWithStars(int max) {
    for (int i = 0; i < max; i++) {
        Vector2d<float> pos = Vector2d<float>(-400+System::rnd(SPACE_WIDTH+800),-400+System::rnd(SPACE_HEIGHT+800));
        Star* s = new Star(g, pos);
        strs.push_back(s);
    }
}

void Space::fillWithPlatforms(int max) {
    for (int i = 0; i < max; i++) {
        Vector2d<float> pos(0,0);
        bool ok = true;
        do {
            ok = true;
            // The platform
            pos = Vector2d<float>(System::rnd(SPACE_WIDTH),System::rnd(SPACE_HEIGHT));
            // Do not intersect other world
            for (auto it = pltforms.begin(); it != pltforms.end(); it++) {
                Rect<float> n(pos.x(),pos.y()-64,160,160);
                Rect<float> o((*it)->position().x(),(*it)->position().y()-64,160,160);
                if (n.intersects(o)) {
                    ok = false;
                    break;
                }
                if (n.intersects(g.player()->rect())) {
                    ok = false;
                    break;
                }
            }
        } while (ok != true);
        Platform* platform = new Platform(g,pos);
        pltforms.push_back(platform);
        // Add a building on this platform
        Vector2d<float> posB = Vector2d<float>(pos.x()+System::rnd(64), pos.y()-64);
        Building* building = new Building(g, posB);
        bldings.push_back(building);
    }
}

void Space::tick() {
    if (!System::rnd(FREQUENCY_FRAGMENTS)) {
        Fragment* f = new Fragment(g, Vector2d<float>(0,0));
        frgments.push_back(f);
    }

    for (auto it = strs.begin(); it != strs.end(); it++) {
        Star* star = *it;
        star->sprite()->setPosition(star->position().x()-g.player()->position().x()+298, star->position().y()-g.player()->position().y()-208);
    }
    for (auto it = pltforms.begin(); it != pltforms.end(); it++) {
        Platform* platform = *it;
        platform->sprite()->setPosition(platform->position().x()-g.player()->position().x()+298, platform->position().y()-g.player()->position().y()+208);

        if (platform->rect().intersects(g.player()->rect())) {
            g.player()->bounce();
            // TODO
        }
    }
    for (auto it = bldings.begin(); it != bldings.end(); it++) {
        Building* building = *it;
        building->sprite()->setPosition(building->position().x()-g.player()->position().x()+298, building->position().y()-g.player()->position().y()+208);
    }

    for (auto it = frgments.begin(); it != frgments.end(); ) {
        Fragment* f = *it;
        f->sprite()->setPosition(f->position().x()-g.player()->position().x()+298, f->position().y()-g.player()->position().y()+208);
        f->tick();
        if (f->dead()) {
            delete *it;
            it = frgments.erase(it);
        } else {
            ++it;        
        }
    }

    clnt->sprite()->setPosition(clnt->position().x()-g.player()->position().x()+298, clnt->position().y()-g.player()->position().y()+208);
    clnt->tick();

    dest->sprite()->setPosition(dest->position().x()-g.player()->position().x()+298, dest->position().y()-g.player()->position().y()+208);
    dest->tick();
}

void Space::newClient() {
    // Pick a random platform
    int platformIdx = System::rnd(bldings.size());
    Platform* platform = nullptr;
    Building* building = nullptr;
    int i = 0;
    for (auto it = pltforms.begin(); it != pltforms.end(); it++) {
        if (i == platformIdx) {
            platform = *it;
            break;
        }
        i++;
    }
    i = 0;
    for (auto it = bldings.begin(); it != bldings.end(); it++) {
        if (i == platformIdx) {
            building = *it;
            break;
        }
        i++;
    }

    // To refresh the model
    if (clnt != nullptr) {
        if (g.creaturesView()->remDrawable(clnt->sprite())) {
            delete clnt->sprite();       
        }
        delete clnt;
        clnt = nullptr;
    }
    clnt = new Client(g, Vector2d<float>(0,0));

    clnt->position().setXY(building->position().x(), building->position().y()+32); 
    clnt->setPlatform(platform);
}

void Space::newDestination() {
    // Pick a random platform
    bool ok = false;
    int platformIdx = 0;
    Platform* platform = nullptr;
    Building* building = nullptr;
    int i = 0;
    while (!ok) {
        platformIdx = System::rnd(bldings.size());
        i = 0;
        for (auto it = pltforms.begin(); it != pltforms.end(); it++) {
            if (i == platformIdx) {
                platform = *it;
                break;
            }
            i++;
        }
        // Do not want to be transported on the same platform
        if (platform == clnt->platform()) {
            continue;
        }
        ok = true;
    }
    i = 0;
    for (auto it = bldings.begin(); it != bldings.end(); it++) {
        if (i == platformIdx) {
            building = *it;
            break;
        }
        i++;
    }
    dest->position().setXY(building->position().x()-32, building->position().y());
    dest->sprite()->show();
}

