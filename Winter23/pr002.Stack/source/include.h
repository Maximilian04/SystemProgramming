#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;
using prClock = chrono::steady_clock;
using prTimer = chrono::time_point<prClock>;

random_device randGenerator("fo");
// mt19937_64 randGen(randGenerator());
// uniform_int_distribution<> prRand(1, 2);

#define LOG(msg)                            \
    ofstream file("log.txt", ios::app);      \
    file << TESTNAME << " : " << msg << endl; \
    file.close();

#define ERROR(msg) {        \
    LOG("ERRROR!!! " << msg) \
    return 1;                 \
}

#define TIMEPOINT(name) prTimer name(prClock::now())