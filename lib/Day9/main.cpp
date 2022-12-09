#include "lib.h"

void part1(){
	using geometry::Point;
	set<Point> positions{Point{0,0}};

	Point tail{0,0};
	Point head{0,0};

	for(string line;getline(cin,line);){
		char move = line[0];
		size_t amount = atoi(line.substr(2).c_str());
		//IO::print(move, amount);
		switch (move){
		case 'R':
		head.x+=amount;
		break;
		
		case 'U':
		head.y+=amount;
		break;
		
		case 'L':
		head.x-=amount;
		break;
		
		case 'D':
		head.y-=amount;
		break;
		
		}

		while( (abs(head.x-tail.x))>1 || (abs(head.y-tail.y)>1) ){
			if (head.x==tail.x) {
				if(tail.y<head.y){
					tail.y+=1;
				} else {
					tail.y-=1;
				}
			} else if (head.y==tail.y){
				if(tail.x<head.x){
					tail.x+=1;
				} else {
					tail.x-=1;
				}
			} else if (head.x < tail.x) {
				if(tail.y<head.y){
					tail.y+=1;
					tail.x-=1;
				} else {
					tail.y-=1;
					tail.x-=1;
				}
			} else {
				if(tail.y<head.y){
					tail.y+=1;
					tail.x+=1;
				} else {
					tail.y-=1;
					tail.x+=1;
				}
			}
			//cout << tail.x << " " << tail.y << endl;
			positions += tail;		
		}
	}

	cout << positions.size() << endl;
}

void part2(){
	using geometry::Point;
	set<Point> positions{Point{0,0}};

	array<Point,10> Rope{Point{0,0}};

	for(string line;getline(cin,line);){
	{
			Point &head = Rope[0];
		char move = line[0];
		size_t amount = atoi(line.substr(2).c_str());
		//IO::print(move, amount);
		switch (move){
		case 'R':
		head.x+=amount;
		break;
		
		case 'U':
		head.y+=amount;
		break;
		
		case 'L':
		head.x-=amount;
		break;
		
		case 'D':
		head.y-=amount;
		break;
		
		}
	}

		while( (abs(Rope[0].x-Rope[1].x))>1 || (abs(Rope[0].y-Rope[1].y)>1) ){
			//IO::print("Rope[0]:", Rope[0].x, Rope[0].y, "Rope[1]:", Rope[1].x, Rope[1].y);
			
			for(st idx = 1;idx<10;++idx){
				Point &head = Rope[idx-1];
				Point &tail = Rope[idx];
				if(abs(head.x-tail.x)<=1 && abs(head.y-tail.y)<=1){
					continue;
				}
			if (head.x==tail.x) {
				if(tail.y<head.y){
					tail.y+=1;
				} else {
					tail.y-=1;
				}
			} else if (head.y==tail.y){
				if(tail.x<head.x){
					tail.x+=1;
				} else {
					tail.x-=1;
				}
			} else if (head.x < tail.x) {
				if(tail.y<head.y){
					tail.y+=1;
					tail.x-=1;
				} else {
					tail.y-=1;
					tail.x-=1;
				}
			} else {
				if(tail.y<head.y){
					tail.y+=1;
					tail.x+=1;
				} else {
					tail.y-=1;
					tail.x+=1;
				}
			}
			}
			//cout << tail.x << " " << tail.y << endl;
			positions += Rope[9];		
		}
	}

	cout << positions.size() << endl;
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
