#include "timer.h"

namespace cg3 {

inline Timer::Timer (const std::string& caption, bool start_) : caption(caption), isStopped(false) {
    if (start_)
        start();
}

inline void Timer::start(){
    #ifdef _WIN32
    #else
    gettimeofday(&begin, NULL);
    #endif
}

inline void Timer::stopAndPrint() {
    #ifdef _WIN32
    isStopped = true;
    double secs;
    #else
    gettimeofday(&end, NULL);
    isStopped = true;
    double secs =
        (end.tv_sec - begin.tv_sec) +
        ((end.tv_usec - begin.tv_usec)/1000000.0);
    #endif
    std::cout << "[" << secs << " secs]\t" << caption << std::endl;
}

inline void Timer::stop() {
    #ifdef _WIN32
    isStopped = true;
    #else
    gettimeofday(&end, NULL);
    isStopped = true;
    #endif
}

inline void Timer::print () {
    double secs;
    #ifdef _WIN32
    #else
    if (isStopped)
        secs =
            (end.tv_sec - begin.tv_sec) +
            ((end.tv_usec - begin.tv_usec)/1000000.0);
    else {
        timeval s;
        gettimeofday(&s, NULL);
        secs =
            (s.tv_sec - begin.tv_sec) +
            ((s.tv_usec - begin.tv_usec)/1000000.0);
    }
    #endif

    std::cout << "[" << secs << " secs]\t" << caption << std::endl;
}

inline double Timer::delay() {
    double secs;
    #ifdef _WIN32
    #else
    if (isStopped)
        secs =
            (end.tv_sec - begin.tv_sec) +
            ((end.tv_usec - begin.tv_usec)/1000000.0);
    else {
        timeval s;
        gettimeofday(&s, NULL);
        secs =
            (s.tv_sec - begin.tv_sec) +
            ((s.tv_usec - begin.tv_usec)/1000000.0);
    }
    #endif
    return secs;
}

}
