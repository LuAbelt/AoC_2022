#include "lib.h"

struct DLNode{
    DLNode(i64 num):value(num){}
    i64 value;
    shared_ptr<DLNode> previous;
    shared_ptr<DLNode> next;
};

auto parseInput(){
    using namespace util;
    auto numbers = util::fromString<i64>(IO::fromCin());

    V<shared_ptr<DLNode>> listOrder;
    shared_ptr<DLNode> begin = make_shared<DLNode>(numbers[0]);
    auto previous = begin;
    listOrder += begin;
    shared_ptr<DLNode> current;
    for(auto &num : numbers |ranges::views::drop(1)){
        current = make_shared<DLNode>(num);
        current->previous = previous;
        previous->next = current;
        listOrder += current;
        previous = current;
    }

    current->next = begin;
    begin->previous = current;

    return make_tuple(listOrder, begin);
}

auto parseInputAsList() {
    list<i64> result;


    for(auto num : IO::fromCin()){
        result += atoi(num.c_str());
    }
    return result;
}

void printList(shared_ptr<DLNode> begin){
    auto current = begin;
    do{
        cout << current->value << ' ';
        current = current->next;
    } while(current!=begin);
    cout << endl;
}

void printList(list<i64> &l){
    for(auto i : l){
        cout << i <<' ';
    }
    cout << endl;
}
void mixList(list<i64> &l, const V<list<i64>::iterator> &order){
    i64 length = l.size()-1;
    cout << endl;
    for(auto &item : order){
        i64 offset = *item%length;

        if (offset==0) {
            continue;
        }

        i64 ownIdx = distance(l.begin(),item);
        i64 newIdx = ownIdx;
        list<i64>::iterator itr;
        if(offset>0){
            newIdx += offset;
            // We overexceeded the list
            if(newIdx>=l.size()){
                newIdx %= length;
                itr = next(l.begin(),newIdx);
            } else {
                itr = next(l.begin(), newIdx+1);
            }
        } else {
            newIdx += offset;

            if(newIdx<=0){
                itr = next(l.end(),newIdx);
            } else {
                itr = next(l.begin(),newIdx);
            }
        }

        l.splice(itr,l,item);
    }
    cout << endl;
}

void mixList(list<i64> &l) {
    using Iterator = list<i64>::iterator;

    V<Iterator> order;
    order.reserve(l.size());
    for (auto itr = l.begin(); itr != l.end(); ++itr) {
        order += itr;
    }

    mixList(l, order);
}

void part1(){
    auto input = parseInputAsList();

    mixList(input);

    auto itr = input.begin();
    while(*itr!=0){
        ++itr;
    }

    i64 total = 0;

    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;
    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;
    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;


    IO::print(total);
}

void part2(){
    auto input = parseInputAsList();

    for(auto& v : input){
        v *= 811589153;
    }

    V<list<i64>::iterator> order;
    order.reserve(input.size());

    for(auto itr = input.begin();itr != input.end(); ++itr){
        order += itr;
    }

    for(auto i : ranges::views::iota(1,11)){
        mixList(input,order);
    }

    auto itr = input.begin();
    while(*itr!=0){
        ++itr;
    }

    i64 total = 0;

    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;
    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;
    for(int i=0;i<1000;++i){
        ++itr;
        if(itr==input.end()){
            itr=input.begin();
        }
    }

    IO::print(*itr);
    total += *itr;


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