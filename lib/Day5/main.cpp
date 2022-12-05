#include "lib.h"

void part1(){
    string line;
    V<deque<char>> towers;
    getline(cin,line);
    towers.resize((line.length()/4)+1,{});
    for(size_t i = 1;i<line.length();i+=4){
        auto idx = i/4;
        if(line[i]!=' '){
            towers[idx].push_back(line[i]);
        }
    }
    getline(cin,line);
    do{
        for(size_t i = 1;i<line.length();i+=4){
            if((line.length()/4)+1>towers.size()){
                towers.resize((line.length()/4)+1);
            }
            auto idx = i/4;
            if(line[i]!=' '){
                towers[idx].push_back(line[i]);
            }
        }
        getline(cin,line);
    }while(line[1]!='1');

    // Skip empty line
    getline(cin,line);

    for(;getline(cin,line);){
        auto sub1 = line.substr(0,line.find("from"));
        auto sub2 = line.substr(line.find("from")+5);

        size_t amount = atoi(sub1.substr(5).c_str());

        size_t source = atoi(sub2.substr(0,sub2.find_first_of(' ')).c_str());
        size_t target = atoi(sub2.substr(sub2.find_last_of(' ')).c_str());
        IO::print(amount,source,target);
        source--;
        target--;
        for(size_t i = 0;i<amount;++i){
            char c = towers[source].front(); towers[source].pop_front();
            towers[target].push_front(c);
        }
    }

    for(const auto& t : towers){
        if(!t.empty()){
            cout << t.front()  ;
        }
    }
}

void part2(){
    string line;
    V<deque<char>> towers;
    getline(cin,line);
    towers.resize((line.length()/4)+1,{});
    for(size_t i = 1;i<line.length();i+=4){
        auto idx = i/4;
        if(line[i]!=' '){
            towers[idx].push_back(line[i]);
        }
    }
    getline(cin,line);
    do{
        for(size_t i = 1;i<line.length();i+=4){
            if((line.length()/4)+1>towers.size()){
                towers.resize((line.length()/4)+1);
            }
            auto idx = i/4;
            if(line[i]!=' '){
                towers[idx].push_back(line[i]);
            }
        }
        getline(cin,line);
    }while(line[1]!='1');

    // Skip empty line
    getline(cin,line);

    for(;getline(cin,line);){
        auto sub1 = line.substr(0,line.find("from"));
        auto sub2 = line.substr(line.find("from")+5);

        size_t amount = atoi(sub1.substr(5).c_str());

        size_t source = atoi(sub2.substr(0,sub2.find_first_of(' ')).c_str());
        size_t target = atoi(sub2.substr(sub2.find_last_of(' ')).c_str());
        IO::print(amount,source,target);
        source--;
        target--;
        deque<char> temp;
        for(size_t i = 0;i<amount;++i){
            char c = towers[source].front(); towers[source].pop_front();
            temp.push_front(c);
        }

        for(auto c : temp){
            towers[target].push_front(c);
        }
    }

    for(const auto& t : towers){
        if(!t.empty()){
            cout << t.front()  ;
        }
    }
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