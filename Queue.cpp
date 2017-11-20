#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct pr{
	int32_t tr;
	uint32_t height;
	std::string name;
};

struct Slots : std::vector<int32_t> {
	Slots(size_t size, int32_t start): vector(size){
		tbegin = begin()-start;
		for( auto i=begin(); i!=end(); i++ ) *i = i-tbegin;
	}
	int32_t& operator[] (int32_t& i){ return tbegin[i]; }
	int32_t& operator[] (int32_t&& i){ return tbegin[i]; } 
	iterator tbegin;
	int32_t& Find(int32_t& x){
		if( tbegin[x] == x ) return tbegin[x];
		else return tbegin[x = Find(tbegin[x])];
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	uint32_t n;
	std::cin >> n;

	std::vector<pr> prs(n);
	for( auto& x: prs ) 
		std::cin >> x.name >> x.tr;
	std::sort( prs.begin(), prs.end(), [](pr& a, pr& b){ return a.tr < b.tr; } );
	for( auto i = prs.begin(); i!=prs.end(); i++ ) 
		if( i->tr > i-prs.begin() ){
			std::cout << -1 << std::endl;		//Check if possible
			return 0;
		}

	Slots queue(n,0);
	for( int32_t i = n-1; i != -1; i-- )
		prs[i].height = queue.Find(prs[i].tr)++;

	for( auto person: prs ) 
		std::cout << person.name << ' ' << n-person.height << '\n';
	std::cout << std::flush;

	return 0;
}
