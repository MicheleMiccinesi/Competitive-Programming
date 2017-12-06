/* Misha and Forest */

#include <iostream>
#include <vector>

typedef uint16_t u16;
typedef std::vector<u16> vu16;

struct node{
	u16 d, s;
};
typedef std::vector<node> vn;

struct edge{
	edge(u16& uu, u16& vv): u{uu}, v{vv} {};
	u16 u, v;
};
typedef std::vector<edge> ve;

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);	

	int N;
	std::cin >> N;

	vn f(N);					//forest
	vu16 o;	o.reserve(N);		//save nodes with d==1

// Reading in a go is not faster
	/*for( auto &n: f ) 
		std::cin >> n.d >> n.s;*/
	int i;
	for( i=0; i!=N; i++ ){
		std::cin >> f[i].d >> f[i].s;
		if( f[i].d==1 ) o.push_back(static_cast<u16>(i));
	}

	u16 d, s;	u16 j;
	ve E;	E.reserve(N-1);
	while( !o.empty() ){
		j = o.back();	d = f[j].d;	s = f[j].s;
		o.pop_back();
		if( d ) {
			f[s].s ^= j;
			if( --f[s].d==1 ) o.push_back(s);
			E.emplace_back(edge(j,s));
		}
	}

	std::cout << E.size() << '\n';
	for( auto &e: E ) std::cout << e.u << ' ' << e.v << '\n';
	std::cout << std::flush;

	return 0;
}
