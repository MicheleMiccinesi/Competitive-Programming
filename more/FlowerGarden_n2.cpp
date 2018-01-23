/* Flowergarden */
/* Problem Source: topcoder */
/* Solution License: contact Michele Miccinesi */

/* Solution O(n^2) */
/* I have in mind an O(n log n) one using graphs */

#include <vector>
#include <numeric>
#include <algorithm>
#include <list>

typedef std::vector<int> vi;

struct FlowerGarden{
	vi getOrdering(vi, vi, vi);
};

vi FlowerGarden::getOrdering(vi height, vi bloom, vi wilt){
	vi o(height.size());
    std::iota(o.begin(), o.end(), 0);
    std::list<int> s;	decltype(s)::iterator is, ip;
    std::sort(o.begin(), o.end(), [&height](const int& a, const int& b){
    	return height[a]<height[b]; });

    for( auto &oo: o ){
        ip = s.begin();
        for( is = s.begin(); is != s.end(); ){
            if(bloom[oo]<=wilt[*is] && bloom[*is]<=wilt[oo])
                ip = ++is;
            else ++is;
        }
        s.insert( ip, oo );        
    }
    auto io = o.begin();
    for( auto &ss:s )
        *(io++) = height[ss];
    return o;
}
