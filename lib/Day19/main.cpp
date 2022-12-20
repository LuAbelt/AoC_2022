#include "lib.h"

struct Blueprint{
    i64 oreCost;
    i64 clayCosts;
    i64pair obsidianCosts;
    i64pair geodeCosts;
};

auto parseInput(){
    using namespace util;

    auto lines = IO::fromCin();

    V<Blueprint> result;

    for( auto line : lines){
        line = line.substr(line.find(":")+1);
        auto parts = split(line,".");

        i64 oreCosts = atoi(split(parts[0], " ")[4].c_str());
        i64 clayCosts = atoi(split(parts[1], " ")[4].c_str());

        i64 obsidianOreCosts = atoi(split(parts[2], " ")[4].c_str());
        i64 obsidianClayCosts = atoi(split(parts[2], " ")[7].c_str());

        i64 geodeOreCosts = atoi(split(parts[3], " ")[4].c_str());
        i64 geodeClayCosts = atoi(split(parts[3], " ")[7].c_str());

        result += Blueprint{oreCosts,clayCosts, make_pair(obsidianOreCosts,obsidianClayCosts),make_pair(geodeOreCosts,geodeClayCosts)};
    }

    return result;
}

struct State {

    i64 numOre;
    i64 numClay;
    i64 numObsidian;

    i64 numOreRobots;
    i64 numClayRobots;
    i64 numObsidianRobots;

    i64 numGeodes;
    auto operator<=>(const State&) const = default;
private:
};

void part1(){
    auto bluePrints = parseInput();

    st idx = 1;
    st total = 0;

    auto theoreticalMax = [](i64 minutesLeft){
        return (minutesLeft*(minutesLeft+1))/2;
    };

    for( auto& bp : bluePrints) {
        i64 currentMax = 0;

        set<State> states;
        states += State{0
                        ,0
                        ,0
                        ,1
                        ,0
                        ,0
                        ,0};

        i64 maxOre = max(bp.oreCost,bp.clayCosts);
        maxOre = max(maxOre, bp.obsidianCosts.first);
        maxOre = max(maxOre, bp.geodeCosts.first);
        i64 maxClay = bp.obsidianCosts.second;
        i64 maxObsidian = bp.geodeCosts.second;

        for(st minute = 1;minute<=24;++minute){
            //IO::print("Blueprint",idx,"minute",minute,"Evaluating",states.size(),"states");
            set<State> newStates;

            i64 maxOreConsumed = maxOre * (24-minute);
            i64 maxClayConsumed = maxClay * (24-minute);
            i64 maxObsidianConsumed = maxObsidian * (24-minute);

            for(auto& state : states) {
                if(state.numGeodes + theoreticalMax(24-minute)<currentMax){
                    // We cannot achieve a better result from this state even if we could build a robot in every step
                    continue;
                }

                i64 oreProd = state.numOreRobots;
                i64 clayProd = state.numClayRobots;
                i64 obsidianProd = state.numObsidianRobots;

                if(state.numOre >= bp.geodeCosts.first && state.numObsidian >= bp.geodeCosts.second) {
                    i64 newOreCnt = state.numOre - bp.geodeCosts.first + oreProd;
                    i64 newObsidianCnt = state.numObsidian - bp.geodeCosts.second + obsidianProd;
                    i64 newClayCnt = state.numClay + clayProd;

                    newOreCnt = min(newOreCnt,maxOreConsumed);
                    newClayCnt = min(newClayCnt,maxClayConsumed);
                    newObsidianCnt = min(newObsidianCnt,maxObsidianConsumed);

                    i64 newNumGeodes = state.numGeodes + (24-minute);
                    newStates += State{newOreCnt
                                       ,newClayCnt
                                       ,newObsidianCnt
                                       ,state.numOreRobots
                                       ,state.numClayRobots
                                       ,state.numObsidianRobots
                                       ,newNumGeodes};
                    currentMax = max(newNumGeodes,currentMax);
                    continue;
                }

                //Build ore robot
                if( state.numOreRobots < maxOre && state.numOre >= bp.oreCost) {
                    i64 oreCnt = state.numOre - bp.oreCost + oreProd;
                    i64 clayCnt = state.numClay + clayProd;
                    i64 obsidianCnt = state.numObsidian + obsidianProd;

                    oreCnt = min(oreCnt,maxOreConsumed);
                    clayCnt = min(clayCnt, maxClayConsumed);
                    obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                    newStates += State {
                        oreCnt,
                        clayCnt,
                        obsidianCnt,
                        state.numOreRobots+1,
                        state.numClayRobots,
                        state.numObsidianRobots,
                        state.numGeodes
                    };
                }

                if( state.numClayRobots < maxClay && state.numOre >= bp.clayCosts){
                    i64 oreCnt = state.numOre - bp.clayCosts + oreProd;
                    i64 clayCnt = state.numClay + clayProd;
                    i64 obsidianCnt = state.numObsidian + obsidianProd;

                    oreCnt = min(oreCnt,maxOreConsumed);
                    clayCnt = min(clayCnt, maxClayConsumed);
                    obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                    newStates += State{oreCnt
                                        ,clayCnt
                                        ,obsidianCnt
                                        , state.numOreRobots
                                        , state.numClayRobots+1
                                        ,state.numObsidianRobots
                                        ,state.numGeodes};

                }

                // Build Obsidian robot
                if( state.numObsidianRobots < maxObsidian && state.numOre >= bp.obsidianCosts.first && state.numClay >= bp.obsidianCosts.second){
                        i64 oreCnt = state.numOre - bp.obsidianCosts.first + oreProd;
                        i64 clayCnt = state.numClay - bp.obsidianCosts.second + clayProd;
                        i64 obsidianCnt = state.numObsidian + obsidianProd;

                        oreCnt = min(oreCnt,maxOreConsumed);
                        clayCnt = min(clayCnt, maxClayConsumed);
                        obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                        newStates += State{oreCnt, clayCnt, obsidianCnt, state.numOreRobots, state.numClayRobots,
                                           state.numObsidianRobots + 1, state.numGeodes};
                }

                i64 oreCnt = state.numOre + oreProd;
                i64 clayCnt = state.numClay + clayProd;
                i64 obsidianCnt = state.numObsidian + obsidianProd;

                oreCnt = min(oreCnt,maxOreConsumed);
                clayCnt = min(clayCnt, maxClayConsumed);
                obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                newStates += State{
                    oreCnt
                    ,clayCnt
                    ,obsidianCnt
                    ,state.numOreRobots
                    ,state.numClayRobots
                    ,state.numObsidianRobots
                    ,state.numGeodes
                };
            }
            states = newStates;
        }
        IO::print("Blueprint",idx,"can open",currentMax,"geodes");
        total += currentMax*idx;
        ++idx;
    }

    IO::print(total);
}

