#include "lib.h"

using Coord = transform::Coord<2>;
using BlockedMatrix = array<V<V<V<bool>>>,4>;

struct Path {
    Path(i64 min, Coord pos, shared_ptr<Path> prev):minute(min),position(pos),previous(prev){};
    i64 minute;
    Coord position;
    shared_ptr<Path> previous;

    auto operator<=>(Path const&) const = default;
};

auto parseInput(){
    auto lines = IO::fromCin();

    V<pair<Coord,i64>> blizzards;
    int y = 0;
    int x = 0;

    for(auto & line : lines){
        x = 0;
        for(char c : line) {
            switch (c) {
                case '>':
                    blizzards.push_back(make_pair(Coord{x,y},0));
                    break;
                case 'v':
                    blizzards.push_back(make_pair(Coord{x,y},1));
                    break;
                case '<':
                    blizzards.push_back(make_pair(Coord{x,y},2));
                    break;
                case '^':
                    blizzards.push_back(make_pair(Coord{x,y},3));
                    break;
            }
            ++x;
        }
        ++y;
    }

    return make_tuple(blizzards,x,y);
}

void printGrid(set<Coord> &blocked, i64 maxX, i64 maxY){
    V<string> grid(maxY,string(maxX,'#'));

    grid[0][1] = '.';
    grid[maxY-1][maxX-2] = '.';

    for(i64 x = 1;x<maxX-1;++x){
        for(i64 y = 1;y<maxY-1;++y){
            if(blocked.contains(Coord{x,y})){
                grid[y][x] = 'X';
            } else {
                grid[y][x]='.';
            }
        }
    }

    for( auto &line : grid){
        IO::print(line);
    }
}

auto findPath(const Coord &start, const Coord &target, const BlockedMatrix &blocked, i64 tStart){
    i64 maxY = blocked[0][0].size();
    i64 maxX = blocked[0][0][0].size();

    i64 maxR = (maxX-2)*(maxY-2);

    V<V<V<i64>>> dist(maxR,V<V<i64>>(maxX,V<i64>(maxY, numeric_limits<i64>::max())));
    priority_queue<tuple<i64,i64,Coord,shared_ptr<Path>>,vector<tuple<i64,i64,Coord,shared_ptr<Path>>>, greater<>> q;
    q.emplace(target.manhattanLength(),0,start,make_shared<Path>(0,start,nullptr));

    shared_ptr<Path> p;

    while(!q.empty()){
        auto [_,cost,pos,node] = q.top();
        q.pop();

        if(pos==target){
            IO::print(cost);
            return make_tuple(cost,node);
            break;
        }

        if(any_of(blocked.begin(),blocked.end(),[=](auto& current){
            return current[(tStart+cost) % current.size()][pos.y()][pos.x()];
        })) {
            IO::print("Illegal position!",pos.x(),pos.y(),cost);
        }

        cost += 1;
        i64 round = (tStart+cost) % maxR;


        if(dist[round][pos.x()][pos.y()]<=cost){
            continue;
        }
        dist[round][pos.x()][pos.y()] = cost;

        i64 h = (target-pos).manhattanLength();

        // Check if the current position is blocked in the next round
        if(none_of(blocked.begin(),blocked.end(),[&round,&pos](auto& current){
            return current[round % current.size()][pos.y()][pos.x()];
        })) {
            q.emplace(cost+h,cost,pos,make_shared<Path>(cost,pos,node));
        }

        if(pos.y()<maxY-2 || (pos.y()==maxY-2 && pos.x() == maxX-2)){
            // Try to move down
            Coord c = pos + Coord{0,1};
            if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){
                return current[round % current.size()][c.y()][c.x()];
            })) {
                q.emplace(cost+h,cost,c,make_shared<Path>(cost,c,node));
            }
        }

        if(pos.x()<maxX-2 && pos.y()!=0){
            // Try to move right
            Coord c = pos + Coord{1,0};
            if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){
                return current[round % current.size()][c.y()][c.x()];
            })) {
                q.emplace(cost+h,cost,c,make_shared<Path>(cost,c,node));
            }
        }

        if(pos.y()>1 || (pos.y()==1&&pos.x()==1)){
            // Try to move up
            Coord c = pos + Coord{0,-1};
            if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){
                return current[round % current.size()][c.y()][c.x()];
            })) {
                q.emplace(cost+h,cost,c,make_shared<Path>(cost,c,node));
            }
        }

        if(pos.x()>1 && pos.y() != maxY-1 ){
            // Try to move left
            Coord c = pos + Coord{-1,0};
            if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){
                return current[round % current.size()][c.y()][c.x()];
            })) {
                q.emplace(cost+h,cost,c,make_shared<Path>(cost,c,node));
            }
        }
    }

}

