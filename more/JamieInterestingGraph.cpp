/* Jamie and Interesting Graph */
/* Problem Source: codeforces 916C */
/* Solution License: contact Michele Miccinesi */

/* Proof: MST construction properties & Bernstein Lemma for density of primes */

#include <iostream>
#include <vector>
#include <cmath>

const int primes[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331};

struct edge{
	int u,v,w;
};

inline bool is_prime(int& n){
	int E = sqrt(n);
	for( int i = 0; primes[i]<=E; ++i )
		if( n%primes[i]==0 ) 
			return false;
	return true;
}


inline int find_prime(int& a, int&& b){
	if(a==2) return 2;
	int p;
	if(!(a%2))p=a+1;
	else p=a;
	for( ; p<=b; p+=2 )
		if(is_prime(p))
			return p; 
}
int main(){
	std::ios_base::sync_with_stdio(false);
	int n,m;
	int MST, SP, e;
	std::cin >> n >> m;

	std::vector<edge> E(m);
	int i;
	E[n-2].u=1;
	E[n-2].v=n;
	E[n-2].w=2;

	int p=find_prime(n,n<<1);
	MST=p;
	SP=2;
	p-=n;


	for( i=0; i!=n-2; ++i ){
		E[i].u=1;
		E[i].v=i+2;
		if(p){
			E[i].w=2;
			--p;
		}
		else 
			E[i].w=1;
	}
	if(p){
		++E[0].w;
		e=4;
	}
	else
		e=3;
	++i;
	for( int u=2; u!=n && i!=m; ++u )
		for( int v=u+1; v!=n+1 && i!=m; ++v, ++i ){
			E[i].u=u;
			E[i].v=v;
			E[i].w=e;
		}

	std::cout << SP << ' ' << MST << '\n';
	for( auto& ee: E )
		std::cout << ee.u << ' ' << ee.v << ' ' << ee.w << '\n';

	std::cout << std::flush;
	return 0;
}
