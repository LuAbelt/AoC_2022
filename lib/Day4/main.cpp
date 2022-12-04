#include "lib.h"

void part1(){
    i64 cnt = 0;
    for(string line; getline(cin,line);){
        string sub1 = line.substr(0,line.find(","));
        string sub2 = line.substr(line.find(",")+1);

        auto begin1 = atoi(sub1.substr(0,sub1.find("-")).c_str());
        auto end1 = atoi(sub1.substr(sub1.find("-")+1).c_str());

        auto begin2 = atoi(sub2.substr(0,sub2.find("-")).c_str());
        auto end2 = atoi(sub2.substr(sub2.find("-")+1).c_str());

        if((begin1<=begin2 && end1>=end2)||(begin2<=begin1 && end2>=end1)){
            ++cnt;
        }
    }
    cout << cnt << endl;
}

void part2(){
    i64 cnt = 0;
    for(string line; getline(cin,line);){
        string sub1 = line.substr(0,line.find(","));
        string sub2 = line.substr(line.find(",")+1);

        auto begin1 = atoi(sub1.substr(0,sub1.find("-")).c_str());
        auto end1 = atoi(sub1.substr(sub1.find("-")+1).c_str());

        auto begin2 = atoi(sub2.substr(0,sub2.find("-")).c_str());
        auto end2 = atoi(sub2.substr(sub2.find("-")+1).c_str());

        if((begin1<=begin2 && end1>=begin2)||(begin2<=begin1 && end2>=begin1)){
            ++cnt;
        }
    }
    cout << cnt << endl;
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