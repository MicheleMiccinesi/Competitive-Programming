/* Mice */
/* Problem Source: codeforces 90B */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>

int main(){
	std::ios_base::sync_with_stdio( false );

	int32_t N;
	std::cin >> N;
	std::vector<int32_t> mice(N);
	std::cin >> N;
	std::vector<int32_t> cheeses(N);
	std::cin >> N >> N;
	for( auto &mouse: mice ) std::cin >> mouse;
	for( auto &cheese: cheeses ) std::cin >> cheese;
	auto icheese = cheeses.begin();
	int32_t hungryMice{0};
	bool isnew{true};
	int32_t D = 1<<30;

	for( auto& mouse: mice ){
//		std::cout << "topo: " << mouse;
		while( icheese < cheeses.end()-1 ){
			if( abs(icheese[1]-mouse) >= abs(icheese[0]-mouse) ) break;
			isnew = true;
			icheese++;
		}
		if( icheese == cheeses.end() ) hungryMice++;
		else if(!isnew){
			if ( abs(icheese[0]-mouse) > D ){
				if (icheese < cheeses.end()-1){
					if( abs(icheese[1]-mouse) != abs(icheese[0]-mouse) )
						hungryMice++;
					else {
						icheese++;
						D = abs(icheese[0]-mouse);
					}
				}
				else hungryMice++;
			}
			else if( D > abs(icheese[0]-mouse) ){
				D = abs(icheese[0]-mouse);
				if (icheese < cheeses.end()-1){
					if( abs(icheese[1]-mouse) != abs(icheese[0]-mouse) )
						hungryMice++;
					else icheese++;
				}
				else hungryMice++;
			}
		}
		else {
			isnew=false;
			D = abs(icheese[0]-mouse);
		}
//		std::cout << " formaggio: " << *icheese << "distanza: " << D << " affamati: " << hungryMice << std::endl;
	}

	std::cout << hungryMice << std::endl;

	return 0;
}
