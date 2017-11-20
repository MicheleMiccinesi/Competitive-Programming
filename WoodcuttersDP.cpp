#include <iostream>


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int32_t x[2],h[2], lastX;
	uint32_t n;
	std::cin >> n;

	std::cin >> x[0] >> h[0];
	lastX=x[0];
	bool i=0, j=1;
	uint32_t cut = 1;

	while(--n){
		std::cin >> x[j] >> h[j];
		if( x[j] <= lastX ){
			lastX = x[i];
			if( h[j] < x[j]-lastX )
				lastX = x[j];
			else 
				lastX = x[j]+h[j];
		}
		else if(h[j] < x[j]-lastX){
			cut++;
			lastX = x[j];
		}
		else if( h[j] >= x[j]-lastX ){
			cut++;
			lastX = x[j]+h[j];
		}
		i = !i; j = !j;
	}
	std::cout << cut << std::endl;

	return 0;
}
