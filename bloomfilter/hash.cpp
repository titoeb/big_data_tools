#include "hash.h"

// Specialising the Murmur3 hash function to be used based on c++ strings.
uint64_t string_hash(string to_hash, unsigned int seed, uint64_t bin_size=numeric_limits<uint64_t>::max() ){
    uint64_t buffer[2];
    MurmurHash3_x86_32(to_hash.c_str(), to_hash.length(), seed, &buffer[0]);

    return ((buffer[0] % (numeric_limits<uint64_t>::max() / 2)) + (buffer[1] % (numeric_limits<uint64_t>::max() / 2))) % bin_size;
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
unsigned long int RandomHash::hash(string input){
    return static_cast<unsigned long int> (string_hash(input, this->seed));
}
