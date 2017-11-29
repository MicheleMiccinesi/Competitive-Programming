/* Coin Change */
/* small number, simple program => C style matrix for shorter code */

#include <iostream>
#include <vector>
#include <algorithm>

const unsigned short N_MAX = 300;
const unsigned short M_MAX = 300;

uint32_t NM[N_MAX+1][M_MAX+1];
unsigned short c[M_MAX+1];

int main(){
	std::ios_base::sync_with_stdio(false);

	unsigned short N, M;
	unsigned short i, j, k;

	unsigned short T;
	std::cin >> T;
	while(T--){
		for( i = 0; i!=N_MAX+1; i++ )
			for( j = 0; j!=M_MAX+1; j++ )
				NM[i][j] = 0;
		NM[0][0] = 1;

		std::cin >> M;
		for( j = 1; j!=M+1; j++ )
			std::cin >> c[j];
		std::sort( c+1, c+M+1 );

		std::cin >> N;
		for( i = 1; i!=N+1; i++ )
			for( j = 1; j!=M+1 && c[j]<=i; j++ )
				for( k = 0; k<=j; k++ )
					NM[i][j] += NM[i-c[j]][k];
		for( j = 1; j!=M+1 && c[j]<=N; j++ )
			NM[N][0]+=NM[N][j];

		std::cout << NM[N][0] << '\n';
	}

	std::cout << std::flush;

	return 0;
}
