/* Problem Source: codeforces 932E */
/* Solution License: contact Michele Miccinesi */
/* raw solution, not optimal */

#include <iostream>
#include <vector>

const uint64_t mod=1000000007;

//k>0, N>1
inline void f(std::vector<uint64_t>& T, const int& k, const int& N){
	for( int i=1; i!=k+1; ++i ){
		for( int j=i, n=N-i+1; j; --j, ++n ){
			(T[j]*=j)+=n*T[j-1];
			T[j]%=mod;
		}
		T[0]=0;
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int N, k;
	std::cin >> N >> k;
	if( N==1 ){
		std::cout << 1 << std::endl;
		return 0;
	}

	std::vector<uint64_t> T(k+1, 0);
	T[0]=1;
	f(T, k, N);

	std::vector<uint64_t> p2(k+1,0);
	{
		int j=N;
		std::vector<int> p;
		uint64_t p2N=1;
		while(j){
			p.push_back(j&1);
			j>>=1;
		}
		for( int i=p.size()-1; i!=-1; --i ){
			p2N*=p2N;
			p2N%=mod;
			if( p[i] ){
				p2N<<=1;
				p2N%=mod;
			}
		}
		p2[0]=p2N;
	}
	for( int i=1; i!=k+1&&i!=N+1; ++i )
		p2[i]=(p2[i-1]*500000004)%mod;

	uint64_t res=0;
	for( int i=0; i!=k+1&&i!=N+1; ++i ){
		res+=(p2[i]*T[i]);
		res%=mod;
	}

	std::cout << res << std::endl;

	return 0;
}
