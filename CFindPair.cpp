/* Find Pair */
/* lexycographic order reduces to divide and modulo operations... */
/* time cost: O(nlogn) */
/* space cost: O(n) */
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
 std::vector<int64_t> numeri;
 int64_t k,n,q,r,temp;
 std::cin >> n >> k;
 --k;
 numeri.reserve(n);
 for(auto i=0;i<n;i++){
  std::cin >> temp;
  numeri.push_back(temp);
 }
 std::sort(numeri.begin(),numeri.end());
 q=k/n;
 r=k%n;
 std::cout << numeri[q] << " " << numeri[r] << std::endl;
}
