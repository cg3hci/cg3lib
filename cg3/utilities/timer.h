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

/**
 * @ingroup cg3core
 * @brief The Timer class
 */
class Timer
{
public:
    Timer(bool _start = true);

	Timer(const char* caption, bool _start = true);

	Timer(const std::string& caption, bool _start = true);

    void start();

    void stopAndPrint();

    void stop();

    void print();

    double delay();

private:
    std::string caption;
    std::chrono::high_resolution_clock::time_point begin, end;
    bool isStopped;
};

} //namespace cg3

#include "timer.cpp"

#endif //CG3_TIMER_H
