#include<iostream>
#include<vector>

#include"DGIM.h"

int main(){
    //vector<int> test{0, 1, 1, 0, 1, 1, 0 ,1, 1, 1, 0, 0, 1, 1, 0};
    vector<int> test{0, 1, 1, 0, 1, 1, 0 ,1, 1, 1, 0, 0, 1, 1, 0};

    DGIM test_DGIM(8, 1);

    for(auto elem: test){
        test_DGIM.add(elem);
        test_DGIM.print();
        cout << "Count: " << test_DGIM.get_count(8) << endl;
    }
}