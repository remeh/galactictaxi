#ifndef MEH_PARTICLE
#define MEH_PARTICLE

#include "core/vector2d.h"
#include "ui/sprite.h"

namespace meh {

class ParticlesManager;

class Particle {
    private:
        /** The position of this Particule. */
        Vector2d<float> pos;
        /** Time to live, in ms./ */
        double ttl;
        /** Angle followed by this Particle in degree. 0 is the right. */
        float ang;
        /** Velocity of this Particle. */
        float velo;
        /** State of this Particle. */
        bool live;
        /** At which speed the velocity is decreasing */
        float sd;
        
        /**
         * At which tick the Particle will be dead.
         */
        double deathTick;

        /**
         * The Sprite used to represent this Particle.
         */
        Sprite* spr;

        /**
         * The ParticlesManager to which this Particle is attached.
         */
        ParticlesManager& pm;

    protected:
    public:
        /**
         * Creates a new Particle at <i>position</i>, moving to the direction <i>angle</i> in degree (0 is the right)
         * at the provided <i>velocity</i>. The parameter <i>ttl</i> is the time (in ms) that the Particle will be alive. 
         *
         * @param position the starting position of this Particle
         * @param ttl in ms is the time left to the Particle to live
         * @param angle the direction of the particle
         * @param velocity the starting speed of this Particle
         * @param slowdown at which speed the velocity is decreasing
         * @param color the color of this Particle
         * @param particlesManager to which ParticleManager this Particle is attached
         */
        Particle(Vector2d<float> position, double ttl, float angle, float velocity, float slowdown, Color color, ParticlesManager& particlesManager);

        /**
         * Updates the particle.
         */
        void tick();

        /**
         * Returns whether this Particle is still alive.
         */
        bool alive() {
            return live;
        }

        /**
         * Returns the sprite used by this Particle.
         */
        Sprite* sprite() {
            return spr;
        }
};

}

#endif // MEH_PARTICLE
