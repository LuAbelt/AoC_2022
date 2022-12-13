#include "lib.h"

class Packet {
    st size;
    V<shared_ptr<Packet>> contents;

public:

    std::optional<i64> value;
    virtual shared_ptr<Packet> get(st idx) const{
        return contents[idx];
    };

    Packet(i64 val)
    :value(val)
    ,size(1)
    {}

    Packet(V<shared_ptr<Packet>> &content)
    :contents(content)
    ,size(content.size())
    {}

    void print(st indent = 0) const {
        string prefix ="";
        for(st i=0;i<indent;++i){
            prefix+="\t";
        }

        if(value.has_value()){
            cout << prefix << value.value() << "," << endl;
            return;
        }

        cout << prefix << "[" << endl;
        for(auto& item : contents){
            item->print(indent+1);
            cout << ",";
        }
        cout << prefix << "]" << endl;
    }


    auto operator<=>(const Packet& Other){
        if(value.has_value() && Other.value.has_value()){
            return value.value() <=> Other.value.value();
        }

        if(value.has_value()){
            if(Other.contents.size()>0){
                return *this <=> *Other.contents[0];
            } else {
                return strong_ordering::greater;
            }
        }

        if(Other.value.has_value()){
            if(contents.size()>0){
                return *contents[0] <=> Other;
            } else {
                return strong_ordering::less;
            }
        }

        for(st idx = 0;idx<contents.size() && idx<Other.contents.size();++idx){
            return *contents[idx] <=> *Other.contents[idx];
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
                ++idx;
            }

            if(input[idx]==','){
                ++idx;
            }
        }
        ++idx;

        if(contents.size()==1 && contents[0]->value.has_value()){
            return contents[0];
        }
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

        cout << line1 << endl;
        p1->print();

        cout << line2 << endl;
        p2->print();
    }

    IO::print(total);
}

void part2(){
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