#include <map>
#include <sstream>
#include "lib.h"
using namespace std;
enum PlayChoice{
    Rock,
    Paper,
    Scissors
};

map<PlayChoice,int> scores = {{PlayChoice::Rock,1},{PlayChoice::Paper,2},{PlayChoice::Scissors,3}};

map<char,PlayChoice> choices = {{'A',PlayChoice::Rock},{'B',PlayChoice::Paper},{'C',PlayChoice::Scissors}
,{'X',PlayChoice::Rock},{'Y',PlayChoice::Paper},{'Z',PlayChoice::Scissors}};

int64_t get_outcome(PlayChoice opponent, PlayChoice me){
    if (me==opponent){
        return 3;
    }

    if(opponent==PlayChoice::Rock){
        if(me==PlayChoice::Paper){
            return 6;
        }
        return 0;
    }

    if(opponent==PlayChoice::Paper){
        if(me==PlayChoice::Scissors){
            return 6;
        }
        return 0;
    }

    if(opponent==PlayChoice::Scissors){
        if(me==PlayChoice::Rock){
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

    map<PlayChoice,PlayChoice> winsAgainst{{PlayChoice::Rock,PlayChoice::Paper}
            ,{PlayChoice::Paper,PlayChoice::Scissors}
            ,{PlayChoice::Scissors,PlayChoice::Rock}};

    map<PlayChoice,PlayChoice> losesAgainst{{PlayChoice::Rock,PlayChoice::Scissors}
            ,{PlayChoice::Paper,PlayChoice::Rock}
            ,{PlayChoice::Scissors,PlayChoice::Paper}};

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
        part1();
    }else if(std::string(argv[1])=="--two"){
        part2();
    } else{
        std::cout << "Wrong usage!" << std::endl;
    }
}