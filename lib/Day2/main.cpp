#include <map>
#include <sstream>
#include "lib.h"
using namespace std;
enum Move {
    Rock,
    Paper,
    Scissors
};

map<Move,int> scores = {{Move::Rock, 1}, {Move::Paper, 2}, {Move::Scissors, 3}};

map<char,Move> choices = {{'A', Move::Rock}, {'B', Move::Paper}, {'C', Move::Scissors}
,                         {'X', Move::Rock}, {'Y', Move::Paper}, {'Z', Move::Scissors}};

int64_t get_outcome(Move opponent, Move me){
    if (me==opponent){
        return 3;
    }

    if(opponent == Move::Rock){
        if(me == Move::Paper){
            return 6;
        }
        return 0;
    }

    if(opponent == Move::Paper){
        if(me == Move::Scissors){
            return 6;
        }
        return 0;
    }

    if(opponent == Move::Scissors){
        if(me == Move::Rock){
            return 6;
        }
        return 0;
    }
}

void part1(){
    int64_t total_score = 0;
    for(string line;getline(cin,line);){
        stringstream ss(line);
        char opponent, me;

        ss >> opponent >> me;

        total_score += scores[choices[me]];
        total_score += get_outcome(choices[opponent],choices[me]);
    }

    cout << total_score << endl;
}

void part2(){
    int64_t total_score = 0;

    map<Move,Move> winsAgainst{{Move::Rock,     Move::Paper}
            ,                  {Move::Paper,    Move::Scissors}
            ,                  {Move::Scissors, Move::Rock}};

    map<Move,Move> losesAgainst{{Move::Rock,     Move::Scissors}
            ,                   {Move::Paper,    Move::Rock}
            ,                   {Move::Scissors, Move::Paper}};

    for(string line;getline(cin,line);){
        stringstream ss(line);
        char opponent, outcome;

        ss >> opponent >> outcome;

        switch (outcome) {
            case 'X':
                total_score += scores[losesAgainst[choices[opponent]]];
                break;
            case 'Y':
                total_score += 3;
                total_score += scores[choices[opponent]];
                break;
            case 'Z':
                total_score += 6;
                total_score += scores[winsAgainst[choices[opponent]]];
                break;
        }

    }

    cout << total_score << endl;
}

int main(int argc, char* argv[]){
    if(std::string(argv[1])=="--one"){
        part1ButCool();
    }else if(std::string(argv[1])=="--two"){
        part2();
    } else{
        std::cout << "Wrong usage!" << std::endl;
    }
}