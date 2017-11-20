#include <iostream>
#include <string>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	input.reserve(50000);
	std::cin >> input;

	std::string output;
	output.reserve(50000);
	output.push_back(input.back());
	for( auto i = input.end()-1; i!=input.begin(); ) 
		if( *--i >= output.back() )
			output.push_back(*i);

	for( auto o = output.end(); o!=output.begin(); (std::cout << *--o) );
	std::cout << std::endl;

	return 0;
}
