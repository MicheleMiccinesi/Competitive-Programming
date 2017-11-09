#include <iostream>
#include <vector>
#include <deque>
#include <stack>

typedef uint32_t uint;
/* Using a deque to calculate the DG transpose back and forth */
struct DG{
private:	
	struct Node{
		std::deque<Node *> links;
		uint value;
		uint n{0};
		char color;		//to be set to 0 before using...
		uint tf;
	};

	struct SCC{
		SCC():
		countMin{0}, min{~uint64_t(0)}, nodes(){}
		std::deque<Node *> nodes;
		uint64_t countMin;
		uint64_t min;
	};

public:

	DG(uint& n):
	nodes(n), SCCs(), TopOrd() {
		tnodes = nodes.begin()-1;
	}

	void readValues(){
		for( auto &x: nodes ) std::cin >> x.value;
	}

	void addLink(uint& a, uint& b){
		tnodes[a].links.push_back(&tnodes[b]);
		tnodes[a].n++;
	}

	uint& readLinks(uint& m){
		while(m) {
			std::cin >> i >> j;
			addLink(i,j);
			m--;
		}
		return m;
	}

	DG& transpose(){
		if(trasposed){
			for( auto &x: nodes ) {
				while( x.n ) {
					x.links.back()->links.push_front(&x);
					x.links.pop_back();
					x.n--;
				}
			}
		} else{
			for( auto &x: nodes ) {
				while( x.n ) {
					x.links.front()->links.push_back(&x);
					x.links.pop_front();
					x.n--;
				}
			}
		}
		for( auto &x: nodes ) x.n = x.links.size();
		trasposed = !trasposed;
		return *this;
	}

	std::stack<Node *>& topologicalOrder(){
		acyclic = true;
		for( auto &x: nodes ) x.color = 0;
		for( auto &x: nodes ) if( !x.color ) singleDFS( x );
		return TopOrd;
	}

	void singleDFS(Node& root){
		root.color++;
		for(auto &x: root.links)
			if( x->color == 1 )acyclic=false;
			else if( !x->color ) singleDFS( *x );
		root.color++;
		TopOrd.push( &root );
	}

	uint64_t (&findSCCs())[2] {
		topologicalOrder();
		transpose();
		for( auto &x: nodes ) x.color=0;
		while( !TopOrd.empty() ){
			if(!TopOrd.top()->color) {
				SCCs.push_back( SCC() );
				DFStoSCC( *TopOrd.top(), SCCs.back() ) ;
			}
			TopOrd.pop();
		}

		minReprSCC[0] = 0; minReprSCC[1] = 1;
		for( auto &x: SCCs ) {
			(minReprSCC[1] *= uint64_t(x.countMin))%=1000000007;
			minReprSCC[0] += uint64_t(x.min);
		}
		return minReprSCC;
	}

	SCC& DFStoSCC(Node &root, SCC& currSCC){
		root.color++;
		currSCC.nodes.push_back(&root);
		if( root.value < currSCC.min ) {
			currSCC.min = root.value;
			currSCC.countMin = 1;
		}
		else if( root.value == currSCC.min ) currSCC.countMin++;
		for( auto &x: root.links ) if( !x->color ) DFStoSCC(*x, currSCC);
		return currSCC;
	}
	uint64_t countMinReprSCC;
	uint64_t minReprSCC[2];

private:
	std::vector<Node> nodes;
	std::vector<Node>::iterator tnodes;
	std::deque<SCC> SCCs;
	std::stack<Node *> TopOrd;
	bool acyclic;
	bool trasposed{false};
	uint i,j;
};

int main(){
	std::ios_base::sync_with_stdio( false );
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	uint n;
	std::cin >> n;
	DG junctions(n);
	junctions.readValues();

	std::cin >> n;
	junctions.readLinks(n);

	for( auto& x: junctions.findSCCs() ) std::cout << x << ' ';
	std::cout << std::endl;

	return 0;
}
