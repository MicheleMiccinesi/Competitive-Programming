#include <iostream>
#include <array>

int main(){
 std::ios_base::sync_with_stdio(false);

 int n,temp;
 std::array<int,1000> towers;
 for(n=0;n<1000;n++) towers[n]=0;
 int max=1,n_tower=0;

 std::cin >> n;

 for(;n>0;n--){
  std::cin >> temp;
  ++towers[temp-1];
  if( towers[temp-1] == 1 )
   ++n_tower;
  else if( towers[temp-1] > max )
   max = towers[temp-1];
 }

 std::cout << max << " " << n_tower << std::endl;
}
