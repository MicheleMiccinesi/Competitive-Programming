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
 
 inline void madd(int32_t& summand, uint32_t ii){
  while (ii < bit.size()){
   bit[ii] += summand;
   ii += ii&(-ii);
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
 for( auto x = numeri.end()-1; x != numeri.begin(); x-- ) std::cin >> (*x)[0];
 
 std::vector<uint32_t> indici1(n+2);
 std::vector<uint32_t> indici2(n+2);
 indici1[0]=indici1[n+1]=indici2[0]=indici2[n+1]=0;
 const auto start21 = indici2.begin()+1;  const auto start11 = indici1.begin()+1;
 const auto end21 = indici2.end()-1; const auto end11 = indici1.end()-1;
 const auto start20 = indici2.begin(); const auto start10 = indici1.begin();
 const auto end20 = indici2.end(); const auto end10 = indici1.end();
 for( auto x = start21; x != end21; x++ ) (*x) = x-start20;
 for( auto x = start11; x != end11; x++ ) (*x) = x-start10;

 std::stable_sort( start11, end11, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][0] < numeri[b][0];} );

 for( auto i = end11-1; i != start10; i-- ) numeri[*i][1] = (numeri[*i][0] == numeri[*(i+1)][0]) ? numeri[*(i+1)][1]+1 : 1;

 numeri[0][1] = 1;
 for( auto i = start11; i != end11; i++ )
  if( numeri[*i][0] == numeri[*(i+1)][0] ) 
   numeri[*i][0] = numeri[0][1]++;
  else {
   numeri[*i][0] = numeri[0][1];
   numeri[0][1] = 1;
  };

 intBIT32 repR( numeri.size() );

 std::sort( start11, end11, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][0] < numeri[b][0];} );
 std::sort( start21, end21, [&numeri](uint32_t const& a, uint32_t const& b){return numeri[a][1] < numeri[b][1];} );
 uint32_t maxRep = numeri[*(end11-1)][0];

 if( maxRep == 1 ) { std::cout << 0 << std::endl; return 0; }

// for( auto &x: indici1 ) ++x;
 
 uint32_t rep = 1;
 uint64_t tot = 0;
 int32_t one=1;
 auto i = start21, j = start11;
// auto numit = numeri.begin()-1;
 
 while( numeri[*i][1] == rep ) i++;
 while( rep != maxRep-1 ){
  while( numeri[*j][0] == rep ) repR.madd( one, *(j++)+1 );
  while( numeri[*i][1] == rep+1 ) tot += repR.sum( *(i++) );  
  ++rep;
 }
 while( numeri[*j][0] == rep ) repR.madd( one, *(j++)+1 );
 while( i != end21 ) tot += repR.sum( *(i++) );  
  
 std::cout << tot << std::endl;
}
