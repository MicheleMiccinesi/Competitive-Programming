#include <iostream>
#include <vector>
#include <array>

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
 std::vector<unsigned short> cubes(n*=2);
 std::array<freq, 90> Freq;
 auto tFreq = Freq.begin()-10;

 for( auto& x: cubes ) { 
  std::cin >> x;
  if( !tFreq[x].n ) nOneReps++;
  else if( tFreq[x].n == 1 ) nTwoReps++; 
  tFreq[x].n++;
 }

 unsigned int tot = nOneReps+nTwoReps;
 bool oddReps = tot%2;
 tot = (tot>>1)*(tot-(tot>>1));
 std::cout << tot <<'\n';

 bool oneReps{0};
 for(auto &x: cubes){
  if( tFreq[x].n == 1 ) std::cout << ((oneReps^=1) ? 2 : 1) << ' ';
  else if( !tFreq[x].v ) { tFreq[x].l =( tFreq[x].n%2 ? oddReps^=1 : 0 ); tFreq[x].v = true; std::cout << (tFreq[x].l ? 2 : 1) <<' '; }
  else std::cout << ((tFreq[x].l^=1) ? 2 : 1)<<' ' ;
 }
 std::cout << std::endl;

 return 0;
}
