#include <iostream>
#include <sstream>
#include <string>

int main(){
 int T,n,sum,max,v;
 std::cin >> T;
 std::stringstream results;
 for(;T>0;T--){
  max=sum=0;
  std::cin >> n;
  std::cin >> v;
  sum = max = v;
  n--;
  if(sum<0) sum=0;
  for(;n>0;n--){
   std::cin >> v;
   sum += v;
   if( sum<0 ) sum=0;
   else if( sum>max ) max=sum;
  }
  results << max << std::endl;
 }
 std::cout << results.str();
}
