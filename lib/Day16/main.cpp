#include "lib.h"

auto parseInput(){
    using namespace util;
    auto lines = IO::fromCin();
    map<string,st> label2Id;
    map<st,string> id2label;

    st id = 0;
    V<i64> flows;
    Adj adj;
    i64 startNode;

    for(auto& line : lines){
        auto left = split(line,";")[0];
        auto right = split(line,";")[1];

        string label = left.substr(left.find_first_of(" ")+1, 2);


        st flow_rate = atoi(split(left,"=")[1].c_str());

        V<string> targets;
        if(right.find("valves")!=string::npos) {
            targets = split(split(right, "valves ")[1], ",");
        } else {
            targets += right.substr(right.find_last_of(" ")+1);
        }
        if(label2Id.find(label)==label2Id.end()){
            label2Id[label] = id;
            id2label[id] = label;


            if(label=="AA"){
                startNode = id;
            }
            ++id;
            flows += 0;
            adj += V<i64>{};
        }

        auto labelId = label2Id[label];
        flows[labelId] = flow_rate;

        for (auto &target : targets){
            if(label2Id.find(target)==label2Id.end()){
                label2Id[target] = id;
                id2label[id] = target;
                ++id;
                flows += 0;
                adj += V<i64>{};
            }

            adj[labelId] += label2Id[target];
        }
    }

    return make_tuple(adj,flows,startNode);
}

void part1(){
    Adj adj;
    V<i64> flows;
    i64 start;

    tie(adj,flows,start) = parseInput();

    V<i64> nodesWithFlow;

    V<V<i64>> distances;

    for(st idx =0;idx<flows.size();++idx){
        if(flows[idx]>0){
            nodesWithFlow += idx;
        }

        V<i64>d,p;
        tie(d,p) = graphs::dijkstra_unit(adj,idx);
        distances += d;
    }

    struct PathState{
        i64 node;
        i64 minutes;
        i64 flow;
        bitset<64> open;
    };

    i64 totalFlow = 0;
    queue<PathState> q;
    q += PathState{start,30,0, bitset<64>{}};

    while(!q.empty()){
        auto node = q.front();q.pop();

        for(auto idx : nodesWithFlow){
            if(!node.open[idx] && distances[node.node][idx]<(node.minutes-1)) {
                auto nOpen = node.open;
                nOpen[idx] = true;
                auto minLeft = node.minutes-distances[node.node][idx]-1;
                auto nFlow = node.flow + minLeft * flows[idx];
                //IO::print("At node ",node.node,"at minute",node.minutes," moving to valve ",idx," resulting in new flow",nFlow);
                totalFlow = max(totalFlow,nFlow);
                q += PathState {idx,minLeft, nFlow,nOpen};
            }
        }
    }

    IO::print(totalFlow);
}

void part2(){
    Adj adj;
    V<i64> flows;
    i64 start;

    tie(adj,flows,start) = parseInput();

    V<i64> nodesWithFlow;

    V<V<i64>> distances;

    for(st idx =0;idx<flows.size();++idx){
        if(flows[idx]>0){
            nodesWithFlow += idx;
        }

        V<i64>d,p;
        tie(d,p) = graphs::dijkstra_unit(adj,idx);
        distances += d;
    }

    struct PathState {
        i64 node;
        i64 minutes;
        i64 flow;
        bitset<64> open;
    };

    i64 totalFlow = 0;

    unordered_map<bitset<64>,i64> candidates;
    {
        queue<PathState> q;
        q += PathState{start, 26, 0, bitset<64>{}};

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            for (auto idx: nodesWithFlow) {
                if (!node.open[idx] && distances[node.node][idx] < (node.minutes - 1)) {
                    auto nOpen = node.open;
                    nOpen[idx] = true;
                    auto minLeft = node.minutes - distances[node.node][idx] - 1;
                    auto nFlow = node.flow + minLeft * flows[idx];
                    //IO::print("At node ",node.node,"at minute",node.minutes," moving to valve ",idx," resulting in new flow",nFlow);
                    totalFlow = max(totalFlow, nFlow);
                    q += PathState{idx, minLeft, nFlow, nOpen};

                    candidates[nOpen] = max(candidates[nOpen],nFlow);
                }
            }
        }
    }

    IO::print("Checking",candidates.size(),"possibilities...");
    for(auto& candidate : candidates){
        auto initialFlow = candidate.second;
        auto openValves = candidate.first;

        queue<PathState> q;
        q += PathState{start, 26, initialFlow, openValves};

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            for (auto idx: nodesWithFlow) {
                if (!node.open[idx] && distances[node.node][idx] < (node.minutes - 1)) {
                    auto nOpen = node.open;
                    nOpen[idx] = true;
                    auto minLeft = node.minutes - distances[node.node][idx] - 1;
                    auto nFlow = node.flow + minLeft * flows[idx];
                    //IO::print("At node ",node.node,"at minute",node.minutes," moving to valve ",idx," resulting in new flow",nFlow);
                    totalFlow = max(totalFlow, nFlow);
                    q += PathState{idx, minLeft, nFlow, nOpen};
                }
            }
        }
    }

    IO::print(totalFlow);
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