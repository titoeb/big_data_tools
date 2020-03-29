#include "lcs.h"


unsigned int edit_distance(string first, string second){
    return first.length() + second.length() + 2 * least_common_subsequence(first, second);
}

unsigned int least_common_subsequence(string first, string second){
    if(first.length() > 0 && second.length() > 0){
        vector< vector<unsigned int>> length(first.length() + 1, vector<unsigned int>(second.length() + 1));

        for(int idx_first=0; idx_first <= first.length(); ++idx_first){
            for(int idx_second=0; idx_second <= second.length(); ++idx_second){

                if((idx_first == 0) || (idx_second == 0)){
                    // There is no subsequence
                    length[idx_first][idx_second] = 0;
                } else {
                    if (first[idx_first-1] == second[idx_second-1]){
                        // If they matched add 1 to the past longest common subsequence.
                        length[idx_first][idx_second] = 1 + length[idx_first - 1][idx_second - 1];
                    } else {
                        length[idx_first][idx_second] = max(length[idx_first][idx_second - 1], length[idx_first-1][idx_second]);
                    }
                }
            }
        }
        return length[first.length() - 1][second.length() -1];
    } else{
            return 0;
    }
}
