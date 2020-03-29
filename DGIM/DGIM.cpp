#include "DGIM.h"



// min function
inline unsigned min_val(unsigned int candidate1, unsigned int candidate2){
    if(candidate1 < candidate2) return candidate1;
    return candidate2;
}


// max function
inline unsigned int max_val(unsigned int candidate1, unsigned int candidate2){
    if(candidate1 < candidate2) return candidate2;
    return candidate1;
}

// Getter functions for Bucket class.
unsigned int Bucket::get_size() const{
        return this->size;
}
unsigned int Bucket::get_time_stamp() const{
            return this->timestamp;
}

// Functions of the DGIM class.
// Add a new value to the DGIM class.
void DGIM::add(int val){
        
    // If the value is the relevant value, then add it to the list.
    if(val == this->count_val){
        this->buckets.push_front(Bucket(1, this->current_time));
    }

    // Finally Update the buckets.
    // If there are three buckets of any size, they will be replaced.
    this->check_buckets();

    // time goes on ...
    ++this->current_time;
}

// Print the current list out :)
void DGIM::print(){
    cout << "[";

    for(auto bucket = this->buckets.begin(); bucket != this->buckets.end(); ++bucket){
        
        // Print bucket value and time stamp
        cout << "(" << bucket->get_size() << ", " << bucket->get_time_stamp() << ")";
        if (next(bucket) != this->buckets.end()){
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

// Get the count for the last min(N, window_size) elements.
unsigned int DGIM::get_count(int window_size){
    window_size = min_val(window_size, this->N);
    unsigned int count = 0;
    for(auto bucket: this->buckets){
        if(this->current_time - bucket.get_time_stamp() <= window_size){
            count += bucket.get_size();
        } else {
            break;
        }
    }
    return count;
}

// Check the list
 void DGIM::check_buckets(){
    if(this->buckets.size() > 2){
        auto last_last_bucket = this->buckets.begin();
        auto last_bucket = next(this->buckets.begin());
        auto bucket = next(next(this->buckets.begin()));

        while(true){
            if((last_last_bucket->get_size() == last_bucket->get_size()) && (last_bucket->get_size() == bucket->get_size())){
                
                Bucket tmp = Bucket(last_bucket->get_size() + bucket->get_size(), max_val(last_bucket->get_time_stamp(), bucket->get_time_stamp()));
                
                this->buckets.insert(next(bucket), tmp);
                this->buckets.erase(last_bucket);
                this->buckets.erase(bucket); 

                last_last_bucket = next(last_last_bucket);
                if (last_last_bucket == this->buckets.end()) break;
                
                last_bucket = next(last_last_bucket);
                if (last_bucket == this->buckets.end()) break;
                
                bucket = next(last_bucket);
                if (bucket == this->buckets.end()) break;

            } else{
                break;
            }
        }
    }

    // Test whether last bucket is not out of the time-window.
    auto last_bucket = --(this->buckets.end());
    if (this->current_time - last_bucket->get_time_stamp() >= this->N){
        this->buckets.erase(last_bucket);
    }
}