#ifndef _DGIM_H_
#define _DGIM_H_

#include<list>
#include<iostream>
#include <iterator>

using namespace std;

inline unsigned min_val(unsigned int candidate1, unsigned int candidate2);

inline unsigned int max_val(unsigned int candidate1, unsigned int candidate2);

class Bucket{
    public:
        Bucket(unsigned int size, unsigned int timestamp):size(size), timestamp(timestamp){}
        
        unsigned int get_size() const;
        unsigned int get_time_stamp() const;

    private:
        unsigned int size;
        unsigned int timestamp;
};

class DGIM{
    public:

        // Add a new value to the DGIM class.   
        DGIM(unsigned int N, int count_val):N(N),count_val(count_val), current_time(0){}

        // Print the current list out :)
        void add(int val);

        // Get the count for the last min(N, window_size) elements.
        unsigned int get_count(int window_size);

        void print();

    private:
        // Check wether any bucket of a specific size has three occurences.
        // Also check whether the last bucket is still relevant.
        void check_buckets();

        // The length of the relevant time-window.
        unsigned int N;

        // The number in the stream that is relevant.
        int count_val;

        // The current time in the stream.
        int current_time;

        // List containing all the buckets.
        list<Bucket> buckets;
};

#endif