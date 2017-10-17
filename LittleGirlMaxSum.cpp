#include <iostream>
#include <vector>
#include <algorithm>

int main(){
 std::ios_base::sync_with_stdio( false );

 int32_t n;
 std::cin >> n;
 int32_t q;
 std::cin >> q;

 std::vector<uint32_t> numeri(n+2);
 for( auto i = numeri.begin() + 1; i != numeri.end() - 1; ++i ) std::cin >> *i;

 std::vector<int32_t> queries(n+2,0);
 uint32_t query;
 while( q-- ){
  std::cin >> query;
  ++queries[query];
  std::cin >> query;
  --queries[query+1];
 }

 for( auto x = queries.begin()+2; x != queries.end()-1; x++) *x += *(x-1);

 std::sort(queries.begin()+1, queries.end()-1);
 std::sort(numeri.begin()+1, numeri.end()-1);
 uint64_t maxSum{0};
 uint64_t lll{1};
 do maxSum += lll*numeri[n]*queries[n]*lll;
  while(--n && queries[n]);
 
 std::cout << maxSum << std::endl;
}
