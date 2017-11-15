#include <iostream>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	uint32_t n;
	char b[2];
	char doubles = 0;
	uint32_t alternating = 1;
	std::cin >> n;

	std::cin >> b[0];
	bool i=0, j=1;
	while(--n){
		std::cin >> b[j];
		if( b[i = !i] == b[j = !j] ) {
			if( ++doubles == 2 ) 
				break;
		}
		else alternating++;
	}
	if(n)
		while(--n){
			std::cin >> b[j];
			if( b[i = !i] != b[j = !j] ) alternating++;
		}

	std::cout << alternating+doubles << std::endl;
	return 0;
}
