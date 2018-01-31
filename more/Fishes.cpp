/* Fishes */
/* Problem Source: codeforces 912D */
/* Solution License: contact Michele Miccinesi */

#ifndef NDEBUG
	#define NDEBUG
#endif
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

std::vector<int> fill_occurrences(const int& r, const int& l){
	std::vector<int> O;	O.reserve(r);
	int i=0;
	while(true){
		if( i==r-1 ) {
			if(l-2*i) O.push_back(l-2*i);
			break;
		}
		else {
			if(r+i<l){
				O.push_back(2);
				++i;
			}
			else{
				if(l-2*i) O.push_back(l-2*i);
				break;
			}
		}
	}
	return O;
}

typedef std::vector<int> vi;
struct pt{
	pt(int const& ii, int const& jj): i(ii), j(jj){
		p=i*static_cast<int64_t>(j);
	}
	int i,j;
	int64_t p;
	bool operator<(const pt& ppt) const{
		return this->p<ppt.p;
	}
};
#include <queue>
template <typename T>
struct pqr: std::priority_queue<T,std::vector<T>>{
	pqr(size_t s): std::priority_queue<T,std::vector<T>>(){
		this->c.reserve(s);
	}
};

int64_t put_fishes(vi& M, vi& N, vi& njm, int k){
	int64_t sum = 0; 
	int tMN,i,j;
	auto bM = M.begin()-1;	auto bN = N.begin()-1;	auto tnjm = njm.begin()-1;
	pqr<pt> Q(M.size());
	Q.emplace(M.size(),tnjm[M.size()]--);
	while(true){
		i=Q.top().i;	j=Q.top().j;
		tMN = static_cast<int>(std::min(bM[i]*static_cast<int64_t>(bN[j]),static_cast<int64_t>(k)));
		sum += Q.top().p*tMN;
#ifndef NDEBUG
		std::cout << "VALORE: "<<Q.top().p << " quanti: " << tMN << '\n';
#endif
		Q.pop();
		if(!(k-=tMN)) 
			return sum;
		if(tnjm[i])
			Q.emplace(i,tnjm[i]--);
		if(i!=1 && tnjm[i-1]==N.size())
			Q.emplace(i-1,tnjm[i-1]--);	
	}
}
int main(){
	std::ios_base::sync_with_stdio(false);

	int m,n,r,k,im,in;
	int64_t sum;
	std::cin >> m >> n >> r >> k;
	if(m>n) 
		std::swap(m,n);
	std::vector<int> M(fill_occurrences(r,m));
	std::vector<int> N(fill_occurrences(r,n));
#ifndef NDEBUG
	for( auto &m: M ) std::cout << m << ' '; std::cout << '\n';
	for( auto &n: N ) std::cout << n << ' '; std::cout << '\n';
#endif
	std::vector<int> nj(M.size(),N.size());
	sum = put_fishes(M,N,nj,k);
	int64_t tot = (m-r+1)*static_cast<int64_t>(n-r+1);
#ifndef NDEBUG
	std::cout << sum << ' ' << tot << '\n';
#endif
	long double ans = ((long double)sum)/tot;

    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    std::cout << ans << std::endl;

    return 0;
}
