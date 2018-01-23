/* Sliding Windows Variations */
/* License info: contact Michele Miccinesi */

#include <iostream>
#include <vector>

template <typename T>
struct window{
	int i,j;
	T v;
};

window<int> min_window_with_sum(std::vector<int>& u, int s){
	window<int> w{0,static_cast<int>(u.size()),-1};
	int i,j,v;
	if((v=u[0])>=s) return window<int>{0,0,u[0]};
	for(i=0,j=1;j!=u.size();++j)
		if((v+=u[j])>=s){
			w.j=j;
			w.v=v;
			++j;
			break;
		}
	for(;j!=u.size();++j){
		v+=u[j];
		for(;v>=s+u[i];++i)
			v-=u[i];
		if(j-i<w.j-w.i){
			w.j=j;
			w.i=i;
			w.v=v;
		}
	}
	return w;
}

window<bool> min_window_with_range(std::vector<int>& u, int a, int b){
	std::vector<int> r(b-a+1,0);
	window<bool> w{0, u.size(), false};
	decltype(r)::iterator tr = r.begin()-a;
	int i, j, t{0};
	bool out;
	for(i=0,j=0; j!=u.size(); ++j){
		if(u[j]<=b && u[j]>=a){
			if(tr[u[j]]++==0) ++t;
			while((out=(u[i]<a || u[i]>b)) || tr[u[i]]>1){
				if(!out)
					--tr[u[i]];
				++i;
			}
			if(t==b-a+1 && j-i<w.j-w.i){
				w.i=i;
				w.j=j;
				w.v=true;
			}
		}
	}
	return w;
}

window<int> each_k_window_min(){}

/* note: window width at least 1 */
window<int32_t> max_sum_window(std::vector<int32_t>& u){
	int i,j,s;
	window<int32_t> w{-1,-1,static_cast<int32_t>(static_cast<uint32_t>(1)<<31)};
	for( i=0, j=0, s=0; j!=u.size(); ++j ){
		if((s+=u[j])>w.v) w.i=i, w.j=j, w.v=s;
		if(s<=0) s=0, i=j+1;
	}
	return w;
}

#include <stack>
std::vector<int32_t> max_of_min_sum_window_foreach_k(std::vector<int32_t>& u){
	std::vector<int32_t> r(u.size());
	std::vector<int32_t> R(u.size(),static_cast<int32_t>(static_cast<uint32_t>(1)<<31)); 
	std::stack<int32_t> s;
	int i;
	for( i=0; i!=u.size(); ++i ){
		while( !s.empty() ){
			if( u[s.top()]>u[i] ){
				r[s.top()]=i;
				s.pop();
			} else break;
		}
		s.push(i);
	}
	while(!s.empty()){
		r[s.top()] = i;
		s.pop();
	}
	while(i--){
		while( !s.empty() ){
			if( u[s.top()]>u[i] ){
				r[s.top()]-=i+2;
				s.pop();
			} else break;
		}
		s.push(i);
	}
	while(!s.empty()){
		r[s.top()]-=i+2;
		s.pop();
	}
	for( i=0; i!= u.size(); ++i )
		R[r[i]] = std::max( R[r[i]], u[i] );
	--i;
	while(i--)
		R[i] = std::max(R[i], R[i+1]);

	return R;
}

int main(){
	std::vector<int> A{5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
	int S = 15;
	window<int> w=min_window_with_sum(A,S);
	std::cout << w.i <<' ' << w.j << ' ' << w.v << "\n\n";
	std::vector<int> B{1, 2, 3, 7, 1, 12, 9, 11, 9, 6, 3, 7, 5, 4, 5, 3, 1, 10, 3, 3};
	int i=1, j=4;
	window<bool> w2=min_window_with_range(B,i,j);
	std::cout << w2.i <<' ' << w2.j << ' ' << w2.v << "\n\n";
	std::vector<int32_t> V{-2, -3, 4, -1, -2, 1, 5, -3};
	window<int32_t> w3=max_sum_window(V);
	std::cout << w3.i <<' ' << w3.j << ' ' << w3.v << "\n\n";
	std::vector<int32_t> w4=max_of_min_sum_window_foreach_k(V);
	for( auto &vv4: w4 ) std::cout << vv4 << ' ';
	std::cout << std::endl;
	return 0;
}
