#include <iostream>
#include <stack>
#include <array>
#include <algorithm>

const unsigned int N_MAX = 1000;

struct el{
 int v;
 int L;
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 std::array<el, N_MAX> els;
 auto start = els.begin();
 auto end = start;

 std::stack<el *> Ls;

 int T;
 std::cin >> T;
 int n;
 while(T--){
  std::cin >> n;
  end = start + n;
  std::for_each(start, end, [&Ls](el &x){
                                   std::cin >> x.v;
                                   while( !Ls.empty() && x.v > Ls.top()->v ){
                                    Ls.top()->L = x.v;
                                    Ls.pop();
                                   }
                                   Ls.push( &x );
                                  } );
  while( !Ls.empty() ) {
   Ls.top()->L = -1;
   Ls.pop();
  }
  std::for_each(start, end, [](el &x){ std::cout << x.L << ' '; } );
  std::cout << std::endl;
 }
}
