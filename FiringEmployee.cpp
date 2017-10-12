#include <iostream>
#include <vector>
#include <cmath>

const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449 };

static const int n_max = 200000;
struct employee{
 int fSenior;	//first senior
 employee( int& n ){
  if( fSenior = n ) {
   nSenior = 1;
   filled = false;
  }
  else {
   nSenior = 0;
   filled = true;
  }
 };
 int const& countSeniors( std::vector<employee>& ranks ){
  if( !filled ) {
   filled = true;
   nSenior = 1 + ranks[fSenior-1].countSeniors( ranks );
  }
  return nSenior;
 };
private:
 int nSenior;
 bool filled;
};

const bool isPrime( int n ){
 int i = 0;
 int sqn = sqrt( n );
 while( primes[i] <= sqn ) {
  if( n%primes[i]==0 ) return false;
  else ++i;
 }
 return true;
}

int& inBlacklist(int &n, std::vector<employee>& ranks){
 static int temp, alfred;
 do{
  std::cin >> temp;
  if( !temp ) alfred = ranks.size();
  ranks.emplace_back( temp );	//
 } while( --n );
 temp = 0;
 do if( alfred - n ) temp += isPrime( ranks[n].countSeniors( ranks )  + n + 1 );
  while( ranks.size() - ++n );
 return temp;
}

int main(){
 std::ios_base::sync_with_stdio( false );
 std::vector<employee> ranks;
 ranks.reserve(n_max);
 int T,n;
 std::cin >> T;
 while( T-- ){
  std::cin >> n;
  std::cout << inBlacklist( n, ranks ) << std::endl;
  ranks.clear();
 }
}
