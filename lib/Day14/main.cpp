#include "lib.h"

class Tomb {
    map<geometry::Point,bool> _blockedPositions;
    map<st,set<st>> _blockedByColumn;
    geometry::Point startPoint{500,0};
    i64 _bottom = 0;
    bool _useBottom = false;

    bool isFree(geometry::Point p){
        if(_useBottom){
            if(p.y>=_bottom){
                return false;
            }
        }
        return !_blockedPositions[p];
    }


public:
    bool addSand() {
        using geometry::Point;
        auto curPos = startPoint;

        if(!isFree(curPos)){
            return false;
        }


        while(_blockedByColumn[curPos.x].lower_bound(curPos.y)
        !=_blockedByColumn[curPos.x].end() || (_useBottom && curPos.y < _bottom)){
            if(_useBottom){
                if(_blockedByColumn[curPos.x].lower_bound(curPos.y)==_blockedByColumn[curPos.x].end()){
                    curPos.y = _bottom-1;
                } else {
                    curPos.y = (*_blockedByColumn[curPos.x].lower_bound(curPos.y))-1;
                }
            } else {
                curPos.y = (*_blockedByColumn[curPos.x].lower_bound(curPos.y))-1;
            }

            //Below is blocked, check if we can move down left:
            if(isFree(Point{curPos.x-1,curPos.y+1})){
                curPos = Point{curPos.x-1,curPos.y+1};
            } else if(isFree(Point{curPos.x+1,curPos.y+1})) {
                curPos = Point{curPos.x+1,curPos.y+1};
            } else {
                //We came to a stop
                //IO::print("Came to a stop at",curPos.x,curPos.y);
                _blockedPositions[curPos] = true;
                _blockedByColumn[curPos.x] += curPos.y;
                return true;
            }
        }

        return false;
    }

    Tomb(set<geometry::Point> blocked, bool useBottom = false)
    :_useBottom(useBottom)
    {
        for(auto p : blocked){
            _blockedPositions[p] = true;
            _blockedByColumn[p.x] += p.y;
            _bottom = max(_bottom,p.y+2);
        }
    }
};

void part1(){
    using IO::print;


    V<string> lines = IO::fromCin();
    i64 result = 0;

    st idx = 0;

    set<geometry::Point> blocked;
    for(auto& line : lines){
        auto parts = util::split(line,"->");

        for(st i = 0;i<parts.size()-1;++i){
            auto firstSplit = util::split(parts[i],",");
            auto firstCoord = util::fromString<st>(firstSplit);


            auto secondSplit = util::split(parts[i+1],",");
            auto secondCoord = util::fromString<st>(secondSplit);

            auto minX = min(firstCoord[0],secondCoord[0]);
            auto maxX = max(firstCoord[0],secondCoord[0]);
            auto minY = min(firstCoord[1],secondCoord[1]);
            auto maxY = max(firstCoord[1],secondCoord[1]);
            for(i64 x = minX;x<=maxX;++x){
                for(i64 y = minY;y<=maxY;++y){
                    blocked += geometry::Point{x,y};
                }
            }
        }

        ++idx;
    }

    Tomb tomb(blocked);

    while(tomb.addSand()){
        ++result;
    }

    print(result);
}

void part2(){

    using IO::print;


    V<string> lines = IO::fromCin();
    i64 result = 0;

    st idx = 0;

    set<geometry::Point> blocked;
    for(auto& line : lines){
        auto parts = util::split(line,"->");

        for(st i = 0;i<parts.size()-1;++i){
            auto firstSplit = util::split(parts[i],",");
            auto firstCoord = util::fromString<st>(firstSplit);


            auto secondSplit = util::split(parts[i+1],",");
            auto secondCoord = util::fromString<st>(secondSplit);


            auto minX = min(firstCoord[0],secondCoord[0]);
            auto maxX = max(firstCoord[0],secondCoord[0]);
            auto minY = min(firstCoord[1],secondCoord[1]);
            auto maxY = max(firstCoord[1],secondCoord[1]);
            for(i64 x = minX;x<=maxX;++x){
                for(i64 y = minY;y<=maxY;++y){
                    blocked += geometry::Point{x,y};
                }
            }
        }

        ++idx;
    }

    Tomb tomb(blocked,true);

    while(tomb.addSand()){
        ++result;
    }

    print(result);
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