/* Longest Palindromic Subsequence */
/* 2*n auxiliar space */
/* TLE on g4g */
/* but utterly fast on my laptop with -O3 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(){
	std::ios_base::sync_with_stdio(false);

	std::string s;
	std::string::iterator sB, sE, is;
	std::string::reverse_iterator ris;
	std::vector<int> pv;
	decltype(pv)::iterator ipv; 
	std::vector<int> p;
	int tp[2];	bool i{0};
	decltype(p)::iterator pB, ip;

	int max, maxp, maxpv;


	int T;
	std::cin >> T;
	while(T--){
		std::cin >> s;
		sB = s.begin();	sE = s.end();
		pv.resize(s.size()+1);	std::fill(pv.begin(), pv.end(), 0);	ipv = pv.end()-1;
		p.resize(s.size()+1);	std::fill(p.begin(), p.end(), 0);
		pB = p.begin()+1;

		for( ris = s.rbegin(); sE-- != sB; ris++, ipv-- ){
			is = sB;	tp[i]=0;
			for( ip = pB; is!=sE; is++, ip++ ){
				tp[!i] = *ip;
				*ip = ( *is==*ris ? tp[i]+1 : std::max(ip[0],ip[-1]) );
				i=!i;
			}
			*ipv = ( *is==*ris ? tp[i]+1 : std::max(ip[0],ip[-1]) );
		}
		maxp = *std::max_element(p.begin(), p.end());
		maxpv = *std::max_element(pv.begin(), pv.end());
		max = (maxpv>maxp ? 2*maxpv-1 : (maxp<<1) );
		std::cout << max << '\n';
	}
	std::cout << std::flush;
	return 0;
}
