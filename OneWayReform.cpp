/* One-Way Reform */
/* Problem Source: codeforces 723E */
/* Solution License: contact Michele Miccinesi */

/* Here I'm trying to minimise the needed swaps on the */
/* given implicit orientation on edges given by the order */
/* in which vertices of each edge are taken from input */

/* otherwise, a much nicer version to code is the one in which */
/* we spaghettify the graph by euler tours, first starting */
/* from odd degree vertices, then from the remaining ones */
/* (with even degree) */

// data types are optimized for the input...
#include <iostream>
#include <vector>
#include <list>
#include <iterator>

typedef uint8_t u8;
typedef uint16_t u16;

struct edge{
	u8 v[2];
};

struct node{
	std::list<std::list<struct edge_ref>::iterator> e, o;
	node(): e(), o(){}
	auto& operator[](const bool& i){
		return i?o:e;
	}
};

struct edge_ref{
	edge_ref(u16& ii): i(ii){}
	u16 i;					//index of edge
	decltype(node::e)::iterator ie0, ie1;				//iterator to the position in the node where the edge is referred
};

// all this mess is due to the implementation of std::list....
inline void delete_edge_ref(auto er, auto& E, auto& EP, auto& V, auto& D){
	const auto &v0 = E[er->i].v[0];
	const auto &v1 = E[er->i].v[1];
	u8 d = (D[v0]?1:0)|(D[v1]?2:0);

	switch(d){
	case 0:
		V[v0][0].erase(er->ie0);
		V[v1][0].erase(er->ie1);
		EP[0].erase(er);	
		break;
	case 1:
		V[v0][0].erase(er->ie0);
		V[v1][1].erase(er->ie1);
		EP[1].erase(er);
		break;
	case 2:
		V[v0][1].erase(er->ie0);
		V[v1][0].erase(er->ie1);
		EP[1].erase(er);
		break;
	}
}

inline void assign_verses(auto &E, auto &EP, auto& V, auto &D){
	u8 v=0;
	u16 e;
	u8 c=0;
	while(!(EP[0].empty() && EP[1].empty())){
		//0: find a new vertex
		//1: we are in an even degree vertex, our source
		//2: we went out from an even degree vertex to an odd degree one
		switch(c){
		case 0:
			if(!EP[0].empty()){
				v = E[EP[0].front().i].v[0];
				c = 1;
			} else {
				v = E[EP[1].front().i].v[0];
				if( D[v] ) 
					v = E[EP[1].front().i].v[1];
				c = 1;
			}
			break;
		case 1:
			if(!V[v][0].empty()){
				auto &er=V[v][0].front();
				if( v == E[er->i].v[1] ){
					std::swap(E[er->i].v[0],E[er->i].v[1]);
					std::swap(er->ie0,er->ie1);
				}
				v=E[er->i].v[1];
				delete_edge_ref(er, E, EP, V, D);
				c=1;
			} else if(V[v][1].empty()){
				c=0;
			} else {
				while(!V[v][1].empty()){
					auto &er=V[v][1].front();
					if( v == E[er->i].v[1] ){
						std::swap(E[er->i].v[0], E[er->i].v[1]);
						std::swap(er->ie0, er->ie1);
					}
					delete_edge_ref(er, E, EP, V, D);
					if( V[v][1].empty() )
						c=2;
					else {
						auto &er=V[v][1].front();
						if( v == E[er->i].v[0] ){
							std::swap(E[er->i].v[0], E[er->i].v[1]);
							std::swap(er->ie0, er->ie1);
						}
						delete_edge_ref(er, E, EP, V, D);
						if( V[v][1].empty() )
							c = 0;
					}
				}
			}
			break;
		case 2:
			e = EP[1].front().i;
			v = D[E[e].v[1]]?E[e].v[0]:E[e].v[1];
			auto &er=V[v][1].front();
			if( v == E[er->i].v[0] ){
				std::swap(E[er->i].v[0], E[er->i].v[1]);
				std::swap(er->ie0, er->ie1);
			}
			delete_edge_ref(er, E, EP, V, D);
			c = V[v][0].empty()&&V[v][1].empty()?0:1;
			break;
		}
	}
}
// partition edges in e-e, e-o; o-o discarded
inline void partition_edges(const auto& E, auto& EP, auto& V, auto& D){
	auto edge_kind = [&D](const edge& e)->u8 {
		return (D[e.v[0]]?1:0)+(D[e.v[1]]?1:0);
	};

	for( u16 i=0; i!=E.size(); ++i ){
		u8 kind = edge_kind(E[i]);
		if(kind!=2){
			const auto &v0 = E[i].v[0];
			const auto &v1 = E[i].v[1];

			EP[kind].emplace_back(i);
			const auto iep = std::prev(EP[kind].end());

			V[v0][D[v1]].emplace_back(iep);
			V[v1][D[v0]].emplace_back(iep);

			iep->ie0 = std::prev( V[v0][D[v1]].end() );
			iep->ie1 = std::prev( V[v1][D[v0]].end() );
		}
	}
}

inline std::vector<edge> read_edges(u16 m, auto& EP, auto& V, auto &D){
	std::vector<edge> E(m);				//edges
	u16 u,v;
	for( u16 i=0; i!=m; ++i ){
		std::cin >> u >> v;
		E[i].v[0]=u-1;
		E[i].v[1]=v-1;
		D[E[i].v[0]]=!D[E[i].v[0]];
		D[E[i].v[1]]=!D[E[i].v[1]];
	}

	partition_edges(E, EP, V, D);

	return E;
}



int main(){
	std::ios_base::sync_with_stdio(false);

	u16 T;
	std::cin >> T;
	while(T--){
	// n cities, m roads
		u8 n;
		u16 m;
		std::cin >> m;
		n=m;
		std::cin >> m;

		std::vector<node> V(n, node());				//nodes
		std::vector<bool> D(V.size());				//parity of the degree of each vertex
		std::fill(D.begin(), D.end(), 0);
		std::list<edge_ref> (EP[2]);				//E[]: {even<->even,  even<->odd} instead odd<->odd can take whatever direction
		auto E(read_edges(m, EP, V, D));		//get edges and partition them
	// assign orientation
		assign_verses(E, EP, V, D);

		u8 tot = 0;
		for( const auto &d: D )
			if(!d)
				++tot;

		std::cout << static_cast<u16>(tot) << '\n';
		for( auto& e: E ) 
			std::cout << static_cast<u16>(e.v[0]+1) << ' ' << static_cast<u16>(e.v[1]+1) << '\n';
	}
	std::cout << std::flush;

	return 0;
}
