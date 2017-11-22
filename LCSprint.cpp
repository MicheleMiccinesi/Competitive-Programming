#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int32_t One = 1;

template <typename T>
struct reversionWrapper { T& iterable; };

template <typename T>
auto std::begin (reversionWrapper<T> x) { return std::rbegin(x.iterable); }

template <typename T>
auto std::end (reversionWrapper<T> x) { return std::rend(x.iterable); }

template <typename T>
reversionWrapper<T> reverse (T&& iterable) { return { iterable }; }


template <typename T>
class tensor{
	int64_t i;
	uint64_t dataIndex,j;

	template <typename X>
	void subPrint(std::vector<X>& toPrint,std::ostream& out, int32_t d){
		int32_t j,i;
		if(dimensions.size()==d) for( j = dataIndex; dataIndex != j+steps[d-1]; out << toPrint[dataIndex++] << '\t' );
		else 
			for(j = dataIndex; dataIndex != j+steps[d-1]; ) { 
				i = dimensions.size()-d; 
				subPrint(toPrint, out, d+1); 
				while(i--) out << '\n';
			}
	}
public:
	std::vector<int32_t> dimensions;
	std::vector<int32_t>::iterator tdimensions;
	std::vector<T> data;
	std::vector<int32_t> steps;
	tensor(const std::vector<int32_t>&& dim)
	{
		dimensions = std::vector<int32_t> (dim);
		tdimensions = dimensions.begin()-1;
		steps = std::vector<int32_t> (dimensions.size()+1);

		steps.back() = 1;
		i = D();
		for(auto &x: reverse(dimensions)) steps[i] = steps[i--]*x;
		data = std::vector<T> (steps.front());
	}
	T& operator() (std::vector<int32_t>& indices){
		dataIndex=0; j = indices.size();
		if(indices.size() == steps.size()-1)
			for(auto x=indices.rbegin(); x!=indices.rend(); x++) dataIndex += steps[j--]*(*x);
		return data[dataIndex];
	}
	T& operator() (std::vector<int32_t>&& indices){
		dataIndex=0; j = indices.size();
		if(indices.size() == steps.size()-1)
			for(auto x=indices.rbegin(); x!=indices.rend(); x++) dataIndex += steps[j--]*(*x);
		return data[dataIndex];
	}	
	auto& size(){
		return steps.front();
	}
	const auto D(){
		return dimensions.size();
	}
	void fill(T&& value){
		std::fill( data.begin(), data.end(), value );
	}
	void print(std::ostream& out){
		dataIndex = 0;
		subPrint(data, out, 1);
	}
	template <typename X>
	void print(std::vector<X>& toPrint, std::ostream& out){
		dataIndex = 0;
		subPrint(toPrint, out, 1);
	}
};

template <typename T>
inline T& max(T& a, T& b){
	return a>b?a:b;
}

typedef std::string::iterator sti;
int32_t& LCS(sti& aB, sti aE, sti& bB, sti bE, tensor<int32_t>& M){
	if( M({aE-aB, bE-bB})!=-1 ) 
		return M({aE-aB, bE-bB});
	if( *aE == *bE )
		return M({aE-aB, bE-bB}) = LCS( aB, aE-1, bB, bE-1, M )+1;
	return M({aE-aB, bE-bB}) = max( LCS( aB, aE-1, bB, bE, M ), LCS( aB, aE, bB, bE-1, M ) );
}

void printLCS(sti& aB, sti aE, sti& bB, sti bE, tensor<int32_t>& M, std::string& s ){	
	int32_t f,g;
	std::vector<int32_t> c(2);
	c[0]=aE-aB;
	c[1]=bE-bB;
	s.resize(M(c));
	for( auto& l: reverse(s) ){
		while( aB[c[0]] != bB[c[1]] ){
			f=g=-1;
			if( c[0]-- )
				f = M(c);
			c[0]++;
			if( c[1]-- )
				g = M(c);
			if( g<f ){
				c[1]++;
				c[0]--;
			}
		}
		l = aB[c[0]];
		c[0]--;
		c[1]--;
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int32_t T;
	std::cin >> T;
	int32_t n,m;
	std::string a,b;
	a.reserve(100);
	b.reserve(100);
	std::vector<int32_t> coor(2);
	while(T--){
		//std::cin >> n >> m;
		std::cin >> a >> b;
		tensor<int32_t> matrix({a.size(),b.size()});
		matrix.fill(-1);				

	/* Prefilling first row and column is saving ifs in LCS( ... ) */
		coor[0]=0; 
		for( coor[1]=0; coor[1]!=b.size() && b[coor[1]]!=a[0]; coor[1]++ ) 
			matrix( coor ) = 0;
		for( ; coor[1]!=b.size(); coor[1]++ )
			matrix( coor ) = 1;
		coor[1]=0;
		for( ; coor[0]!=a.size() && a[coor[0]]!=b[0]; coor[0]++ )
			matrix( coor ) = 0;
		for( ; coor[0]!=a.size(); coor[0]++ )
			matrix( coor ) = 1;

		sti abegin = a.begin();
		sti bbegin = b.begin();
		std::cout << LCS( abegin, a.end()-1, bbegin, b.end()-1, matrix ) << std::endl;

		std::string lcs;
		printLCS( abegin, a.end()-1, bbegin, b.end()-1, matrix, lcs );

		std::cout << lcs << std::endl;

		matrix.print(std::cout);
	}	
	return 0;
}
