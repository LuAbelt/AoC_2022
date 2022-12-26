#include "lib.h"

using Coord = transform::Coord<2>;

Coord NW{-1,-1};
Coord N{0,-1};
Coord NE{1,-1};
Coord E{1,0};
Coord W{-1,0};
Coord SW{-1,1};
Coord S{0,1};
Coord SE{1,1};


array<Coord,3> North = {NW,N,NE};
array<Coord,3> South = {SE,S,SW};
array<Coord,3> East = {NE,E,SE};
array<Coord,3> West = {SW,W,NW};
array Directions = {North,South,West,East};
auto All = {NE,N,NW,W,SW,S,SE,E};

auto parseInput(){
    using namespace util;

    auto lines = IO::fromCin();
    map<i64,Coord> elfs;
    set<Coord> occupied;

    i64 idx = 0;
    i64 x = 0;
    i64 y = 0;

    for(auto & line : lines){
        x = 0;
        for(char c : line){
            if(c=='#'){
                elfs[idx] = Coord{x,y};
                occupied += elfs[idx];
                ++idx;
            }
            ++x;
        }
        ++y;
    }

    return make_tuple(elfs,occupied);
}

bool moveRound(map<i64,Coord> &elfs, set<Coord> &occupied, st roundNum){
    map<Coord,i64> coordCnt;

    map<i64,Coord> proposedPos;

    set<Coord> newOccupied;

    for(auto& elf: elfs){
        if(std::none_of(All.begin(), All.end(), [&elf,&occupied](auto & c){
            return occupied.contains(elf.second+c);
        })){
            //IO::print("Id",elf.first,"(",elf.second.x(),elf.second.y(),")","proposed not to move");
            newOccupied += elf.second;
            continue;
        }

        bool hasProposed = false;
        for( st idx = 0; idx<4; ++idx){
            auto Dirs = Directions[(roundNum+idx)%4];
            if( std::none_of(Dirs.begin(), Dirs.end(),[&elf,&occupied](auto &c){
                return occupied.contains(elf.second+c);
            })){
                //IO::print("Id",elf.first,"(",elf.second.x(),elf.second.y(),")","proposed not move into direction",(roundNum+idx)%4);
                proposedPos[elf.first] = elf.second + Dirs[1];
                coordCnt[elf.second+Dirs[1]]++;
                hasProposed = true;
                break;
            }
        }
        if(!hasProposed){
            //IO::print("Id",elf.first,"(",elf.second.x(),elf.second.y(),")","cannot move");
            newOccupied += elf.second;
        }
    }

    for(auto &proposed : proposedPos){
        if(coordCnt[proposed.second]==1){
            elfs[proposed.first] = proposed.second;
            newOccupied += proposed.second;
        } else {
            newOccupied += elfs[proposed.first];
        }
    }

    assert(occupied.size()==newOccupied.size());
    occupied = newOccupied;

    return !proposedPos.empty();
}

void printGrid(set<Coord> & occupied){
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for(auto pos : occupied){
        minX = min(minX,pos.x());
        maxX = max(maxX,pos.x());
        minY = min(minY,pos.y());
        maxY = max(maxY,pos.y());
    }

    for( int y = minY; y<=maxY;++y){
        for (int x = minX; x <= maxX; ++x) {
            if(occupied.contains(Coord{x,y})){
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
}

void part1() {
    auto [elfs, occupied] = parseInput();

    printGrid(occupied);
    IO::print();

    for(int i = 0; i<10; ++i){
        moveRound(elfs,occupied,i);
        IO::print("After round",i);
        printGrid(occupied);
    }

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for(auto pos : occupied){
        minX = min(minX,pos.x());
        maxX = max(maxX,pos.x());
        minY = min(minY,pos.y());
        maxY = max(maxY,pos.y());
    }

    i64 total = (maxX-minX+1)*(maxY-minY+1)-occupied.size();

    IO::print(total);
}

void part2() {
    auto [elfs, occupied] = parseInput();

    printGrid(occupied);
    IO::print();
    i64 round = 0;

    while(moveRound(elfs,occupied,round)){
        round++;
    }

    printGrid(occupied);

    IO::print(round+1);
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