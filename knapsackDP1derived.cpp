#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
class tensor: public std::vector<V>{
	std::vector<size_t> dimensions;
	std::vector<size_t> steps;
	std::vector<size_t>::iterator tsteps, sB;
public:
	tensor(std::vector<size_t>& d):
	dimensions(d), steps(d.size()+1){
		steps.back() = 1;
		sB = steps.begin()+1;
		auto dB = dimensions.begin();
		for( auto dd = dimensions.end()-1; dd!= dimensions.begin()-1; dd-- )
			steps[dd-dB]=steps[dd-dB+1]**dd;
		this->resize(steps[0]);
	}
	tensor(std::vector<size_t>&& d):
	dimensions(d), steps(d.size()+1){
		steps.back() = 1;
		sB = steps.begin()+1;
		auto dB = dimensions.begin();
		for( auto dd = dimensions.end()-1; dd!= dimensions.begin()-1; dd-- )
			steps[dd-dB]=steps[dd-dB+1]**dd;
		this->resize(steps[0]);
	}
	using std::vector<V>::resize;
	tensor& resize(std::vector<size_t>& d){
		dimensions = d;
		steps.resize(d.size()+1);
		steps.back() = 1;
		sB = steps.begin()+1;
		auto dB = dimensions.begin();
		for( auto dd = dimensions.end()-1; dd!= dimensions.begin()-1; dd-- )
			steps[dd-dB]=steps[dd-dB+1]**dd;
		this->resize(steps[0]);
		return *this;
	}
	tensor& resize(std::vector<size_t>&& d){
		dimensions = d;
		steps.resize(d.size()+1);
		steps.back() = 1;
		sB = steps.begin()+1;
		auto dB = dimensions.begin();
		for( auto dd = dimensions.end()-1; dd!= dimensions.begin()-1; dd-- )
			steps[dd-dB]=steps[dd-dB+1]**dd;
		this->resize(steps[0]);
		return *this;
	}
	typename std::vector<V>::iterator it(std::vector<size_t>& c){
		i=this->begin();
		for( tsteps = sB; tsteps != steps.end(); tsteps++ )
			i+=c[tsteps-sB]**tsteps;
	}
	typename std::vector<V>::iterator it(std::vector<size_t>&& c){
		i=this->begin();
		for( tsteps = sB; tsteps != steps.end(); tsteps++ )
			i+=c[tsteps-sB]**tsteps;
	}
	V& operator() (std::vector<size_t>& c){
		i=this->begin();
		for( tsteps = sB; tsteps != steps.end(); tsteps++ )
			i+=c[tsteps-sB]**tsteps;	
		return *i;
	}
	V& operator() (std::vector<size_t>&& c){
		i=this->begin();
		for( tsteps = sB; tsteps != steps.end(); tsteps++ )
			i+=c[tsteps-sB]**tsteps;	
		return *i;
	}
	const size_t& d(size_t j){
		return dimensions[j];
	}
	typename std::vector<V>::iterator i;
};

const unsigned short W_MAX = 100;
const unsigned short N_MAX = 100;

template <typename V, typename W>
struct obj{
	V v;
	W w;
};

template <typename V, typename W>
auto knapsackDP1( std::vector<obj<V,W>>& o, tensor<V>& M ) -> tensor<V>& {
	std::sort( o.begin(), o.end(), [](obj<V,W>& a, obj<V,W>& b){ return a.w<b.w; } );
	
	auto o0 = o.begin()-1;
	std::vector<size_t> c(2);
	std::vector<size_t> tc(2);
	std::vector<size_t> ttc(2);

	for( c[0]=0; c[0]!=o.size()+1; c[0]++ ) M[c[0]] = 0;
	for( c[1]=0; c[1]!=M.size(); c[1]+=M.d(1) ) M[c[1]] = 0;

	W sumW=0;
	for( c[0]=1; c[0]!=M.d(0); c[0]++ ){
		sumW += o0[c[0]].w;
		for( c[1]=1; c[1]!=M.d(1) && c[1]!=sumW+1; c[1]++ ){
		    tc[0]=c[0]-1; tc[1]=c[1];
			if( o0[c[0]].w > c[1] )
				M(c) = M(tc);
			else {
			    ttc[0] = tc[0]; ttc[1] = tc[1]-o0[c[0]].w;
				M(c) = std::max( M(tc), static_cast<W>(M(ttc) + o0[c[0]].v) );
		
			}	    
		}
		tc[0]=c[0];
		for( ; c[1]!=M.d(1); c[1]++ ){
		    tc[1]=c[1]-1;
			M(c)=M(tc);
		}
	}

	/*for( c[0]=0; c[0]!=M.d(0); c[0]++ ){
		for( c[1]=0; c[1]!=M.d(1); c[1]++ )
			std::cout << M(c) <<'\t';
		std::cout << '\n';
	}*/
	return M;
}


int main(){
	std::ios_base::sync_with_stdio(false);

	std::vector<size_t> d {N_MAX+1, W_MAX+1};
	std::vector<obj<unsigned short, unsigned short>> o;		o.reserve(N_MAX);
	tensor<unsigned short> M(d);
	
	size_t W, n, wS, vS;
	unsigned short T;
	std::cin >> T;
	while(T--){
		std::cin >> n >> W;
		o.resize(n);
		d = { n+1, W+1 };
		M.resize(d);
		for( auto &oo: o ) std::cin >> oo.v;
		for( auto &oo: o ) std::cin >> oo.w;
		
		wS = 0;
		for( auto &oo: o ) wS += oo.w;
		if( wS<=W ){
			vS = 0;
			for( auto &oo: o ) vS += oo.v;
			std::cout << vS << '\n';
		} 
		else
			std::cout << knapsackDP1( o, M )({ n, W }) << '\n';
	}
	std::cout << std::flush;

	return 0;
}
