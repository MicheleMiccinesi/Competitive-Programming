#include <iostream>
#include <vector>

const int N_MAX = 10000;
int main(){
 std::ios_base::sync_with_stdio( false );

 int T;
 std::cin >> T;
 std::vector<int32_t> array;
 array.reserve(N_MAX+1);
 int n,u,q,l,r,val;

 while( T-- ){
  std::cin >> n;
  array.resize(n+1);
  std::fill(array.begin(), array.end(), 0);
  
  std::cin >> u;
  while(u--){
   std::cin >> l >> r >> val;
   array[l] += val;
   array[r+1] -= val;
  }
  
  for( auto j = array.begin() + 1; j != array.end() - 1; j++) *j += *(j-1);
  
  std::cin >> q;
  while( q-- ){
   std::cin >> val;
   std::cout << array[val] << std::endl;
  }
 }
}
