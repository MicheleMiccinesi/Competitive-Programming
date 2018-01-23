/* Alarm Clock */
/* Problem Source: codeforces 898D */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	std::ios_base::sync_with_stdio(false);

	int n,m,k;
	std::cin >> n >> m >> k;
	if(k==1) {
		std::cout << n << std::endl;
		return 0;
	}

	std::vector<int> a(n);
	for( auto &aa: a ) std::cin >> aa;
	std::sort( a.begin(), a.end() );
	
	int i, j, c;
	for( c=0, i=0, j=k-1; j!=n; ++j )
		if( a[j]<a[i]+m ) a[j]=!++c;
		else while( !a[++i] );

	std::cout << c << std::endl;

	return 0;
}
