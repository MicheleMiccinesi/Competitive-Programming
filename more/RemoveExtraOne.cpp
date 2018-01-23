/* Remove Extra One */
/* Problem Source: codeforces 900C */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>


int main(){
	std::ios_base::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<int> mr(n,0);
	decltype(mr)::iterator tmr = mr.begin()-1;
	int lm[] = {0,0};
	bool i = true;
	int el;
	while(n--){
		std::cin >> el;
		if( el>lm[i] ){
			tmr[el]--;
			i=!i;
			lm[i]=el;
		}
		else if( el>lm[!i] ){
			lm[!i] = el;
			tmr[lm[i]]++;
		}
	}

	n = mr.size()+1;
	int J{n},M{-1};
	for( int j=1; j!=n; j++ )
		if( tmr[j]>M || (tmr[j]==M && j<J) ) {
			M = tmr[j];
			J = j;
		}
	std::cout << J << std::endl;

	return 0;
}
