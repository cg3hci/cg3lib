#ifndef CG3_TIMER_H
#define CG3_TIMER_H

#include <time.h>
#include <iostream>
#include <string>
#ifndef _WIN32
#include <sys/time.h>
#endif

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
        #ifdef _WIN32

        #else
        timeval begin, end;
        #endif
        bool isStopped;
};

}

#include "timer.tpp"

#endif //CG3_TIMER_H
