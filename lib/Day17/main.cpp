#include "lib.h"

using Part = V<V<bool>>;

using Coord = transform::Coord<2>;

const array<V<V<bool>>,5> pieces = {
        {
                {{true,true,true,true}}
                ,{
                        {false,true,false},
                        {true,true,true},
                        {false,true,false}
                    }
                ,{
                        {true,true,true},
                        {false,false,true},
                        {false,false,true}
                    }
                , {
                        {true},
                        {true},
                        {true},
                        {true}
                    }
                ,{
                        {true,true},
                        {true,true}
                }
        }
};

const Coord LEFT = {-1,0};
const Coord RIGHT = {1,0};
const Coord DOWN = {0,-1};

void drawGrid(const set<Coord> &grid, const Part &activePiece, const Coord &position, i64 maxY,st maxRows = 20){
    V<string> visualization;
    visualization += "+-------+ 0";

    for(i64 i=0;i<maxY;++i){
        visualization += "|.......| " + to_string(i+1);
    }



    for(i64 yOff = 0 ;yOff<activePiece.size();++yOff){
        for(i64 xOff = 0; xOff<activePiece[yOff].size();++xOff){
            if(!activePiece[yOff][xOff]){
                continue;
            }
            auto p = position + Coord{xOff,yOff};
            assert(p.x()>=0);
            assert(p.x()<=7);
            assert(p.y()>=0);
            visualization[p.y()][p.x()+1] = '@';
        }
    }

    for(auto& position : grid){
        assert(position.x()>=0);
        assert(position.x()<=8);
        assert(position.y()>=0);

        visualization[position.y()][position.x()+1] = '#';
    }

    visualization[0] = "+-------+";

    for(auto line : visualization | ranges::views::reverse | ranges::views::take(maxRows)){
        IO::print(line);
    }
}

void drawGrid(const set<Coord> &grid, st maxY,st numRows = 20){
    V<string> visualization;
    visualization += "+-------+ 0";

    for(i64 i=0;i<maxY;++i){
        visualization += "|.......| " + to_string(i+1);
    }

    for(auto& position : grid){
        assert(position.x()>=0);
        assert(position.x()<=8);
        assert(position.y()>=0);

        visualization[position.y()][position.x()+1] = '#';
    }

    visualization[0] = "+-------+";

    for(auto line : visualization | ranges::views::reverse | ranges::views::take(numRows)){
        IO::print(line);
    }
}


bool movePart(const Coord &direction, set<Coord> &grid, Coord &position, Part &part){
    i64 pieceWidth = part[0].size();
    i64 pieceHeight = part.size();

    if((position.x()+direction.x())<0 || position.x()+pieceWidth+direction.x() > 7){
        return false;
    }

    for(i64 x = 0; x<pieceWidth;++x) {
        for (i64 y = 0; y < pieceHeight; ++y) {
            if (!part[y][x]) {
                continue;
            }

            if ((x + direction.x() >= 0) && (x + direction.x() < pieceWidth)
                && (y + direction.y() >= 0) && (y + direction.y() < pieceHeight)
                && part[y + direction.y()][x + direction.x()]) {
                continue;
            }

            Coord posToCheck = position + direction + Coord{x, y};

            if (grid.find(posToCheck) != grid.end()) {
                return false;
            }
        }
    }

        position += direction;
        return true;
}

void fixPart(Part &part, Coord &position, set<Coord> &grid){
    for(i64 y = 0; y<part.size();++y){
        for(i64 x = 0; x<part[y].size();++x){
            if(part[y][x]) {
                Coord fixPos = position + Coord{x, y};
                grid += fixPos;
            }
        }
    }
}

