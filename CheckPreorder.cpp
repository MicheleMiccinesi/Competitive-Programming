#include <iostream>
#include <stack>
#include <limits>

bool check_preordered_tree(int & n){
 static std::stack<int> a_sinistra_di;
 static int a_destra_di;
 static int elemento;
 a_destra_di = std::numeric_limits<int>::min();
 while( n-- ){
  std::cin >> elemento;
  if( elemento < a_destra_di ) { 
   while( a_sinistra_di.size() ) a_sinistra_di.pop();
   while( n-- ) std::cin >> elemento; 
   return false;
  }
  while( a_sinistra_di.size() && a_sinistra_di.top() <= elemento && a_sinistra_di.size() ){
   a_destra_di = a_sinistra_di.top();
   a_sinistra_di.pop();
  } 
  a_sinistra_di.push( elemento );
 }
 while(a_sinistra_di.size()) a_sinistra_di.pop();
 return true;
}

int main(){
 int T;
 std::cin >> T;
 int n;
 while( T-- ){
  std::cin >> n;
  std::cout << check_preordered_tree(n) << std::endl;
 }
}
