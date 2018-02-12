/* Biconnected Graph */
/* Problem Source: g4g */
/* Solution License: contact Michele Miccinesi */
/* Exercise... */
/* with this you could easily enumerate the articulation points... */

#include <iostream>
#include <vector>

template <class LINK, class AUGMENT>
struct node{
	node():l(), property(){}
	std::vector<LINK> l;		//links
	AUGMENT property;
};

struct dfs_cutv{
	int p;
	int h, d;
	bool visited{false}, cut{false};
};

bool dfs(std::vector<node<int, dfs_cutv>>& V, int r){
	for( auto &i: V[r].l ){
		if( i==V[r].property.p )
			continue;
		if( V[i].property.visited ){
			V[r].property.d=std::min(V[r].property.d, V[i].property.h);
			continue;
		}
		V[i].property.h=V[i].property.d=V[r].property.h+1;
		V[i].property.visited=true;
		V[i].property.p=r;
		if(dfs(V, i)==false)
			return false;
		if( V[i].property.d>=V[r].property.h ){
			V[r].property.cut=true;
			return false;
		}
		V[r].property.d=std::min(V[r].property.d, V[i].property.d);
	}
	return true;
}

bool is_biconnected(std::vector<node<int, dfs_cutv>>& V){
	int connected_components{0};
	for( int r=0; r!=V.size(); ++r ){
		if( V[r].property.visited )
			continue;
		
		if( ++connected_components>1 ){
			V[r].property.cut=true;
			return false;
		}

		V[r].property.h=0;
		V[r].property.d=0;
		V[r].property.p=-1;
		V[r].property.visited=true;
		int children{0};

		for( auto &i: V[r].l ){
			if( V[i].property.visited )
				continue;
			if( ++children>1 )
				return false;
			V[i].property.visited=true;
			V[i].property.p=r;
			V[i].property.d=V[i].property.h=1;

			if(dfs(V, i)==false)
				return false;
		}
	}
	return true;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int T;
	std::cin >> T;

	while(T--){
		int N, E;
		std::cin >> N >> E;

		std::vector<node<int, dfs_cutv>> V(N);

		while(E--){
			int u, v;
			std::cin >> u >> v;
			V[u].l.emplace_back(v);
			V[v].l.emplace_back(u);
		}

		std::cout << is_biconnected(V) << '\n';
	}

	std::cout << std::flush;

	return 0;
}
