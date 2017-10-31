#include <iostream>
#include <vector>
#include <array>

struct cube{
 unsigned short number;
 bool group;
};

struct freq{
 unsigned short n{0};
 bool l;
 bool v{false};
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 int n;
 unsigned short nOneReps{0}, nTwoReps{0};
 std::cin >> n;
 std::vector<cube> cubes(n*=2);
 std::array<freq, 90> Freq;
 auto tFreq = Freq.begin()-10;

 for( auto& x: cubes ) { 
  std::cin >> x.number;
  if( !tFreq[x.number].n ) nOneReps++;
  else if( tFreq[x.number].n == 1 ) nTwoReps++; 
  tFreq[x.number].n++;
 }

 unsigned int tot = nOneReps+nTwoReps;
 bool oddReps = tot%2;
 tot = (tot>>1)*(tot-(tot>>1));
 bool oneReps{0};

 for(auto &x: cubes){
  if( tFreq[x.number].n == 1 ) x.group = oneReps^=1;
  else if( !tFreq[x.number].v ) { tFreq[x.number].l = x.group = ( tFreq[x.number].n%2 ? oddReps^=1 : 0 ); tFreq[x.number].v = true; }
  else x.group = tFreq[x.number].l^=1;
 }

 std::cout << tot <<'\n';
 for(auto &x: cubes) std::cout << (x.group?2:1) <<' ';
 std::cout << std::endl;

 return 0;
}
