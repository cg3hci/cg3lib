#ifndef CG3_TIMER_H
#define CG3_TIMER_H

#include <QString>

#include <time.h>
#include <iostream>
#include <sys/time.h>

namespace cg3 {

class Timer {
    public:
        Timer (const std::string& caption, bool start_ = true);

        void start();

        void stopAndPrint();

        void stop();

        void print ();

        double delay();

    private:
        std::string caption;
        timeval begin, end;
        bool isStopped;
};

}

#include "timer.tpp"

#endif //CG3_TIMER_H
