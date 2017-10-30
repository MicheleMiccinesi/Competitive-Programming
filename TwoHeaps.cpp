#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

struct cube{
 unsigned short number;
 bool group;
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 int n;
 std::cin >> n;
 std::vector<cube> cubes(n*=2);
 std::array<unsigned short, 90> nFreq;
 nFreq.fill(0);
 auto tnFreq = nFreq.begin()-10;
 for( auto& x: cubes ) { std::cin >> x.number; ++tnFreq[x.number]; }
 std::vector<cube *> cubesOrder(n);
 for( int i = 0; i!=n; ++i) cubesOrder[i] = &cubes[i];

 unsigned short N[]{0,0}, l[]{0,0};
 bool group{0};
 std::sort( cubesOrder.begin(), cubesOrder.end(), [&tnFreq](cube *const & a, cube *const & b){
                                                                                              if( tnFreq[a->number] < tnFreq[b->number] ) return true; 
                                                                                              if( tnFreq[a->number] == tnFreq[b->number] ) return a->number < b->number;
                                                                                              return false;
                                                                                             } );
 for(auto &x : cubesOrder){
  if( x->number != l[group] ) {
   l[group] = x->number;
   ++N[group];}
  x->group = group;
  group^=1;
 }

 std::cout << N[0]*N[1] <<'\n';
 for(auto &x: cubes) std::cout << (x.group?2:1) <<' ';
 std::cout << std::endl;

 return 0;
}
