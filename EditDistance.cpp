/* C-style for loops... */

#include <iostream>
#include <string>
#include <vector>

const unsigned short N_MAX = 100;

int main(){
	std::ios_base::sync_with_stdio(false);

	unsigned short m, n;
	std::string a,b;
	a.reserve(N_MAX); 	b.reserve(N_MAX);

	std::vector<unsigned short> eD;											//edit Distance vector
	eD.reserve(N_MAX+1);
	unsigned short d[2];														//d: temp for [*-1][*-1] edit Distance
	bool k;

	unsigned short i, j;
	unsigned short T;
	std::cin >> T;
	while(T--){
		std::cin >> m >> n;
		std::cin >> a >> b;
		eD.resize(m+1);

		i = 0;
		for( auto &ed: eD ) ed = i++; 

		for( j=0; j!=n; j++ ){
			d[!k] = j;
			eD.front() = j+1;
			for( i=0; i!=m; i++ ){
				d[k] = eD[i+1];
				k = !k;
				if( a[i] == b[j] )
					eD[i+1] = d[k];
				else 
					eD[i+1] = std::min( d[k], std::min( eD[i], eD[i+1] ) )+1;
			}
		}

		std::cout << eD.back() << '\n';
	}

	return 0;
}
