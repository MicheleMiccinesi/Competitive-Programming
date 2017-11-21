/* TTDSP - The Truly Deadly Swimming Pool */
/* Copyright 2017-2187 Michele Miccinesi  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <cmath>

template <typename T>
std::vector<T>& rndGen(T& a, T& b, std::vector<T>& elements){
    std::random_device r; 

    std::seed_seq seed1{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e1(seed1);
    std::uniform_int_distribution<T> uniformDist(a, b);
    for( auto&x: elements ) x = uniformDist(e1);

    return elements;
}

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
	tensor(const std::vector<int32_t>& dim)
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
	void readData(){
		for(auto&x: data) std::cin >> x;
	}
	auto& size(){
		return steps.front();
	}
	const auto D(){
		return dimensions.size();
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


class deadlyPool{
	tensor<int32_t>& reliefMap;
	std::vector<bool> isFlood;
	std::vector<int32_t> goFront;
	std::vector<int32_t> goBack;
	int64_t capacity;
	int32_t i,j,jj;
	unsigned char d;

	struct compareByHeight{
		tensor<int32_t>& reliefMap;
	
		compareByHeight(tensor<int32_t>& map):
		reliefMap(map){}
	
		bool operator() (int32_t&a, int32_t&b){
			return reliefMap.data[a]>reliefMap.data[b]; 
		}
	};
	compareByHeight comp; 
	struct priority_queue_with_reserve : std::priority_queue<int32_t, std::vector<int32_t>, compareByHeight> {
		priority_queue_with_reserve(compareByHeight& comp, int32_t size) : priority_queue(comp) {
			this->c.reserve(size);
		}
	};

	priority_queue_with_reserve movingBoundary;
	std::queue<int32_t> flooding;

	std::vector<uint64_t> tj;
	void fillBoundaryHeap(int32_t currentD, const int32_t &zeroD){
		tj[currentD]=tj[currentD-1];
		if(currentD == zeroD){
			auto end = reliefMap.steps[currentD]+tj[currentD];
			for(; tj[currentD]!=end; tj[currentD]++){
				goBack[tj[currentD]] = 0;
				goFront[tj[currentD]] = (1<<(currentD-1));
				isFlood[tj[currentD]] = 1;
				movingBoundary.push(tj[currentD]);
			}
			end = tj[currentD-1] + reliefMap.steps[currentD-1];
			for(tj[currentD] = end-reliefMap.steps[currentD]; tj[currentD] != end; tj[currentD]++){
				goBack[tj[currentD]] = (1<<(currentD-1));
				goFront[tj[currentD]]=0;
				isFlood[tj[currentD]]=1;
				movingBoundary.push(tj[currentD]);
			}
		}
		else
			for(int32_t k = 1; k != reliefMap.tdimensions[currentD]-1; k++){
				tj[currentD] += reliefMap.steps[currentD];
				fillBoundaryHeap(currentD+1, zeroD);
			}
	}
public:
	deadlyPool(tensor<int32_t>& map):
	reliefMap(map), isFlood(map.size()), tj(map.D()+1), goFront(isFlood.size()), goBack(isFlood.size()), comp(map), movingBoundary(comp, reliefMap.size()), flooding()
	{
		tj[0]=0;
	}

	void letWaterFlow(bool& fast){
		std::fill(isFlood.begin(), isFlood.end(),0);
		std::fill(tj.begin(), tj.end(), 0);
		std::fill(goFront.begin(), goFront.end(), ~int32_t(0));
		std::fill(goBack.begin(), goBack.end(), ~int32_t(0));
		capacity = 0;
		/* Assuming each dimension is at least long 2 */

		for(j=1; j!=reliefMap.D()+1; j++) fillBoundaryHeap(1,j);
		int32_t source, level;
		if(fast)
			while(!movingBoundary.empty()){
				flooding.push( movingBoundary.top() );
				movingBoundary.pop();
				level = reliefMap.data[flooding.front()];
				while( !flooding.empty() ){
					source = flooding.front();
					flooding.pop();
					for(unsigned char d=0; d!= reliefMap.D(); d++){
						if( goFront[source] & (One<<d) ){
							j=source+reliefMap.steps[d+1];
							goBack[j] &= ~(One<<d);
							if(!isFlood[j]){
									isFlood[j]=1;
								if(level<reliefMap.data[j])
									movingBoundary.push(j);
								else {
									capacity += level-reliefMap.data[j];
									flooding.push(j);
								}
							}
						}
						if( goBack[source] & (One<<d) ){
							j=source-reliefMap.steps[d+1];
							goFront[j] &= ~(One<<d);
							if(!isFlood[j]){
								isFlood[j]=1;
								if(level<reliefMap.data[j])
									movingBoundary.push(j);
								else{
									capacity += level-reliefMap.data[j];
									flooding.push(j);
								}
							}
						}
					}
				} 
			}
		else 
			while(!movingBoundary.empty()){
				flooding.push( movingBoundary.top() );
				movingBoundary.pop();
				level = reliefMap.data[flooding.front()];
				while( !flooding.empty() ){
					source = flooding.front();
					flooding.pop();
					waterLevel[source] += level;
					waterQuantity[source] += level-reliefMap.data[source];
					for(unsigned char d=0; d!= reliefMap.D(); d++){
						if( goFront[source] & (One<<d) ){
							j=source+reliefMap.steps[d+1];
							goBack[j] &= ~(One<<d);
							if(!isFlood[j]){
									isFlood[j]=1;
								if(level<reliefMap.data[j])
									movingBoundary.push(j);
								else {
									capacity += level-reliefMap.data[j];
									flooding.push(j);
								}
							}
						}
						if( goBack[source] & (One<<d) ){
							j=source-reliefMap.steps[d+1];
							goFront[j] &= ~(One<<d);
							if(!isFlood[j]){
								isFlood[j]=1;
								if(level<reliefMap.data[j])
									movingBoundary.push(j);
								else{
									capacity += level-reliefMap.data[j];
									flooding.push(j);
								}
							}
						}
					}
				} 
			}
	}

	uint64_t water(){
		return capacity;
	}
