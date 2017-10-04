#include <iostream>
#include <array>

unsigned int& water_quantity(std::array<unsigned int,101>& w){
 static unsigned int wq;
 wq=0;
 if( w[0] < 3 )return wq;

 static unsigned int maxR,maxL;
 maxR=0; maxL=0;
 static unsigned int l,r;	
 l=1;r=w[0];

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
 std::ios_base::sync_with_stdio(false);
 
 unsigned int T,n;
 std::array<unsigned int,101> w;
 std::cin >> T;
 while(T--){
  std::cin >> n;
  w[0]=n;
  do std::cin >> w[n];
   while(--n);
  std::cout << water_quantity(w) << std::endl;
 }
}
