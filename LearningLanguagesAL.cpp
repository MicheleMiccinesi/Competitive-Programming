#include <iostream>
#include <vector>
#include <list>

struct graph{
	graph(short &n):
	nodes(n) , CC{0} {
		 tnodes = nodes.begin()-1;
	}

	struct Node{
		std::list<Node *> links;
		char color{0};
	};

	void addLink(short& a, short& b){
		tnodes[a].links.push_back(&tnodes[b]);
		tnodes[b].links.push_back(&tnodes[a]);
	}

	short& DFS(){
		for( auto &x: nodes ) if( !x.color ) {
				singleDFS(&x); 
				++CC; }
		return CC;
	}

	void singleDFS(Node *root){
		root->color++;
		for(auto &x: root->links) if( !x->color ) singleDFS(x);
		root->color++;
	}

	short CC;	//Connected Components
private:
	std::vector<Node> nodes;
	std::vector<Node>::iterator tnodes;
};


int main(){

	short n,m,k,t;
	std::cin >> n >> m;
	bool ignorance = true;

	graph employees(n);
	std::vector<std::list<short>> emplPerLang(m);
	auto templPerLang = emplPerLang.begin()-1;
	for( auto i=1; i!=n+1; i++ ){
		std::cin >> k;
		if(k) m=false;
		while(k--){
			std::cin >> t;
			templPerLang[t].push_back(i);
		}
	}
	if(m){
		std::cout << n << std::endl;
		return 0;
	}


	for( auto &x: emplPerLang ){
		if( x.size()>1 ){
			auto j = x.begin();
			auto k = x.begin();
			for( k++; k!= x.end(); j++, k++)
				employees.addLink( *j, *k);
		}
	}

	std::cout << employees.DFS()-1 << std::endl;
	return 0;
}
