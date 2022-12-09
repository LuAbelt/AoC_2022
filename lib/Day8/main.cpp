#include "lib.h"

void part1(){
	V<V<i64>> grid;
for(string line{}; getline(cin,line);){
	grid.push_back({});
	for(auto c : line){
		grid.back().push_back(c-'0');
	}
}

V<V<bool>> visible(grid.size(),V<bool>(grid[0].size(),false));
i64 maxH =0;
V<i64> maxV(grid[0]);

for(size_t i =0;i<grid[0].size();++i){
visible[0][i] = true;
visible[grid.size()-1][i] =true;
}

for(size_t i=0;i<grid.size();i++){
	visible[i][0]=true;
	visible[i][grid[i].size()-1] = true;
}
for(size_t y = 1;y<grid.size()-1;++y){
	maxH = grid[y][0];
	for(size_t x = 1;x<grid[y].size()-1;++x){
		printf("Checking (%d|%d) (v=%d,mH=%d,mV=%d)\n",x,y,grid[x][y],maxH,maxV[x]);
		if(grid[y][x]>maxH || grid[y][x] > maxV[x]){
			visible[y][x] = true;
		}

		maxH = max(maxH,grid[y][x]);
		maxV[x] = max(maxV[x], grid[y][x]);
	}
}

maxH = 0;
maxV = grid[grid.size()-1];

cout <<"End check left ajove" << endl;

for(size_t y = grid.size()-2;y>0;--y){
	maxH = grid[y][grid[y].size()-1];
	cout << grid[y].size()-1 << "/" << y << endl;
	for(size_t x = grid[y].size()-2;x>0;--x){
		printf("Checking (%d|%d) (v=%d,mH=%d,mV=%d)\n",x,y,grid[x][y],maxH,maxV[x]);
		if(grid[y][x]>maxH || grid[y][x] > maxV[x]){
			visible[y][x] = true;
		}
maxH = max(maxH,grid[y][x]);
		maxV[x] = max(maxV[x], grid[y][x]);
	}
}

i64 cnt=0;
i64 y = 0;
i64 x = 0;
for ( auto row : visible){
	x=0;
	for(bool entry : row){
	if (entry){
	       	++cnt;
		//printf("(%d|%d) is visible\n",x,y);
	}
	cout << entry;
	++x;
	}
	++y;
	cout << endl;
}

cout << cnt << endl;
}

void part2(){
	V<V<i64>> grid;
for(string line{}; getline(cin,line);){
	grid.push_back({});
	for(auto c : line){
		grid.back().push_back(c-'0');
	}
}

V<V<i64>> score1(grid.begin()->size(),V<i64>(grid.size(),0));
V<V<i64>> score2(grid.begin()->size(),V<i64>(grid.size(),0));
V<i64> lastIdxH = {0,0,0,0,0,0,0,0,0,0};
V<V<i64>> lastIdxV(grid[0].size(), lastIdxH);
for(size_t y = 0;y<grid.size();++y){
	lastIdxH = {0,0,0,0,0,0,0,0,0,0};

	for(size_t x = 0;x<grid[y].size();++x){
		auto v = grid[y][x];
		
		auto lastH = lastIdxH[v];
		auto lastV = lastIdxV[x][v];
		for (auto i = v+1;i<10;++i){
		//cout << i << endl;
			lastH = max(lastH,lastIdxH[i]);
			lastV = max(lastV,lastIdxV[x][i]);
		}
		
		score1[y][x] = (x-lastH) * (y-lastV);
		assert(score1[y][x]>=0);

		lastIdxH[v] = x;
		lastIdxV[x][v] = y;
	}
}

lastIdxH = V<i64>(10,grid[grid.size()-1].size()-1);
lastIdxV = V<V<i64>>(grid[0].size(), V<i64>(10,grid.size()-1));

for(i64 y = grid.size()-1;y>=0;--y){
lastIdxH = V<i64>(10,grid[y].size()-1);
	for(i64 x = grid[y].size()-1;x>=0;--x){

		auto v = grid[y][x];
		
		auto lastH = lastIdxH[v];
		auto lastV = lastIdxV[x][v];
		for (auto i = v+1;i<10;++i){
			lastH = min(lastH,lastIdxH[i]);
			lastV = min(lastV,lastIdxV[x][i]);
		}
		
		score2[y][x] = (lastH-x) * (lastV-y);

		assert(score2[y][x]>=0);
		lastIdxH[v] = x;
		lastIdxV[x][v] = y;

	}

}
i64 maxV = 0;
for(auto y = 0ul;y<grid.size();++y){
	for(i64 x =0;x<grid[y].size();++x){
		//printf("(%d/%d) - [%d|%d]\n", y,x,score1[y][x],score2[y][x]);
		maxV = max(maxV,score1[y][x] * score2[y][x]);
	}
}
cout << maxV << endl;
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
