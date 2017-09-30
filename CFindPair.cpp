/* Find Pair */
/* Time cost: O(n log n) */
/* Space cost: N, that is maximum input provided. Could be n using a vector */
/* Considering that 800KB are not so small, I'll compare array VS vector */
#include <iostream>
#include <array>
#include <algorithm>

const int N = 100000;

int main(){
 std::ios_base::sync_with_stdio(false);
 
 std::array<int64_t, N+1> numeri;
 int64_t k,n,q,temp;
 std::cin >> numeri[N] >> k;
 --k;
 n = numeri[N];
 while(n--) std::cin >> numeri[n];
 std::sort(numeri.begin(),numeri.begin()+numeri[N]);
 q=k/numeri[N];
 int64_t n_q,L=q,R=q;
 if( numeri[q]-numeri[0] ) while( numeri[--L]==numeri[q] );
 else L = -1;
 if( numeri[q]-numeri[numeri[N]-1] ) while( numeri[++R]==numeri[q] );
 else R = numeri[N];
 ++L;

 std::cout << numeri[q] << " " << numeri[(k-numeri[N]*L)/(R-L)] << std::endl;
}
