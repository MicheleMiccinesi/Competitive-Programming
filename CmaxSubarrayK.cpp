#include <iostream>
#include <deque>
#include <string>

struct array_element{
 int position;
 int value;
};


int main(){
 std::ios_base::sync_with_stdio(false);
 
 int T=0,N=0,k=0,i=0,v=0,j=0;
 std::cin >> T;
 std::deque<array_element> sliding_window;

 for(;T>0;T--){
  std::cin >> N >> k;
  for(i=0;i<k;i++){
   std::cin >> v;
   while( !sliding_window.empty()){
    if(sliding_window.back().value <= v) sliding_window.pop_back();
    else break;
   }
   sliding_window.emplace_back( array_element{i,v} );
  }
  std::cout << sliding_window.front().value << " ";
  for(;i<N;i++){
   std::cin >> v;
   while( !sliding_window.empty() ){
    if(sliding_window.back().value <= v) sliding_window.pop_back();
    else break;
   }
   while( !sliding_window.empty() ){
    if(sliding_window.front().position <= i-k) sliding_window.pop_front();
    else break;
   }
   sliding_window.emplace_back( array_element{i,v} );
   std::cout << sliding_window.front().value << " ";
  }
  sliding_window.clear();
  std::cout << std::endl;
 }
}
