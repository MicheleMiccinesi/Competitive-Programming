/* Jamie and Binary Sequence */
/* Problem Source: codeforces 916B */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <deque>
uint64_t _1 = 1;

struct p{
	int64_t i,m;
};

inline char msbi(int64_t n){
	for( char i=63; i; --i )
		if(n&(_1<<i))
			return i;
	return 0;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	std::deque<p> N;

	uint64_t n;
	uint64_t k,le2;
	short bits=0;
	std::cin >> n >> k;

	if( n==0 ){
		if( k==0 )
			std::cout << "Yes\n" << std::endl;
		else
			std::cout << "No" << std::endl;
		return 0;
	}

	for( short i=63; i!=-1; --i )
		if(n&(_1<<i)){
			N.push_back({i,1});
			++bits;
		}
	if(bits>k) 
		std::cout << "No" << std::endl;
	else{
		k-=bits;
		std::cout << "Yes\n";
		while( k>=N[0].m ){
			k+=N[0].m;		//so that then you subtract power of 2 times m
			le2=msbi(k/N[0].m);
			if(N.size()==1){
				N[0].m<<=le2;
				N[0].i-=le2;
				k-=N[0].m;
			}
			else{
				if(le2>=N[0].i-N[1].i){
					N[1].m+=(N[0].m<<=(N[0].i-N[1].i));
					k-=N[0].m;
					N.pop_front();
				}
				else{
					N[0].m<<=le2;
					k-=N[0].m;
					N[0].i-=le2;	//break....is optional, if you don't like it
					break;
				}
			}
		}
		if(k>0){
			if(N.back().m==1){
				N.back().m=2;
				--N.back().i;
				--k;
			}
			else {
				--N.back().m;
				N.push_back({N.back().i-1, int64_t(2)});
				--k;
			}
			while(k>0){
				N.back().m=1;
				N.push_back({N.back().i-1,int64_t(2)});
				--k;
			}
		}

		for( auto& b: N )
			for( int64_t i=0; i!=b.m; ++i )
				std::cout << b.i << ' ';
		std::cout << std::endl;
	}


	return 0;
}
