#include "SizeGen.h"

SizeGen::SizeGen(): randGenerator("foo"), sizeList() {
    sizeList.push_back(0);
}

size_t SizeGen::getSize() {
    return sizeList.back();
}

void SizeGen::newSize() {
    size_t size = 0;

    if (getSize() == 0) {
        size = (size_t)1e3;
    } else if (getSize() <= 3e4) {
        size = getSize() + (size_t)1e3;
    } else if (getSize() <= 1e5) {
        size = (size_t)1e5;
    } else {
        size = getSize() + (size_t)1e5;
    }

    sizeList.push_back(size);
}

size_t SizeGen::getStoredSize() {
    return sizeList.front();
}

void SizeGen::nextStoredSize() {
    sizeList.pop_front();
}
