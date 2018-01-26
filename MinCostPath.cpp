/* Minimum Cost Path (Positive Edges) */
/* Is it guaranteed that the edges are positives?! */
/* Otherwise, use Bellman Ford */

#include <queue>
#include <vector>
#include <iostream>
#include <limits>

const short N_MAX = 50;

template <class T> 
struct priority_queue_with_reserve : std::priority_queue<T, std::vector<T>> {
	priority_queue_with_reserve(size_t n) : 
	std::priority_queue<T,std::vector<T>> () {
		this->c.reserve(n);
	}
};

template <class C, class T>
struct node{
	T v;
	int d;
	std::vector<typename C::iterator> l;
	char vv;
	node()	:	l() {
		l.reserve(4);
	}
};

template <typename T>
struct matrix_graph : std::vector<node<matrix_graph<T>,T>> {
	matrix_graph(){};
	matrix_graph(size_t n) 	: M{n}, N{n}, std::vector<node<matrix_graph<T>, T>>(n*n, node<matrix_graph<T>,T>()) {
		for( auto &el: *this ){
			std::cin >> el.v;
		};
		if(N>1)
			create_links();
	}

	void rsz(size_t n){
		M = N = n;
		this->resize(n*n);
		for( auto &el: *this ){
			std::cin >> el.v;
			el.l.resize(0);
		};
		if(N>1)
			create_links();
	}

	void create_links(){
		typename std::vector<node<matrix_graph<T>,T>>::iterator	it = this->begin(), 
																iE = this->begin()+N-1, 
												 		 		E = this->end()-1;
		it->vv = 0;												 		 		
		it->l.emplace_back(it+N);	
		it->l.emplace_back(it+1);
		it++;
		while( it != iE ){
			it->vv = 0;
			it->l.emplace_back(it+N);
			it->l.emplace_back(it-1);
			it->l.emplace_back(it+1);
			it++;
		}
		it->vv = 0;
		it->l.emplace_back(it+N);
		it->l.emplace_back(it-1);
		it++;

		while( (iE+=N) != E ){
			it->vv = 0;
			it->l.emplace_back(it-N);
			it->l.emplace_back(it+N);	
			it->l.emplace_back(it+1);
			it++;
			while( it != iE ){
				it->vv = 0;
				it->l.emplace_back(it-N);
				it->l.emplace_back(it+N);
				it->l.emplace_back(it-1);
				it->l.emplace_back(it+1);
				it++;
			}
			it->vv = 0;
			it->l.emplace_back(it-N);
			it->l.emplace_back(it+N);
			it->l.emplace_back(it-1);
			it++;
		}

		it->vv = 0;
		it->l.emplace_back(it-N);	
		it->l.emplace_back(it+1);
		it++;
		while( it != iE ){
			it->vv = 0;
			it->l.emplace_back(it-N);
			it->l.emplace_back(it-1);
			it->l.emplace_back(it+1);
			it++;
		}
		it->vv = 0;
		it->l.emplace_back(it-N);
		it->l.emplace_back(it-1);
		it++;
	}
	size_t M,N;
};

template <class O>
struct distance{
	typename O::iterator it;
	int d;
	distance( decltype(it)&& iit, int&& dd ):
	it{iit}, d{dd} {
		iit->vv = 1;
		iit->d = dd;
	}
	distance( decltype(it)&& iit, int& dd ):
	it{iit}, d{dd} {
		iit->vv = 1;
		iit->d = dd;
	}
	distance( decltype(it)& iit, int&& dd ):
	it{iit}, d{dd} {
		iit->vv = 1;
		iit->d = dd;
	}
	friend bool operator<(const distance<O>& a, const distance<O>& b){
		return a.d > b.d;		//The nearer the greater!
	}
};

int main(){
    std::ios_base::sync_with_stdio(false);

	int min_path;
	matrix_graph<int> M;	 	M.reserve(N_MAX*N_MAX);
	priority_queue_with_reserve<distance<decltype(M)>> D(N_MAX*N_MAX);	

	short N,T;
	std::cin >> T;
	while(T--){
		std::cin >> N;
		
		if( N==1 ) {
		    std::cin >> N;
		    std::cout << N << '\n';
		}
		else{
		    M.rsz(N);
    		D.emplace(distance<decltype(M)>(M.begin(), M[0].v));
    		auto it = D.top().it;
    		while(!D.empty()){
			if( D.top().it->d < D.top().d ){
				D.pop();
				continue;
			}
    			it = D.top().it;	it->vv = 2;
    			D.pop();
    			for( auto &inode: it->l ){
    				switch( inode->vv ){
    				case 0: 
    					D.emplace(distance<decltype(M)>(inode, it->d+inode->v));
    					break;
    				case 1:
					if( it->d+inode->v < inode->d )
						D.emplace(distance<decltype(M)>(inode, it->d+inode->v));
    				}
    			}
    		}   

		    std::cout << M.back().d << '\n';
		}
	}

	return 0;
}
