/* Fair Workload */
/* Problem Source: topcoder */
/* Solution License: contact Michele Miccinesi */
/* Binary Search on possible answer; for each possibility,
   you'll have to prove a greedy strategy for the partitioning,
   the proof is easy by contradiction */

#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

class FairWorkload{
	bool _enough(const int& k, std::vector<int>& F) const;
	int _workers;
public:
	int getMostWork(std::vector<int> folders, int workers){
		bool ok; _workers=workers; int m;
		int b[]={*std::max_element(folders.begin(), folders.end()),std::accumulate(folders.begin(), folders.end(), 0)};
		while(b[0]<b[1]) ok=_enough(m=(b[0]+b[1])>>1,folders),b[ok]=m+!ok;
		return b[0];
	}
};

bool FairWorkload::_enough(const int& k, std::vector<int>& F) const {
	int w=1, tk=0;
	for( auto& f: F ){
		if(tk+f<=k) tk+=f;
		else {
			tk=f;
			if(++w>_workers) return false;
		}
	}
	return true;
}
