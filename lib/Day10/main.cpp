#include "lib.h"

void part1(){

	i64 X = 1;
	i64 cycle = 0;
	i64 total = 0;

	for(string line;getline(cin,line)&&cycle<=220;){
		++cycle;

			//printf("cycle: %d, X: %d\n",cycle,X);
		if(((cycle-20)%40)==0){
			printf("cycle: %d, X: %d\n",cycle,X);
			total+=X*cycle;
		}

		if(line.starts_with("addx")){

		++cycle;

			//printf("cycle: %d, X: %d\n",cycle,X);
		if(((cycle-20)%40)==0){
			printf("cycle: %d, X: %d\n",cycle,X);
			total+=X*cycle;
		}

			i64 v = atoi(line.substr(4).c_str());
			X+=v;
		}
	}
	cout << total << endl;
}

void part2(){

	i64 X = 1;
	i64 cycle = 0;
	i64 total = 0;
	
	V<string> buffer(6,string(40,'.'));

	for(string line;getline(cin,line);){
		cout << cycle << endl;
		if(abs(X-(cycle%40))<=1){
			buffer[(cycle)/40][(cycle)%40] = '#';

		}
		++cycle;
			//printf("cycle: %d, X: %d\n",cycle,X);
		if(((cycle-20)%40)==0){
			//printf("cycle: %d, X: %d\n",cycle,X);
			total+=X*cycle;
		}

		if(line.starts_with("addx")){

		if(abs(X-(cycle%40))<=1){
			buffer[(cycle)/40][(cycle)%40] = '#';
		}
		++cycle;

			//printf("cycle: %d, X: %d\n",cycle,X);
		if(((cycle-20)%40)==0){
			//printf("cycle: %d, X: %d\n",cycle,X);
			total+=X*cycle;
		}

			i64 v = atoi(line.substr(4).c_str());
			X+=v;
		}
	}
	cout << total << endl;
	for(auto line : buffer){
		cout << line << endl;
	}
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
