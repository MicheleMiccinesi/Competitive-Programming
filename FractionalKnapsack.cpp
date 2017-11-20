#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct object{
	int32_t value;
	int32_t weight;
};

const int32_t N_MAX = 100;

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int32_t n, weight, currWeight, currValue;
	float fracValue;
	std::vector<object> objs;
	objs.reserve(N_MAX);

	unsigned short T;
	std::cin >> T;
	std::cout << std::fixed;
	while( T-- ){

		currValue = 0;
		currWeight = 0;
		std::cin >> n >> weight;
		objs.resize(n);

		for( auto &obj: objs ) 
			std::cin >> obj.value >> obj.weight;

		std::sort( objs.begin(), objs.end(), [](object& a, object& b){ return  a.value * b.weight  > b.value*a.weight ; } );

		for( auto &obj: objs ) {
			currWeight += obj.weight;
			currValue += obj.value;
			if( currWeight-weight > 0 ) {
				fracValue = static_cast<float>(currValue) - static_cast<float>(obj.value*(currWeight-weight)) / obj.weight;
				break;
			}
		}
		if( currWeight <= weight ) std::cout << std::setprecision(2) << static_cast<float>(currValue) << std::endl;
		else std::cout << std::setprecision(2) << fracValue << std::endl; 
	}
	return 0;
}
