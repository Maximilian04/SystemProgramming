#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <Windows.h>

using namespace std;
using prClock = chrono::steady_clock;
using prTimer = chrono::time_point<prClock>;

#ifndef TESTNAME
#define TESTNAME "testname"
#endif

#include "SizeGen.h"

random_device randGenerator("fo");
// mt19937_64 randGen(randGenerator());
// uniform_int_distribution<> prRand(1, 2);

#define LOG(msg)                               \
    {                                           \
        ofstream file("logNames.txt", ios::app); \
        file << TESTNAME << endl;                 \
        file.close();                              \
        file.open("log.txt", ios::app);             \
        file <<  msg << endl;                        \
        file.close();                                 \
    }

#define LOGERROR(msg) {        \
    LOG("ERRROR!!! " << msg) \
    return 1;                 \
}

#define TIMEPOINT(name) prTimer name(prClock::now())

#define LOGRESULT \
    LOG(chrono::duration_cast<chrono::milliseconds>(tpEnd - tpBegin).count() << " ms");

#define SCAN_ARR                        \
    size_t size = 0;                     \
    int* arr = nullptr;                   \
    {                                      \
        ifstream input("arr.txt");          \
                                             \
        input >> size;                        \
        arr = (int*)calloc(size, sizeof(int)); \
        if (!arr) {                             \
            LOGERROR("MEM ERR");                 \
            return 1;                             \
        }                                          \
                                                    \
        for (size_t i = 0; i < size; ++i) {          \
            input >> arr[i];                          \
        }                                              \
                                                        \
        input.close();                                   \
    }                                                     \
