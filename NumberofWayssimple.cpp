#include <iostream>
#include <vector>

int main(){
 std::ios_base::sync_with_stdio(false);
 
 int32_t n;
 std::cin >> n;

 if( n<3 ) {
  std::cout << 0 << std::endl;
  return 0;
 }

 std::vector<int32_t> numeri;
 numeri.resize(n);
 int64_t sum{0}

 for(auto &x: numeri) {
  std::cin >> x;
  sum += x;
 }

 if( sum % 3) {
  std::cout << 0 << std::endl;
  return 0;
 }

 int64_t bisum, partsum{0};
 uint64_t nways{0}, nfound{0};
 sum /= 3;
 bisum = sum << 1;
 
 for(auto x = numeri.begin(); x != numeri.end() - 1; x++) {
  partsum += *x;
  if( partsum == bisum ) nways += nfound;
  if( partsum == sum ) nfound++; 
 }

 std::cout << nways << std::endl;
}
