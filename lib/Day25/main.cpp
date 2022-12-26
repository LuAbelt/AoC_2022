#include "lib.h"

i64 snafuToDecimal(string &num){
    i64 result = 0;
    i64 base = 1;
    for(char c : num | ranges::views::reverse){
        switch (c) {
            case '=':
                result += -2*base;
                break;
            case '-':
                result += -1*base;
                break;
            case '0':
                break;
            case '1':
                result += 1*base;
                break;
            case '2':
                result += 2*base;
                break;
        }

        base *= 5;
    }

    return result;
}

string decimalToSnafu(i64 num){
    string res;
    i64 base = 1;

    while (num!=0) {
        auto nextBase = base*5;

        auto rem = num % nextBase;
        switch (rem/base) {
            case 0:
            case 1:
            case 2:
                res = to_string(rem/base) + res;
                num -= (rem/base)*base;
                break;
            case 3:
                res = '=' + res;
                num += 2*base;
                break;
            case 4:
                res = '-' + res;
                num += base;
                break;
        }
        base *= 5;
    }
    return res;
}

void part1(){
    auto lines = IO::fromCin();
    i64 total = 0;
    for(auto &l : lines){
        auto n = snafuToDecimal(l);
        //IO::print(n);
        total += n;
    }
    IO::print(total);
    IO::print(decimalToSnafu(total));
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