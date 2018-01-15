// Circular Range Minimum Query 
// First naive version 
// 1.3s
// License: contact the author 

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define NDEBUG

inline uint32_t to_msbit(uint32_t& n){
	return ((((((n|=(n>>1))|=(n>>2))|=(n>>4))|=(n>>8))|=(n>>16))+=1)>>=1;
}

template <class V, class Op>
class lazy_seg_tree{
	struct _el{
		V v;
		V l{0};
		uint32_t r[2];
	};
	std::vector<_el> c;
	uint32_t n, p2, k, _first, _last, _size;
	Op _op;
	V& _range_query_naive(uint32_t a, const uint32_t& i, const uint32_t& j){
		V& Lazy{c[a].l}, & v{c[a].v};
		uint32_t& r0{c[a].r[0]},& r1{c[a].r[1]};
		a<<=1;
		if(Lazy){
			v+=Lazy;
			if(r0!=r1){
				c[a].l+=Lazy;
				c[a+1].l+=Lazy;
			}
			Lazy-=Lazy;
		}
		if(i<=r0&&j>=r1)
			return v;
		if(j<=c[a].r[1])
			return _range_query_naive(a,i,j);
		if(i>c[a].r[1])
			return _range_query_naive(a+1,i,j);
		return _op(_range_query_naive(a,i,j), _range_query_naive(a+1,i,j));
	}

	void _push_lazy(uint32_t a){
		uint32_t& r0{c[a].r[0]}, r1{c[a].r[1]};
		V& Lazy{c[a].l};
		c[a].v+=Lazy;
		if(r0!=r1){
			a<<=1;
			c[a].l+=Lazy;
			c[a+1].l+=Lazy;
		}
		Lazy-=Lazy;
	}

	void _add(uint32_t a, const uint32_t& i, const uint32_t& j, const V& w){
		uint32_t &r0{c[a].r[0]}, &r1{c[a].r[1]};
		V& v{c[a].v}, &Lazy{c[a].l};
		a<<=1;
		if(Lazy){
			v+=Lazy;
			if(r0!=r1){
				c[a].l+=Lazy;
				c[a+1].l+=Lazy;
			}
			Lazy-=Lazy;
		}
		if(i<=r0&&j>=r1){
			v+=w;
			if(r0!=r1){
				c[a].l+=w;
				c[a+1].l+=w;
			}
			return;
		}
		if(c[a].r[1]>=i)
			_add(a, i, j, w);
		else if(c[a].l)
			_push_lazy(a);
		if(c[a].r[1]<j)
			_add(a+1, i, j, w);
		else if(c[a+1].l)
			_push_lazy(a+1);
		v=_op(c[a].v,c[a+1].v);
	}
public:
	typedef V ValueType;
	typedef Op OpType;
	lazy_seg_tree(std::vector<V>& v): c(v.size()<<1), _size(v.size()),n(v.size()), p2(v.size()), _op(), _first(0), _last(v.size()-1){
		k=(n^=to_msbit(p2));
		uint32_t i, j;
		for( i=_size, j=(k<<1); j!=_size; ++i, ++j ){
			c[i].v=v[j];
			c[i].r[0]=c[i].r[1]=j;
		}
		for( j=0; i!=c.size(); ++i, ++j ){
			c[i].v=v[j];
			c[i].r[0]=c[i].r[1]=j;
		}
		
		for( j=((--i)>>1); j; --i, --j ){
			c[j].r[1]=c[i].r[1];
			c[j].v=_op(c[i].v, c[i-1].v);
			--i;
			c[j].r[0]=c[i].r[0];
		}
	}
	void add(const uint32_t &i, const uint32_t &j, const ValueType& w){
		if(j<i){
			_add(1, _first, j, w);
			_add(1, i, _last, w);
		}
		else 
			_add(1, i, j, w);
	}
	const ValueType& operator()(const uint32_t &i, const uint32_t &j){
		return j<i?(i==j+1?c[1].v:_op(_range_query_naive(1,_first, j),_range_query_naive(1,i,_last))):_range_query_naive(1,i,j);
	}
};

template <class T>
struct _MIN{
	T& operator()( T& a, T& b){
		return a<b?a:b;
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<int64_t> V(n);
	for( auto &v: V )
		std::cin >> v;
	lazy_seg_tree<int64_t, _MIN<int64_t>> L(V);
	std::cin >> n;

	uint32_t i,j;
	int64_t v;
	std::string line;
	std::getline(std::cin, line);
	while(n--){
		std::getline(std::cin, line);
		std::stringstream line_stream; 
		line_stream << line;
		if(line_stream >> i >> j >> v){
			if(v)
				L.add(i,j,v);
		}
		else
			std::cout << L(i,j) <<'\n';
	}
	std::cout << std::flush;
	return 0;
}
