#include <vector>
#include <iostream>

/*
namespace FI {
 const int L = 1 << 15 | 1;
 char buf[L], *front, *back;
 void nextChar(char &);
 template <typename T>void nextNumber(T &);
}

void FI::nextChar(char &c) {
 if(front == back) std::cin.readsome(buf, L), back = (front=buf) + std::cin.gcount();
 c = !std::cin.gcount() ? (char)EOF : *front++;
}

template<typename T>void FI::nextNumber(T &x) {
 char c; int f = 1;
 for(nextChar(c); c>'9'||c<'0'; nextChar(c)) if(c == '-') f = -1;
 for(x=0; c>='0'&& c<='9'; nextChar(c)) x = x*10+c-'0';
 x *= f;
}
*/

class intBIT32{
public:

 intBIT32 (uint32_t n){
  bit = std::vector<int32_t> (n+1,0);
  std::fill( bit.begin(), bit.end(), 0 );
 };

 inline int32_t sum(uint32_t i) { 
  bit[0] = 0;
  while(i){
   bit[0] += bit[i];
   i ^= (i&(-i));
  }
  return bit[0];
 };

 int32_t operator() (uint32_t i) {
  uint32_t j = i&(-i);
  bit[0] = bit[i--];
  while( j >>= 1 ){
   bit[0] -= bit[i];
   i ^= (i&(-i));
  }
  return bit[0];
 };

 inline uint32_t& goup(uint32_t& i) { i&=(i-1); return i; };
 uint32_t up(uint32_t const& i) { return i&(i-1); };

 uint32_t& gor(uint32_t& i) { i += i&(-i); return i;};
 uint32_t r(uint32_t const& i) { return i + i&(-i); };

 uint32_t& gol(uint32_t& i) { i ^= ( i&(-i) | ((i&(-i)) >> 1) ); return i; };
 uint32_t l(uint32_t const& i) { return (i&(i-1))^((i&(-i))>>1); };

 inline void cadd(int32_t summand, uint32_t i){
  while (i < bit.size()){
   bit[i] += summand;
   i += i&(-i);
  }
 };
private:
 std::vector<int32_t> bit;  
};

#include <algorithm>

struct segment{
 segment( int32_t &ll, int32_t &rr ): l{ll}, r{rr} {};
 segment( ) {};
 int32_t l, r;
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );

 uint32_t n;
// FI::nextNumber<uint32_t>( n );
 std::cin >> n;
 std::vector<segment> segments(n);
// for( auto &x: segments ) FI::nextNumber<int32_t>(x.l), FI::nextNumber<int32_t>(x.r);
 for( auto &x: segments ) std::cin >> x.l >> x.r;

 std::vector<uint32_t> sortVect( segments.size() );
 while( n-- ) sortVect[n] = n;

 std::sort( sortVect.begin(), sortVect.end(), [&segments](const uint32_t& a, const uint32_t& b) { return segments[a].r < segments[b].r; } );
 for( auto x = sortVect.begin(); x != sortVect.end(); x++ ) segments[*x].r = x - sortVect.begin() + 1;

 std::sort( sortVect.begin(), sortVect.end(), [&segments](const uint32_t& a, const uint32_t& b) { return segments[a].l > segments[b].l; } );

 intBIT32 countInv( segments.size() );
 for( auto &x: sortVect ){
  segments[x].l = countInv.sum( segments[x].r );
  countInv.cadd( 1, segments[x].r );
 }

 for( auto &x: segments ) std::cout << x.l << '\n';
 std::cout << std::flush;
}
