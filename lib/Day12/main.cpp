#include "lib.h"

void part1(){
    using IO::print;

    i64 result = 0;
    int x = 0;
    using geometry::Point;
    map<geometry::Point,st> point2Id;
    st id = 0;
    st startId = 0;
    st targetId = 0;
    string lastLine;
    Adj adj;
    for(string line;getline(cin,line);){
        int y = 0;


        for(auto c:line){
            point2Id[Point{x,y}] = id;
            adj.emplace_back(V<i64>{});
            if(c=='S'){
                startId = id;
            }
            if(c=='E'){
                targetId = id;
            }

            if(x>0){
                auto up = lastLine[y];
                auto upId = point2Id[Point{x-1,y}];

                if(up == 'S'){
                    adj[upId] += id;
                    adj[id] +=upId;
                }

                if(up!='E'&& c!='E'){

                    if( ((up-c)<=1)){

                        adj[id] += upId;
                    }

                    if((c-up)<=1){
                        adj[upId] += id;
                    }
                }

                if(c=='z' && up == 'E'){
                    adj[id] += upId;
                }

                if(c=='E' && up == 'z'){
                    adj[upId] += id;
                }
            }

            if(y>0){
                auto left = line[y-1];
                auto leftId = point2Id[Point{x,y-1}];

                if(left == 'S'){
                    adj[leftId] += id;
                    adj[id] += leftId;
                }

                if(left=='E' && c == 'z'){
                    adj[id] += leftId;
                }

                if(left=='z' && c == 'E'){
                    adj[leftId] += id;
                }

                if(left!='E' && c!='E') {
                    if ((left - c) <= 1) {
                        adj[id] += leftId;
                    }
                    if ((c - left) <= 1) {
                        adj[leftId] += id;
                    }
                }
            }

            ++id;
            ++y;
        }
        ++x;
        y=0;
        lastLine = line;
    }

    print(startId, targetId);
    auto dist = graphs::dijkstra_unit(adj,(i64)startId);

    result = dist[targetId];

    print(result);
}

void part2(){
    using IO::print;

    i64 result = 0;
    int x = 0;
    using geometry::Point;
    map<geometry::Point,st> point2Id;
    st id = 0;
    st startId = 0;
    st targetId = 0;
    string lastLine;
    V<V<i64pair>> adj;
    V<i64pair> aEdges;
    for(string line;getline(cin,line);){
        int y = 0;


        for(auto c:line){
            point2Id[Point{x,y}] = id;
            adj.emplace_back(V<i64pair>{});
            if(c=='S'){
                startId = id;
            }
            if(c=='E'){
                targetId = id;
            }

            if(c=='a') {
                aEdges += i64pair{id,0};
            }

            if(x>0){
                auto up = lastLine[y];
                auto upId = point2Id[Point{x-1,y}];

                if(up == 'S'){
                    adj[upId] += i64pair{id,1};
                    adj[id] += i64pair{upId,1};
                }

                if(up!='E'&& c!='E'){

                    if( ((up-c)<=1)){

                        adj[id] += i64pair{upId,1};
                    }

                    if((c-up)<=1){
                        adj[upId] += i64pair{id,1};
                    }
                }

                if(c=='z' && up == 'E'){
                    adj[id] += i64pair{upId,1};
                }

                if(c=='E' && up == 'z'){
                    adj[upId] += i64pair{id,1};
                }
            }

            if(y>0){
                auto left = line[y-1];
                auto leftId = point2Id[Point{x,y-1}];

                if(left == 'S'){
                    adj[leftId] += i64pair{id,1};
                    adj[id] += i64pair{leftId,1};
                }

                if(left=='E' && c == 'z'){
                    adj[id] += i64pair{leftId,1};
                }

                if(left=='z' && c == 'E'){
                    adj[leftId] += i64pair{id,1};
                }

                if(left!='E' && c!='E') {
                    if ((left - c) <= 1) {
                        adj[id] += i64pair{leftId,1};
                    }
                    if ((c - left) <= 1) {
                        adj[leftId] += i64pair{id,1};
                    }
                }
            }

            ++id;
            ++y;
        }
        ++x;
        y=0;
        lastLine = line;
    }

    for(auto &edge : aEdges){
        adj[startId] +=edge;
    }

    V<i64> dist, parent;
    tie(dist, parent) = graphs::dijkstra(adj,(i64)startId);

    result = dist[targetId];

    print(result);
}

void part3(){
    using IO::print;

    i64 result = 0;
    int x = 0;
    using geometry::Point;
    map<geometry::Point,st> point2Id;
    st id = 0;
    st startId = 0;
    st targetId = 0;
    V<string> map;
    V<V<i64pair>> adj;

    for(string line;getline(cin,line);){
        map.push_back(line);
        int y = 0;

        auto getCost = [](i64 d){
            if (d<0){
                return 0LL;
            }

            if(d==0){
                return 1LL;
            }

            i64 res = 1;
            for(int i = 1;i<=d;++i){
                res+=i;
            }

            return res;
        };
        for(auto c:line){
            point2Id[Point{x,y}] = id;
            adj.emplace_back(V<i64pair>{});

            if(c=='S'){
                startId = id;
                c = 'a';
            }
            if(c=='E'){
                targetId = id;
                c='z';
            }

            if(x>0){
                auto up = map[x-1][y];
                if(up=='S'){
                    up='a';
                }
                if(up=='E'){
                    up = 'z';
                }
                auto upId = point2Id[Point{x-1,y}];

                
                adj[upId] += i64pair{id,getCost(c-up)};
                adj[id] += i64pair{upId,getCost(up-c)};
            }

            if(y>0){
                auto left = map[x][y-1];
                if(left=='S'){
                    left='a';
                }
                if(left=='E'){
                    left = 'z';
                }
                auto leftId = point2Id[Point{x,y-1}];

                adj[leftId] += i64pair{id,getCost(c-left)};
                adj[id] += i64pair{leftId,getCost(left-c)};
            }

            ++id;
            ++y;
        }
        ++x;
        y=0;
    }

    V<i64> dist, parent;
    tie(dist, parent) = graphs::dijkstra(adj,(i64)startId);

    auto cur = targetId;
    while(cur!=startId){
        print(cur);
        cur=parent[cur];
    }

    result = dist[targetId];

    print(result);
}


int main(int argc, char* argv[]){
    if(std::string(argv[1])=="--one"){
        part1();
    }else if(std::string(argv[1])=="--two"){
        part2();
    } else if(std::string(argv[1])=="--three") {
        part3();
    } else {
        std::cout << "Wrong usage!" << std::endl;
    }
}