#include <iostream>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int32_t x[2],h[2], tx, th;
	uint32_t n;
	std::cin >> n;

	std::cin >> x[0] >> h[0] >> x[1] >> h[1];
	bool i=0, j=1;
	uint32_t cut = 1;

	if(--n){
		while(--n){
			std::cin >> tx >> th;
			if( h[j] < x[j]-x[i] ) cut++;
			else if( h[j] < tx-x[j] ) {
				x[j] += h[j];
				cut++;
			}
			i = !i; j = !j;
			h[j]=th; x[j]=tx;
		}
		cut++;
	}
	std::cout << cut << std::endl;

	return 0;
}
