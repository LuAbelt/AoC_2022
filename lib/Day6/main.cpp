#include "lib.h"

void part1(){

    for(string line;getline(cin,line);){
        for(size_t idx = 4;idx<line.length();++idx){
            set<char> chars{};

            for(size_t idx2 = idx-4;idx2<idx;++idx2){
                chars += line[idx2];
            }

            if(chars.size()==4){
                cout << idx << endl;
                break;
            }
            chars.clear();
        }
    }
}

void part2(){
    for(string line;getline(cin,line);){
        for(size_t idx = 14;idx<line.length();++idx){
            set<char> chars{};

            for(size_t idx2 = idx-14;idx2<idx;++idx2){
                chars += line[idx2];
            }

            if(chars.size()==14){
                cout << idx << endl;
                break;
            }
            chars.clear();
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