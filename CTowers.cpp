#include <iostream>
#include <array>
#include <algorithm>

int main(){
 int n,temp;
 std::array<int,1000> towers;
 for(n=0;n<1000;n++) towers[n]=0;

 std::cin >> n;
 for(;n>0;n--){
  std::cin>>temp;
  ++towers[temp-1];
 }
 std::sort(towers.begin(),towers.end(),[](int& a,int& b){return b<a;});
 n=0; //check
 int n_tower=0;
 std::cout << towers[0];
 while(towers[n++]) n_tower++;
 std::cout << " " << n_tower << std::endl;
}
