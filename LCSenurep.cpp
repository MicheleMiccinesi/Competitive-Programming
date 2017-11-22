/* Counting All LCSs  with repetitions */

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

void countLCS(std::string& a, std::string& b, tensor<int32_t>& l, tensor<int32_t>& c){
	auto a0 = a.begin()-1; auto b0 = b.begin()-1;
	auto aB = a.begin(); auto bB = b.begin();
	auto aE = a.end(); auto bE = b.end();
	std::vector<int32_t> co(2);
	std::vector<int32_t> col(2);
	std::vector<int32_t> cou(2);
	std::vector<int32_t> coul(2);
	for( auto ai = aB; ai!=aE; ai++ )
		for( auto bi = bB; bi!=bE; bi++ ){
			co[0] = col[0] = ai-a0; cou[0] = coul[0] = co[0]-1;
			co[1] = cou[1] = bi-b0; col[1] = coul[1] = co[1]-1;
			if( *ai != *bi ){
				if( l(col) == l(cou) ){
					l(co) = l(col);
					if( l(coul) < l(cou) )
						c(co) = c(cou) + c(col);
					else
						c(co) = max( c(cou), c(col) );
				}
				else if( l(cou) > l(col) ){
					l(co) = l(cou);
					c(co) = c(cou);
				}
				else {
					l(co) = l(col);
					c(co) = c(col);
				}
			}
			else {
				l(co) = l(coul)+1;
				c(co) = c(coul) + (l(cou)==l(co))*c(cou) + (l(col)==l(co))*c(col);
			}
		}
}

int main(){
	std::string s1, s2;
	std::cin >> s1 >> s2;

	tensor<int32_t> lenght({s1.size()+1, s2.size()+1});
	tensor<int32_t> count({s1.size()+1, s2.size()+1});

	std::vector<int32_t> c(2);
	c[0] = 0;
	for( c[1] = s2.size(); c[1]!= 0; c[1]-- ){
		lenght(c) = 0; 
		count(c) = 1;
	}
	for( ; c[0] != s1.size()+1; c[0]++ ){
		lenght(c) = 0;
		count(c) = 1;
	}
	std::cout << "CONTO" << std::endl;
	countLCS( s1, s2, lenght, count );
	std::cout << "Lenght: \n";
	lenght.print(std::cout);
	std::cout << '\n';
	std::cout << "Count: \n";
	count.print(std::cout);
	std::cout << "\n\nThat is, " << count({s1.size(), s2.size()}) << " LCSs of lenght " << lenght({s1.size(), s2.size()}) << std::endl;

	return 0;
}
