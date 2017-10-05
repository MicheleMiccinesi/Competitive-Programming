#include <iostream>
#include <list>
#include <vector>
#include <iterator>

struct t_couple {
 t_couple(unsigned int ind1, unsigned int ind2, unsigned int stg) 
 : strenght {stg}
 {
  if(ind1<ind2) {inds[0]=ind1;inds[1]=ind2;}
  else {inds[0]=ind2; inds[1]=ind1;};
 };
 friend bool const operator<(const t_couple& l,const t_couple& r){
  return l.strenght < r.strenght;
 };
 friend bool const operator>(const t_couple& l,const t_couple& r){
  return l.strenght > r.strenght;
 };
 friend bool const operator==(const t_couple& l,const t_couple& r){
  return l.inds[0]==r.inds[0] || l.inds[1]==r.inds[1] || l.inds[0]==r.inds[1] || l.inds[1]==r.inds[0]; 
 };
 unsigned int const& operator[] (const unsigned int& i){
  return inds[i%2];
 }; 
 ~t_couple(){};
private:
 unsigned int inds[2];
 unsigned int strenght;
};

std::vector<unsigned int>& find_couples(std::list<t_couple>& lista, std::vector<unsigned int>& result){
 while(!lista.empty()){
  result[lista.back()[0]-1]=lista.back()[1];
  result[lista.back()[1]-1]=lista.back()[0];
  lista.remove(lista.back());
 }
 return result;
}

std::list<t_couple>& read_strenght(unsigned int& n, std::list<t_couple>& lista){
 unsigned int temp;
 for(unsigned int i=1;i!=n+1;++i)
  for(unsigned int j=1;j!=i;++j){
   std::cin >> temp;
   lista.emplace_back(i,j,temp);
  };
 lista.sort();
 return lista; 
}

int main(){
 std::ios_base::sync_with_stdio(false);

 unsigned int n;
 std::cin >> n;
 n*=2;
 std::vector<unsigned int> result;
 result.reserve(n);
 std::list<t_couple> strenght;
 read_strenght(n,strenght);
 find_couples(strenght,result);
 for(unsigned int i=0;i!=n;++i) std::cout << result[i] << " ";
 std::cout << std::endl;
}
