#include <iostream>
#include <vector>

struct trisect{
 trisect(int64_t &ss, int32_t &a, int32_t & b):
 sum{ss}, bisum{ss << 1} {
  sums[0] = a;
  sums[1] = sums[0]+b;
  nfound = (sums[0] == sum) ? 1 : 0;
  nways = (sums[1] == bisum) ? nfound : 0;
  nfound += (sums[1] == sum) ? 1 : 0;
 };
 inline void put(int32_t a){
  sums[i] = sums[i^1] + a;
  if( sums[i] == bisum ) nways += nfound;
  if( sums[i] == sum ) nfound++; 
  i ^= 1;  
 };
 uint64_t const& operator() (){
  return nways;
 };
private:
 bool i{0}; 
 uint64_t nways;
 uint64_t nfound;
 int64_t sums[2];
 int64_t sum;
 int64_t bisum; 
};

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
 int64_t sum{0};

 for(auto &x: numeri) {
  std::cin >> x;
  sum += x;
 }

 if( sum % 3) {
  std::cout << 0 << std::endl;
  return 0;
 }

 trisect trisection(sum /= 3, numeri[0], numeri[1]);
 for(auto x = numeri.begin() + 2; x != numeri.end() - 1; x++) trisection.put( *x ); 

 std::cout << trisection() << std::endl;
}
