#include <iostream>
#include <vector>

int main(){
 std::ios_base::sync_with_stdio( false );

 int n, i{0};
 std::cin >> n;
 if( n == 1 ) { std::cout << "1 0" << std::endl; return 0; }
 if( n == 2 ) { std::cout << "1 1" << std::endl; return 0; }
 std::vector<int> t_bars(n);
 auto x = t_bars.begin();
 std::cin >> *(x);
 while( ++x != t_bars.end() ){
  std::cin >> *x;
  *x += *(x-1);
 }

 x = t_bars.begin();
 auto semisum = t_bars.back() / 2;
 do ++i;
  while( *++x <= semisum );
 if ( *(x-1) <= t_bars.back() - *x ) ++i;

 std::cout << i << ' '<< t_bars.size() - i << std::endl;
 
}
