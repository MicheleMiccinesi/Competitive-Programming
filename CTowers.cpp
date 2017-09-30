/* Towers */
/* Time cost: O(n), n: number of bars */
/* Space cost: O(N), N: possible heights */
/* With hashing we would save on space, lose on time */
/* With N=1000 the array should stay in L1 or L2 cache */
#include <iostream>
#include <array>

const int N = 1000;

int main(){
 std::ios_base::sync_with_stdio(false);

 std::array<int,N+1> towers;
 towers.fill(0);

 int n;
 std::cin >> n;

 int temp;
 int max=1;
 while( n-- ){
  std::cin >> temp;
  ++towers[temp];
  if( towers[temp] == 1 )
   ++towers[0];
  else if( towers[temp] > max )
   max = towers[temp];
 }

 std::cout << max << " " << towers[0] << std::endl;
}
