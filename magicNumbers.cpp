#include <iostream>

int main(){
	unsigned short mn[] = {144,14,1};
	unsigned short pw[] = {1000,100,10};
	unsigned short j;

	uint32_t i;
	std::cin >> i;


	while(i){
		for(j = 0; j!= 3; j++)
			if( i%pw[j] == mn[j] ){
				i/=pw[j];
				break;
			}
		if( j==3 ) {
			std::cout << "NO" <<std::endl;
			return 0;
		}
	}
	std::cout << "YES" << std::endl;

	return 0;
}
