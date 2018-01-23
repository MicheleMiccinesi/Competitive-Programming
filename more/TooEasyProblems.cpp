/* Too Easy Problems */
/* Problem Source: codeforces 913D */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

struct p{
	int a,t;
};

int main(){
	std::ios_base::sync_with_stdio(false);

	int n,T;
	std::cin >> n >> T;

	std::vector<p> P(n);
	for( auto &pp: P ) std::cin >> pp.a >> pp.t;

	std::vector<int> o(n);
	std::iota(o.begin(), o.end(), 0);
	std::sort(o.begin(), o.end(), [&P](int &a, int &b){
		return P[a].a!=P[b].a?P[a].a>P[b].a:P[a].t<P[a].t;
	});

	int mT{0},K=0;
	auto cmp = [&P](const int& a, const int& b)->bool{ return P[a].t!=P[b].t?P[a].t<P[b].t:a<b; };
	std::set<int,decltype(cmp)> S(cmp);
	decltype(S)::iterator last;
	for( auto &oo: o ){
		if( P[oo].t>T ) continue;
		if( K<P[oo].a ){
			if( mT+P[oo].t<=T ){
				S.emplace(oo);
				mT+=P[oo].t;
				++K;
			} else if( P[oo].t<P[*--(last=S.end())].t ){
				mT-=(P[*last].t-P[oo].t);
				S.erase(last);
				S.emplace_hint(S.end(),oo);
			}
		} else break;
	}

	std::cout << K << '\n' << K << '\n';
	for( auto &ss: S ) std::cout << ss+1 << ' ';
	std::cout << std::endl;

	return 0;
}
