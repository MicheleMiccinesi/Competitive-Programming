#include <iostream>
#include <queue>

unsigned short const boardBoxes = 30;

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	unsigned short snakesLadders[boardBoxes];
	bool boxesNew[boardBoxes];
	auto tsnakesLadders = snakesLadders-1;
	auto tboxesNew = boxesNew-1;

	unsigned short T;
	std::cin >> T;

	unsigned short N;
	unsigned short a;
	unsigned short ndiceRolls;
	unsigned short position, pos_i, pos_j;
	std::queue<unsigned short> movesBFS[2];
	bool i=0, ii=1;
	while( T-- ){
		for(auto &x: snakesLadders) x = &x-snakesLadders+1;
		for(auto &x: boxesNew) x = true;

		std::cin >> N;
		while(N--){
			std::cin >> a;
			std::cin >> tsnakesLadders[a];
		}

		ndiceRolls = 0;
		for(position = 1; position != tsnakesLadders[position]; tboxesNew[position] = false, position = tsnakesLadders[position]);
		if(position == boardBoxes){
			std::cout << ndiceRolls << std::endl;
			return 0;
		}
		movesBFS[i].push(position);

		while(!movesBFS[i].empty()){
			ndiceRolls++;
			while(!movesBFS[i].empty())
				for(position = movesBFS[i].front(), movesBFS[i].pop(), pos_i = position+1; pos_i != position+7; pos_i++){
					for(pos_j = pos_i; pos_j != tsnakesLadders[pos_j] && tboxesNew[pos_j]; tboxesNew[pos_j] = false, pos_j = tsnakesLadders[pos_j]);
					if(pos_j == boardBoxes){
						std::cout << ndiceRolls << std::endl;
						while(!movesBFS[i].empty()) movesBFS[i].pop();
						while(!movesBFS[ii].empty()) movesBFS[ii].pop();
						break;
					}
					else if( tboxesNew[pos_j] ) {
						movesBFS[ii].push(pos_j);	
						tboxesNew[pos_j] = false;
					}
				}
			i = !i;
			ii = !ii;
		}
	}
}
