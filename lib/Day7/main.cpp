#include "lib.h"

void part1(){
    using Tree = data_structures::Tree<>;
    i64 total = 0;
    V<shared_ptr<Tree>> dirs;
    shared_ptr<Tree> _currentDir = nullptr;
    V<string> lines;
    for(string line;getline(cin,line);) {
        lines+=line;
    }

    i64 idx = 0;
    while(idx<lines.size()) {
        string line = lines[idx];
        if(line.starts_with("$ cd")){
            string targetDir = line.substr(line.find_last_of(" ")+1);

            if(targetDir == ".."){
                _currentDir = _currentDir->parent();
                ++idx;
                continue;
            }

            if(!_currentDir){
                auto dir = make_shared<Tree>(targetDir, 0, _currentDir);
                dirs += dir;
                _currentDir = dir;
            } else if(!_currentDir->hasChild(targetDir)){
                auto dir = make_shared<Tree>(targetDir, 0, _currentDir);
                dirs += dir;
                if (_currentDir) {_currentDir->addChild(dir);}
                _currentDir = dir;
            } else {
                // Safe because we are only here if such a child exists
                _currentDir = _currentDir->getChildren().find(targetDir)->second;
            }
            ++idx;
        } else {
            // ls
            ++idx;
            while(idx<lines.size() && !lines[idx].starts_with("$")){
                string line1 = lines[idx];
                if(line1.starts_with("dir")){
                    // Do nothing?
                } else {
                    i64 size = atoi(line1.substr(0,line1.find(" ")).c_str());
                    string fname = line1.substr(line1.find(" ")+1);

                    _currentDir->addChild(make_shared<Tree>(fname,size,_currentDir));
                }
                ++idx;
            }
        }
    }

    for(auto dir:dirs){
        auto size = dir->evaluate(std::plus<i64>{},0LL);
        if(size <=100000){
            total += size;
        }
    }

    cout << total << endl;
}

void part2(){
    using Tree = data_structures::Tree<>;
    i64 total = 0;
    V<shared_ptr<Tree>> dirs;
    shared_ptr<Tree> _currentDir = nullptr;
    V<string> lines;
    for(string line;getline(cin,line);) {
        lines+=line;
    }

    i64 idx = 0;
    while(idx<lines.size()) {
        string line = lines[idx];
        if(line.starts_with("$ cd")){
            string targetDir = line.substr(line.find_last_of(" ")+1);

            if(targetDir == ".."){
                _currentDir = _currentDir->parent();
                ++idx;
                continue;
            }

            if(!_currentDir){
                auto dir = make_shared<Tree>(targetDir, 0, _currentDir);
                dirs += dir;
                _currentDir = dir;
            } else if(!_currentDir->hasChild(targetDir)){
                auto dir = make_shared<Tree>(targetDir, 0, _currentDir);
                dirs += dir;
                if (_currentDir) {_currentDir->addChild(dir);}
                _currentDir = dir;
            } else {
                _currentDir = _currentDir->getChildren().find(targetDir)->second;
            }
            ++idx;
        } else {
            // ls
            ++idx;
            while(idx<lines.size() && !lines[idx].starts_with("$")){
                string line1 = lines[idx];
                if(line1.starts_with("dir")){
                    // Do nothing?
                } else {
                    i64 size = atoi(line1.substr(0,line1.find(" ")).c_str());
                    string fname = line1.substr(line1.find(" ")+1);

                    _currentDir->addChild(make_shared<Tree>(fname,size,_currentDir));
                }
                ++idx;
            }
        }
    }

    while(_currentDir->parent()){
        _currentDir = _currentDir->parent();
    }

    auto rootSize = _currentDir->evaluate(std::plus<>{},0L);

    i64 unusedSpace = 70000000-rootSize;
    i64 requiredSpace = 30000000 - unusedSpace;

    i64 current = rootSize;

    set<string> names;

    for(auto& dir : dirs){
        auto size = dir->evaluate();
        if(size>=requiredSpace){
            current = min(current,size);
        }
    }

    cout << current << endl;
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