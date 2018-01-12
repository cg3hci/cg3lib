/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "timer.h"

namespace cg3 {

inline Timer::Timer (const std::string& caption, bool _start) : caption(caption), isStopped(false) {
    if (_start)
        start();
}

inline void Timer::start() {
    begin = std::chrono::high_resolution_clock::now();
}

inline void Timer::stopAndPrint() {
    stop();
    print();
}

inline void Timer::stop() {
    end = std::chrono::high_resolution_clock::now();
    isStopped = true;
}

inline void Timer::print () {
    double secs = delay();
    std::cout << "[" << secs << " secs]\t" << caption << std::endl;
}

inline double Timer::delay() {
    double secs;
    if (isStopped) {
        secs = (double) (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())/1000000;
    }
    else {
        std::chrono::high_resolution_clock::time_point s = std::chrono::high_resolution_clock::now();
        secs = (double) (std::chrono::duration_cast<std::chrono::microseconds>(s - begin).count())/1000000;
    }
    return secs;
}

}
