/* Boxes Packing */
/* Problem Source: codeforces 903C */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	std::ios_base::sync_with_stdio(false);
	
	short n;
	std::cin >> n;
	std::vector<int> b(n);	//boxes
	for( auto &bb: b ) std::cin >> bb;
	std::sort( b.begin(), b.end() );
	int l, c{1}, mc{1};
	l=b.front();
	for( auto i=b.begin()+1; i!=b.end(); i++ ){
		if( *i == l ){
			++c;
			mc = std::max( c, mc );
		}
		else{
			c=1;
			l=*i;
		}
	}
	std::cout << mc << std::endl;

	return 0;
}
