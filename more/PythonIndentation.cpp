/* Python Indentation */
/* Problem Source: Python Indentation on codeforces */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

const int mod = 1000000007;

inline void get_blocks(std::vector<int>& b, const int &n){
	std::string c;
	for( int i=0, j=0; i!=n; ++i ){
		c.clear();
		while(c.empty())
			std::getline(std::cin, c);
		switch( c[0] ){
			case 's':
				b.push_back(j);
				j=0;
				break;
			case 'f':
				++j;
				break;
			default:
				break;
		}
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	//blocks of code with delta indendation
	std::vector<int> b;												
	b.reserve(n);
	get_blocks(b, n);
	int i = b.size()-1;

	int s=1;
	for( int j=0; j!=i; ++j )
		s+=b[j];

	std::vector<int> S(s,1);
	int B=0;
	while(i--){
		for( int j=B+1; j<S.size(); ++j ){
			S[j]+=S[j-1];
			if(S[j]>mod) S[j]-=mod;
		}
		B+=b[i];
	}
	std::cout << S.back() << std::endl;

	return 0;
}
