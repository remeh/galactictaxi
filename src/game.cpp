#include <cmath>
#include <cstdio>
#include "meh"

#include "game.h"
#include "space.h"
#include "player.h"

using namespace meh;

Color Game::orange(1.0f,0.3f,0.0f,0.2f);
Color Game::darkGray(0.8f,0.8f,0.8f,0.9f);
Color Game::red(1.0f,0.0f,0.0f,0.7f);
Color Game::white(1.0f,1.0f,1.0f,0.8f);

Game::Game() :
    Canvas(640,480),
    rnning(true),
    fontNormal("./res/yapix.ttf",14),
    fontMedium("./res/yapix.ttf",20),
    fontLarge("./res/yapix.ttf",48),
    cstomerLoaded(false),
    endMessageMurder(0),
    playingEngineSound(false),
    playerIsExplosing(false),
    endPlayerExplosion(0),
    points(0) { 

    bckgroundView = new View();
    pltformsView = new View(bckgroundView);
    crturesView = new View(pltformsView);
    mnuView = nullptr;
    setView(bckgroundView);


    playerHurted = 0;

    initResources();

    plyer = new Player(*this);
    printf("Filled the gas of the taxi...\n");
    spce = new Space(*this);
    printf("End of space generation...\n");

    rrows.reserve(4);
    rrows[LEFT_I] = crturesView->addSprite(Vector2d<float>(50,224), Vector2d<float>(32,32), "bonzommes", Rect<float>(96,64,32,32));
    rrows[UP_I] = crturesView->addSprite(Vector2d<float>(304,50), Vector2d<float>(32,32), "bonzommes", Rect<float>(128,64,32,32));
    rrows[RIGHT_I] = crturesView->addSprite(Vector2d<float>(548,224), Vector2d<float>(32,32), "bonzommes", Rect<float>(160,64,32,32));
    rrows[DOWN_I] = crturesView->addSprite(Vector2d<float>(304,388), Vector2d<float>(32,32), "bonzommes", Rect<float>(192,64,32,32));

    dmageBarLine = dynamic_cast<DrawableRectangle*>(crturesView->addDrawable(new DrawableRectangle(Rect<float>(300,10,300,40), Game::white, 1.0f)));
    dmageBar = dynamic_cast<DrawableRectangle*>(crturesView->addDrawable(new DrawableRectangle(Rect<float>(300,10,0,39), Game::red, true)));

    // stringstream
    ss = nullptr;

    sMusic->play();

    start();

    displayMenu();
}

Game::~Game() {
    if (spce) {
        delete spce;
        spce = nullptr;
    }
}

void Game::start() {
    // FIRST TICK
    plyer->tick();
    spce->tick();
    bckgroundView->tick();
}

void Game::initResources() {
    bckgroundView->resourcesManager().loadBitmap("world","./res/world.png");
    sBim = bckgroundView->resourcesManager().loadSample("bim","./res/bim.wav");
    sEngine = bckgroundView->resourcesManager().loadSample("engine","./res/engine3.wav");
    sSplash = bckgroundView->resourcesManager().loadSample("splash","./res/splash.wav");
    sDring = bckgroundView->resourcesManager().loadSample("dring","./res/dring.wav");
    sExplosion = bckgroundView->resourcesManager().loadSample("explosion","./res/explosion.wav");
    sNewClient = bckgroundView->resourcesManager().loadSample("newclient","./res/new.wav");
    sEngine->setPlayMode(Sample::LOOP);
    crturesView->resourcesManager().loadBitmap("bonzommes","./res/bonzomme.png");
    sMusic = bckgroundView->resourcesManager().loadSample("music","./res/music.ogg");
    if (sMusic) {
        sMusic->setPlayMode(Sample::LOOP);
    }
}

void Game::displayMenu() {
    mnuView = new View(crturesView);
    // Menu
    Color blackTransp(0.01f,0.01f,0.01f,0.9f);
    menuRectLine = dynamic_cast<DrawableRectangle*>(mnuView->addDrawable(new DrawableRectangle(Rect<float>(30,30,580,420),Game::white, 3.0f)));
    menuRect = dynamic_cast<DrawableRectangle*>(mnuView->addDrawable(new DrawableRectangle(Rect<float>(30,30,580,420),blackTransp, true)));
    state = MENU;
    setView(bckgroundView);
}

void Game::quitMenu() {
    setView(bckgroundView);
    delete mnuView;
    mnuView = nullptr;
    state = GAME;
}

