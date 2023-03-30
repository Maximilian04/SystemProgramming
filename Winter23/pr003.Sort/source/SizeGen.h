#ifndef SIZEGEN_H
#define SIZEGEN_H

#include <random>
#include <deque>

using namespace std;

class SizeGen {
public:
    SizeGen();

    size_t getSize();
    void newSize();

    size_t getStoredSize();
    void nextStoredSize();

private:
    random_device randGenerator;
    deque<size_t> sizeList;
};

#endif // SIZEGEN_H
