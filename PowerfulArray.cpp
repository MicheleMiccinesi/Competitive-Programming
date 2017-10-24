#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct value{
 int val;
 int index;
};

struct query{
 int l, r;
 int64_t sol;
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 int n,t;
 std::cin >> n >> t;
 std::vector<value> array(n);
 auto tarray = array.begin()-1;
 for( auto &x: array ) std::cin >> x.val;

 std::vector<int> order;
 order.reserve(n);
 for( int i = 0; i < n; order.push_back(i++) );

 std::sort( order.begin(), order.end(), [&array](const int& a, const int& b){ return array[a].val < array[b].val; } );
 int index = 0;
 for( auto i = order.begin(); i != order.end()-1; i++ ){
  array[*i].index = index;
  if( array[*i].val != array[*(i+1)].val ) index++;
 }
 array[order.back()].index = index++;	
 int& numValues = index;

 std::vector<int> valueFreq(numValues,0);

 std::vector<query> queries(t);
 for( auto &y: queries ) std::cin >> y.l >> y.r;

 std::vector<int> qOrder;
 qOrder.reserve(t);
 for( int i = 0; i < t; qOrder.push_back(i++) );
 std::sort( qOrder.begin(), qOrder.end(), [&queries](const int& a, const int& b){ return queries[a].l < queries[b].l; });
 int start = queries[ qOrder.front() ].l;
 int N = 1+queries[ qOrder.back() ].l - start;
 int rN = std::sqrt( N );
 int MoStep = rN;
 int i=0, f=0;
 while( MoStep < N ){
  while( queries[qOrder[f]].l - start < MoStep ) ++f;
  std::stable_sort( qOrder.begin()+i, qOrder.begin()+f, [&queries](const int& a, const int& b){ return queries[a].r < queries[b].r; } );
  MoStep += rN;
  i=f;
 }
 if( f != qOrder.end()-qOrder.begin() ) std::stable_sort( qOrder.begin()+i, qOrder.end(), [&queries](const int& a, const int& b){ return queries[a].r < queries[b].r;} );
 //valueFreq
 int64_t power{0};
 int64_t one = 1, two = 2;
 int l,r;
 l = queries[qOrder.front()].l;
 r = l-1;
 for( auto& x: qOrder ){
  while( queries[x].l < l ){
   --l;
   power += (two*valueFreq[ tarray[l].index ]++ + 1)*tarray[l].val*one;
  }
  while( queries[x].r > r ){
   ++r;
   power += (two*valueFreq[ tarray[r].index ]++ + 1)*tarray[r].val*one;
  } 
  while( queries[x].l > l ){
   power -= (two*valueFreq[ tarray[l].index ]-- - 1)*tarray[l].val*one;
   ++l;
  } 
  while( queries[x].r < r ){
   power -= (two*valueFreq[ tarray[r].index ]-- - 1)*tarray[r].val*one;
   --r;
  }
  queries[x].sol = power; 
 }

 for( auto& x: queries ) std::cout << x.sol << '\n';
 std::cout << std::flush;
}
