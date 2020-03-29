#include<iostream>
#include<string>
#include<random>

#include "bloomfilter.h"

using namespace std;

string random_string(int len){
    string output_string(len, 'a');

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        output_string[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return output_string;
}

int main(){
    int n_false_positives = 0;
    int n_inserted_strings = 300;
    int n_tested_strings = 10000;
    int string_length = 10;

    vector<string> test_strings_in;
    vector<string> test_strings_not_in;
    Bloomfilter test_filter(1000000, 2000);

    // Generate random strings for the bloom filter.
    for(int idx=0; idx<n_inserted_strings; ++idx){
        test_strings_in.push_back(random_string(string_length));
    }

     for(int idx=0; idx<n_tested_strings; ++idx){
        test_strings_not_in.push_back(random_string(string_length));
    }

    // Add all test elements to the bloom filter
    for(auto elem: test_strings_in){
        test_filter.add(elem);
    }

    // Check for some other strings that are not in the bloom filter.
     for(auto elem: test_strings_not_in){
        if(test_filter.is_in(elem) == true){
            n_false_positives++;
        }
    }
    cout << n_false_positives << endl;
    cout << "The false positive rate is " << (static_cast<double>(n_false_positives) / static_cast<double>(n_tested_strings)) << endl;
    return 0;
}