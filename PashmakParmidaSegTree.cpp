/* Pashmak and Parmida */
/* Problem Source: codeforces 459D */
/* Solution License: contact Michele Miccinesi */
/* again... */
/* with segment tree */

#include <iostream>
#include <vector>
#include <numeric>	//iota
#include <algorithm>	//stable_sort

typedef uint32_t u32;
typedef uint64_t u64;

struct seg{
	u32 size;
	std::vector<u32> c;
	seg(u32& n): size(n), c(n<<1,0){}
	void inc(u32 i){
		i+=size;
		do
			++c[i];
		while(i>>=1);
	}
	u32 post(u32 i){
		u32 j=(size<<1)-1;
		i+=size;
		u32 sum{0};
		do{
			if(i&1){
				sum+=c[i];
				++i;
			}
			if(!(j&1)){
				sum+=c[j];
				--j;
			}
		} while((i>>=1)<=(j>>=1));

		return sum;
	}
};

struct occurrence{
	u32 l,r;
};

inline std::vector<occurrence> fill_occurrences(const std::vector<u32>& v, u32& max){
	max=0;							//max occurrences of a number
	u32 n=v.size();
	std::vector<u32> o(n);				      //to sort v at distance
	std::iota(o.begin(), o.end(), 0);

	std::stable_sort(o.begin(), o.end(), 
		[&v](const u32& i, const u32& j){
			return v[i]<v[j];
		}
	);

	std::vector<occurrence> O(n);
	u32 i,j{0};					
	O[o[0]].l=1;
	for( i=1; i!=n; ++i ){
		if(v[o[i]]==v[o[i-1]]){
			if((O[o[i]].l=O[o[i-1]].l+1)>max)
				max=O[o[i]].l;
		}
		else{
			O[o[i]].l=1;
			O[o[j]].r=O[o[i-1]].l;
			while(++j!=i)
				O[o[j]].r=O[o[j-1]].r-1;
		}
	}
	O[o[j]].r=O[o[i-1]].l;
	while(++j!=i)
		O[o[j]].r=O[o[j-1]].r-1;

	return O;
}

inline u64 count_pairs(auto& O, u32 max){
	u32 n=O.size();
	seg POL(max+=2);	  //left partial occurrences: seg::post(i) is returning the postfix sum 
                          //                     		of scanned occurrences not lesser than i
	u64 np{0};		 //number of pairs with the required property
	for( u32 i=1; i!=n; ++i ){
		POL.inc(O[i-1].l);
		np+=POL.post(O[i].r+1);
	}

	return np;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	u32 n;
	std::cin >> n;
	std::vector<u32> v(n);
	for( auto &vv: v ) 
		std::cin >> vv;

	u32 max;
	auto O(fill_occurrences(v, max));

	std::cout << count_pairs(O, max) << std::endl;

	return 0;
}
