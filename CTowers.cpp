#include <iostream>
#include <array>

int main(){
 std::ios_base::sync_with_stdio(false);

 std::array<int,1001> towers;
 towers.fill(0);

 int n;
 std::cin >> n;

 int temp;
 int max=1;
 for(;n>0;n--){
  std::cin >> temp;
  ++towers[temp];
  if( towers[temp] == 1 )
   ++towers[0];
  else if( towers[temp] > max )
   max = towers[temp];
 }

 std::cout << max << " " << towers[0] << std::endl;
}
