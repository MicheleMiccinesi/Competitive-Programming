#include <iostream>

int main(){
 std::ios_base::sync_with_stdio(false);

 int T, n, missing,input;
 std::cin >> T;
 while(T--){
  std::cin >> n;
  switch(n%4){
   case (0):
    missing=n;
    break;
   case (1): 
    missing=1;
    break;
   case (2): 
    missing=n+1;
    break;
   case (3):
    missing=0;
    break;
  }
  while(--n){
   std::cin >> input;
   missing ^= input;
  }
  std::cout << missing << std::endl;
 }
}
