#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>

template <typename T>
struct dirGraph{
	dirGraph(int V):
	nodes(V)
	{}

	const bool& topologicalSort(){
		topSortable=true;
		for( auto& x: nodes ) if(!x.color) {
			x.color++;
			if(!nodeDFStoStack(x)) return topSortable;
			sortedTop.push(&x.value);
			x.color++;
		}
		return topSortable;
	}
	void addChildren(int&& rootIndex,int&& childrenIndex){
		nodes[rootIndex].children.push_back(&(nodes[childrenIndex]));
	}
	void addChildren(int& rootIndex,int& childrenIndex){
		nodes[rootIndex].children.push_back(&(nodes[childrenIndex]));
	}
	void printTopSort(){
		while(!sortedTop.empty()) {
			std::cout << *(sortedTop.top());
			sortedTop.pop();
		}
		std::cout << std::endl;
	}
	struct node{
		T value;
		std::list<node *> children;
		char color{0};
	};
	std::vector<node> nodes;
private:
	const bool& nodeDFStoStack(node& root){
		for(auto &x: root.children) 
			if(!x->color) {
				x->color++;
				if(!nodeDFStoStack(*x)) return topSortable;
				sortedTop.push(&x->value);
				x->color++;
			}
			else if(x->color==1) return topSortable=false;
		return topSortable;
	}
	std::stack<T *> sortedTop;
	bool topSortable;
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	dirGraph<char> alphabet(26);
	char letter{'a'};
	for(auto &x: alphabet.nodes) x.value=letter++;

	int n,m,j;
	std::string words[2];
	bool i=1;
	std::cin >> n;
	std::cin >> words[0];
	while(--n){
		std::cin >> words[i];
		m = words[1].length()<words[0].length()?words[1].length():words[0].length();
		for( j=0; j!=m && words[0][j]==words[1][j]; j++ );
		if( j==m ) {
			if( words[!i].length()>words[i].length() ) {
				std::cout << "Impossible" << std::endl; 
				return 0; 
			}
		}
		else alphabet.addChildren(words[!i][j]-'a',words[i][j]-'a');
		i = !i;
		words[i].erase();
	}

	if(!alphabet.topologicalSort()) std::cout << "Impossible" << std::endl;
	else alphabet.printTopSort();

	return 0;
}
