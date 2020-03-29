#include "bloomfilter.h"

// The bloomfilter has two inputs. The length of its signature arrays and the number of hash functions that is used.
Bloomfilter::Bloomfilter(unsigned int n_bits, unsigned int n_hash_functions):n_bits(n_bits), n_hash_functions(n_hash_functions), signature(n_bits, false), hash_functions(n_hash_functions){
    // What is left to to do is to assign the random hash functions
    for(auto hash_class: this->hash_functions){

        // Internally, the seed is randomly created.
        hash_class = RandomHash();

        // Question:
            // -> For each RandomHash object the random device, mersenne-twister ... is created. Is the performance too bad for 
            // really a high number of hash functions?
    }
}

// Based on the number of hash functions and the number of bits the false positive ratio can be computed.
double Bloomfilter::false_positive_probability(){
    return pow(1.0 - pow(1.0 - (1.0 / n_bits), this->n_hash_functions * this->n_bits), this->n_hash_functions);
}

// Check whether an element is in the filter.
bool Bloomfilter::is_in(string candidate){
    // Iterator over all hash functions
    // Compute the bucket the hash function maps the candidate to.
    // Check if the bit in the signature is true.
    // If it is false, we know the element is not in the bloomfilter and return false
    // else continue iteration
    // If we checked all hash functions and all entries were true, the candiate may be in the bloomfilter.
    int idx = 0;
    for(auto hash_class: this->hash_functions){
        if(this->signature[hash_class.hash(candidate) % this->n_bits] == false){
            return false;
        }
    }
    return true;
}

// Add a candidate to the set.
void Bloomfilter::add(string candidate){
    // Iterate over all hash functions.
    // Compute the bucket that it maps the input to.
    // Set the according entry to true.
    int idx = 0;
    for(auto hash_class: this->hash_functions){
        this->signature[hash_class.hash(candidate) % this->n_bits] = true;
        ++idx;
    }
}