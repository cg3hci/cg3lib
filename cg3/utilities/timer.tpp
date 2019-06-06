/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "timer.h"

namespace cg3 {

inline Timer::Timer(bool _start) :
    caption("Timer"),
    isStopped(false)
{
    if (_start)
        start();
}

/**
 * @brief Timer::Timer
 * @param caption
 * @param _start
 */
inline Timer::Timer (const char* caption, bool _start) :
	caption(caption),
	isStopped(false)
{
	if (_start)
		start();
}

/**
 * @brief Timer::Timer
 * @param caption
 * @param _start
 */
inline Timer::Timer (const std::string& caption, bool _start) :
    caption(caption),
    isStopped(false)
{
    if (_start)
        start();
}

/**
 * @brief Timer::start
 */
inline void Timer::start()
{
    begin = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Timer::stopAndPrint
 */
inline void Timer::stopAndPrint()
{
    stop();
    print();
}

/**
 * @brief Timer::stop
 */
inline void Timer::stop()
{
    end = std::chrono::high_resolution_clock::now();
    isStopped = true;
}

/**
 * @brief Timer::print
 */
inline void Timer::print ()
{
    double secs = delay();
	int mins = (int)secs / 60;
	if (mins == 0)
		std::cout << "[" << secs << " secs]\t" << caption << std::endl;
	else {
		secs = secs - mins * 60;
		int hours = mins / 60;
		if (hours == 0)
			std::cout << "[" << mins << " mins; " << secs << " secs]\t" << caption << std::endl;
		else {
			mins = mins - hours * 60;
			std::cout << "[" << hours << " hours; " << mins << " mins; " << secs << " secs]\t" << caption << std::endl;
		}
	}
}

/**
 * @brief Timer::delay
 * @return
 */
inline double Timer::delay()
{
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

} //namespace cg3
