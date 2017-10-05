#include <iostream>

const unsigned int MAX_T = 100;

int main(){
 std::ios_base::sync_with_stdio(false);

 unsigned int T, n;
/* arr[0] is the lenght of the given array; while reading from r to l, leaders are recorded
   from r to l starting from the last element of the array. In arr[arr[0]+1] the index of 
   the leftmost leader still to be printed */
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
