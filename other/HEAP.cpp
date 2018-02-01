/* heap */
/* License: contact Michele Miccinesi */

#include <bits/stdc++.h>
// How to check properties of C?
template <class T, class C>
struct heap{
	struct type_traits{
		type_traits(): cmp(){}
		C cmp;
	};
private:
	int counter{0};
	typename std::vector<T>::iterator tc;
	void find_to_erase(size_t& s, const T& v){
		if( s<=c.size() ){
			if( tc[s]==v ) {
				erase(s);
				find_to_erase_blocked_source(s,v);
			}
			else if( traits.cmp(v,tc[s]) ) {
				find_to_erase(s<<=1,v);
				find_to_erase(++(s<<=1),v);
			}
		}
		s>>=1;
	}
	void find_to_erase_blocked_source(size_t& s, const T& v){
		if( s<=c.size() ){
			if( tc[s]==v ) {
				erase(s);
				find_to_erase_blocked_source(s,v);
			}
			else if( traits.cmp(v,tc[s]) ) {
				find_to_erase(s<<=1,v);
				find_to_erase(++(s<<=1),v);
			}
		}
	}
public:
	type_traits traits;
	std::vector<T> c;
	heap( size_t n ): c(n), traits() {	tc=c.begin()-1; }
	heap( std::vector<T>&& v ): c(), traits(){
		std::swap(v, c);
		tc = c.begin()-1;
	}
	heap( std::vector<T>& v ): c(v), traits(){
		tc = c.begin()-1;
	}
	template <class CC>
	heap( heap<T,CC>&& h ): c(), traits(){
		std::swap( h.c, c );
		tc = c.begin()-1;
	}
	void heapify(C& cmp){
		traits.cmp = cmp;
		for( size_t n = (c.size()>>1); n; --n )
			heapify_range(n,c.size(),cmp);
	}
	void heapify(C&& cmp){
		std::swap(traits.cmp, cmp);
		for( size_t n = (c.size()>>1); n; --n )
			heapify_range(n,c.size(),traits.cmp);
	}
	void heapify(){
		for( size_t n = (c.size()>>1); n; --n )
			heapify_range(n,c.size(),traits.cmp);
	}
	void heapify_range(size_t s, size_t const& e, const C& cmp){
		size_t ss = s;
		while((ss<<=1) <= e){
			if(ss!=e)
				ss = cmp(tc[ss], tc[ss+1])?ss+1:ss;
			if(cmp(tc[s], tc[ss])){
				std::swap(tc[s],tc[ss]);
				s=ss;
				++counter;
			}
		}
	}
	T pop(){
		auto top_copy = c[0];
		c[0] = c.back();
		c.resize(c.size()-1);
		heapify_range(1,c.size(), traits.cmp);
		return top_copy;
	}
	const T& top(){
		return c[0];
	}
	// std::reverse if you want to keep the heap property!
	std::vector<T>& sort(){
		counter=0;
		for( size_t e = c.size(); e!=1; ){
			std::swap(tc[e],c[0]);
			heapify_range(1,--e,traits.cmp); 
		}
#ifndef NDEBUG
		std::cout << c.size() << " elements, " << counter<< " swaps, " << c.size()*log2(c.size()) << "=n log n\n";
#endif
		return c;
	}
	void push(const T &v){
		c.push_back(v);
		for( size_t s = c.size(), sp = (s>>=1); sp; sp>>=1, s>>=1){
			if( traits.cmp(tc[sp],tc[s]) )
				std::swap(tc[sp], tc[s] );
			else 
				break;
		}
	}
	size_t find(const T& v){
		size_t t;
		if(c.empty())return 0;
		std::stack<size_t> s;
		if( traits.cmp(c[0],v) ) return 0;
		else if( c[0]==v) return 1;
		s.push(size_t(1));
		while(!s.empty()){
			t = s.top();
			s.pop();
			if((t<<=1) <= c.size()){
				if(tc[t]==v)
					return t;
				else if(traits.cmp(v,tc[t]))
					s.push(t);
				if(t != c.size()){
					++t;
					if(tc[t]==v)
						return t;
					else if(traits.cmp(v,tc[t]))
						s.push(t);
				}
			}
		}
		return 0;
	}
	std::vector<size_t> find_all(const T& v){
		std::vector<size_t> o;
		std::stack<int> s;
		size_t t;
		if( traits.cmp(c[0],v) ) return o;
		else if(c[0]==v) o.push_back(1);
		s.push(1);
		while(!s.empty()){
			t = s.top(), s.pop();
			if((t<<=1) <= c.size()){
				if(tc[t]==v)
					o.push_back(t);
				if(!traits.cmp(tc[t],v))
					s.push(t);
				if(t != c.size()){
					++t;
					if(tc[t]==v)
						o.push_back(t);
					if(!traits.cmp(tc[t],v))
						s.push(t);
				}
			}
		}
		return o;
	}
	void erase(const size_t& t){
		if(t<=0||t>c.size()) return;
		tc[t]=c.back();
		c.resize(c.size()-1);
		if(t!=c.size()+1)	update(t,tc[t]);
	}
	void remove(const T& v){
		erase(find(v));
	}
	void remove_all(const T& v){
		size_t s=1;
		find_to_erase(s,v);
	}
	void remove_all_by_find_all(const T& v){
		auto V(find_all(v));
		for( auto &x: V )
			while(x<=c.size()){
				if(tc[x]==v)
					erase(x);
				else break;
			}
	}
	const T& operator[](const size_t& t){ return tc[t]; }
	void update(size_t t, const T& v){
		tc[t]=v;
		size_t k;
		for( k=(t>>1); k; k>>=1, t>>=1 ){
			if( traits.cmp(tc[k],tc[t]) )
				std::swap(tc[t],tc[k]);
			else break;
		}
		for(k=(t<<1); k<=c.size(); k<<=1){
			if(k!=c.size())
				k = traits.cmp(tc[k+1],tc[k])?k:k+1;
			if( traits.cmp(tc[t],tc[k]) )
				std::swap(tc[k],tc[t]);
			else break;
			t=k;
		}
	}
};

#ifndef NDEBUG
int main(){
	size_t n;
	std::cin >> n;
	std::vector<int> v(n);
	for( auto &vv: v ) std::cin >> vv;

	struct compare{
		compare(){}
		const bool operator()( const int& a, const int& b ) const{
			return a<b;
		}
	} C;
	heap<int, compare> h(std::move(v));
	h.heapify(C);
	for( auto &hh: h.c ) std::cout << hh << ' ';
	std::cout << ' ' << std::endl;
	for( auto &ee: h.sort() ) std::cout << ee << ' ';
	std::cout << ' ' << std::endl;
	std::reverse(h.c.begin(), h.c.end());
	int i;
	std::vector<bool> V(1001);
	std::fill(V.begin(), V.end(), 0);
	while(!std::cin.eof()){
		std::cin >>  i;
		if(h.find(i)) 
			std::cout << "TROVATO "<< i <<'\n';
		else if(!V[i])
			std::cout << "NON TROVATO " << i <<'\n';

		h.remove_all_by_find_all(i);
		V[i]=true;
		std::cout << " RIMANGONO " << h.c.size() << std::endl;
	}
	if(h.c.empty()) std::cout << "\n HEAP VUOTO!" << std::endl;
	return 0;
}
#endif


/* HEAP_test.py: 

import random
import sys

n = int(sys.argv[1])

print n
v=[]
for i in xrange(0,n):
	v.append(random.randint(0,1000))
	sys.stdout.write(str(v[-1])+' ')
sys.stdout.flush()
for i in v:
	print i
*/
