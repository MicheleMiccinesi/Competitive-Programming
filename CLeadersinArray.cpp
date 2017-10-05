#include <iostream>

const unsigned int MAX_T = 100;

int main(){
 unsigned int T, n;
 unsigned int arr[MAX_T+2];
 std::cin >> T;
 while( T-- ){
  std::cin >> arr[0];
  for(n=1;n!=arr[0]+1;++n) std::cin >> arr[n];
  arr[arr[0]+1]=arr[0];
  n-=2;
  while(n){
   if(arr[n]>arr[arr[arr[0]+1]]) arr[--arr[arr[0]+1]]=arr[n];
   --n;
  }
  do std::cout << arr[arr[arr[0]+1]] <<' ';
   while(arr[arr[0]+1]++ != arr[0]);
  std::cout << std::endl;
 }
}
