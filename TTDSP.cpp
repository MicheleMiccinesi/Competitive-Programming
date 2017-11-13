/* TTDSP - The Truly Deadly Swimming Pool */
/* Copyright 2017-2187 Michele Miccinesi  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const uint32_t One = 1;

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
public:
	std::vector<uint32_t> dimensions;
	std::vector<uint32_t>::iterator tdimensions;
	std::vector<T> data;
	std::vector<uint32_t> steps;
	tensor(const std::vector<uint32_t>& dim)
	{
		dimensions = std::vector<uint32_t> (dim);
		tdimensions = dimensions.begin()-1;
		steps = std::vector<uint32_t> (dimensions.size()+1);

		steps.back() = 1;
		i = D();
		for(auto &x: reverse(dimensions)) steps[i] = steps[i--]*x;
		data = std::vector<T> (steps.front());
	}
	T& operator() (std::vector<uint32_t>& indices){
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
};


class deadlyPool{
	tensor<int32_t>& reliefMap;
	std::vector<bool> isFlood;
	std::vector<uint32_t> goFront;
	std::vector<uint32_t> goBack;
	int64_t capacity;
	uint32_t i,j;
	unsigned char d;
	struct compareByHeight{
		tensor<int32_t>& reliefMap;
	
		compareByHeight(tensor<int32_t>& map):
		reliefMap(map){}
	
		bool operator() (uint32_t&a, uint32_t&b){
			return reliefMap.data[a]>reliefMap.data[b]; 
		}
	};
	compareByHeight comp; 
	std::priority_queue<uint32_t, std::vector<uint32_t>, compareByHeight> movingBoundary;
	std::vector<uint64_t> tj;
	void fillBoundaryHeap(uint32_t currentD, const uint32_t &zeroD){
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
			for(uint32_t k = 1; k != reliefMap.tdimensions[currentD]-1; k++){
				tj[currentD] += reliefMap.steps[currentD];
				fillBoundaryHeap(currentD+1, zeroD);
			}
	}
public:
	deadlyPool(tensor<int32_t>& map):
	reliefMap(map), isFlood(map.size()), tj(map.D()+1,0), goFront(isFlood.size(),~uint32_t(0)), goBack(isFlood.size(),~uint32_t(0)), comp(map), movingBoundary(comp)
	{
/*	if1 */
		std::fill(isFlood.begin(), isFlood.end(),0);
		capacity = 0;
		/* Assuming each dimension is at least long 2 */
		tj[0]=0;
		for(j=1; j!=reliefMap.D()+1; j++) fillBoundaryHeap(1,j);
		uint32_t source;
		while(!movingBoundary.empty()){
			source = movingBoundary.top();
			movingBoundary.pop();
			flowFrom(source,reliefMap.data[source]);
		}
	}
	void flowFrom(uint32_t source, int32_t& level){
		uint32_t j;
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
						flowFrom(j,level);
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
						flowFrom(j,level);
					}
				}
			}
		}
	}
	uint64_t waterQuantity(){
		return capacity;
	}
};


int main(){
	std::ios_base::sync_with_stdio(false);

	uint64_t d;
	std::cout << "Numero di dimensioni della mappa dei rilievi: ";
	std::cin >> d;
	std::vector<uint32_t> dimensions(d);
	std::cout << "\nDimensioni: ";
	for(auto &x: dimensions) std::cin >> x;
	tensor<int32_t> rilievi(dimensions);
	std::cout << "\nInserire la mappa dei rilievi: ";
	rilievi.readData();

	deadlyPool piscina(rilievi);
	std::cout << piscina.waterQuantity() << std::endl;
	return 0;


}

/* if1 */
/*	if(reliefMap.D()==1){
			goFront = std::vector<bool> (isFlood.size());
			goBack = std::vector<bool> (isFlood.size());
			std::fill(goFront,1);
			std::fill(goBack,1);
		}
		else if(reliefMap.D()<=8){
			goFront = std::vector<uint8_t> (isFlood.size(),~uint8_t(0));
			goBack = std::vector<uint8_t> (isFlood.size(),~uint8_t(0));
		}
		else if(reliefMap.D()<=16){
			goFront = std::vector<uint16_t> (isFlood.size(),~uint16_t(0));
			goBack = std::vector<uint16_t> (isFlood.size(),~uint16_t(0));
		}
		else if(reliefMap.D()<=32){
			goFront = std::vector<uint32_t> (isFlood.size(),~uint32_t(0));
			goBack = std::vector<uint32_t> (isFlood.size(),~uint32_t(0));
		}
		else {
			std::cout << "2^10 exa would be better than one" << std::endl; 
			std::exit(1);
		}*/
