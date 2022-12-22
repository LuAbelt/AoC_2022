//
// Created by lukas on 03/12/2021.
//

#include "lib.h"

enum CellState {
    Nothing
    ,Empty
    ,Wall
};

using Coord = transform::Coord<2>;

array<transform::Coord<2>,4> Directions = {
        Coord{0,1}
        ,Coord{1,0}
        ,Coord{0,-1}
        ,Coord{-1,0}
};

auto parseInput() {
    auto lines = IO::fromCin();
    auto mapLines = lines | ranges::views::take_while([](auto& line){return !line.empty();});
    st maxLength = 0;
    st mapSize = 0;
    for(auto&line : mapLines){
        maxLength = max(maxLength,line.length());
        ++mapSize;
    }

    V<V<CellState>> map(mapSize+2,V<CellState>(maxLength+2,Nothing));
    st curLine = 1;
    for(auto &line : mapLines){
        st curColumn = 1;
        for(auto &c : line){
            switch (c) {
                case '.':
                    map[curLine][curColumn] = Empty;
                    break;
                case '#':
                    map[curLine][curColumn] = Wall;
                    break;
            }
            ++curColumn;
        }
        ++curLine;
    }

    return make_tuple(map,lines[lines.size()-1]);
}
using Coord = transform::Coord<2>;


void part1(){
    auto [map,instructions] = parseInput();

    st direction = 0;
    Coord current{1,1};

    while(map[current.x()][current.y()] == Nothing){
        current += Directions[direction];
    }

    st instrIdx = 0;
    while (instrIdx != instructions.size()){
        auto nextIdx = instrIdx;
        while(instrIdx< instructions.size() && isdigit(instructions[nextIdx])){
            nextIdx++;
        }

        st steps = atoi(instructions.substr(instrIdx,(nextIdx-instrIdx)).c_str());

        for(int i = 0; i<steps;++i){
            Coord next = current + Directions[direction];

            bool end = false;
            switch (map[next.x()][next.y()]) {
                case Nothing: {
                    auto otherDir = (direction + 2) % 4;
                    Coord otherNext = current + Directions[otherDir];
                    while (otherNext.y()>=0
                            && otherNext.x()>=0
                            && otherNext.x() < map.size()
                            && otherNext.y() < map[0].size()
                            && map[otherNext.x()][otherNext.y()] != Nothing) {
                        otherNext += Directions[otherDir];
                    }
                    otherNext += Directions[direction];
                    if (map[otherNext.x()][otherNext.y()] == Empty) {
                        current = otherNext;
                    } else if (map[otherNext.x()][otherNext.y()] == Wall) {
                        end = true;
                        break;
                    } else {
                        IO::print("No");
                    }
                    break;
                }
                case Empty:
                    current = next;
                    break;
                case Wall:
                    end = true;
                    break;
            }
            if(end){
                break;
            }
        }

        instrIdx = nextIdx;

        if(instrIdx < instructions.size()){
            if(instructions[instrIdx]=='R'){
                direction = (direction + 1)%4;
            } else if (instructions[instrIdx]=='L'){
                direction = (direction+3)%4;
            }
            ++instrIdx;
        }
    }

    IO::print(1000*(current.x())+4*(current.y())+direction);
}

