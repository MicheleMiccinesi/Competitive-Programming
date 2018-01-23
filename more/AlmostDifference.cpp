/* Almost Difference */
/* Problem Source: codeforces 903D */
/* Solution License: contact Michele Miccinesi */


#include <unordered_map>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

typedef long double int128_t;
int main(){
	std::ios_base::sync_with_stdio(false);

	int64_t n, i;
	int64_t 	cl{0}, cr{0};
	int64_t lsum{0};
	int128_t sum;
	sum = static_cast<int128_t>( 0 );
	std::cin >> n;
	if( n==1 ) { 
		std::cout << 0 << std::endl;
		return 0;
	}

	std::unordered_map<int64_t, int64_t> v;

	int64_t j=0;
	while(j!=n){		
		std::cin >> i;

		sum += j*i-lsum;
		if( v.find(i-1) == v.end() ) cl = 0;
		else cl = v[i-1];
		if( v.find(i+1) == v.end() ) cr = 0;
		else cr = v[i+1];
		sum += cr-cl;

		if( v.find(i) == v.end() )
			v[i] = 1;
		else 
			++v[i];
		lsum += i;
		++j;
	}
	std::cout << std::fixed << std::setprecision(0) << sum << std::endl;


	return 0;
}
