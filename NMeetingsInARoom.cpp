#include <iostream>
#include <vector>
#include <algorithm>

const uint16_t N_MAX = 100;

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<uint32_t> S;		//starting time
	S.reserve(N_MAX);
	auto tS = S.begin()-1;			//meetings numbered from 1
	std::vector<uint32_t> F;		//finishing time
	F.reserve(N_MAX);
	auto tF = F.begin()-1;			//meetings numbered from 1
	std::vector<uint16_t> P;		//pointer for sorting
	P.reserve(N_MAX);
	auto tP = P.begin()-1;


	uint16_t T;
	uint16_t N;
	uint32_t lastF;
	std::cin >> T;
	while(T--){
		std::cin >> N;
		S.resize(N);
		F.resize(N);
		P.resize(N);
		for( auto& x: S) std::cin >> x;
		for( auto& x: F) std::cin >> x;

		for( auto x = P.begin(); x != P.end(); x++ ) *x = (x-tP);
		std::sort( P.begin(), P.end(), [&tF](uint16_t& a, uint16_t& b){ return tF[a] < tF[b]; } );	

		lastF = 0;	
		for( auto& i: P )
			if( tS[i] > lastF ){
				std::cout << i << ' ';
				lastF = tF[i];
			}
		std::cout << std::endl;
	}
	return 0;
}
