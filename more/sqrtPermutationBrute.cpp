/* Square Root of Permutation */
/* Problem Source: codeforces 612E */
/* Solution License: contact Michele Miccinesi */
/* Solution1: bruteforce AHAH (TLE of course...) */

#include <iostream>
#include <vector>

void dfs(auto& n, auto &s, const auto &p, const int& i, const int& j, int& N, const int &eN){
	int a{i}, b{j}, c;
	int tN{0};
	auto clear = 
		[&i, &j, &a, &s, &n, &p, &N, &tN, &c]()
		{
			if(tN==0)
				return;
			int aa{i}, bb{j};
			if( a==i ){
				s[aa]=0;
				n[bb]=true;
				c=aa;
				aa=bb;
				bb=p[c];
			}
			while( aa!=a ){
				s[aa]=0;
				n[bb]=true;
				c=aa;
				aa=bb;
				bb=p[c];
			}
			tN=0;
		};

	while(s[a]!=b){
		if(n[b] && s[a]==0){
			s[a]=b;
			n[b]=false;
			c=a;
			a=b;
			b=p[c];
			++tN;
		} else{
			clear();
			return;
		}
	}

	N+=tN;
	if( N==eN )
		return;

	for( int ii=i+1; ii!=s.size(); ++ii ){
		if( s[ii]==0 ){
			for( int jj=1; jj!=s.size(); ++jj ){
				if( jj!=ii && jj!=p[ii] && n[jj] ){
					dfs(n, s, p, ii, jj, N, eN);
					if( N==eN )
						return;
				}
			}
			break;
		}
	}

	if(N!=eN){
		N-=tN;
		clear();
	}
}

std::vector<int> sqrt(const std::vector<int>& p){
	std::vector<int> s(p.size(), 0);
	std::vector<bool> n(s.size(), true);
	int N{0};
	const int eN=p.size()-1;

	for( int i=1; i!=s.size(); ++i ){
		if( i==p[i] ){
			s[i]=i;
			n[i]=false;
			++N;
		}
	}
	if( N==eN )
		return s;

	for( int i=1; i!=s.size(); ++i ){
		if( s[i]==0 ){
			for( int j=1; j!=s.size(); ++j ){
				if( j!=i && j!=p[i] && n[j] ){
					dfs(n, s, p, i, j, N, eN);
					if( N==eN )
						return s;
				}
			}
			break;
		}
	}

	if( N==eN )
		return s;
	else 
		return std::vector<int> (0);
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;
	std::vector<int> p(++n);
	for( int i=1; i!=n; ++i )
		std::cin >> p[i];

	std::vector<int> q(sqrt(p));

	if( q.empty() )
		std::cout << -1 << std::endl;
	else{
		for( int i=1; i!=q.size(); ++i )
			std::cout << q[i] << ' ';
		std::cout << std::endl;
	}

	return 0;
}
