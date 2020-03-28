#ifndef _BLOOMFILTER_H_
#define _BLOOMFILTER_H_

#include<string>
#include<vector>
#include<math.h>

#include "hash.h"

using namespace std;

class Bloomfilter{
    public:
        // The bloomfilter has two inputs. The length of its signature arrays and the number of hash functions that is used.
        Bloomfilter(unsigned int n_bits, unsigned int n_hash_functions);
        
        // Check whether an element is in the filter.
        bool is_in(string candidate);

        // Add a candidate to the set.
        void add(string candidate);

        // Based on the number of hash functions and the number of bits the false positive ratio can be computed.
        double false_positive_probability();

    private:
        int n_bits;
        int n_hash_functions;
        vector<bool> signature;
        vector<RandomHash> hash_functions;
};

#endif