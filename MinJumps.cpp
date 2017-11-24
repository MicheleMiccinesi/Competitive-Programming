#include <iostream>
#include <vector>

const unsigned short N_MAX = 100;

int main(){
	unsigned short n;
	std::vector<unsigned short> jumps;
	jumps.reserve(N_MAX);

	unsigned short T;
	std::cin >> T;

	while(T--){
		std::cin >> n;
		jumps.resize(n);
		for( auto &j: jumps ) std::cin >> j;
		
		bool i{0}, j{1};
		unsigned short le[] = {1, 1+jumps[0]}; 		//last end
		unsigned short countJump = 1;
		while( le[j]<n ){
			countJump++;
			for( unsigned short k = le[i]; k!= le[j] ; k++ )
				if( k+jumps[k] >= le[i] )
					le[i] = k+jumps[k]+1;
			i = !i;
			j = !j;
			if( le[j] <= le[i] )
				break;
		}

		if( le[j] >= n ) 
			std::cout << countJump << std::endl;
		else 
			std::cout << -1 << std::endl;
	}

	return 0;
}