namespace std {
    template <>
    class hash<State>
    {
    public:
        std::uint64_t operator()(const State& State) const
        {
            return State.numOre
                    + State.numClay *           100
                    + State.numObsidian *       10000
                    + State.numOreRobots *      1000000
                    + State.numClayRobots *     100000000
                    + State.numObsidianRobots * 10000000000
                    + State.numGeodes *         1000000000000;
        }
    };
}

void part2(){
    auto bluePrints = parseInput();

    st idx = 1;
    st total = 1;

    auto theoreticalMax = [](i64 minutesLeft){
        return (minutesLeft*(minutesLeft+1))/2;
    };

    for( auto& bp : bluePrints | ranges::views::take(3)) {
        i64 currentMax = 0;

        unordered_set<State> states;
        states += State{0,0,0,1,0,0,0};

        i64 maxOre = max(bp.oreCost,bp.clayCosts);
        maxOre = max(maxOre, bp.obsidianCosts.first);
        maxOre = max(maxOre, bp.geodeCosts.first);
        i64 maxClay = bp.obsidianCosts.second;
        i64 maxObsidian = bp.geodeCosts.second;

        for(st minute = 1;minute<=32;++minute){
            IO::print("xBlueprint",idx,"minute",minute,"Evaluating",states.size(),"states");
            unordered_set<State> newStates;

            i64 maxOreConsumed = maxOre * (32-minute);
            i64 maxClayConsumed = maxClay * (32-minute);
            i64 maxObsidianConsumed = maxObsidian * (32-minute);

            for(auto& state : states) {
                if(state.numGeodes + theoreticalMax(32-minute)<currentMax){
                    // We cannot achieve a better result from this state even if we could build a robot in every step
                    continue;
                }

                i64 oreProd = state.numOreRobots;
                i64 clayProd = state.numClayRobots;
                i64 obsidianProd = state.numObsidianRobots;

                if(state.numOre >= bp.geodeCosts.first && state.numObsidian >= bp.geodeCosts.second) {
                    i64 newOreCnt = state.numOre - bp.geodeCosts.first + oreProd;
                    i64 newObsidianCnt = state.numObsidian - bp.geodeCosts.second + obsidianProd;
                    i64 newClayCnt = state.numClay + clayProd;

                    newOreCnt = min(newOreCnt,maxOreConsumed);
                    newClayCnt = min(newClayCnt,maxClayConsumed);
                    newObsidianCnt = min(newObsidianCnt,maxObsidianConsumed);

                    i64 newNumGeodes = state.numGeodes + (32-minute);
                    newStates += State{newOreCnt
                            ,newClayCnt
                            ,newObsidianCnt
                            ,state.numOreRobots
                            ,state.numClayRobots
                            ,state.numObsidianRobots
                            ,newNumGeodes};
                    currentMax = max(newNumGeodes,currentMax);
                }

                //Build ore robot
                if( state.numOreRobots < maxOre && state.numOre >= bp.oreCost) {
                    i64 oreCnt = state.numOre - bp.oreCost + oreProd;
                    i64 clayCnt = state.numClay + clayProd;
                    i64 obsidianCnt = state.numObsidian + obsidianProd;

                    oreCnt = min(oreCnt,maxOreConsumed);
                    clayCnt = min(clayCnt, maxClayConsumed);
                    obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                    newStates += State {
                            oreCnt,
                            clayCnt,
                            obsidianCnt,
                            state.numOreRobots+1,
                            state.numClayRobots,
                            state.numObsidianRobots,
                            state.numGeodes
                    };
                }

                if( state.numClayRobots < maxClay && state.numOre >= bp.clayCosts){
                    i64 oreCnt = state.numOre - bp.clayCosts + oreProd;
                    i64 clayCnt = state.numClay + clayProd;
                    i64 obsidianCnt = state.numObsidian + obsidianProd;

                    oreCnt = min(oreCnt,maxOreConsumed);
                    clayCnt = min(clayCnt, maxClayConsumed);
                    obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                    newStates += State{oreCnt
                            ,clayCnt
                            ,obsidianCnt
                            , state.numOreRobots
                            , state.numClayRobots+1
                            ,state.numObsidianRobots
                            ,state.numGeodes};

                }

                // Build Obsidian robot
                if( state.numObsidianRobots < maxObsidian && state.numOre >= bp.obsidianCosts.first && state.numClay >= bp.obsidianCosts.second){
                    i64 oreCnt = state.numOre - bp.obsidianCosts.first + oreProd;
                    i64 clayCnt = state.numClay - bp.obsidianCosts.second + clayProd;
                    i64 obsidianCnt = state.numObsidian + obsidianProd;

                    oreCnt = min(oreCnt,maxOreConsumed);
                    clayCnt = min(clayCnt, maxClayConsumed);
                    obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                    newStates += State{oreCnt, clayCnt, obsidianCnt, state.numOreRobots, state.numClayRobots,
                                       state.numObsidianRobots + 1, state.numGeodes};
                }

                i64 oreCnt = state.numOre + oreProd;
                i64 clayCnt = state.numClay + clayProd;
                i64 obsidianCnt = state.numObsidian + obsidianProd;

                oreCnt = min(oreCnt,maxOreConsumed);
                clayCnt = min(clayCnt, maxClayConsumed);
                obsidianCnt = min(obsidianCnt, maxObsidianConsumed);

                newStates += State{
                        oreCnt
                        ,clayCnt
                        ,obsidianCnt
                        ,state.numOreRobots
                        ,state.numClayRobots
                        ,state.numObsidianRobots
                        ,state.numGeodes
                };
            }
            states = newStates;
        }
        IO::print("Blueprint",idx,"can open",currentMax,"geodes");
        total *= currentMax;
        ++idx;
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