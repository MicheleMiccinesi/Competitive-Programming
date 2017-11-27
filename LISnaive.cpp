/* Longest Increasing Sequence */
/* Naive DP Algorithm */

#include <iostream>
#include <vector>
#include <algorithm>

const unsigned short N_MAX = 100;

struct LisEl{
	unsigned short v;
	unsigned short c;
	std::vector<LisEl>::iterator p;
};

unsigned short LIS( std::vector<LisEl>& S ){
	auto iSB = S.begin(), iSE = S.end();

	for( auto iiS = iSB; iiS != iSE; iiS++ ){
		for( auto iS = iSB; iS != iiS; iS++ )
			if( iS->v < iiS->v && iS->c >= iiS->c ){
				iiS->c = iS->c+1;
				iiS->p = iS;
			}
	}

	auto i = iSB;
	for( auto ii = iSB; ii!=iSE; ii++ ) 
		if( ii->c > i->c ) i = ii;
	return i->c;
}



int main(){
	std::ios_base::sync_with_stdio(false);

	std::vector<LisEl> S(N_MAX);
	unsigned short N;

	unsigned short T;
	std::cin >> T;
	while(T--){
		std::cin >> N;
		if(N){
			S.resize(N);

			for( auto is = S.begin(); is!=S.end(); is++ ){
				is->p = is;
				is->c = 1;
				std::cin >> is->v;
			}
			std::cout << LIS(S) <<'\n';
		} else std::cout << 0 <<'\n';
	}

	std::cout << std::flush;

	return 0;
}
