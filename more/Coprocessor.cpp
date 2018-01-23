/* Coprocessor */
/* Problem Source: codeforces 909E */
/* Solution License: contact Michele Miccinesi */
/* Greedy+BFS solution; but in truth I prefer topological sort + 
   DP, because in such way we can answer also the generalization
   to this problem. */

#define NDEBUG
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

struct edge{
	int u,v;
};

template <class _NODE_>
inline std::vector<_NODE_> get_edges(int& n, int& m);

template <class _PRINT_>
inline void print(_PRINT_& O);

struct node{
	std::vector<int> O;
	int in{0};
	bool co;					//if co, it must be processed on co-processor
};

template <>
inline void print(node& n){
	for( auto &v: n.O ) std::cout << v << ' ';
	std::cout << "  ::   IN: " << n.in << "  ::  Tipo: " << n.co << std::endl;
}

template <>
inline void print(std::vector<node>& G){
	for( int i=0; i!=G.size(); ++i ){
		std::cout << "Vertice: " << i << " --> ";
		print(G[i]);
	}
}

template <>
inline std::vector<node> get_edges(int& n, int& m){
	std::vector<node> G(n);
	short co;
	for( auto &g: G ) {
		std::cin >> co;
		g.co = co==1;
	}

	std::vector<edge> E(m);
	std::vector<int> O(n,0);
	for( auto &e: E ) {
		std::cin >> e.v >> e.u;
		++O[e.u];
		++G[e.v].in;
	}
	for( int i=0; i!=n; ++i ){
		G[i].O=std::vector<int> (0);
		G[i].O.reserve(O[i]);
	}
	for( auto &e: E ) {
		G[e.u].O.push_back(e.v);
	}
	#ifndef NDEBUG
	print(G);
	#endif
	return G;
}

template <int _n_, typename _I_>
inline void process_jobs(std::vector<node>& G, std::queue<int> (&Q)[_n_], _I_&& i){
	#ifndef NDEBUG
	std::cout << "process_jobs nella coda " << i << std::endl;
	#endif	
	assert(i<_n_);
	while(!Q[i].empty()){
		for( auto &v: G[Q[i].front()].O ){
			#ifndef NDEBUG
			std::cout << "Sono nel vertice " << v << " entrandovi da " << Q[i].front() << std::endl;
			#endif
			if(--G[v].in==0){
				assert(G[v].co<_n_);
				#ifndef NDEBUG
				std::cout << "Inserisco nella coda " << G[v].co << " il vertice " << v << std::endl;
				#endif
				Q[G[v].co].push(v);
			}
		}
		#ifndef NDEBUG
		std::cout << "Rimuovo dalla coda " << i << " il vertice " << Q[i].front() << std::endl;
		#endif
		Q[i].pop();
	}
}


int main(){
	std::ios_base::sync_with_stdio(false);

	int n,m;
	std::cin >> n >> m;
	auto G(get_edges<node>(n,m));		//Build graph

	std::queue<int> Q[]{std::queue<int>(), std::queue<int>()};

	for( int i=0; i!=n; ++i ){
		if( G[i].in==0 ){
			#ifndef NDEBUG
			std::cout << "Inserisco nella coda " << G[i].co << " il vertice " << i << std::endl;
			#endif
			Q[G[i].co].push(i);
		}
	}
	int co_cycles = 0;
	while( !(Q[0].empty() && Q[1].empty()) ){
		process_jobs(G,Q,0);
		#ifndef NDEBUG
		std::cout << "Dimensioni delle code: " << Q[0].size() << " " << Q[1].size() << std::endl;
		#endif
		if(Q[1].empty()) break;
		process_jobs(G,Q,1);
		++co_cycles;
	}

	std::cout << co_cycles << std::endl;

	return 0;
}
