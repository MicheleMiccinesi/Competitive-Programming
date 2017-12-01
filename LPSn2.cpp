/* Longest Palindromic Subsequence */
/* Tabular solution, n^2 space, faster than the other I coded */

#include <iostream>
#include <string>

short LPS[1000][1000];

int main(){
    std::ios_base::sync_with_stdio(false);
    
    for( auto i=0; i!=999; i++ ){
        LPS[i][i] = 1;
        LPS[i+1][i] = 0;
    }
    LPS[999][999] = 1;
	std::string s;      s.reserve(1000);
	short i,j,d,n;

	int T;
	std::cin >> T;
	while(T--){
		std::cin >> s;
		n = s.size();
		for( d=1; d!=n; d++){
		    j=d;
		    for( i=0; i!=n-d; j++, i++ )
		        LPS[i][j] = ( s[i]==s[j] ? 2+LPS[i+1][j-1] : std::max( LPS[i][j-1], LPS[i+1][j] ) );
		}
	    std::cout << LPS[0][n-1] << '\n';
	}
	std::cout << std::flush;
	return 0;
}
