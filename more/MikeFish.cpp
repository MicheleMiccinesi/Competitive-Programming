/* Mike and Fish */
/* Problem Source: codeforces div1 547D */
/* Solution License: contact Michele Miccinesi */

/* Unefficient implementation (with 'fronzoli') */
/* But the idea of the is problem simple & elegant */
#define NDEBUG
#include <iostream>		//cout, cin
#include <vector>		//vector
#include <queue>
#include <array>		//array
#include <algorithm>	//sort
#include <numeric>		//iota

template <int N>
struct simplex{
	simplex(){}
	simplex(const int& u0, const int & u1){ 
		u[0]=u0;  
		u[1]=u1;
	}
	simplex(std::array<int, N>&& uu): u(std::move(uu)){}
	simplex(std::array<int, N>& uu): u(uu){}

	std::array<int, N> u;
	std::array<int, N> i;
};

template <int N>
std::array<int, N> get_minimal_range(std::vector<simplex<N>>& E){
	std::vector<int> O(E.size());
	std::iota(O.begin(), O.end(), 0);
	std::array<int, N> I;

	auto sort = 
		[&E, &O, &I](const int& k)
		{
			std::sort(O.begin(), O.end(), 
				[&E, &k](int& i, int& j)
				{
					return E[i].u[k]<E[j].u[k];
				}
			);
			
			E[O[0]].i[k]=0;
			for( int i=1, j=0; i!=O.size(); ++i, ++j ){
				if( E[O[i]].u[k]==E[O[j]].u[k] )
					E[O[i]].i[k]=E[O[j]].i[k];
				else
					E[O[i]].i[k]=E[O[j]].i[k]+1;
			}
			I[k]=E[O.back()].i[k]+1;
		};

	for( int i=0; i!=N; ++i )
		sort(i);

	return I;
}

void dfs(const auto& E, auto& V, auto &D, auto& C, const int& i, bool k){
	auto traverse_edge = 
		[&E, &V, &C, &k, &i]() -> const auto&
		{
			const auto &e=V[k][i].front();
			const auto &j=E[e].i[!k];
			C[e]=k?2:1;
			return j;
		};

	const auto &j = traverse_edge();
	--D[k][i];
	V[k][i].pop();
	//now we are in the other vertex:
	k=!k;
	if(--D[k][j]==0)
		return;
	while( C[V[k][j].front()] )
		V[k][j].pop();
	dfs(E, V, D, C, j, k);
}

std::vector<char> get_verses(const auto& E, auto& V){
	std::vector<char> C(E.size(), 0);		//0: non visited; 1: red; 2: blue (or viceversa)
	std::array<std::vector<int>, 2> D;
	
	for( char k=0; k!=2; ++k ){
		D[k].resize(V[k].size());
		for( int i=0; i!=D[k].size(); ++i )
			D[k][i]=V[k][i].size();
	}

	for( char k=0; k!=2; ++k )
		for( int i=0; i!=D[k].size(); ++i ){
			if( D[k][i]&1 ){
				while(C[V[k][i].front()])
					V[k][i].pop();
				dfs(E, V, D, C, i, static_cast<bool>(k));
			}
		}
	for( char k=0; k!=2; ++k )
		for( int i=0; i!= D[k].size(); ++i )
			if( D[k][i] ){
				while(C[V[k][i].front()])
					V[k][i].pop();
				dfs(E, V, D, C, i, static_cast<bool>(k));
			}

	return C;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int m;
	std::cin >> m;
	std::vector<simplex<2>> E(m);
	for( auto &e: E ) 
		std::cin >> e.u[0] >> e.u[1];


	std::array<std::vector<std::queue<int>>, 2> V;
	{
		auto I(get_minimal_range(E));
		V[0].resize(I[0]);
		V[1].resize(I[1]);
	}
	for( int i=0; i!=E.size(); ++i ){
		V[0][E[i].i[0]].emplace(i);
		V[1][E[i].i[1]].emplace(i);
	}

	std::vector<char> C(get_verses(E, V));
	char color[]={' ', 'r', 'b'};
	for( auto &c: C )
		std::cout << color[c];
	std::cout << std::endl;

	return 0;
}
