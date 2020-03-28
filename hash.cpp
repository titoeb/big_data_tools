#include "hash.h"

// Specialising the Murmur3 hash function to be used based on c++ strings.
unsigned int string_hash(string to_hash, unsigned int seed){
    unsigned int result;
    MurmurHash3_x86_32(to_hash.c_str(), to_hash.length(), seed, &result);
    return result;
}

// Empty constructor, sample a random seed in constructor.
RandomHash::RandomHash(){
    // Create a random device that generates os-provided random numbers
    random_device random_device;

    // Initiallize the mersenne-twister with the os-provided random number.
    mt19937 generator(random_device());

    // Create a sample that sample a random number from the support of unsigned int.
    uniform_int_distribution<unsigned int> random_unsigned_integer(0, numeric_limits<unsigned int>::max());

    // Finally, sample the random seed.
    this->seed = random_unsigned_integer(generator);
};

// return the hash value based on the input string.
// hash value is computed using 128 bit murmurhash3 based on the internal seed value.
unsigned int  RandomHash::hash(string input){
    return string_hash(input, this->seed);
}
