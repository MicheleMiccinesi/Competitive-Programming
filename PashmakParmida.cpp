#include <iostream>
#include <algorithm>
#include <vector>

class intBIT32{
public:
 intBIT32 (uint32_t n){
  bit = std::vector<int32_t> (n+1,0);
 };

 inline int32_t& sum(uint32_t& ii) { 
  bit[0] = 0; i = ii;
  while(i){
   bit[0] += bit[i];
   i ^= (i&(-i));
  }
  return bit[0];
 };

 inline void cadd(int32_t summand, uint32_t ii){
  while (ii < bit.size()){
   bit[ii] += summand;
   ii += ii&(-ii);
  }
 };

 inline void add(int32_t& summand, uint32_t& ii){
  i = ii;
  while (i < bit.size()){
   bit[i] += summand;
   i += i&(-i);
  }
 };

private:
 std::vector<int32_t> bit; 
 uint32_t i; 
};

struct numRep{
 uint32_t second;
 uint32_t first;
 inline uint32_t& operator[] (const int i) {return i ? second : first;};
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 
 int n;
 std::cin >> n;
 if (n < 3) { std::cout << 0 << std::endl; return 0; }
 std::vector<numRep> numeri(n+1);
 numeri[0][0] = numeri[0][1] = 0;
 for( auto x = numeri.begin()+1; x != numeri.end(); x++ ) std::cin >> (*x)[0];
 
 std::vector<uint32_t> indici1(n+2);
 std::vector<uint32_t> indici2(n+2);
 indici1[0]=indici1[n+1]=indici2[0]=indici2[n+1]=0;
 auto start = indici2.begin();
 auto end = indici2.end()-1;
 for( auto x = start+1; x != end; x++ ) (*x) = x-start;
 start = indici1.begin(), end = indici1.end()-1;
 for( auto x = start+1; x != end; x++ ) (*x) = x-start;

 std::stable_sort( ++start, end, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][0] < numeri[b][0];} );

 for( auto i = start; i != end; i++ ) numeri[*i][1] = (numeri[*i][0] == numeri[*(i-1)][0]) ? numeri[*(i-1)][1]+1 : 1;

 --start; 
 numeri[0][1] = 1;
 for( auto i = end-1; i != start; i-- )
  if( numeri[*i][0] == numeri[*(i-1)][0] ) 
   numeri[*i][0] = numeri[0][1]++;
  else {
   numeri[*i][0] = numeri[0][1];
   numeri[0][1] = 1;
  };

 intBIT32 repR( numeri.size() );

 std::sort( ++start, end, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][0] < numeri[b][0];} );
 std::sort( indici2.begin()+1, indici2.end()-1, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][1] < numeri[b][1];} );

 uint32_t rep = 0;
 uint64_t tot = 0;
 uint32_t one=1;
 int32_t mone=-1;
 int32_t k;
 auto i = indici2.begin()+1, j = indici1.begin()+1;
 while( i != indici2.end()-1  && numeri[*i][1] == rep+1 ) i++;
 ++rep;
 while( i != indici2.end()-1 ){
  for( k = 0; numeri[*j][0] == rep && j != indici1.end()-1; ++k, ++j) repR.add( mone, *j );
  if(k) repR.add( k, one );

  while( numeri[*i][1] == rep+1 && i != indici2.end()-1 )
   tot += repR.sum( *(i++) );  

  ++rep;
 }
  
 std::cout << tot << std::endl;
}
