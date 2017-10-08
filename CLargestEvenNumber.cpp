#include <iostream>

int main(){
 std::ios_base::sync_with_stdio(false);
 unsigned int T,c,temp;
 char d;
 std::cin >> T;
 int numeri[11];
 while(T--){
  numeri[10]=10; for(temp=0;temp!=10;temp++)numeri[temp]=0;
  do std::cin.get(d); while(d<48 || d>57);
  while(d>47 && d<58){
   c=d-48;
   ++numeri[c];
   if(c%2 == 0 && c<numeri[10])numeri[10]=c;
   std::cin.get(d);
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
 }
}
