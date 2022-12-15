#include "lib.h"

struct Sensor{
    transform::Coord<2> ownPos;
    transform::Coord<2> beaconOffset;
};


struct Range{
    i64 begin,end;

    bool operator<(const Range & Other) const {
        if(begin==Other.begin){
            return end<Other.end;
        }

        return begin<Other.begin;
    };
};

auto parseInput(){
    using namespace util;
    auto lines = IO::fromCin();

    V<Sensor> sensors;

    for (auto& line : lines){
        auto parts = split(line,":");

        auto sensorPart = split(parts[0], "at ")[1];
        auto sensorCoords = split(sensorPart,",");
        auto sensorX = atoi(split(sensorCoords[0],"=")[1].c_str());
        auto sensorY = atoi(split(sensorCoords[1],"=")[1].c_str());


        auto beaconPart = split(parts[1], "at ")[1];
        auto beaconCoords = split(beaconPart,",");
        auto beaconX = atoi(split(beaconCoords[0],"=")[1].c_str());
        auto beaconY = atoi(split(beaconCoords[1],"=")[1].c_str());

        transform::Coord<2> sensorPos{sensorX,sensorY};
        transform::Coord<2> beaconPos{beaconX,beaconY};
        sensors += Sensor{sensorPos,beaconPos-sensorPos};
    }

    return sensors;
}

void part1() {
    i64 targetRow = 2000000;

    auto sensors = parseInput();

    set<Range> coveredRanges;
    set<i64> beaconX;
    for (const auto& sensor:sensors){
        // Can we reach the targetrow?
        i64 yDiff = targetRow-sensor.ownPos.y();
        auto beaconPos = sensor.ownPos + sensor.beaconOffset;
        if(beaconPos.y()==targetRow){
            beaconX += beaconPos.x();
        }
        if( abs(yDiff) <= sensor.beaconOffset.manhattanLength() ){
            i64 xOff = sensor.beaconOffset.manhattanLength()-abs(yDiff);
            Range r{sensor.ownPos.x() - xOff, sensor.ownPos.x() + xOff};
            coveredRanges += r;
        }
    }

    //Merge ranges
    set<Range> mergedRanges;
    Range activeRange = *coveredRanges.begin();

    for(const auto& range : coveredRanges){
        if(range.begin < activeRange.end+1){
            activeRange.end = max(activeRange.end,range.end);
        } else {
            mergedRanges += activeRange;
            activeRange = range;
        }
    }

    mergedRanges += activeRange;

    i64 total = 0;
    auto currentBeacon = beaconX.begin();
    for(auto &r : mergedRanges){
        while(currentBeacon != beaconX.end() && *currentBeacon<r.begin){
            ++currentBeacon;
        }
        total += (r.end-r.begin)+1;

        if(*currentBeacon >= r.begin && *currentBeacon <= r.end ){
            --total;
        }
    }

    IO::print(total);
}


void part2(){
    auto sensors = parseInput();
    i64 boundMax = 4000000;
    V<set<Range>> ranges(boundMax+1);

    for(auto& sensor: sensors){
        auto manhattan = sensor.beaconOffset.manhattanLength();

        //IO::print("Sensor at ",sensor.ownPos.x(),sensor.ownPos.y());
        for(i64 yOff = 0; yOff <= manhattan;++yOff){
            i64 xOff = manhattan-yOff;
            i64 begin = max(0L,sensor.ownPos.x()-xOff);
            if(begin>boundMax){
                continue;
            }
            i64 end = min(boundMax, sensor.ownPos.x()+xOff);

            auto y = sensor.ownPos.y()+yOff;

            if(y>=0 && y<=boundMax){
                ranges[y] += Range{begin,end};
            }
            y = sensor.ownPos.y()-yOff;
            if(y>=0 && y<=boundMax){
                ranges[y] += Range{begin,end};
            }
        }
    }

    i64 finalX,finalY;
    bool found = false;
    for(i64 y = 0;y<=boundMax;++y){
        found = false;
        auto activeRange = *ranges[y].begin();
        if(activeRange.begin!=0){
            finalY = y;
            finalX = 0;
            break;
        }

        for(auto& range : ranges[y]){
            if(range.begin < activeRange.end+1){
                activeRange.end = max(activeRange.end,range.end);
            } else {
                finalX = activeRange.end+1;
                finalY = y;
                found = true;
                break;
            }
        }
        if(found){
            break;
        }
    }
    IO::print(finalX,finalY);
    IO::print(finalX*4000000+finalY);
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