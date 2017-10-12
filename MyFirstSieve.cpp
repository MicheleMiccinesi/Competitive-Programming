#include <iostream>
#include <vector>

static const int n_max = 200000;

struct sieve{
 sieve(int n){
  int N = 6*(n/6)+7;
  numbers.reserve(N);
  auto zero = numbers.begin();
  prime = zero+5;
  factor = zero+5;
  numbers.emplace_back(false,zero,zero);
  numbers.emplace_back(false,zero,zero);
  numbers.emplace_back(true, zero+2 , zero+3);
  numbers.emplace_back(true, zero+2 , zero+5);
  numbers.emplace_back(false,zero,zero);
  numbers.emplace_back(true, zero+3 , zero+7);
  zero = numbers.end();
  numbers.emplace_back(false,zero,zero);
  while( numbers.size() < N - 5 ){
   numbers.emplace_back(true, zero-1 , zero+5);
   numbers.emplace_back(false,zero,zero);
   numbers.emplace_back(false,zero,zero);
   numbers.emplace_back(false,zero,zero);
   numbers.emplace_back(true, zero+1 , zero+7);
   zero = numbers.end();
   numbers.emplace_back(false,zero,zero);  
  }
  (zero-1)->next = numbers.end();
  zero = numbers.begin();
  totPrimes = N/3 + 1;
  while( prime != numbers.end() ){
   factor = prime;
   while( factor != numbers.end() ) {
    if(( factor - zero ) * ( prime - zero ) < numbers.end()-zero) {
     (zero + (( factor - zero ) * ( prime - zero )))->isPrime = false;
     totPrimes--;
    }
    if( !factor->isPrime ){
     if(factor->next - numbers.end()) {
      factor->next->prev = factor->prev;
      factor->prev->next = factor->next;
     }
     else factor->prev->next = factor->next;
    }
    factor = factor->next;
   }
   prime = prime->next;   
  }
 };
 void printPrimes(){
  int y=0;
  for(auto& h: numbers) {
   if(h.isPrime) std::cout << y << ", ";
   y++;
  }
 };
 void printPrimeVector(){
  for(auto& h: numbers) std::cout << h.isPrime << ", ";
 };
 bool const& operator[] (int i){return numbers[i].isPrime;};
 int totPrimes;
private:
 struct sieve_element{
  sieve_element( bool b, std::vector<sieve_element>::iterator pr, std::vector<sieve_element>::iterator ne ) :
   isPrime{b}, prev{pr}, next{ne} {};
  bool isPrime;
  std::vector<sieve_element>::iterator prev;
  std::vector<sieve_element>::iterator next;
 };
 std::vector<sieve_element> numbers;
 std::vector<sieve_element>::iterator prime;
 std::vector<sieve_element>::iterator factor;
};

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

int& inBlacklist(int &n, std::vector<employee>& ranks, sieve& isPrime){
 static int temp, alfred;
 do{
  std::cin >> temp;
  if( !temp ) alfred = ranks.size();
  ranks.emplace_back( temp );	//
 } while( --n );
 temp = 0;
 do if( alfred - n ) temp += isPrime[ ranks[n].countSeniors( ranks )  + n + 1 ];
  while( ranks.size() - ++n );
 return temp;
}

int main(){
 std::ios_base::sync_with_stdio( false );
 std::vector<employee> ranks;
 ranks.reserve(n_max);
// sieve isPrime(450);
 sieve isPrime(n_max);
// std::cout << isPrime.totPrimes;
// isPrime.printPrimes();
 int T,n;
 std::cin >> T;
 while( T-- ){
  std::cin >> n;
  std::cout << inBlacklist( n, ranks, isPrime ) << std::endl;
  ranks.clear();
 }
}
