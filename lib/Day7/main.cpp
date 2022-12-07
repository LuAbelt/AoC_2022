#include "lib.h"

class File {
public:
    i64 _size = 0;
    shared_ptr<File> _parent;
    string _name;
    map<string,shared_ptr<File>> _children;
public:
    File(string name,i64 size, shared_ptr<File> parent) :
    _name(name),
    _size(size),
    _parent(parent)
    {};

    File(File& Other) = default;

    shared_ptr<File> getParent() const {
        return _parent;
    }

    string getName() const {
        return _name;
    }

    virtual i64 getSize() const {
        return _size;
    }

    virtual void addChild(shared_ptr<File> child) {

    }

    virtual shared_ptr<File> getChild(const string&) {
        return nullptr;
    }
    virtual const map<string,shared_ptr<File>>& getChildren() const {
        return _children;
    }
};

class Directory
: public File {
private:
    map<string, shared_ptr<File>> _children;
public:
    Directory(string name, i64 size, shared_ptr<File> parent)
    :File(name,size,parent)
    {
    };

    void addChild(shared_ptr<File> f) override{
        _children[f->getName()] = f;
    }

    shared_ptr<File> getChild(const string &name) override {
        return _children[name];
    }

    virtual i64 getSize() const override {
        return std::accumulate(_children.begin(), _children.end(), 0,
                               [](i64 cur, auto entry){
            return cur + entry.second->getSize();
        });
    }

     const map<string,shared_ptr<File>>& getChildren() const override {
        return _children;
    }
};

void part1(){
    i64 total = 0;
    V<shared_ptr<Directory>> dirs;
    shared_ptr<File> _currentDir = nullptr;
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
                _currentDir = _currentDir->getParent();
                ++idx;
                continue;
            }

            if(!_currentDir){
                auto dir = make_shared<Directory>(targetDir, 0, _currentDir);
                dirs += dir;
                _currentDir = dir;
            } else if(_currentDir->getChildren().find(targetDir)==_currentDir->getChildren().end()){
                auto dir = make_shared<Directory>(targetDir, 0, _currentDir);
                dirs += dir;
                if (_currentDir) {_currentDir->addChild(dir);}
                _currentDir = dir;
            } else {
                auto itr = _currentDir->getChildren().find(targetDir);
                _currentDir = _currentDir->getChild(targetDir);
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

                    _currentDir->addChild(make_shared<File>(fname,size,_currentDir));
                }
                ++idx;
            }
        }
    }

    for(auto dir:dirs){
        if(dir->getSize()<=100000){
            total += dir->getSize();
        }
    }

    cout << total << endl;
}

void part2(){
    i64 total = 0;
    V<shared_ptr<Directory>> dirs;
    shared_ptr<File> _currentDir = nullptr;
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
                _currentDir = _currentDir->getParent();
                ++idx;
                continue;
            }

            if(!_currentDir){
                auto dir = make_shared<Directory>(targetDir, 0, _currentDir);
                dirs += dir;
                _currentDir = dir;
            } else if(_currentDir->getChildren().find(targetDir)==_currentDir->getChildren().end()){
                auto dir = make_shared<Directory>(targetDir, 0, _currentDir);
                dirs += dir;
                if (_currentDir) {_currentDir->addChild(dir);}
                _currentDir = dir;
            } else {
                auto itr = _currentDir->getChildren().find(targetDir);
                _currentDir = _currentDir->getChild(targetDir);
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

                    _currentDir->addChild(make_shared<File>(fname,size,_currentDir));
                }
                ++idx;
            }
        }
    }

    while(_currentDir->getParent()){
        _currentDir = _currentDir->getParent();
    }

    i64 unusedSpace = 70000000-_currentDir->getSize();
    i64 requiredSpace = 30000000 - unusedSpace;

    i64 current = _currentDir->getSize();

    set<string> names;

    for(auto& dir : dirs){
        names += dir->getName();
        if(dir->getSize()>=requiredSpace){
            current = min(current,dir->getSize());
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