/* Task 2: statistical properties of capacity and water level */
	template <typename E>
	void probabilityDist(int32_t repetitions, E& min, E& max){
		std::cout << repetitions << " repetitions" << std::endl;
		waterLevel = std::vector<int64_t> (reliefMap.data.size(),0);
		waterQuantity = std::vector<uint64_t> (reliefMap.data.size(),0);
		cumCapacity = 0;
		while(repetitions--){
			rndGen(min, max, reliefMap.data);
			letWaterFlow(fastCalc=false);
			cumCapacity += capacity;
//			reliefMap.print(std::cout);
//			std::cout << '\n';
		}
		std::cout<< "\n\nCumulative Water Level: " << std::endl;
		print(waterLevel, std::cout);
		std::cout<< "\n\nCumulative Water Quantity: " << std::endl;
		print(waterQuantity, std::cout);
		std::cout << "\n\nCumulative Capacity: " << cumCapacity << std::endl;
	}

	template <typename X>
	void print(std::vector<X>& toPrint, std::ostream& out){
		reliefMap.print(toPrint, out);
	}
	std::vector<int64_t> waterLevel;
	std::vector<uint64_t> waterQuantity;
	uint64_t cumCapacity;
	bool fastCalc{true};
};

int main(){
	std::ios_base::sync_with_stdio(false);

	uint64_t d;
	std::cout << "Numero di dimensioni della mappa dei rilievi: ";
	std::cin >> d;
	std::vector<int32_t> dimensions(d);
	std::cout << "\nDimensioni: ";
	for(auto &x: dimensions) std::cin >> x;
	tensor<int32_t> rilievi(dimensions);

	deadlyPool piscina(rilievi);
	std::cout << "Inserire minimo e massimo: ";
	int32_t min, max;
	std::cin >> min >> max;
	std::cout << "Inserire il numero di ripetizioni della simulazione casuale: ";
	int32_t ripetizioni;
	std::cin >> ripetizioni;
	if(ripetizioni < 0) ripetizioni = -ripetizioni;
	if(min>max) piscina.probabilityDist(ripetizioni,max,min);
	else piscina.probabilityDist(ripetizioni, min, max);
	return 0;
}
