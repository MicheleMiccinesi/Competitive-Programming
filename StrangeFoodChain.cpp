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
 
int main(){
	const unsigned int N = 100000;
 
	struct animalKind{
		animalKind(){};
		animalKind* predator;
		animalKind* prey;
		disjointSets<animalKind, std::vector>::element* el;
	};
	disjointSets<animalKind, std::vector> animalKinds;
	animalKinds.Reserve(N);
	std::vector<animalKind*> animals(N);
	auto tanimals = animals.begin()-1;
	animals.reserve(N);
 
	unsigned int T,n,k,i,j;
	unsigned short c;
	unsigned int falseAsserts;
	disjointSets<animalKind, std::vector>::element* tEl;
	disjointSets<animalKind, std::vector>::element* set_i[3];
	disjointSets<animalKind, std::vector>::element* set_j[3];
 
	std::cin >> T;
	while (T--){
		std::cin >> n;
		animals.resize(n);
		n<<=1;
		animalKinds.Reserve(n);
		n>>=1;
		std::fill(animals.begin(), animals.end(), nullptr);
		std::cin >> k;
		falseAsserts = 0;
		while (k--){
			std::cin >> c >> i >> j;
			if( i>n || j>n || (c==2 && i==j)) falseAsserts++;
			else if(c==1 && i==j);
			else if( !tanimals[i] && !tanimals[j] ){
				tEl = &animalKinds.MakeSet({});
				tEl->object.el = tEl;
				tanimals[i] = &tEl->object;
				
				tEl = &animalKinds.MakeSet({});
				tEl->object.el = tEl;
				tanimals[i]->prey = &tEl->object;
				tEl->object.predator = tanimals[i];
 
				tEl = &animalKinds.MakeSet({});
				tEl->object.el = tEl;
				tanimals[i]->predator = &tEl->object;
				tEl->object.prey = tanimals[i];
				tEl->object.predator = tanimals[i]->prey;
				tanimals[i]->prey->prey = &tEl->object;
 
				if( c == 1 ) tanimals[j] = tanimals[i];
				else if ( c == 2 ) tanimals[j] = tanimals[i]->prey;
			}
			else if( !tanimals[i] ){
				if(c==2) tanimals[i] = tanimals[j]->predator;
				else if(c==1) tanimals[i] = tanimals[j];
			}
			else if( !tanimals[j] ){
				if(c==2) tanimals[j] = tanimals[i]->prey;
				else if(c==1) tanimals[j] = tanimals[i];
			}
			else{
				set_i[1] = &animalKinds.FindSet(*tanimals[i]->predator->el);
				set_i[2] = &animalKinds.FindSet(*tanimals[i]->el);
				set_i[0] = &animalKinds.FindSet(*tanimals[i]->prey->el);
				set_j[0] = &animalKinds.FindSet(*tanimals[j]->predator->el);
				set_j[1] = &animalKinds.FindSet(*tanimals[j]->el);
				set_j[2] = &animalKinds.FindSet(*tanimals[j]->prey->el);
				unsigned char b;
				for( b=0; b!=3; b++) if( set_i[1] == set_j[b] ) break;
				if( b==3 ) for(unsigned short kk=0; kk!=3; kk++) animalKinds.Union(*set_i[(kk+c)%3], *set_j[kk]);
				else if( set_i[c] != set_j[0] ) falseAsserts++;
			}
		}
		std::cout << falseAsserts << std::endl;	
	}
}
