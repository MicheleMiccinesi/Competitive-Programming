/* for Licence info contact: Michele Miccinesi */
/* Queue: linear time and space */

#define NDEBUG
#include <iostream>   //ubiquitos
#include <cassert>		//just for managing silly users...
#include <algorithm>  //unused
#include <stack>      //for available slots of heights
#include <vector>     //ubiquitos
#include <string>     //for persons names

struct sl{
	sl(int& bb, int& ee): b{bb}, e{ee}{}
	sl(int&& bb, int& ee): b{bb}, e{ee}{}
	int b,e;
};

struct p{
	std::string n;	//name
	int h;			//height
};
// check: return 0 if no solution exists, else return the length of the queue
inline int check(std::vector<std::vector<int>>& o){
	int s, i, n=o.size();
	for( i=0, s=0; i!=n; s+=o[i].size(), ++i )
		if(s<i)
			return 0;
	return s;
}

inline void split_last(int &i, std::stack<sl>& s, sl& ds){
	assert(i<ds.e&&i>=ds.b);
	s.emplace(i,ds.e);
	ds.e=i;
}

// save height in ps, put order in the returned vector
std::vector<int> guess_query(std::vector<std::vector<int>>& o, std::vector<p>& ps){
	int n=check(o);
	if(!n) return std::vector<int>(0);

	std::stack<sl> s;	//available slots for taller and taller people
	sl ds(0,n);			//remaining down slot, for shorter persons
	
	std::vector<int> q(n);
	// i: index for scanning o; j: index for writing to q, scanning through the slots!
	for( int i=o.size()-1, j=n-1; i!=-1; --i ){
		if(!o[i].empty()){
			split_last(i,s,ds);
			for( auto &oo: o[i]){
				assert(!s.empty()&&j>=0);
				q[j]=oo;
				ps[oo].h=n-s.top().b;
				if(++s.top().b==s.top().e) 
					s.pop();
				--j;
			}
		}
	}
	return q;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	std::vector<p> ps(n);		//persons

	std::vector<std::vector<int>> o(n,std::vector<int>());
	for( int i=0, m; i!=n; ++i ){
		std::cin >> ps[i].n >> m;
		o[m].push_back(i);
	}

	auto q(guess_query(o,ps));

	if(q.empty()) 
		std::cout << -1 << '\n';
	else 
		for( auto &i: q ) std::cout << ps[i].n << ' ' << ps[i].h << '\n';
	std::cout << std::flush;

	return 0;
}
