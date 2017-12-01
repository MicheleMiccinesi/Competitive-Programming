/* Weighted Job Scheduling */
/* INPUT:  n° of Jobs */
/* for each job: start time, end time, profit */

#include <iostream>
#include <vector>
#include <algorithm>

struct Job{
	int i, f, p;
};

struct Sc{
	int f, p;
};

int main(){
	std::vector<Job> J;
	std::vector<Sc> S;

	int nJ;
	std::cin >> nJ;
	J.resize(nJ);
	for( auto &jj: J) std::cin >> jj.i >> jj.f >> jj.p;
	std::sort( J.begin(), J.end(), [](const Job& j1, const Job& j2){ return j1.f<j2.f; } );
	S.push_back({J[0].f, J[0].p});
	decltype(S)::iterator iS;
	for( auto &j: J ){
		iS = std::upper_bound(S.begin(), S.end(), j, [](const Job& jj, Sc& ss){ return ss.f>jj.i; });
	//	iS = std::lower_bound(S.begin(), S.end(), j, [](Sc& ss, const Job& jj){ return ss.f<=jj.i; });
		if( iS == S.begin() ){
			if( j.p > S.back().p )
				S.push_back({j.f, j.p});
		}
		else if( iS == S.end() ){
			S.push_back({j.f, j.p+S.back().p});
		}
		else if( iS[-1].p+j.p > S.back().p )
			S.push_back({j.f, j.p+iS[-1].p});
	}
	std::cout << S.back().p << '\n';
	std::cout << std::flush;
	return 0;
}
