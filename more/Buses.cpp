/* Buses */
/* Problem Source: codeforces 102D */
/* Solution license: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <numeric>

const uint32_t M = 1000000007;
class rBIT{
	std::vector<uint32_t> c;
	uint32_t& r_sum(uint32_t& i){
		s=c[0];
		for( ; i; i&=i-1 )
			(s+=c[i])%=M;
		return s;
	}
public:
	uint32_t s;
	rBIT(uint32_t& n): c(n,0){ c[0]=1;}
	template < typename C>
	void add(uint32_t i, C&& a){
		for( ; i<c.size(); i+=(i&-i) )
			(c[i]+=a)%=M;
	}
	uint32_t& sum(uint32_t i){
		s=c[0];
		for( ; i; i&=i-1 )
			(s+=c[i])%=M;
		return s;
	}
	uint32_t& sum(uint32_t i, uint32_t j){
		s=0;
		if(!i) return r_sum(j);
		--i;
		while(i!=j){
			while(i<j){
				(s+=c[j])%=M;
				j&=j-1;
			}
			while(j<i){
				if(s>=c[i]) (s-=c[i]);
				else (s+=M-c[i])%=M;
				i&=i-1;
			}
		}
		return s;
	}
};

struct segment{
	uint32_t i[2];
};
#include <algorithm>
int main(){
	std::ios_base::sync_with_stdio(false);
	uint32_t m,n;
	std::cin >> n >> m;
	if(!m) {
		std::cout << 0 << std::endl;
		return 0;
	}
	std::vector<uint32_t> v(2*m);
	for( auto &vv: v ) std::cin >> vv;
	
	std::vector<segment> b(m);
	
	std::vector<uint32_t> o(2*m);
	std::iota(o.begin(), o.end(), 0);
	std::sort(o.begin(), o.end(), [&v](uint32_t &a, uint32_t& b)
		{ return v[a]<v[b]; } );
	if(v[o[0]]||v[o.back()]!=n){
		std::cout << 0 << std::endl;
		return 0;
	}
	uint32_t i=0;
	for( uint32_t j=0; j!=2*m-1; ++j ) {
		b[o[j]>>1].i[o[j]&1]=i;
		i += v[o[j+1]]!=v[o[j]];
	} b[o.back()>>1].i[o.back()&1]=i;
	
	std::sort(b.begin(), b.end(), [](segment& a, segment& b) 
		{ return a.i[1]<b.i[1]; } );
	rBIT r(++i);
	for( auto &bb: b )
		r.add(bb.i[1],r.sum(bb.i[0], bb.i[1]-1));
	std::cout << r.sum(i-1, i-1) << std::endl;

	return 0;
}
