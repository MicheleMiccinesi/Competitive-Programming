/* Tree Vertex Cover */
/* Post order (recursively) */
#include <iostream>
#include <vector>
#include <list>

struct node{
	node(): l(){}
	std::list<node*> l;		//links (egdes)
	int c, ccs;				//min cover, sum of children min covers
	bool v{0};				//visited
};

struct graph: std::vector<node>{
	graph(int N): std::vector<node> (N, node()){
		t = begin()-1;
	};
	node& operator[](int& x){
		return t[x];
	}

private:
	iterator t;
};
/* using templates to support pointers&, pointers&&, iterators&, iterators&&.. in one move */
template <typename T>
void mvct(T&& s){
	s->v = true;
	s->ccs = s->c = 0;
	for( auto il = s->l.begin(); il!=s->l.end(); ){
		if( (*il)->v )
			il = s->l.erase(il);
		else{
			mvct(*il);
			s->ccs += (*il)->c;
			s->c += (*il)->ccs+1;
			il++;
		}
	}
	s->c = std::min( s->ccs+1, s->c );
}

int main(){
	std::ios_base::sync_with_stdio(false);
  
	int N;
	std::cin >> N;

	graph tree(N);

	int u,v;
	while(--N){
		std::cin >> u >> v;
		tree[u].l.push_back(&tree[v]);
		tree[v].l.push_back(&tree[u]);
	}
  
	mvct(tree.begin());
	std::cout << tree.begin()->c << std::endl;
  
	return 0;
}
