#include <iostream>

int main(){
 std::ios_base::sync_with_stdio(false);
 int T,n,sum,max,v;
 std::cin >> T;
 while(T--){
  std::cin >> n;
  std::cin >> max;
  sum = (max<0?0:max);
  while(--n){
   std::cin >> v;
   sum += v;
   if( sum<0 ) sum=0;
   else if( sum>max ) max=sum;
  }
  std::cout << max << std::endl;
 }
}
