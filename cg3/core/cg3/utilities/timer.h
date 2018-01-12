/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TIMER_H
#define CG3_TIMER_H

#include <time.h>
#include <iostream>
#include <string>
#include <chrono>

namespace cg3 {

class Timer {
    public:
        Timer (const std::string& caption, bool _start = true);

        void start();

        void stopAndPrint();

        void stop();

        void print();

        double delay();

    private:
        std::string caption;
        std::chrono::high_resolution_clock clock;
        std::chrono::high_resolution_clock::time_point begin, end;
        bool isStopped;
};

}

#include "timer.tpp"

#endif //CG3_TIMER_H
