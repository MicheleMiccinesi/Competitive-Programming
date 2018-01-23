/* Party Lemonade */
/* Problem Source: codeforces 913C */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>

#define NDEBUG
uint64_t uno = 1;
int main(){
	std::ios_base::sync_with_stdio(false);

	uint64_t n, L;
	std::cin >> n >> L;
	std::vector<uint64_t> c(n);
	for( auto &cc: c ) std::cin >> cc;
	c.resize(32);
	
	uint64_t i;
	for( i=1; i!=n; ++i )
		if( c[i]>(c[i-1]<<1) ) c[i] = (c[i-1]<<1);
	for( i=n; i!=32; ++i ) c[i] = (c[i-1]<<1);

#ifndef NDEBUG
	for( auto &cc: c ) std::cout << cc <<' ';
		std::cout << '\n';
#endif
	
	uint64_t cost = 0;
	for( i=0; L||i<n; ++i ){
		if( c[i]<cost ) cost = c[i];
		if( L&(uno<<i) ) cost += c[i];
		L&= ~( (uno<<(i+1))-1 );
	}
	std::cout << cost << std::endl;


	return 0;
}
