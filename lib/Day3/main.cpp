#include "lib.h"

void part1(){
    V<string> lines;
    int64_t total = 0;
    for(string line; getline(cin,line);){
        lines += line;
        auto sub1 = line.substr(0,line.size()/2);
        auto sub2 = line.substr(line.size()/2);

        for(auto c : sub1){
            if(sub2.find(c) != string::npos){
                if(islower(c)){
                    total+=(c-'a'+1);
                } else {
                    total+=(c-'A'+27);
                }
                break;
            }
        }
    }

    auto view = lines | ranges::views::transform([](auto&& line){
        return std::pair<string,string>{line.substr(0,line.size()/2),line.substr(line.size()/2)};
    })
    | ranges::views::transform([](const auto &pair) {
        return std::pair<set<char>,set<char>>(set(pair.first.begin(),pair.first.end()), set(pair.second.begin(),pair.second.end()));
    })
    | ranges::views::transform([](const auto& p){
        set<char> out;
        set_intersection(p.first.begin(),p.first.end(),p.second.begin(),p.second.end(),inserter(out,out.begin()));
        assert(out.size()==1);
        return *out.begin();
    })
    | ranges::views::transform([](const auto& c){
        if(islower(c)){
            return c-'a'+1;
        }
        return c-'A'+27;
    });

    auto total2 = accumulate(view.begin(), view.end(),0LL, std::plus{});

    cout << total << endl;
    cout << total2 << endl;
}

void part2(){
    std::vector<string> lines;
    int64_t total = 0;
    size_t idx = 0;
    set<char> elements;
    for(string line;getline(cin,line);){
        lines += line;
        set<char> current;
        for (char c : line){
            current += c;
        }
        if(idx%3==0){
            elements = current;
        } else {
            set<char> out;
            std::set_intersection(elements.begin(), elements.end(), current.begin(), current.end()
                                  , std::inserter(out,out.begin()));

            elements = out;
        }

        if(idx%3==2){
            assert(elements.size()==1);
            for(auto c : elements){
                if(islower(c)){
                    total += (c-'a'+1);
                } else {
                    total +=(c-'A'+27);
                }
            }
        }

        ++idx;
    }

    cout << total << endl;
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