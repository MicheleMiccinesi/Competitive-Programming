/* Queue: linear time */
/* strictly taller, possibly equal heights */
/* For licence: Michele Miccinesi */

#include <iostream>
#include <vector>
#include <string>

struct p{
	std::string n;	//name
	int h;			    //height
};

// save height in ps, put order in the returned vector
std::vector<int> guess_query(int h,int n, std::vector<std::vector<int>>& o, std::vector<p>& ps, std::vector<int>& hs){
	std::vector<int> q;
	std::vector<int> s;
	s.reserve(h);
	q.reserve(n);

	for( int i=0; i!=o.size(); ++i){
		if(!o[i].empty())
			s.push_back(i);
		while(!s.empty()){
			if(o[s.back()].empty())
				s.pop_back();
			else break;
		}
		if(s.empty()) return q;
		ps[o[s.back()].back()].h=hs[s.back()];
		q.push_back(o[s.back()].back());
		o[s.back()].pop_back();
	}
	while(!s.empty()){
		if(o[s.back()].empty()) {
			s.pop_back();
			continue;
		}
		ps[o[s.back()].back()].h=hs[s.back()];
		q.push_back(o[s.back()].back());
		o[s.back()].pop_back();		
	}

	return q;
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	std::vector<p> ps(n);		//persons

	std::vector<std::vector<int>> o(n,std::vector<int>());
	int max=0, max_height=0;
	for( int i=0, m; i!=n; ++i ){
		std::cin >> ps[i].n >> m;
		if(o[m].empty()) ++max_height;
		o[m].push_back(i);
		if(max<m) max=m;
	}
	o.resize(++max);
	std::vector<int> hs(max);
	for( int i=0, h=max_height; i!=max; ++i ){
		if(!o[i].empty()){
			hs[i]=h;
			--h;
		}
	}

	auto q(guess_query(max_height,n,o,ps,hs));

	if(q.size()!=n) 
		std::cout << -1 << '\n';
	else 
		for( auto &i: q ) std::cout << ps[i].n << ' ' << ps[i].h << '\n';
	std::cout << std::flush;

	return 0;
}
