/* Square Root of Permutation */
/* Problem Source: codeforces 612E */
/* Solution License: contact Michele Miccinesi */
/* Solution O(n): by cycles */

#include <iostream>
#include <vector>

namespace _permutation_sqrt{

inline std::vector<std::vector<std::vector<int>>> get_cycles(const auto &p){
	std::vector<std::vector<std::vector<int>>> c(p.size()+1, std::vector<std::vector<int>>());
	std::vector<bool> v(p.size(), 0);
	for( int i=1; i!=p.size(); ++i ){
		if( v[i]==false ){
			std::vector<int> cycle;
			cycle.emplace_back(i);
			v[i]=true;
			for( int j=p[i]; j!=i; j=p[j] ){
				cycle.emplace_back(j);
				v[j]=true;
			}
			c[cycle.size()].emplace_back(std::move(cycle));
		}
	}
	return c;
}

inline bool it_is_square(const auto &c){
	for(int i=0; i<c.size(); i+=2)
		if( c[i].size() & 1 )
			return false;
	return true;
}

}//end namespace _permutation_sqrt

inline std::vector<int> sqrt(auto &p){
	using namespace _permutation_sqrt;

	std::vector<int> s(p.size());
	auto c(get_cycles(p));

	if(!it_is_square(c))
		return std::vector<int>(0);

	for( int i=(p.size()>>1)&-2; i; i-=2 ){
		while( !c[i].empty() ){
			int ii=i<<1;
			c[ii].emplace_back(std::move(std::vector<int> (ii)));
			for( int j=0, k=0; j!=c[ii].back().size(); j+=2, ++k )
				c[ii].back()[j]=c[i].back()[k];
			c[i].pop_back();
			for( int j=1, k=0; k!=c[i].back().size(); j+=2, ++k )
				c[ii].back()[j]=c[i].back()[k];
			c[i].pop_back();
		}
	}

	for( auto &cc: c[1] )
		s[cc[0]]=cc[0];
	for( int i=3, j=2; i<c.size(); i+=2, ++j )
		for( auto &cc: c[i] )
			for( int k=0; k!=cc.size(); ++k )
				s[cc[k]]=cc[k+j<cc.size() ? k+j : k+j-cc.size()];
	for( int i=2; i<c.size(); i+=2 )
		for( auto &cc: c[i] ){
			for( int k=0; k!=cc.size()-1; ++k )
				s[cc[k]]=cc[k+1];
			s[cc.back()]=cc[0];
		}
	
	return s;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	std::vector<int> p(++n);
	for( int i=1; i!=n; ++i )
		std::cin >> p[i];

	auto s(sqrt(p));

	if( s.empty() )
		std::cout << -1 << std::endl;
	else{
		for( int i=1; i!=s.size(); ++i )
			std::cout << s[i] << ' ';
		std::cout << std::endl;
	}

	return 0;
}
