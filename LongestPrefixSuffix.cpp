#include <iostream>
#include <vector>
#include <string>

int main() {
	std::ios_base::sync_with_stdio(false);
	
	std::string s;			std::vector<int> lp;
	s.reserve(100000);		lp.reserve(100000);
	int i, E;

	short T;
	std::cin >> T;
	while(T--){
		std::cin >> s;
		E = s.size();
		lp.resize(E);
		lp[0]=0;
		
		for( i=1; i!=E; ++i ){
		    lp[i]=lp[i-1];            // lp[i-1]: length of longest proper prefix which is also a proper suffix ending in place i-1
		    while(lp[i] && s[i]!=s[lp[i]])
		        lp[i]=lp[lp[i]-1];
	        lp[i] += s[i]==s[lp[i]];
		}
		
		std::cout << lp.back() << '\n';
	}
	std::cout << std::flush;
	
	return 0;
}
