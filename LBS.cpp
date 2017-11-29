/* Longest Bitonic Subsequence O(N LOG N) */
/* LIS simplest O(nlogn) time cost */

#include <iostream>
#include <vector>
#include <algorithm>

const int16_t N_MAX = 100;
/* In position ls[i] there is the minimum last element by now of the LIS of length i+1 */

struct lms{
	int16_t v;
	int16_t c,	tn;		//c: lis; tn: lis terminating number
	int16_t rc,	rtn;	//same for reverse lis
};


/* I keep the terminating numbers because the bitonic s. can't have a plateau , otherwise wouldn't be necessary */
int main(){
	
	std::vector<int16_t> ls(0);
	ls.reserve(N_MAX);
	decltype(ls)::iterator ils;
	size_t n;
	std::vector<lms> LMS;
	LMS.reserve(N_MAX); 

	unsigned short mlms;
	unsigned short T;
	std::cin >> T;

	while(T--){
		std::cin >> n;
		ls.resize(0);
		LMS.resize(n);
		for( auto &o: LMS ){
			std::cin >> o.v;
			ils = std::lower_bound(ls.begin(), ls.end(), o.v);
			if( ils == ls.end() )
				ls.emplace_back(o.v);
			else *ils = o.v;
			o.c = ls.size();
			o.tn = ls.back();
		}
		mlms = ls.size();
		ls.resize(0);
		auto ilms = LMS.rbegin();
		for( ; ilms!=LMS.rend()-1; ilms++ ){
			ils = std::lower_bound(ls.begin(), ls.end(), ilms->v);
			if( ils == ls.end() )
				ls.emplace_back(ilms->v);
			else *ils = ilms->v;
			ilms->rc = ls.size();
			ilms->rtn = ls.back();
			if( ilms->rc+(ilms+1)->c > mlms ) mlms = ilms->rc+(ilms+1)->c - (ilms->rtn==ilms[1].tn)*1;			
		}
		ils = std::lower_bound(ls.begin(), ls.end(), ilms->v);
		if( ils == ls.end() )
			ls.emplace_back(ilms->v);
		else *ils = ilms->v;
		ilms->rc = ls.size();
		ilms->rtn = ls.back();
		if( mlms < ilms->rc ) mlms = ilms->rc;
		std::cout << mlms << '\n';
	}
	std::cout << std::flush;

	return 0;
}
