/* Find Pair */
/* lexycographic order reduces to divide and modulo operations... */
/* time cost: O(nlogn) */
/* space cost: O(n) */
/* would it be faster on an array of N_MAX=10000 elements  */
/* considering that we don't need to initialize its elements? */
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
 std::ios_base::sync_with_stdio(false);
 
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
