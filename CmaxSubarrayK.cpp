#include <iostream>
#include <deque>
#include <string>
#include <sstream>

struct array_element{
 int position;
 int value;
};


int main(){
 std::stringstream results;
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
  results << sliding_window.front().value << " ";
  for(;i<N;i++){
   std::cin >> v;
   while( !sliding_window.empty() ){
    if(sliding_window.back().value <= v) sliding_window.pop_back();
    else break;
   }
   sliding_window.emplace_back( array_element{i,v} );
   for(j=0;j<sliding_window.size();j++) {
    if(sliding_window.at(j).position == i-k) { 
     sliding_window.erase(sliding_window.begin()+j);
     break;
    }
   }
   results << sliding_window.front().value << " ";
  }
  sliding_window.clear();
  results << std::endl;
 }
 std::cout << results.str();
 return 1;
}
