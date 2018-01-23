/* Sereja and Brackets */
/* Problem Source: codeforces 380C */
/* Solution License: contact Michele Miccinesi */
/* Noncommutative extension to segment tree, prosaic version */

#include <vector>
#include <iostream>

struct par{
	par(){}
	constexpr par(const uint32_t&& o, const uint32_t&& c, const uint32_t&& cm): open(o), close(c), complete(cm){}
	uint32_t open,close,complete;
};

struct _BRA_KET{
	static constexpr par zero{(uint32_t)0,(uint32_t)0,(uint32_t)0};
	static std::false_type commute;
	par operator()(const par& a, const par& b){
		par new_par;
		if(a.open<b.close){
			new_par.complete = a.complete+b.complete+a.open;
			new_par.open = b.open;
			new_par.close = a.close+b.close-a.open;
		} else {
			new_par.complete = a.complete+b.complete+b.close;
			new_par.open = b.open+a.open-b.close;
			new_par.close = a.close;
		}
		return new_par;
	}
	void operator()(par&& a, const par& b){
		if(a.open<b.close){
			a.complete += b.complete+a.open;
			a.close += b.close-a.open;
			a.open = b.open;
		} else {
			a.complete += b.complete+b.close;
			a.open += b.open-b.close;
		}
	}
	void operator()(const par& a, par&& b){
		if(a.open<b.close){
			b.complete += a.complete+a.open;
			b.close += a.close-a.open;
		} else {
			b.complete += a.complete+b.close;
			b.open += a.open-b.close;
			b.close = a.close;
		}
	}
};


template <class T, class Op>
class seg_tree{
protected:
	Op _op;
	T _range_query(uint32_t& i, uint32_t& j, std::false_type){
		T vi{Op::zero}, vj{Op::zero};
		for(; i<=j; i>>=1, j>>=1){
			if(i&1){
				_op(std::move(vi), c[i]);
				//std::cout << "i: " << i << " complete left: " << vi.complete <<'\n';
				++i;
			}// else std::cout << "i: " << i <<'\n';
			if(!(j&1)){
				_op(c[j], std::move(vj));
				//std::cout << "j: " << j << " complete right: " << vj.complete <<'\n';
				--j;
			}// else std::cout << "j: " << j <<'\n';
		}
		_op(std::move(vi),vj);
		//std::cout << "complete: " << vi.complete << '\n';
		return vi;
	}
	T _range_query(uint32_t& i, uint32_t& j, std::true_type){
		T v{Op::zero};
		for(; i<=j; i>>=1, j>>=1){
			if(i&1){
				_op(std::move(v), c[i]);
				++i;
			}
			if(!(j&1)){
				_op(c[j], std::move(v));
				--j;
			}
		}
		return v;
	}
public:
	std::vector<T> c;
	uint32_t _size;
	uint32_t offset;
	seg_tree(): _op(), c(0), _size(0){}
	seg_tree(std::vector<T>& v): c(v.size()<<1), _size(c.size()), _op(){
		int i,j;
		for( i=_size, j=0; i!=c.size(); ++i, ++j )
			c[i]=v[j];
		for( j=((--i)>>1); j; i-=2, --j )
			c[j]=_op(c[i-1],c[i]);
	}
	T operator()(uint32_t i, uint32_t j){
		return _range_query(i+=offset,j+=offset,Op::commute);
	}
};

template <uint32_t OFFSET>
struct countBracket:seg_tree<par,_BRA_KET>{
	countBracket(std::string& s){
		c.reserve(s.size()<<1);
		c.resize(s.size());
		offset=s.size()-OFFSET;
		_size=s.size();

		for( auto &p: s )
			switch(p){
			case '(':
				c.emplace_back((uint32_t)1, (uint32_t)0, (uint32_t)0);
				break;
			case ')':
				c.emplace_back((uint32_t)0, (uint32_t)1, (uint32_t)0);
				break;
			}
		int i, j;
		for(i=c.size()-1, j=i>>1; j; i-=2, --j)
			c[j]=_op(c[i-1], c[i]);
	}
	void print(){
		for( auto &x: c )
			std::cout << x.complete << ' ';
		std::cout << std::endl;
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string s;
	std::getline(std::cin, s);
	countBracket<(uint32_t)1> bk(s);
	//bk.print();

	size_t m;
	std::cin >> m;
	uint32_t i,j;
	while(m--){
		std::cin >> i >> j;
		if(i==j){
			std::cout << 0 << '\n';
			continue;
		}
		std::cout << (bk(i,j).complete<<1) << '\n';
	}
	std::cout << std::flush;

	return 0;
}


/*
())( ())(())(


5 
3       1
1   1   1   0
1 0 1 0 0 0 0 0 
00000000
*/
