#ifndef MEH_PARTICLES_MANAGER
#define MEH_PARTICLES_MANAGER

#include <deque>
#include "core/vector2d.h"

using namespace std;

namespace meh {

class View;
class Color;
class Particle;

/**
 * The particles manager deals with the
 * many particules displayed in the view.
 *
 * There is one ParticlesManager per view.
 *
 * As of today, it is a simple implementation fully
 * computed on the CPU, the performance aren't extremly
 * good and so, a ParticlesManager is limited to 5000
 * particles maximum.
 */
class ParticlesManager {
    private:
        /**
         * To which view this ParticlesManager is attached.
         */
        View* v;

        /**
         * Checks for dead particles and delete them.
         */
        void checkForDeadParticles();

        /**
         * List of Particle managed by this ParticlesManager.
         */
        deque<Particle*> ptcles;

    protected:
    public:
        /**
         * Default constructor.
         *
         * @param view the view to which this ParticlesManager is attached.
         */
        ParticlesManager(View* view);

        /**
         * Default destructor.
         */
        ~ParticlesManager();

        /**
         * Updates all Particles state.
         */
        void tick();

        /**
         * Returns the view to which this ParticlesManager is attached.
         */
        View& view() {
            return *v;
        }

        /**
         * Adds a simple Particle to this ParticlesManager.
         * @param position the starting position of this Particle
         * @param ttl in ms is the time left to the Particle to live
         * @param angle the direction of the particle
         * @param velocity the starting speed of this Particle
         * @param slowdown at which speed the velocity is decreasing
         * @param color the color of this Particle
         */
        void addParticle(Vector2d<float> position, double ttl, float angle, float velocity, float slowdown, Color color);
};

}

#endif // MEH_PARTICLES_MANAGER
