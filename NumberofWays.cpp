#include <iostream>
#include <vector>

int main(){
 std::ios_base::sync_with_stdio(false);
 
 std::vector<int32_t> array;
 std::vector<int32_t> postsum;
 int32_t n, el;
 int64_t sum, goodsum;
 uint32_t nfound;
 uint64_t nways;
 std::cin >> n;
 array.reserve(n);
 postsum.reserve(n);
 sum = 0; goodsum = 0; nfound = 0, nways = 0;

 while(n--){
  std::cin >> el;
  array.push_back(el);
  sum += el;
 }
 if( ! (sum % 3) ){
  sum /= 3;
  n = array.size();
  while( n-- ){
   if( (goodsum += array[n]) == sum ) nfound++;
   postsum[n] = nfound;
  }
  goodsum = 0;
  while( ++n - array.size() + 2 )
   if( (goodsum += array[n]) == sum ) nways += postsum[n+2]; 
 }
 std::cout << nways << std::endl;
}
