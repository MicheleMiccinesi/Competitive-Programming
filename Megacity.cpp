#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct city{
 int32_t x, y;
 unsigned int population;
 uint32_t r2;
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 int n;
 std::cin >> n;
 std::vector<city> cities(n);
 std::vector<city *> citiesOrder(n);
 for( int i = 0; i!=n; ++i) citiesOrder[i] = &cities[i];

 int32_t s;
 std::cin >> s;

 for(auto &x: cities){
  std::cin >> x.x >> x.y >> x.population;
  x.r2 = x.x*x.x + x.y*x.y;
 }

 std::sort( citiesOrder.begin(), citiesOrder.end(), [](city *& a, city *& b){ return a->r2 < b->r2; } );
 for(auto &x : citiesOrder) if( (s += x->population) >= 1000000 ) { std::cout << std::fixed << std::setprecision(6) << std::sqrt(x->r2) <<std::endl; return(0); }
 std::cout << "-1" << std::endl;
 return 0;
}
