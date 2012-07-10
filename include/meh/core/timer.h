#ifndef MEH_TIMER_H
#define MEH_TIMER_H

#include <allegro5/allegro.h>

namespace meh {

/**
 * A Timer would be use to a task a certain amount of times
 * depending of a delay.
 *
 * For example :
 *
 * <pre>
 * Timer t(1000);
 * t.start();
 * while (sometest) {
 *   ... 
 * }
 * t.stop();
 * </pre>
 *
 * At this point, <pre>t.count()</pre> would returns how many seconds
 * the loop took to execute.
 *
 */
class Timer {
    private:
        ALLEGRO_TIMER* aTimer;
    protected:
    public:
        Timer(int delay);
        ~Timer();

        /**
         * Returns the allegro timer.
         */
        ALLEGRO_TIMER* timer() {
            return aTimer;
        }

        /**
         * Starts this Timer.
         */
        void start();
        /**
         * Stops this Timer.
         */
        void stop();

        /**
         * Resets the timer count to 0.
         */
        void reset();

        /**
         * Returns the count of this Timer.
         */
        int count();
        /**
         * Sets the count of this Timer.
         */
        void setCount(int count);

        /**
         * Returns the delay used by this Timer.
         */
        double delay();
        /**
         * Sets the delay used by this Timer.
         */
        void setDelay(int delay);

};

} // namespace meh

#endif // MEH_TIMER_H
