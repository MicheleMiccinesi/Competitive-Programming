/* Finding Team Member */
/* Before writing down this solution, which is essentially an experimentation in C++, */
/* I was lingering with another one in which I defined a structure in which each row */
/* has an order given by strenght of the couple, while on columns I was keeping the order */
/* given by index... trying to use array, since n_max is only 400...  */

#include <iostream>
#include <list>
#include <vector>
#include <iterator>

struct t_couple {
 t_couple(unsigned int ind1, unsigned int ind2, unsigned int stg) 
 : strenght {stg}
 {
  if(ind1<ind2) {inds[0]= ind1;inds[1]=ind2;}
  else {inds[0]=ind2; inds[1]=ind1;};
 };
 friend bool operator<(const t_couple& l,const t_couple& r){
  return l.strenght<r.strenght;
 };
 friend bool operator>(const t_couple& l,const t_couple& r){
  return l.strenght>r.strenght;
 };
 friend bool operator==(const t_couple& l,const t_couple& r){
  return l.inds[0]==r.inds[0] || l.inds[1]==r.inds[1] || l.inds[0]==r.inds[1] || l.inds[1]==r.inds[0]; 
 };
 const unsigned int& operator[] (const unsigned int& i){
  return inds[i%2];
 }; 
 ~t_couple(){};
private:
 unsigned int inds[2];
 unsigned int strenght;
};

std::vector<unsigned int>& find_couples(std::list<t_couple>& lista, std::vector<unsigned int>& result){
 if(!lista.empty()){
  t_couple& temp=lista.back();
  while(!lista.empty()){
   temp=lista.back();
   result[temp[0]-1]=temp[1];
   result[temp[1]-1]=temp[0];
   lista.remove(temp);
  }
 }
 return result;
}

std::list<t_couple>& read_strenght(unsigned int n, std::list<t_couple>& lista){
 unsigned int temp;
 for(auto i=1;i!=n+1;++i)
  for(auto j=1;j!=i;++j){
   std::cin >> temp;
   lista.push_back(t_couple(i,j,temp));
  };
 lista.sort();
 return lista; 
}

int main(){
 unsigned int n;
 std::cin >> n;
 n*=2;
 std::vector<unsigned int> result;
 result.reserve(n);
 std::list<t_couple> strenght;
 read_strenght(n,strenght);
 find_couples(strenght,result);
 for(auto i=0;i<n;++i) std::cout << result[i] << " ";
 std::cout << std::endl;
}
