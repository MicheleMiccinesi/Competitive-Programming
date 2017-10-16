#include <iostream>
#include <vector>

const int N_MAX = 100000;

int main(){
 std::ios_base::sync_with_stdio( false );

 char c[2];
 bool i{0};
 std::vector<uint32_t> pfxSum;
 pfxSum.reserve( N_MAX );
 std::cin >> c[i];
 pfxSum.push_back(0);
 std::cin >> c[i^=1];
 do{
  pfxSum.push_back( pfxSum.back() );
  if( c[i] == c[i^1] ) pfxSum.back()++;
  std::cin >> c[i^=1];
 } while( c[i] == '.' || c[i] == '#' );
 std::cin.putback(c[i]);

 int n;
 std::cin >> n;
 int i1, i2;

 while( n-- ){
  std::cin >> i1 >> i2;
  std::cout << pfxSum[i2-1] - pfxSum[i1-1] << std::endl;
 }
}
