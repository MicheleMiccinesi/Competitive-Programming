#include <iostream>
#include <vector>

unsigned int N_MAX=200000;

template <typename T> 
struct vecmer{
 vecmer (unsigned int& n) :
  base{vettore1}, temp{vettore2}, inversions{0}
 {
  vettore1.reserve(n); vettore1.resize(n);
  vettore2.reserve(n); vettore2.resize(n);
 }
 void resize (unsigned int& n) 
 {
  vettore1.resize(n);
  vettore2.resize(n);
 }
 auto& operator[] (int i) {return base[i];};
 void merge_sort(){
  inversions = 0;
  tf = temp.begin() + base.size();
  block = 1;
  while(base.size() > block){
   ti = temp.begin();
   li = base.begin();
   lf = ri = li + block;
   rf = ri + block;
   if(rf > base.end()) rf = base.end();
   do {
    merge();
    if(base.end() - ri <= block)
     while(ri != base.end()) *ti++ = *ri++;
    else {
     li = rf;
     lf = ri = li + block;
     rf = ri + block;
     if(rf > base.end()) rf = base.end();
    }
   }
    while(ti != tf);
   block <<= 1;
   swap();
  }
 }
 uint64_t const& inv(){ return inversions; }
 std::vector<T>& base;
 std::vector<T>& temp;
 ~vecmer(){};
private:
 int block;
 uint64_t inversions;
 std::vector<T> vettore1;
 std::vector<T> vettore2; 
 typename std::vector<T>::iterator li,lf,ri,rf,ti,tf;
 void merge(){
  while(li != lf && ri != rf){
   if(*ri < *li){
    inversions += lf-li;
    *ti++ = *ri++;
   }
   else *ti++ = *li++;
  }
  if(li == lf) 
   while(ri != rf) *ti++ = *ri++;
  else 
   while(li != lf) *ti++ = *li++;
 }
 void swap(){
  std::vector<T>& tmp=base;
  base=temp;
  temp=tmp;
 }
};

int main(){
 std::ios_base::sync_with_stdio(false);

 vecmer<int> miovettore( N_MAX );
 unsigned int T,n; int i;
 std::cin >> T;
 while( T-- ){
  std::cin >> n;
  miovettore.resize(n);
  for(i=0; i<n; i++) std::cin >> miovettore[i];
  miovettore.merge_sort();
  std::cout << miovettore.inv() << std::endl;
 }
}
