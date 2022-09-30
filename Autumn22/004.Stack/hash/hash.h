/**
 * @file hash.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Hash function
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

typedef uint32_t Hash_t;

const Hash_t nullhash = 0;

Hash_t getHash(Hash_t hash, void* ptr, size_t size);
Hash_t getHash(void* begin, size_t size);
Hash_t getHash(void* begin, void* end);

