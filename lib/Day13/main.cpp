#include "lib.h"

class Packet {
    V<shared_ptr<Packet>> contents;
    std::optional<i64> value;

public:
    Packet(i64 val)
    :value(val)
    {}

    Packet(V<shared_ptr<Packet>> &content)
    :contents(content)
    {}

    void print(st indent = 0) const {
        string prefix ="";
        for(st i=0;i<indent;++i){
            prefix+="\t";
        }

        if(value.has_value()){
            cout << prefix << value.value();
            return;
        }

        cout << prefix << "[" << endl;
        for(auto& item : contents){
            item->print(indent+1);
            cout << "," <<endl;
        }
        cout << prefix << "]";

        if(indent==0){
            cout << endl;
        }
    }

    string toString() const {
        string r;
        if(value.has_value()){
            r += to_string(value.value());
            return r;
        }

        r += "[";
        for(auto& item : contents){
            r+=item->toString();
            if(item !=contents.back() ) r+= ",";
        }
        r+= "]";

        return r;
    }

    void printFlat(st indent = 0) const {
        cout << toString() << endl;
    }

    auto operator<=>(Packet const& Other) const{
        if(value.has_value() && Other.value.has_value()){
            return value.value() <=> Other.value.value();
        }

        if(value.has_value()){
            if(Other.contents.size()>0){
                auto cmpRes = *this <=> *Other.contents[0];
                if(cmpRes == 0 && Other.contents.size()>1) {
                    return strong_ordering::less;
                }
                return cmpRes;
            } else {
                return strong_ordering::greater;
            }
        }

        if(Other.value.has_value()){
            if(contents.size()>0){
                auto cmpRes = *contents[0] <=> Other;
                if(cmpRes == 0 && contents.size()>1){
                    return strong_ordering::greater;
                }
                return cmpRes;
            } else {
                return strong_ordering::less;
            }
        }

        for(st idx = 0;idx<contents.size() && idx<Other.contents.size();++idx){
            auto compRes = *contents[idx] <=> *Other.contents[idx];
            if(compRes!=0) {
                return compRes;
            }
        }

        return contents.size() <=> Other.contents.size();
    }

    auto compareTo(const Packet& Other, st indent = 0) const{
#if 0
        string prefix ="";
        for(st i=0;i<indent;++i){
            prefix+="\t";
        }
        cout << prefix;
        cout << "- Compare ";
        printflat();
        cout << " vs ";
        Other.printflat();
        cout << endl;
#endif
        if(value.has_value() && Other.value.has_value()){
            return value.value() <=> Other.value.value();
        }

        if(value.has_value()){
            if(Other.contents.size()>0){
                auto cmpRes = this->compareTo(*Other.contents[0],indent+1);
                if(cmpRes == 0 && Other.contents.size()>1) {
                    return strong_ordering::less;
                }
                return cmpRes;
            } else {
                return strong_ordering::greater;
            }
        }

        if(Other.value.has_value()){
            if(contents.size()>0){
                auto cmpRes = contents[0]->compareTo(Other,indent+1);
                if(cmpRes == 0 && contents.size()>1){
                    return strong_ordering::greater;
                }
                return cmpRes;
            } else {
                return strong_ordering::less;
            }
        }

        for(st idx = 0;idx<contents.size() && idx<Other.contents.size();++idx){
            auto compRes = contents[idx]->compareTo(*Other.contents[idx],indent+1);
            if(compRes!=0) {
                return compRes;
            }
        }

        return contents.size() <=> Other.contents.size();
    }
};

shared_ptr<Packet> parsePacket(string &input, st &idx) {
        V<shared_ptr<Packet>> contents;
        while(idx < input.size() && input[idx]!=']'){
            if(isdigit(input[idx])){
                i64 value = 0;
                while(isdigit(input[idx])){
                    value *= 10;
                    value += input[idx]-'0';
                    idx++;
                }
                contents.emplace_back(make_shared<Packet>(value));
            }

            if(input[idx]=='['){
                idx+=1;
                contents.emplace_back(parsePacket(input,idx));
            }

            if(input[idx]==','){
                ++idx;
            }
        }
        ++idx;

        return make_shared<Packet>(contents);
}

void part1(){
    i64 total = 0;
    auto lines = IO::fromCin();
    for(st idx = 0;idx<lines.size();idx+=3){
        string line1 = lines[idx];
        string line2 = lines[idx+1];

        st i = 1;
        auto p1 = parsePacket(line1,i);
        i=1;
        auto p2 = parsePacket(line2,i);

        auto cmpRes = *p1 <=> *p2;

        if(cmpRes<0){
            //IO::print("Correct order for idx ",(idx/3)+1);
            total += (idx/3)+1;
        }
    }

    IO::print(total);
}

shared_ptr<Packet> parsePacket(string input){
    st i = 1;
    return parsePacket(input,i);
}

void part2(){
    i64 total = 0;
    auto lines = IO::fromCin();

    V<shared_ptr<Packet>> packages;

    packages.reserve(lines.size()+2);

    packages.emplace_back(parsePacket(string("[[2]]")));
    packages.emplace_back(parsePacket(string("[[6]]")));
    for(st idx = 0;idx<lines.size();idx+=3){
        string line1 = lines[idx];
        string line2 = lines[idx+1];

        packages += parsePacket(line1);
        packages += parsePacket(line2);
    }

    sort(packages.begin(), packages.end(),[](shared_ptr<Packet> lhs, shared_ptr<Packet> rhs){
        return (*lhs <=> *rhs)<0;
    });

    total =1;
    for(st idx = 0; idx<packages.size();++idx){
        packages[idx]->printFlat();
        if(packages[idx]->toString() == "[[2]]" || packages[idx]->toString() =="[[6]]"){
            total *=(idx+1);
        }
    }

    IO::print(total);
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