#include <algorithm>
#include "lib.h"

using namespace std;
void part1(){
    std::vector<std::vector<int64_t>> elfs;
    std::vector<int64_t> sums;

    size_t cur_idx = 0;
    int64_t cur_sum = 0;
    int64_t cur_max = 0;
    elfs.push_back({});
    sums.push_back(0);

    for(string line;getline(cin,line);){
        if(line.empty()){
            cur_max = max(cur_max,cur_sum);
            ++cur_idx;
            cur_sum = 0;
            elfs.push_back({});
            sums.push_back(0);
            continue;
        }

        int64_t val = atoi(line.c_str());
        elfs[cur_idx].push_back(val);
        sums[cur_idx] += val;
        cur_sum += val;
    }

    cout << cur_max << endl;
}

void part2(){
    std::vector<std::vector<int64_t>> elfs;
    std::vector<int64_t> sums;

    size_t cur_idx = 0;
    int64_t cur_sum = 0;
    int64_t cur_max = 0;
    elfs.push_back({});
    sums.push_back(0);

    for(string line;getline(cin,line);){
        if(line.empty()){
            cur_max = max(cur_max,cur_sum);
            ++cur_idx;
            cur_sum = 0;
            elfs.push_back({});
            sums.push_back(0);
            continue;
        }

        int64_t val = atoi(line.c_str());
        elfs[cur_idx].push_back(val);
        sums[cur_idx] += val;
        cur_sum += val;
    }

    std::sort(sums.begin(), sums.end(), std::greater<>());

    cout << std::accumulate(sums.begin(),std::next(sums.begin(),3),0,std::plus<>()) << endl;
}

int main(int argc, char* argv[]){
    if(std::string(argv[1])=="--one"){
        part1();
    }else if(std::string(argv[1])=="--two"){
        part2();
    } else{
        std::cout << "Wrong usage!" << std::endl;
    }
}