void part1(){

    auto [blizzards,maxX,maxY] = parseInput();

    Coord start{1,0};
    Coord target{maxX-2,maxY-1};

    BlockedMatrix blocked;

    blocked[0] = blocked[2] = V<V<V<bool>>>(maxX-2,V<V<bool>>(maxY,V<bool>(maxX,false)));
    blocked[1] = blocked[3] = V<V<V<bool>>>(maxY-2,V<V<bool>>(maxY,V<bool>(maxX,false)));

    // Precalculate all blocked positions
    for (auto &b : blizzards) {
        switch (b.second) {
            case 0: {
                for (int i = 0; i < maxX - 2; ++i) {
                    auto newX = b.first.x() + (i % (maxX - 2));
                    if (newX >= maxX-1) {
                        newX -= (maxX - 2);
                    }
                    blocked[0][i][b.first.y()][newX] = true;
                }
            }
                break;
            case 1:
            {
                for (int i = 0; i < maxY-2; ++i) {
                    auto newY = b.first.y() + (i%(maxY-2));
                    if(newY >= maxY-1 ){
                        newY-=(maxY-2);
                    }
                    blocked[1][i][newY][b.first.x()] = true;
                }
            }
                break;
            case 2:
            {
                for (int i = 0; i < maxX - 2; ++i) {
                    auto newX = b.first.x() - (i%(maxX-2));
                    if(newX <= 0 ){
                        newX += (maxX-2);
                    }
                    blocked[2][i][b.first.y()][newX] = true;
                }
            }
                break;
            case 3:
            {
                for (int i = 0; i < maxY - 2; ++i) {
                    auto newY = b.first.y() - (i%(maxY-2));
                    if(newY <= 0 ){
                        newY+=(maxY-2);
                    }
                    blocked[3][i][newY][b.first.x()] = true;
                }
            }
            break;
        }
    }


    auto [cost,p] = findPath(start,target,blocked,0);

    while(p){
        IO::print("Minute",p->minute,"at",p->position.x(),p->position.y());
        p=p->previous;
    }
    IO::print(cost);
}

void part2(){

    auto [blizzards,maxX,maxY] = parseInput();

    Coord start{1,0};
    Coord target{maxX-2,maxY-1};

    BlockedMatrix blocked;

    blocked[0] = blocked[2] = V<V<V<bool>>>(maxX-2,V<V<bool>>(maxY,V<bool>(maxX,false)));
    blocked[1] = blocked[3] = V<V<V<bool>>>(maxY-2,V<V<bool>>(maxY,V<bool>(maxX,false)));

    // Precalculate all blocked positions
    for (auto &b : blizzards) {
        switch (b.second) {
            case 0: {
                for (int i = 0; i < maxX - 2; ++i) {
                    auto newX = b.first.x() + (i % (maxX - 2));
                    if (newX >= maxX-1) {
                        newX -= (maxX - 2);
                    }
                    blocked[0][i][b.first.y()][newX] = true;
                }
            }
                break;
            case 1:
            {
                for (int i = 0; i < maxY-2; ++i) {
                    auto newY = b.first.y() + (i%(maxY-2));
                    if(newY >= maxY-1 ){
                        newY-=(maxY-2);
                    }
                    blocked[1][i][newY][b.first.x()] = true;
                }
            }
                break;
            case 2:
            {
                for (int i = 0; i < maxX - 2; ++i) {
                    auto newX = b.first.x() - (i%(maxX-2));
                    if(newX <= 0 ){
                        newX += (maxX-2);
                    }
                    blocked[2][i][b.first.y()][newX] = true;
                }
            }
                break;
            case 3:
            {
                for (int i = 0; i < maxY - 2; ++i) {
                    auto newY = b.first.y() - (i%(maxY-2));
                    if(newY <= 0 ){
                        newY+=(maxY-2);
                    }
                    blocked[3][i][newY][b.first.x()] = true;
                }
            }
                break;
        }
    }


    i64 total = 0;
    auto [cost,_] = findPath(start,target,blocked,0);
    IO::print("Cost from start to target:",cost);
    total+=cost;

    tie(cost,_) = findPath(target,start,blocked,total);
    IO::print("Cost from target to start:",cost);
    total+=cost;

    tie(cost,_) = findPath(start,target,blocked,total);
    IO::print("Cost from target to start:",cost);
    total+=cost;

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