void Game::mainLoop() {
    // Refresh the display at 60FPS
    while (rnning) {
        keyboardHandler().refreshState();

        if (keyboardHandler().keydown(ALLEGRO_KEY_ESCAPE)) {
            if (state == GAME) {
                displayMenu();
            }
        }

        if (state == MENU || state == GAMEOVER) {
            if (state == MENU && keyboardHandler().keydown(ALLEGRO_KEY_SPACE)) {
                quitMenu();
            }
            if (keyboardHandler().keydown(ALLEGRO_KEY_R)) {
                spce->restart();
                plyer->setDamage(0);
                plyer->setPosition(0,0);
                plyer->setSpeed(Vector2d<float>(0,0));
                points = 0;
                endMessageMurder = 0;
                playerIsExplosing = false;
                cstomerLoaded = false;
                endPlayerExplosion = 0;
                quitMenu();
            }
            if (keyboardHandler().keydown(ALLEGRO_KEY_Q)) {
                rnning = false;
            }
        } else {

            plyer->setDirection(UNKNOWN);
            bool engine = false;

            if (keyboardHandler().keydown(ALLEGRO_KEY_LEFT)) {
                plyer->setDirection(LEFT);
                plyer->left();
                engine = true;
            } else if (keyboardHandler().keydown(ALLEGRO_KEY_RIGHT)) {
                plyer->setDirection(RIGHT);
                plyer->right();
                engine = true;
            }
            
            if (keyboardHandler().keydown(ALLEGRO_KEY_DOWN)) {
                plyer->setDirection(plyer->direction() | DOWN);
                plyer->down();
                engine = true;
            } else if (keyboardHandler().keydown(ALLEGRO_KEY_UP)) {
                plyer->setDirection(plyer->direction() | UP);
                plyer->up();
                engine = true;
            }

            if (playerIsExplosing) {
                playerExplosion();
                if (endPlayerExplosion < System::currentTime()) {
                    displayMenu();
                    state = GAMEOVER;
                }
            }

            plyer->tick();
            
            spce->tick();

            bckgroundView->tick();

            if (!playingEngineSound && engine) {
                sEngine->play();
                playingEngineSound = true;
            }
            if (playingEngineSound && !engine) {
                sEngine->stop();
                playingEngineSound = false;
            }

            // Damage bar
            float percent = plyer->damage()/100.0f;
            dmageBar->setWidth(dmageBarLine->rect().width()*percent);

            if (playerHurted > 0) {
                Color color(1.0f,1.0f,1.0f,1.0f);
                color.setRGBA(1.0f,(1.0f - playerHurted/100.0f), (1.0f - playerHurted/100.0f), 1.0f);
                plyer->sprite()->setTintColor(color);
                playerHurted -= 2;
                if (playerHurted == 0) {
                    color.setRGBA(1.0f,1.0f,1.0f,1.0f);
                    plyer->sprite()->setTintColor(color);
                }
            }
        }
        
        if (refresh()) {
            fontNormal.draw(Vector2d<float>(5,10),Game::white, "Points: ");
            stringstream ss;
            ss << points;
            fontNormal.draw(Vector2d<float>(60,10),Game::white, ss.str());
            if (state == GAME) {
                    if (!cstomerLoaded) {
                        if (endMessageMurder > System::currentTime()) {
                            fontNormal.draw(Vector2d<float>(5,60),Game::red, "YOU'VE MURDERED YOUR CUSTOMER! ...");
                        } else {
                            fontNormal.draw(Vector2d<float>(5,60),Game::white, "Find your next customer!");
                        }
                    } else {
                        fontNormal.draw(Vector2d<float>(5,60),Game::white, "Drop your customer to the destination.");
                    }
                    fontMedium.draw(Vector2d<float>(200,20),Game::white, "Damage:");
            } else if (state == MENU) {
                fontLarge.draw(Vector2d<float>(40,40), Game::orange, "Galactic Taxi");
                fontMedium.draw(Vector2d<float>(50,90), Game::white, "Your galaxy is composed of many tiny worlds.");
                fontMedium.draw(Vector2d<float>(50,120), Game::white, "Everything was fine before the expansion of the");
                fontMedium.draw(Vector2d<float>(50,150), Game::white, "galactic internet, but now, people need to be ");
                fontMedium.draw(Vector2d<float>(50,180), Game::white, "transported between their world. This is why you've");
                fontMedium.draw(Vector2d<float>(50,210), Game::white, "created the brand-new service : Galactic Taxis !");
                fontMedium.draw(Vector2d<float>(50,240), Game::white, "Call from and for everywhere in the galaxy!");
                fontMedium.draw(Vector2d<float>(50,310), Game::white, "CONTROLS");
                fontMedium.draw(Vector2d<float>(50,340), Game::white, "SPACE - to start/resume");
                fontMedium.draw(Vector2d<float>(50,370), Game::white, "R - to regenerate and restart");
                fontMedium.draw(Vector2d<float>(50,400), Game::white, "Q - to quit");
            } else if (state == GAMEOVER) {
                fontLarge.draw(Vector2d<float>(40,40), Game::orange, "GAME OVER");
                if (points > 0) {
                    fontMedium.draw(Vector2d<float>(50,120), Game::white, "You've succeeded to earn");
                    ss << " $";
                    fontMedium.draw(Vector2d<float>(150,150), Game::white, ss.str());
                    fontMedium.draw(Vector2d<float>(50,180), Game::white, "But everything was in the taxi..."); 
                } else if (points == 0) {
                    fontMedium.draw(Vector2d<float>(50,120), Game::white, "You didn't earn anything...");
                    fontMedium.draw(Vector2d<float>(50,150), Game::white, "Well, you should find another job's idea...");
                } else {
                    fontMedium.draw(Vector2d<float>(50,120), Game::white, "You've lost money !");
                    fontMedium.draw(Vector2d<float>(50,150), Game::white, "Seriously ?!");
                }

                fontMedium.draw(Vector2d<float>(50,370), Game::white, "R - to regenerate and restart");
                fontMedium.draw(Vector2d<float>(50,400), Game::white, "Q - to quit");
            }
            
            flip();
        }
    }
}