void part1(){
    string moves;
    getline(cin,moves);
    set<Coord> grid;

    for(int y = 0;y<=8;++y){
        grid += Coord{y,0};
    }

    st curHeight = 0;
    i64 moveIdx = 0;

    for(st move = 0; move<2022;++move){
        //IO::print("Spawn new piece");
        auto part = pieces[move % 5];
        auto position = Coord{2,(i64)curHeight+4};
        //drawGrid(grid,part,position,curHeight+7);

        while(true) {
            char dirChar = moves[moveIdx%moves.size()];
            switch (dirChar) {
                case '<':
                    //IO::print("Move piece left");
                    movePart(LEFT,grid,position,part);
                    //drawGrid(grid,part,position,curHeight+7);
                    break;

                case '>':
                    //IO::print("Move piece right");
                    movePart(RIGHT,grid,position,part);
                    //drawGrid(grid,part,position,curHeight+7);
                    break;
            }
            ++moveIdx;

            //IO::print("Move piece down");
            if(!movePart(DOWN,grid,position,part)){
                fixPart(part,position,grid);
                curHeight = max(curHeight,position.y()+part.size()-1);
                //drawGrid(grid,part,position,curHeight+7);
                break;
            }
            //drawGrid(grid,part,position,curHeight+7);
        }
    }

    drawGrid(grid,curHeight+5,curHeight+6);

    IO::print(curHeight);
}

void part2(){
    string moves;
    getline(cin,moves);
    set<Coord> grid;

    for(int y = 0;y<=8;++y){
        grid += Coord{y,0};
    }

    st curHeight = 0;
    st moveIdx = 0;

    struct Fingerprint {
        array<st,7> rowDepths;
        st partIdx;
        st moveIdx;

        auto operator<=>(const Fingerprint&) const = default;
    };

    map<Fingerprint, pair<st,st>> seen;
    decltype(seen)::iterator entry;
    const st numMovees = 1000000000000;
    st movesRemaining = 1000000000000;
    st partIdx = 0;

    while(movesRemaining>0){
        partIdx%=5;
        auto move = numMovees - movesRemaining;

        auto part = pieces[partIdx];
        auto position = Coord{2,(i64)curHeight+4};

        while(true) {
            moveIdx %= moves.size();
            char dirChar = moves[moveIdx];
            switch (dirChar) {
                case '<':
                    movePart(LEFT,grid,position,part);
                    break;

                case '>':
                    movePart(RIGHT,grid,position,part);
                    break;
            }
            ++moveIdx;

            if(!movePart(DOWN,grid,position,part)){
                fixPart(part,position,grid);
                curHeight = max(curHeight,position.y()+part.size()-1);
                //drawGrid(grid,part,position,curHeight+7);
                break;
            }
        }
        partIdx++;
        --movesRemaining;

        // Create Fingerprint for this move
        array<st,7> rowState{0,0,0,0,0,0,0};
        for(i64 x = 0;x<7;++x){
            Coord c{x,(i64)curHeight};
            while(grid.find(c)==grid.end()){
                rowState[x]++;
                c = Coord{x,(i64)curHeight - (i64)rowState[x]};
            }
        }

        Fingerprint fp{rowState,partIdx,moveIdx};

        if(seen.find(fp) != seen.end()){
            IO::print("Found fingerprint.");
            IO::print("Next part:",partIdx);
            IO::print("Next move:",moves[moveIdx]);
            entry = seen.find(fp);
            break;
        }

        seen[fp] = make_pair(movesRemaining,curHeight);
    }


    //Calculate number of moves this cycle took
    st cycleLength = entry->second.first - movesRemaining;
    st heightDiff = curHeight - entry->second.second;

    IO::print(numMovees-movesRemaining, curHeight, cycleLength,heightDiff);

    //We do not explicitly simulate the cycles
    st simulatedHeight = heightDiff * (movesRemaining/cycleLength);

    // We still need to finish the last few steps manually
    movesRemaining %= cycleLength;

    while(movesRemaining>0){
        partIdx %= 5;
        auto move = numMovees - movesRemaining;

        auto part = pieces[partIdx];
        auto position = Coord{2,(i64)curHeight+4};

        while(true) {
            moveIdx %= moves.size();
            char dirChar = moves[moveIdx];
            switch (dirChar) {
                case '<':
                    movePart(LEFT,grid,position,part);
                    break;

                case '>':
                    movePart(RIGHT,grid,position,part);
                    break;
            }
            ++moveIdx;

            if(!movePart(DOWN,grid,position,part)){
                fixPart(part,position,grid);
                curHeight = max(curHeight,position.y()+part.size()-1);
                break;
            }
        }

        --movesRemaining;
        partIdx++;
    }

    IO::print(simulatedHeight+curHeight);
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