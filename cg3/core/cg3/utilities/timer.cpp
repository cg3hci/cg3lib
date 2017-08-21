#include "timer.h"

namespace cg3 {

inline Timer::Timer (const std::string& caption, bool start_) : caption(caption), isStopped(false) {
    if (start_)
        start();
}

inline void Timer::start(){
    gettimeofday(&begin, NULL);
}

inline void Timer::stopAndPrint() {
    gettimeofday(&end, NULL);
    isStopped = true;
    double secs =
        (end.tv_sec - begin.tv_sec) +
        ((end.tv_usec - begin.tv_usec)/1000000.0);

    std::cout << "[" << secs << " secs]\t" << caption << std::endl;
}

inline void Timer::stop() {
    gettimeofday(&end, NULL);
    isStopped = true;
}

inline void Timer::print () {
    double secs;
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

    std::cout << "[" << secs << " secs]\t" << caption << std::endl;
}

inline double Timer::delay() {
    double secs;
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

    return secs;
}

}
