#ifndef LD23_GAME_H
#define LD23_GAME_H

#include <vector>
#include <sstream>
#include "meh"

using namespace meh;
using namespace std;

class Space;
class Player;

class Game : public Canvas {
    public:
        static Color orange;
        static Color red;
        static Color darkGray;
        static Color white;

    private:
        bool rnning;

        View* crturesView;
        View* pltformsView;
        View* bckgroundView;
        View* mnuView;

        meh::Font fontNormal;
        meh::Font fontMedium;
        meh::Font fontLarge;

        Space* spce; 

        Player* plyer;

        meh::DrawableRectangle* dmageBarLine;
        meh::DrawableRectangle* dmageBar;
        meh::DrawableRectangle* menuRectLine;
        meh::DrawableRectangle* menuRect;

        vector<Sprite*> rrows;

        bool cstomerLoaded;

        long endMessageMurder;

        bool playingEngineSound;

        bool playerIsExplosing;
        double endPlayerExplosion;

        int points;
        
        int state;

        // XXX should be in Player
        int playerHurted;

        Sample* sBim;
        Sample* sEngine;
        Sample* sSplash;
        Sample* sDring;
        Sample* sMusic;
        Sample* sExplosion;
        Sample* sNewClient;

        stringstream* ss;

    protected:
    public:
        Game();
        ~Game();

        void mainLoop();

        void stop() { rnning = false; }
        bool running() { return rnning; } 

        void initResources();


        View* backgroundView() { return bckgroundView; }
        View* platformsView() { return pltformsView; }
        View* creaturesView() { return crturesView; }
        View* menuView() { return mnuView; }

        Space* space() { return spce; }

        Player* player() { return plyer; }

        void newClient();
        void newDestination();

        vector<Sprite*>& arrows() { return rrows; }
        void displayArrow(int dir);
        void hideArrows();

        bool customerLoaded() { return cstomerLoaded; }
        void loadCustomer() { cstomerLoaded = true; }
        void dropCustomer() { cstomerLoaded = false; }
        void murderCustomer();

        void bloodExplosion(Vector2d<float> pos);
        void fragmentExplosion(Vector2d<float> pos);
        void playerExplosion();

        void addPoints(int i) { points += i; }

        void hurtPlayer();

        void displayMenu();
        void quitMenu();

        void start();
        
        void dring();
        void soundNewClient();
};

#endif // LD23_GAME_H

