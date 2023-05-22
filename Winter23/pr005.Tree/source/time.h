#ifndef TIME_H
#define TIME_H

#include <chrono>

using prClock = std::chrono::steady_clock;
using prTimer = std::chrono::time_point<prClock>;

#define TIMEPOINT(name) prTimer name(prClock::now())

#define GETDURATION(tpBegin, tpEnd) std::chrono::duration_cast<chrono::milliseconds>(tpEnd - tpBegin).count()

#endif // TIME_H
