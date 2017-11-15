/* Wilbur and Array */

#include <iostream>
#include <vector>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	uint32_t n;
	uint64_t moves = 0;
	std::cin >> n;
	int32_t values[] = {0,0};
	bool i=0,j=1;

	while( n-- ){
		std::cin >> values[j];
		moves += ( values[i]>values[j] ? values[i]-values[j] : values[j]-values[i] );
		i = !i;
		j = !j;
	}

	std::cout << moves << std::endl;

	return 0;
}
