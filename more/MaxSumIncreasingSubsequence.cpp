/* Max Sum Increasing Subsequence */
/* Problem Source: me */
/* Solution License: contact Michele Miccinesi */

/* This is a solution using Binary Search Tree (in particular map)
   Proof: consider a given vector v[]; say i, j are index; I create
   a map with the indices as key, the max sum of possible increasing 
   subsequences ending with the value associated to i (v[i]) as the 
   value of each element in the map. For each possible value we maintain
   only the key i with minimum corresponding value v[i]; and this is done
   implicitly by inserting the new pair <i, sum> only if the next element
   would have greater sum. Time Cost: O(log n)  */
   
#include <iostream>
#include <vector>
#include <map>

namespace IS{

long long maxSum(std::vector<int>& v){
	if(v.empty())
		return 0;

	long long sum;
	auto cmp = [&v](const int& a, const int& b)->bool{
		return v[a]<v[b];
	};
	std::map<int,long long, decltype(cmp)> is(cmp);

	is[0]=(long long)v[0];
	for( int i=0; i!=v.size(); ++i ){
		if(v[i]<=0)
			continue;

		auto j = is.lower_bound(i);
		if(j==is.end()){
			is[i] = (--j)->second+v[i];
		}
		else if(j==is.begin()){
			if(v[j->first]!=v[i])
				is[i]=v[i];
		}
		else{
			auto k=j;
			--k;
			if(v[j->first]!=v[i]){
				if((is[i]=k->second+v[i])>=j->second)
					is.erase(j);
			} else{
				if(k->second+v[i]>=j->second){
					is.erase(j);
					is[i]=k->second+v[i];
				}
			}
		}
	}
	#ifndef NDEBUG
	for( auto &ii: is ) std::cout << ii.first << ':' << ii.second << ' ';
	std::cout << std::endl;
	#endif
	return (is.rbegin())->second; 
}

}

#ifndef NDEBUG
int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for( auto &vv: v ) 
		std::cin >> vv;

	std::cout << IS::maxSum(v) << std::endl;

	return 0;
}
#endif
   
