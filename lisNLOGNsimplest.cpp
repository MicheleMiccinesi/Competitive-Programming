/* simplest O(n log n) time cost */

#include <iostream>
#include <vector>
#include <algorithm>

const int16_t N_MAX = 1000;
/* In position ls[i] there is the minimum last element (by now) of the LIS of length i+1 */

int main(){
	
	std::vector<int16_t> ls(0);
	ls.reserve(N_MAX);
	decltype(ls)::iterator ils;
	size_t n;
	int16_t el;

	unsigned short T;
	std::cin >> T;

	while(T--){
		std::cin >> n;
		ls.resize(0);
		while(n--){
			std::cin >> el;
			ils = std::lower_bound(ls.begin(), ls.end(), el);
			if( ils == ls.end() )
				ls.emplace_back(el);
			else *ils = el;
		}
		std::cout << ls.size() << '\n';
	}
	std::cout << std::flush;

	return 0;
}
