#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

template <typename T>
inline T& max(T& a, T& b){
	return a>b?a:b;
}

short M[100][100];

typedef std::string::iterator sti;
short& LCS(sti& aB, sti aE, sti& bB, sti bE){
	if( M[aE-aB][bE-bB]!=-1 ) 
		return M[aE-aB][bE-bB];
	if( *aE == *bE )
		return M[aE-aB][bE-bB] = LCS( aB, aE-1, bB, bE-1 )+1;
	return M[aE-aB][bE-bB] = max( LCS( aB, aE-1, bB, bE ), LCS( aB, aE, bB, bE-1 ) );
}

int main(){
	std::ios_base::sync_with_stdio(false);

	short n,m;
	std::string a,b;
	a.reserve(100);
	b.reserve(100);
	std::vector<short> co(2);
	sti abegin, bbegin;

	short T;
	std::cin >> T;
	while(T--){
		std::cin >> n >> m;
		std::cin >> a >> b;

		for( co[0] = 0; co[0] != n; co[0]++ )
			for( co[1] = 0; co[1] != m; co[1]++ )
				M[co[0]][co[1]] = -1;

		co[0]=0; 
		for( co[1]=0; co[1]!=m && b[co[1]]!=a[0]; co[1]++ ) 
			M[co[0]][co[1]] = 0;
		for( ; co[1]!=m; co[1]++ )
			M[co[0]][co[1]] = 1;
		co[1]=0;
		for( ; co[0]!=n && a[co[0]]!=b[0]; co[0]++ )
			M[co[0]][co[1]] = 0;
		for( ; co[0]!=n; co[0]++ )
			M[co[0]][co[1]] = 1;

		abegin = a.begin();
		bbegin = b.begin();
		std::cout << LCS( abegin, a.end()-1, bbegin, b.end()-1 ) << std::endl;
	}	
	return 0;
}
