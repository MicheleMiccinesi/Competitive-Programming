#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

struct cube{
 unsigned short number;
 cube *pre,*suc{nullptr};
 bool group;
};

struct freq{
 unsigned short n{0};
 cube *l;
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
  if( !tFreq[x.number].n++ ) {
   nOneReps++;
   tFreq[x.number].l = &x; }
  else {
   if( tFreq[x.number].n == 2 ) nTwoReps++; 
   x.pre = tFreq[x.number].l;
   x.pre->suc = tFreq[x.number].l = &x; }
 }

 unsigned int tot = nOneReps+nTwoReps;
 bool oddReps = tot%2;
 tot = (tot>>1)*(tot-(tot>>1));
 bool oneReps{0};

 for(auto x = cubes.end(); x!= cubes.begin();){
  x--;
  if( tFreq[x->number].n == 1 ) x->group = oneReps^=1;
  else if( !x->suc ) x->group = ( tFreq[x->number].n%2 ? oddReps^=1 : 0 );
  else x->group = x->suc->group^1;
 }

 std::cout << tot <<'\n';
 for(auto &x: cubes) std::cout << (x.group?2:1) <<' ';
 std::cout << std::endl;

 return 0;
}
