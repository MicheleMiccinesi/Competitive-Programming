/* Unusual Sequences */
/* Problem Source: codeforces 900D */
/* Solution License: contact Michele Miccinesi */


#include <iostream>
#include <vector>

const uint64_t mo = 1000000007;

uint64_t psums(uint64_t m){
	if(m==1) return static_cast<uint64_t>(1);
	m--;
	uint64_t tm = m;
	uint64_t r = 1;
	uint8_t p = 0;
	while( tm>>=1 ) p++;
	tm = (1<<p);
	while( tm ){
		(r*=r)%=mo;
		if( m&tm )
			(r <<= 1)%=mo;
		tm >>= 1;
	}
	return r;
}

struct prime{
	uint64_t d, p;		//d: divisor(prime); p: power
};

void sums(uint64_t m, uint64_t& r, std::vector<prime>& v, int& i, bool l){
	int j;
	if(l){
		l=!l;
		(r += mo-psums(m))%=mo;
		for( j=i+1; j!= v.size(); j++ )
			sums(m/v[j].d, r, v, j, l);
	}
	else{
		l=!l;
		(r += psums(m))%=mo;
		for( j=i+1; j!= v.size(); j++ )
			sums(m/v[j].d, r, v, j, l);
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::vector<prime> div;

	uint64_t x, y, r{0}, m;
	std::cin >> x >> y;
	if( y%x ){
		std::cout << 0 << std::endl;}
	else if( y==x ){
		std::cout << 1 << std::endl;}
	else{
		y/=x;
		m = y;
		uint64_t d = 2, p;
		while( m != 1 )	{
			p=0;
			while(!(m%d)){
				p++;
				m/=d;
			}
			if(p)
				div.push_back({d,p});
			d++;
		}
		int i=-1;
		sums(y,r,div,i,false);
		std::cout << r << std::endl;
	}

	return 0;
}
