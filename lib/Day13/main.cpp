#include "lib.h"

void part1(){
    i64 total = 0;
    auto lines = IO::fromCin();
    for(st idx = 0;idx<lines.size();idx+=3){
        string line1 = lines[idx];
        string line2 = lines[idx+1];

        auto p1 = data_structures::parseRecList<i64>(line1);
        auto p2 = data_structures::parseRecList<i64>(line2);

        auto cmpRes = *p1 <=> *p2;

        if(cmpRes<0){
            //IO::print("Correct order for idx ",(idx/3)+1);
            total += (idx/3)+1;
        }
    }

    IO::print(total);
}

void part2(){
    i64 total = 0;
# if 0
    auto lines = IO::fromCin();

    using ListTy = data_structures::RecursiveList<i64>;
    using namespace data_structures;
    V<shared_ptr<ListTy>> packages;

    packages.reserve(lines.size()+2);

    packages.emplace_back(parseRecList<i64>(string("[[2]]")));
    packages.emplace_back(parseRecList<i64>(string("[[6]]")));
    for(st idx = 0;idx<lines.size();idx+=3){
        string line1 = lines[idx];
        string line2 = lines[idx+1];

        packages += parseRecList(line1);
        packages += parseRecList(line2);
    }

    sort(packages.begin(), packages.end(),[](auto lhs, auto rhs){
        return (*lhs <=> *rhs)<0;
    });

    total =1;
    for(st idx = 0; idx<packages.size();++idx){
        if(packages[idx]->toString() == "[[2]]" || packages[idx]->toString() =="[[6]]"){
            total *=(idx+1);
        }
    }
#else
    using ListTy = data_structures::RecursiveList<i64>;
    using namespace data_structures;

    i64 idx1 = 1;
    i64 idx2 = 2;

    auto item2 = parseRecList(string("[[2]]"));
    auto item6 = parseRecList(string("[[6]]"));

    string line;
    while(getline(cin,line)){
        if(line.empty()){
            continue;
        }
        auto item = parseRecList(line);

        if((*item<=>*item2)<0){
            ++idx1;
        }

        if((*item<=>*item6)<0){
            ++idx2;
        }
    }

    IO::print(idx1*idx2);
#endif
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