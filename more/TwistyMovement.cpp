/* Problem Source: codeforces 934C */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>

struct matrix: std::vector<short>{
	int d[2];
	matrix(const int &i, const int &j): std::vector<short>(i*j){
		d[0]=i*j;
		d[1]=j;
	}
	short& operator()(const int &i, const int &j){
		return operator[](i*d[1]+j);
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	if( n<3 ){
		std::cout << n << std::endl;
		return 0;
	}
	std::vector<short> V(n+2);
	std::vector<short> C1(n+2), C2(n+2);

	for( int i=1; i!=n+1; ++i )
		std::cin >> V[i];

	C1[0]=C2[n+1]=0;
	for( int i=1; i!=n+1; ++i )
		C1[i]=V[i]==1?C1[i-1]+1:C1[i-1];
	for( int i=n; i; --i )
		C2[i]=V[i]==2?C2[i+1]+1:C2[i+1];
	C1[n+1]=C1[n];
	C2[0]=C2[1];

	matrix T(n+2, n+2);
	for( int j=2; j!=n+1; ++j ){
		if( V[n-j+1]==2 )
			for( int i=1; i!=j; ++i )
				T(i, j)=T(i, j-1)+1;
		else
			for( int i=1; i!=j; ++i )
				T(i, j)=std::max(T(i, j-1), static_cast<short>(C1[n+1-i]-C1[n-j]));
		T(j, j)=1;
	}

	short l=0;
	for( int i=1; i!=n+1; ++i )
		for( int j=i; j!=n+1; ++j )
			l=std::max(l, static_cast<short>(C1[i-1]+T(n+1-j, n+1-i)+C2[j+1]));

	std::cout << l << std::endl;

	return 0;
}
