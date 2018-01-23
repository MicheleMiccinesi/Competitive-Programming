/* Ada and Bee Hives */
/* Problem Source: codeforces */
/* Solution License: contact Michele Miccinesi */
/* in few words: 2d fenwick tree */

#include <iostream>
#include <vector>

template <typename T>
struct matrix: std::vector<T>{
	size_t d[2];
	template <typename A, typename B>
	matrix(A&& a, B&& b): d{a,b}, std::vector<T>(a*b){}
	template <typename A, typename B>
	T& operator()(A&& a, B&& b){ return this->operator[](d[1]*a+b); }
};

// Counting from 1
template <typename T, typename S>
class rrBIT2{
public:
	S s,ss;
	matrix<T> c;
	template <typename A, typename B>
	rrBIT2(A&& a, B&& b): c(a+1,b+1){}
	rrBIT2(matrix<T>& M): c(M.d[0]+1, M.d[1]+1){
		for( size_t i=1; i!=c.d[0]; ++i )
			for( size_t j=1; j!=c.d[1]; ++j )
				c(i,j) = M(i-1,j-1);
		for( size_t i=1; i!=c.d[0]; ++i )
			for( size_t j=1; j!=c.d[1]; ++j )
				if( j+(j&-j)<c.d[1] )
					c(i,j+(j&-j))+=c(i,j);
		for( size_t i=1; i!=c.d[0]; ++i )
			for( size_t j=1; j!=c.d[1]; ++j )				
				if( i+(i&-i)<c.d[0] )
					c(i+(i&-i),j)+=c(i,j);
	}
	template <typename A=T, typename B>
	void add(A&& a, size_t i, B&& jB){
		for( ; i<c.d[0]; i+=(i&-i) )
			for( size_t j=jB; j<c.d[1]; j+=(j&-j) )
				c(i,j)+=a;
	}
	template <typename B>
	S& sum(size_t i, B&& jB){
		s-=s;
		for( ; i; i&=i-1 )
			for( size_t j=jB; j; j&=j-1 )
				s+=c(i,j);
		return s;
	}
	S& ssum(size_t& ii, size_t& jj, size_t& i, size_t& j){
		ss = sum(i,j);
		ss -= sum(--ii,j);
		ss -= sum(i,--jj);
		ss += sum(ii, jj);
		return ss;
	}
};
#include <algorithm>
int main(){
	std::ios_base::sync_with_stdio(false);

	int N,M,Q;
	std::cin >> N >> M >> Q;
	matrix<int64_t> m(N,M);
	for( auto &mm: m ) std::cin >> mm;
	rrBIT2<int64_t, int64_t> c(m);
	int q;
	size_t i,j,ii,jj;
	int64_t a;
	while(Q--){
		std::cin >> q;
		switch(q){
		case 1:
			std::cin >> i >> j >> a;
			c.add(a,i,j);
			break;
		case 2:
			std::cin >> ii >> jj >> i >> j;
			std::cout << c.ssum(ii,jj,i,j) <<'\n';
			break;
		}
	}

	std::cout << std::flush;
	return 0;
}