void Game::newClient() {
    spce->newClient();
}

void Game::newDestination() {
    spce->newDestination();
}

void Game::displayArrow(int dir) {
    if (dir & UP) {
        rrows[UP_I]->show();
    }
    if (dir & DOWN) {
        rrows[DOWN_I]->show();
    }
    if (dir & LEFT) {
        rrows[LEFT_I]->show();
    }
    if (dir & RIGHT) {
        rrows[RIGHT_I]->show();
    }
}

void Game::hideArrows() {
    rrows[LEFT_I]->hide();
    rrows[RIGHT_I]->hide();
    rrows[UP_I]->hide();
    rrows[DOWN_I]->hide();
}

void Game::murderCustomer() {
    endMessageMurder = System::currentTime() + 3000;
    if (sSplash) {
        sSplash->play();
    }
}

void Game::bloodExplosion(Vector2d<float> pos) {
    pos.setXY(pos.x()+ 298 - plyer->rect().x(),pos.y() + 208 - plyer->rect().y());

    for (int i = 0; i < 30; i++) {
        int ang = System::rnd(360);
        double ttl = 300 + System::rnd(150);
        double velocity = 1.4 + System::rnd(1000)/1000.0;
         creaturesView()->particlesManager().addParticle(pos,ttl,ang,velocity,0.05, Game::red);
        
    }
}

void Game::fragmentExplosion(Vector2d<float> pos) {
    pos.setXY(pos.x()+ 298 - plyer->rect().x(),pos.y() + 208 - plyer->rect().y());

    for (int i = 0; i < 30; i++) {
        int ang = System::rnd(360);
        double ttl = 300 + System::rnd(150);
        double velocity = 1.4 + System::rnd(1000)/1000.0;
         creaturesView()->particlesManager().addParticle(pos,ttl,ang,velocity,0.05, Game::darkGray);
    }
}

void Game::hurtPlayer() {
    if (sBim) {
        sBim->play();
    }
    if (playerHurted <= 0) {
        playerHurted = 100;
        plyer->incDamage(10);
    }

    if (plyer->damage() > 100) {
        plyer->setDamage(100);
    }
    
    if (plyer->damage() >= 100 && !playerIsExplosing) {
        playerIsExplosing = true;
        sExplosion->play();
        endPlayerExplosion = System::currentTime()+3000;
    }
}

void Game::playerExplosion() {
    Vector2d<float> pos(298+32,208+16);
    for (int i = 0; i < 10; i++) {
        int ang = System::rnd(360);
        double ttl = 600 + System::rnd(150);
        double velocity = 1.4 + System::rnd(1000)/1000.0;
        creaturesView()->particlesManager().addParticle(pos,ttl,ang,velocity,0.05, Game::orange);
    }
}

void Game::dring() {
    if (sDring) {
        sDring->play();
    }
}

void Game::soundNewClient() {
    if (sNewClient) {
        sNewClient->play();
    }
}

