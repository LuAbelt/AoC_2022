#include "lib.h"
using transform::Coord3;

const array<Coord3,6> Directions = {
        Coord3{0,0,1},
        Coord3{0,0,-1},
        Coord3{0,1,0},
        Coord3{0,-1,0},
        Coord3{1,0,0},
        Coord3{-1,0,0},
};

auto parseInput(){
    auto lines = IO::fromCin();

    set<Coord3> coords;

    for( auto& line : lines){
        auto nums = util::fromString<i64>(util::split(line,","));

        coords += Coord3{nums[0],nums[1],nums[2]};
    }

    return coords;
}

void part1(){

    auto coords = parseInput();

    i64 total = 0;

    for(auto& c : coords){
        for (const auto& d : Directions){
            Coord3 candidate = c + d;

            if(coords.find(candidate)==coords.end()){
                ++total;
            }
        }
    }

    IO::print(total);
}

void part2(){
    auto coords = parseInput();

    geometry::BoundingBox bbox(*coords.begin(),*coords.begin());

    for(auto& c : coords){
        bbox.extend(c);
    }

    set<transform::Coord3> _relevantCoords;


    bbox.extend(bbox.min() + Coord3{-1,-1,-1});
    bbox.extend(bbox.max() + Coord3{1,1,1});

    auto start = bbox.min() ;

    set<Coord3> _explored;
    queue<Coord3> open;

    open += start;

    i64 total = 0;

    while(!open.empty()){
        auto current = open.front();open.pop();

        if(_explored.find(current)!=_explored.end()){
            continue;
        }
        _explored += current;
        for(auto& d : Directions){
            auto candidate = current + d;

            if(!bbox.contains(candidate)){
                continue;
            }


            if(_explored.find(candidate)!=_explored.end()){
                continue;
            }

            if(coords.find(candidate)!=coords.end()){
                //IO::print("Found coord",candidate.x(),candidate.y(),candidate.z(), "from", current.x(),current.y(),current.z());
                ++total;

            } else {
                open += candidate;
            }
        }
    }

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