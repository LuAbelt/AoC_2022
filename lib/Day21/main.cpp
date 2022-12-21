#include "lib.h"

enum Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

auto parseInput(){
    map<string, i64> values;
    map<string, tuple<Operation, string,string>> ops;

    Adj adj;

    map<i64,string> id2label;
    map<string,i64> label2Id;

    i64 idx = 0;

    auto getId = [&adj,&id2label,&label2Id,&idx](string &label){
        if(!label2Id.contains(label)){
            label2Id[label] = idx;
            id2label[idx] = label;
            ++idx;
            adj += V<i64>{};
        }
        return label2Id[label];
    };
    for(auto& line : IO::fromCin()){
        auto lhs = util::split(line,":")[0];
        auto rhs = util::split(line,":")[1];

        if(std::any_of(rhs.begin(), rhs.end(),[](char c){ return ::isdigit(c);})){
            values[lhs] = atoi(rhs.c_str());
        } else {
            string splitChar;
            Operation op;
            if(rhs.find("+") != string::npos){
                splitChar = "+";
                op = ADD;
            }
            if(rhs.find("-") != string::npos){
                splitChar = "-";
                op = SUBTRACT;
            }
            if(rhs.find("*") != string::npos){
                splitChar = "*";
                op = MULTIPLY;
            }
            if(rhs.find("/") != string::npos){
                splitChar = "/";
                op = DIVIDE;
            }

            string operand1 = util::split(rhs, splitChar)[0];
            string operand2 = util::split(rhs, splitChar)[1];

            // Add to adjacency list
            auto idTarget = getId(lhs);
            auto idOp1 = getId(operand1);
            auto idOp2 = getId(operand2);

            ops[lhs] = make_tuple(op,operand1,operand2);

            adj[idOp1] += idTarget;
            adj[idOp2] += idTarget;
        }
    }

    return make_tuple(adj,ops,values,label2Id, id2label);
}

void part1(){

    auto [adj,ops,values,label2Id,id2Label] = parseInput();

    auto topoSort = graphs::full_topological_sort(adj);


    for(auto& id : topoSort){
        string label = id2Label[id];

        if(values.contains(label)){
            continue;
        }

        auto [op,lhs,rhs] = ops[label];

        switch (op) {
            case ADD:
                values[label] = values[lhs] + values[rhs];
                break;
            case SUBTRACT:
                values[label] = values[lhs] - values[rhs];
                break;
            case MULTIPLY:
                values[label] = values[lhs] * values[rhs];
                break;
            case DIVIDE:
                values[label] = values[lhs] / values[rhs];
                break;
        }
    }

    IO::print(values["root"]);
}

void part2(){
    auto [adj,ops,values,label2Id,id2Label] = parseInput();

    auto topoSort = graphs::full_topological_sort(adj);

    values.erase("humn");

    for(auto& id : topoSort){
        string label = id2Label[id];
        if(label=="root"){
            continue;
        }
        if(values.contains(label)){
            continue;
        }

        auto [op,lhs,rhs] = ops[label];

        if(!values.contains(lhs)||!values.contains(rhs)){
            continue;
        }

        switch (op) {
            case ADD:
                values[label] = values[lhs] + values[rhs];
                break;
            case SUBTRACT:
                values[label] = values[lhs] - values[rhs];
                break;
            case MULTIPLY:
                values[label] = values[lhs] * values[rhs];
                break;
            case DIVIDE:
                values[label] = values[lhs] / values[rhs];
                break;
        }
    }

    auto [_, lhs, rhs] = ops["root"];

    string label = !values.contains(lhs) ? lhs : rhs;
    i64 targetVal = values.contains(lhs) ? values[lhs] : values[rhs];

    while(!values.contains("humn")){
        auto [op, lhs, rhs] = ops[label];
        label = values.contains(lhs) ? rhs : lhs;
        i64 knownVal = values.contains(lhs) ? values[lhs] : values[rhs];
        bool isLhs = values.contains(lhs);

        switch (op) {
            case ADD:
                values[label] = targetVal - knownVal;
                break;
            case SUBTRACT:
                if(isLhs){
                    values[label] = knownVal - targetVal;
                } else {
                    values[label] = targetVal + knownVal;
                }
                break;
            case MULTIPLY:
                values[label] = targetVal / knownVal;
                break;
            case DIVIDE:
                if(isLhs){
                    values[label] = knownVal / targetVal;
                } else {
                    values[label] = targetVal * knownVal;
                }
                break;
        }
        targetVal = values[label];
    }

    IO::print(values["humn"]);
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