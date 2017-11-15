#include <iostream>
#include <string>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::string word;
	std::cin >> word;
	char hello[] = "hello";

	char i = 0;
	for( auto j = word.begin(); j!=word.end(); j++ ) 
		if ( *j == hello[i] ) 
			if( ++i == 5 ){
				std::cout << "YES" << std::endl;
				return 0;
			}

	std::cout << "NO" << std::endl;
	return 0;
}
