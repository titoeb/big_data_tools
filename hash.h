#ifndef _HASH_H_
#define _HASH_H_

#include <string>
#include <random>
#include <limits>

#include "MurmurHash3.h"
using namespace std;

// Specialising the Murmur3 hash function to be used based on c++ strings.
unsigned int string_hash(string to_hash, unsigned int seed);

// Creating a class for hash functions with a random seed.
class RandomHash{
    public:
        // Empty constructor, sample a random seed in constructor.
        RandomHash();

        // Construction with a given seed.
        RandomHash(unsigned int seed): seed(seed){};

        // return the hash value based on the input string.
        // hash value is computed using 128 bit murmurhash3 based on the internal seed value.
        unsigned int hash(string input);

    private:
        unsigned int seed;
};

#endif