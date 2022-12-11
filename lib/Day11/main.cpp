#include "lib.h"

class Monkey{
    V<i64> _items;
    function<int64_t(int64_t)> _operation;
    i64 _trueTarget, _falseTarget;
    i64 _inspectionCnt = 0;
    i64 _test;
    ui64 _mod = 0;
public:
    Monkey(V<i64> items, function<int64_t(int64_t)> operation, i64 trueT, i64 falseT, i64 test)
    :_items(items)
    ,_operation(operation)
    ,_trueTarget(trueT)
    ,_falseTarget(falseT)
    ,_test(test)
    {}

    Monkey(V<i64> items, function<int64_t(int64_t)> operation, i64 trueT, i64 falseT, i64 test,i64 mod)
            :_items(items)
            ,_operation(operation)
            ,_trueTarget(trueT)
            ,_falseTarget(falseT)
            ,_test(test)
            ,_mod(mod)
    {}

    void simulateRound(V<Monkey> &Monkeys) {
        for( auto &item : _items){
            //cout << "Inspecting item " << item << endl;
            ++_inspectionCnt;
            item = _operation(item);
            //cout << "Item is now " << item << endl;
            if(_mod==0) {
                item /= 3;
            } else {
                item = item % _mod;
            }

            //cout << "Worry level reduced: " << item << endl;
            if((item % _test)==0){
                //cout << "Passing to monkey " << _trueTarget << endl;
                Monkeys[_trueTarget]._items.push_back(item);
            } else {
                //cout << "Passing to monkey " << _falseTarget << endl;
                Monkeys[_falseTarget]._items.push_back(item);
            }
        }

        _items.clear();
    }

    i64 inspectionCount() const {
        return _inspectionCnt;
    }

    void setMod(ui64 mod){
        _mod = mod;
    }
};

void part1(){
    i64 total = 0;

    V<Monkey> Monkeys;

    ui64 mod = 1;
    for(string line;getline(cin,line);){
        string line2;
        getline(cin,line2);
        //cout << line2 << endl;
        size_t pos = line2.find(':');
        size_t pos2 = line2.find(',');
        V<i64> items;
        while(pos!=string::npos){
            i64 item = atoi(line2.substr(pos+1,pos2-pos).c_str());
            items.push_back(item);

            pos = pos2;
            pos2 = line2.find( ',',pos2+1);

        }

        getline(cin,line2);
        line2 = line2.substr(line2.find('=')+1);
        function<i64(i64)> fn;
        if(line2.find('*')!=string::npos){
            string lhs = line2.substr(1,line2.find('*')-2);
            string rhs = line2.substr(line2.find('*')+2);

            if(lhs=="old" && rhs == "old"){
                //cout << "both" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,std::placeholders::_1);
            } else if (lhs == "old") {
                //cout << "lhs" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,atoi(rhs.c_str()));
            } else {
                //cout << "rhs" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,atoi(lhs.c_str()));
            }
        } else {
            string lhs = line2.substr(1,line2.find('+')-2);
            string rhs = line2.substr(line2.find('+')+2);
            //cout << '#' << lhs << '#' << rhs << endl;

            if(lhs=="old" && rhs == "old"){
                //cout << "both" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,std::placeholders::_1);
            } else if (lhs == "old") {
                //cout << "lhs" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,atoi(rhs.c_str()));
            } else {
                //cout << "rhs" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,atoi(lhs.c_str()));
            }
        }

        getline(cin,line2);
        i64 test = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        getline(cin,line2);
        i64 trueT = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        getline(cin,line2);
        i64 falseT = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        Monkey m(items,fn,trueT,falseT,test);

        //IO::print(fn(5),test,trueT,falseT);

        Monkeys.push_back(m);
        getline(cin,line);
    }

    for(i64 i = 0;i<20;++i){
        cout << "Round " << i << endl;
        for(auto &m : Monkeys){
            m.simulateRound(Monkeys);
        }
    }

    V<i64> counts;

    for (auto& m : Monkeys){
        counts += m.inspectionCount();
    }

    std::sort(counts.begin(), counts.end(),std::greater{});
    IO::print(counts[0],counts[1],counts[0]*counts[1]);
}

void part2(){
    i64 total = 0;

    V<Monkey> Monkeys;
    ui64 mod = 1;
    for(string line;getline(cin,line);){
        string line2;
        getline(cin,line2);
        //cout << line2 << endl;
        size_t pos = line2.find(':');
        size_t pos2 = line2.find(',');
        V<i64> items;
        while(pos!=string::npos){
            i64 item = atoi(line2.substr(pos+1,pos2-pos).c_str());
            items.push_back(item);

            pos = pos2;
            pos2 = line2.find( ',',pos2+1);

        }

        getline(cin,line2);
        line2 = line2.substr(line2.find('=')+1);
        function<i64(i64)> fn;
        if(line2.find('*')!=string::npos){
            string lhs = line2.substr(1,line2.find('*')-2);
            string rhs = line2.substr(line2.find('*')+2);

            if(lhs=="old" && rhs == "old"){
                //cout << "both" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,std::placeholders::_1);
            } else if (lhs == "old") {
                //cout << "lhs" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,atoi(rhs.c_str()));
            } else {
                //cout << "rhs" << endl;
                fn = std::bind(std::multiplies<i64>{},std::placeholders::_1,atoi(lhs.c_str()));
            }
        } else {
            string lhs = line2.substr(1,line2.find('+')-2);
            string rhs = line2.substr(line2.find('+')+2);
            //cout << '#' << lhs << '#' << rhs << endl;

            if(lhs=="old" && rhs == "old"){
                //cout << "both" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,std::placeholders::_1);
            } else if (lhs == "old") {
                //cout << "lhs" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,atoi(rhs.c_str()));
            } else {
                //cout << "rhs" << endl;
                fn = std::bind(std::plus<i64>{},std::placeholders::_1,atoi(lhs.c_str()));
            }
        }

        getline(cin,line2);
        i64 test = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        getline(cin,line2);
        i64 trueT = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        getline(cin,line2);
        i64 falseT = atoi(line2.substr(line2.find_last_of(' ')).c_str());

        Monkey m(items,fn,trueT,falseT,test);

        //IO::print(fn(5),test,trueT,falseT);

        Monkeys.push_back(m);
        mod*=test;
        getline(cin,line);
    }

    IO::print("Mod ", mod);
    for(auto &m : Monkeys){
        m.setMod(mod);
    }

    for(i64 i = 0;i<10000;++i){
        //cout << "Round " << i << endl;
        for(auto &m : Monkeys){
            m.simulateRound(Monkeys);
        }
    }

    V<i64> counts;

    for (auto& m : Monkeys){
        counts += m.inspectionCount();
    }

    std::sort(counts.begin(), counts.end(),std::greater{});
    IO::print(counts[0],counts[1],counts[0]*counts[1]);
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