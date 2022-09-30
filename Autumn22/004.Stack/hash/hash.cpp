#include <string.h>

#include "hash.h"

Hash_t updateHash(Hash_t* hash, Hash_t add);

Hash_t updateHash(Hash_t* hash, Hash_t add) {
    *hash += add;
    return *hash;
}

Hash_t getHash(Hash_t hash, void* ptr, size_t size) {
    size_t intSize = size / sizeof(Hash_t);
    for (size_t done = 0; done < intSize; done++) {
        updateHash(&hash, *((Hash_t*)ptr + done));
    }

    if (intSize * sizeof(Hash_t) != size) {
        Hash_t temp = 0;
        memcpy(&temp, (Hash_t*)ptr + intSize, intSize * sizeof(Hash_t) - size);
        updateHash(&hash, temp);
    }

    return hash;
}

Hash_t getHash(void* begin, size_t size) {
    return getHash(0, begin, size);
}

Hash_t getHash(void* begin, void* end) {
    return getHash(begin, (uint8_t*)end - (uint8_t*)begin);
}
