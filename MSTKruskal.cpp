/* KRUSKAL */

/* Disjoint Set Union */
#include <iostream>
#include <list>
#include <vector>
#include <type_traits>

/* T: type of object, M: container for the elements */
template <typename T, template <typename, typename ...> class M >
struct disjointSets{
	struct element{
		element(T& obj):
		object{obj}, set{this}, rank{0} {}

		element(T& obj, element* s):
		object{obj}, set{s}, rank{0} {}

		T object;
		unsigned int rank;
		element* set;
	};

	disjointSets():
	sets(), elements(){}

	element& MakeSet(T&& obj){
		elements.emplace_back(obj);
		addSet(elements.back());
		return elements.back();
	}

	element& MakeSet(T& obj){
		elements.emplace_back(obj);
		addSet(elements.back());
		return elements.back();
	}

	element& FindSet(element& el){
		if( el.set == &el ) return el;
		return *(el.set = &FindSet(*el.set));
	}

	element& Union(element& a, element& b){
		element* rootA = &FindSet(a);
		element* rootB = &FindSet(b);
		if( rootA == rootB ) return *rootA;
		if( rootA->rank < rootB->rank ) return *(rootA->set = rootB);
		if( rootA->rank > rootB->rank ) return *(rootB->set = rootA);
		rootA->rank++;
		return *(rootB->set = rootA);		
	}

	bool Reserve(const unsigned int& size){
		return reserve(size, has_reserve<M<element>>{});
	}

	const auto& CountSets(){
		for( auto i = sets.begin(); i!=sets.end(); i++ ) if( (*i)->set != *i) sets.erase(i);
		return sets;
	}
	void Clear(){
		elements.clear();
		sets.clear();
	}
private:
	M<element> elements;
	std::list<element*> sets;
	void addSet(element& el){
		sets.push_back(&el);
	}

	template <typename X, typename = void>
	struct has_reserve : std::false_type {};

	template <typename X>
	struct has_reserve<X, typename std::enable_if<std::is_same <decltype( std::declval<X>().reserve( std::declval<typename X::size_type>() ) ), void>::value>::type>
  	: std::true_type {};

  	bool reserve(const unsigned int& size, std::true_type){
  		elements.reserve(size);
  		return true;
  	}
  	bool reserve(unsigned int& size, std::false_type){
  		return false;
  	}
};

#include <algorithm>
/* Light version: only report weight */
struct Edge{
	uint32_t v[2];
	uint32_t weight;
};


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	uint32_t N, M;
	std::cin >> N >> M;

	disjointSets<uint32_t, std::vector> spannedVertices;
	spannedVertices.Reserve(N);
	std::vector<std::decltype(spannedVertices)::element*> MST(N);
	auto tMST = MST.begin()-1;
	uint32_t i = 0;
	for( auto &vertex: MST ) vertex = &spannedVertices.MakeSet( ++i );

	std::vector<Edge> edges(M);
	for( auto& edge: edges ) {
		for( auto& vertex: edge.v ) std::cin >> vertex;
		std::cin >> edge.weight;
	}

	std::sort(edges.begin(),edges.end(), [](Edge& a, Edge& b){ return a.weight < b.weight; } );
	uint32_t edgesOfMST = 0;
	uint64_t weightOfMST = 0;
	for( auto &edge: edges ){
		if( &spannedVertices.FindSet( *tMST[edge.v[0]] ) != &spannedVertices.FindSet( *tMST[edge.v[1]] )) {
			edgesOfMST++;
			weightOfMST += edge.weight;
			spannedVertices.Union( *tMST[edge.v[0]], *tMST[edge.v[1]] );
			if( edgesOfMST == N-1 ) break;
		}
	}

	std::cout << weightOfMST << std::endl;

	return 0;
}
