#include <iostream>
#include <vector>
#include <string>

int main(){
 std::ios_base::sync_with_stdio( false );

 std::string stringa;
 std::getline(std::cin, stringa);
 std::vector<uint32_t> pfxSum( stringa.end()-stringa.begin() );
 pfxSum[0] =0;
 for(auto x = stringa.begin(); x != stringa.end()-1; pfxSum[x-stringa.begin()+1] = pfxSum[x-stringa.begin()] + ( *x == *(x+1) ), ++x);

 int n;
 std::cin >> n;
 int i1, i2;
 while( n-- ){
  std::cin >> i1 >> i2;
  std::cout << pfxSum[i2-1] - pfxSum[i1-1] << std::endl;
 }

}
