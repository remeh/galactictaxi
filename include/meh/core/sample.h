#ifndef MEH_SAMPLE_H
#define MEH_SAMPLE_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

using namespace std;

namespace meh {


class Sample {
    public:
        typedef enum {
            ONCE = ALLEGRO_PLAYMODE_ONCE,
            LOOP = ALLEGRO_PLAYMODE_LOOP,
            BIDIR = ALLEGRO_PLAYMODE_BIDIR
        } PlayMode;

    private:
        ALLEGRO_SAMPLE* aSample;
        float g;
        float p;
        float s;
        PlayMode pMode;
        ALLEGRO_SAMPLE_ID sampleId;

    protected:
    public:
        /**
         * Default constructor.
         * Will automatically load the sample.
         *
         * @param filename the filename of the sound to load
         */
        Sample(string filename);
        ~Sample();

        /**
         * Returns a pointer to the ALLEGRO_SAMPLE 
         *
         * \return a pointer to the ALLEGRO_SAMPLE
         */
        ALLEGRO_SAMPLE* sample() {
            return aSample;
        };

        float gain() {
            return g;
        }

        void setGain(float g) {
            this->g = g;
        }

        float pan() {
            return p;
        }

        void setPan(float p) {
            this->p = p;
        }
        
        float speed() {
            return s;
        }

        void setSpeed(float s) {
            this->s = s;
        }

        PlayMode playMode() {
            return pMode;
        }

        void setPlayMode(PlayMode pm) {
            pMode = pm;
        }

        void play();

        void stop();
};

}

#endif // MEH_SAMPLE_H
