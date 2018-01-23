/* Homework */
/* Problem Source: codeforces 102C */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

int main(){
	std::ios_base::sync_with_stdio(false);

	std::string s;
	std::cin >> s;
	int n;
	std::cin >> n;
	if( n>=s.size() ){
		std::cout << 0 << std::endl;
		return 0;
	}

	std::vector<int> A(26,0);
	for( auto &c: s )
		++A[c-'a'];
	std::vector<int> O(26);
	std::iota(O.begin(), O.end(), 0);
	std::sort(O.begin(), O.end(), [&A](int& a, int& b){
		return A[a]<A[b];});

	int i, tot;
	for( i=0, tot=A[O[0]]; tot<=n; ){
		A[O[i]]=0;
		if(++i!=26)
			tot+=A[O[i]];
	}
	int c = 0;
	for( auto &a: A ) if(a) ++c;
	std::cout << c << '\n';

	for( int j = 0; j!=s.size(); ++j )
		if(A[s[j]-'a'])std::cout << s[j];
	std::cout << std::endl;

	return 0;
}
