#include <iostream>
#include <string>
#include <sstream>
#include <vector>

unsigned int water_quantity(std::vector<unsigned int>& w){
 if( w.size() < 3 )return 0;
 unsigned int maxR=0,maxL=0;
 unsigned int l=0,r=w.size()-1;	
 unsigned int wq=0;		
 while( r >= l ){
  if( maxL <= maxR ){
   if( w[l] > maxL ) maxL = w[l];
   else wq += maxL - w[l];
   l++;
  }
  else {
   if( w[r] > maxR ) maxR = w[r];
   else wq += maxR - w[r];
   r--;
  }
 }
 return wq;
}

int main(){
 int T,n;
 unsigned int l;
 std::vector<unsigned int> w;
 w.reserve(100);
 std::stringstream results;
 std::cin >> T;
 for(;T>0;T--){
  std::cin >> n;
  for(;n>>0;n--){
   std::cin >> l;
   w.push_back(l);
  }
  results << water_quantity(w) << std::endl;
  w.clear();
 }
 std::cout << results.str();
}
