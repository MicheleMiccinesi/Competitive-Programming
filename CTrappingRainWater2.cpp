/* Trapping Rain Water */
/* Trying to write a version of the algorithm that exploit the latency of reading */
/* More sums but less reading than the first version*/
/* Time cost for single test: O(n) */
/* Space cost: max n (== 100) + 6 */
#include <iostream>
#include <array>

int main(){
 std::ios_base::sync_with_stdio(false);
 
 unsigned int T,n,wq,maxL,maxR,n_max;
 std::array<unsigned int,100> w;
 std::cin >> T;
 while( T-- ){
  wq=0; maxL=0; maxR=0;
  std::cin >> n;
  while( n-- ){
   std::cin >> w[n];
   if( w[n] >= maxL ) maxL = w[ n_max = n ];
   else wq += maxL - w[n];
  }
  while( ++n < n_max ) {
   if ( w[n] >= maxR ) maxR = w[n];
   wq += maxR - maxL;
  } 
  std::cout << wq << std::endl;
 }
}
