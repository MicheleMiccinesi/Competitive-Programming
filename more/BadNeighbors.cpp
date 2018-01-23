/* Bad Neighbors */
/* Problem Source: codeforces */
/* Solution License: contact Michele Miccinesi */

#include <vector>
struct BadNeighbors{
    int maxDonations(std::vector<int>);
};

int BadNeighbors::maxDonations(std::vector<int> donations){
    const auto n = donations.size();
    if( n==1 ) return donations[0];
    
    std::vector<int> d0(n);
    std::vector<int> d1(n);
    d0[0]=donations[0];d0[1]=std::max(donations[0], donations[1]);
    d1[1]=donations[1];d1[0]=0;
    for( auto i = 2; i!=n; i++ ){
        d1[i] = std::max( d1[i-1], d1[i-2]+donations[i] );
        d0[i] = std::max( d0[i-1], d0[i-2]+donations[i] );
    }
	return std::max( d0[n-2], d1[n-1] );   
}
