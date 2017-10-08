#include <iostream>
#include <string>

int main(){
 std::ios_base::sync_with_stdio(false);
 unsigned int T,c,temp;
 std::string number;
 std::cin >> T;
 int numeri[11];

 while(T--){
  numeri[10]=10; for(temp=0;temp!=10;temp++)numeri[temp]=0;
  std::cin >> number;

  for(auto& x: number){
   c=x-'0';
   ++numeri[c];
   if(c%2 == 0 && c<numeri[10]) numeri[10]=c;
  }

  temp=10;
  if(numeri[10]==10)
   while(temp--)
    while(numeri[temp]--) std::cout << temp;  
  else {
   --numeri[numeri[10]];  
   while(temp--)
    while(numeri[temp]--) std::cout << temp;
   std::cout << numeri[10];
  }
  std::cout << std::endl;
  number.clear();
 }
 
}