void part2(){
    auto [map,instructions] = parseInput();

    st direction = 0;
    Coord current{1,1};
    st currentSide = 1;

    while(map[current.x()][current.y()] == Nothing){
        current += Directions[direction];
    }

    std::map<Coord,i64> sideMap;
#ifdef SAMPLE
    i64 sideLength = 4;
#else
    i64 sideLength = 50;
#endif

    {
        i64 sideIdx = 1;
        for (i64 x = 1; x < map.size(); x += sideLength) {
            for (i64 y = 1; y < map[x].size(); y += sideLength) {
                if(map[x][y]!=Nothing){
                    for(i64 xx=x;xx<x+sideLength;++xx){
                        for(i64 yy=y;yy<y+sideLength;++yy){
                            sideMap[Coord{xx,yy}] = sideIdx;
                        }
                    }
                    ++sideIdx;
                }
            }
        }
    }

    st instrIdx = 0;

    V<string> pathMap(map.size(),string{});
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            pathMap[x] += map[x][y] == Nothing ? ' ' : map[x][y] == Empty ? '.' : '#';
        }
    }

    auto getNext = [&sideMap,&map](const Coord &current, i64 direction) -> tuple<Coord,i64,bool>{
        Coord next = current+Directions[direction];
        i64 nextDir = direction;
#ifdef SAMPLE
        switch (map[next.x()][next.y()]) {
            case Nothing:
                switch (sideMap[current]) {
                    case 1:
                        switch (direction) {
                            case 0:
                                next = Coord{
                                    13-current.x(),
                                    16
                                };
                                nextDir = 2;
                                assert(map[next.x()][next.y()] != Nothing);
                            break;
                            case 2:
                            {
                                i64 nextX = 5;
                                i64 nextY = 4 + current.x();
                                nextDir = 1;
                                next = Coord{nextX,nextY};
                            }
                                assert(map[next.x()][next.y()] != Nothing);
                            break;
                            case 3:
                                next = Coord{
                                    5,
                                    5-(current.y()-8)
                                };
                                nextDir = 1;
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 2:
                        switch (direction) {
                            case 1:
                                nextDir = 3;
                                next = Coord {
                                    12,
                                    13-current.y()
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 2:
                                nextDir = 3;
                                next = Coord {
                                    12,
                                    17-(current.x()-4)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                                nextDir = 1;
                                next = Coord {
                                    1,
                                    13-current.y()
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 3:
                        switch (direction) {
                            case 1:
                                nextDir = 0;
                                next = Coord {
                                    13-(current.y()-4),
                                    9
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                                nextDir = 0;
                                next = Coord {
                                    current.y()-4,
                                    9
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 4:
                        //Only one direction here
                        nextDir = 1;
                        next = Coord {
                            9,
                            17-(current.x()-4)
                        };
                        assert(map[next.x()][next.y()] != Nothing);
                        break;
                    case 5:
                        switch (direction) {
                            case 1:
                                nextDir = 3;
                                next = Coord {
                                    8,
                                    5-(current.y()-8)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 2:
                                nextDir = 3;
                                next = Coord{
                                    8,
                                    8-(current.y()-8)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 6:
                        switch (direction) {
                            case 0:
                                nextDir = 2;
                                next = Coord{
                                    5-(current.y()-8),
                                    12
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 1:
                                nextDir = 0;
                                next = Coord{
                                    9-(current.y()-12),
                                    1
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                                nextDir = 2;
                                next = Coord {
                                    9-(current.x()-12),
                                    12
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                }
                if(map[next.x()][next.y()] == Wall){
                    return make_tuple(current,direction,true);
                }
                assert(map[next.x()][next.y()] == Empty);
                return make_tuple(next,nextDir,false);
                break;
            case Empty:
                return make_tuple(next,direction,false);
                break;
            case Wall:
                return make_tuple(current,direction,true);
                break;
        }
#else
        /*
         * Our Map looks roughly like this:
         *            1122
         *            1122
         *            33
         *            33
         *          4455
         *          4455
         *          66
         *          66
         */
        switch (map[next.x()][next.y()]) {
            case Nothing:
                switch (sideMap[current]) {
                    case 1:
                        switch (direction) {
                            case 2:
                            // Leaving side 1 on the left, entering 4 from the right
                                next = Coord{
                                    151-current.x(),
                                    1
                                };
                                nextDir = 0;
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                            // Leaving side 1 from the top, entering side 6 from the right
                            {
                                nextDir = 0;
                                next = Coord {
                                    150+(current.y()-50),
                                    1
                                };
                            }
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 2:
                        switch (direction) {
                            case 0:
                                // Leacing side 2 to th right, entering side 5 from the right
                                nextDir = 2;
                                next = Coord{
                                    151-current.x(),
                                    100
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 1:
                                // Leaving side 2 to the bottom, entering 3 from the right
                                nextDir = 2;
                                next = Coord{
                                    50+(current.y()-100),
                                    100
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                                // Leaving side 2 from the top, entering side 6 from the bottom
                                nextDir = 3;
                                next = Coord{
                                    200,
                                    current.y()-100
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 3:
                        switch (direction) {
                            case 0:
                                // Leaving side 3 to the right, entering 2 from the bottom
                                nextDir = 3;
                                next = Coord{
                                    50,
                                    100+(current.x()-50)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 2:
                                // Leaving side 3 to the left, entering 4 from the top
                                nextDir = 1;
                                next = Coord{
                                    101,
                                    current.x()-50
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 4:
                        switch (direction) {
                            case 2:
                                // Leaving 4 to the right, entering 1 from the left
                                nextDir = 0;
                                next = Coord{
                                    51-(current.x()-100),
                                    51
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 3:
                                // Leaving 4 to the top, entering 3 from the left
                                nextDir = 0;
                                next = Coord{
                                    50+current.y(),
                                    51
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 5:
                        switch (direction) {
                            case 0:
                                // Leacing 5 to the right, entering 2 from the right
                                nextDir = 2;
                                next = Coord{
                                    151-current.x(),
                                    150
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 1:
                                // Leaving 5 to the bottom. entering 6 from the right
                                nextDir = 2;
                                next = Coord{
                                    150+(current.y()-50),
                                    50
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                    case 6:
                        switch (direction) {
                            case 0:
                                // Leaving 6 to the right, entering 5 from the bottom
                                nextDir = 3;
                                next = Coord{
                                    150,
                                    50+(current.x()-150)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 1:
                                // Leaving 6 to the bottom, entering 2 from the top
                                nextDir = 1;
                                next = Coord {
                                    1,
                                    100+current.y()
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            case 2:
                                // Leaving 6 to the left, entering 1 from the top
                                nextDir = 1;
                                next = Coord{
                                    1,
                                    50+(current.x()-150)
                                };
                                assert(map[next.x()][next.y()] != Nothing);
                                break;
                            default:
                                IO::print("Wrong",sideMap[current],direction);
                                break;
                        }
                        break;
                }
                if(map[next.x()][next.y()] == Wall){
                    return make_tuple(current,direction,true);
                }
                assert(map[next.x()][next.y()] == Empty);
                return make_tuple(next,nextDir,false);
            case Empty:
                return make_tuple(next,direction,false);
            case Wall:
                return make_tuple(current,direction,true);
        }

#endif
    };

    array<char,4> symbols = {'>','v','<','^'};
    while (instrIdx != instructions.size()){
        auto nextIdx = instrIdx;
        while(instrIdx< instructions.size() && isdigit(instructions[nextIdx])){
            nextIdx++;
        }

        st steps = atoi(instructions.substr(instrIdx,(nextIdx-instrIdx)).c_str());

        for(int i = 0; i<steps;++i){
            pathMap[current.x()][current.y()] = symbols[direction];
            bool end;
            tie(current, direction, end) = getNext(current,direction);
            if(end){
                break;
            }
        }

        instrIdx = nextIdx;

        if(instrIdx < instructions.size()){
            if(instructions[instrIdx]=='R'){
                direction = (direction + 1)%4;
            } else if (instructions[instrIdx]=='L'){
                direction = (direction+3)%4;
            }
            ++instrIdx;
        }

        /*for(auto& line : pathMap){
            IO::print(line);
        }
        IO::print();*/
    }

    IO::print(1000*(current.x())+4*(current.y())+direction);
}

int main(int argc, char* argv[]){
  if(std::string(argv[1])=="--one"){
    part1();
  } else if(std::string(argv[1])=="--two"){
    part2();
  } else {
    std::cout << "Wrong usage. Allowed arguments: '--one' or '--two'";
  }
}

