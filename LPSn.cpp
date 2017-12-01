/* Longest Palindromic Subsequence */
/* n+2 auxiliary space */
/* TLE on g4g */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(){
    std::ios_base::sync_with_stdio(false);
    
    short T;
    std::cin >> T;
    
	std::string s;
	s.reserve(1000);
	std::string::iterator sB, sE;
	short max;
	std::vector<short> p;
	p.reserve(1001);
	short tp[2];	bool i;
	decltype(p)::iterator pB, ip;
	
	while(T--){
	    std::cin >> s;
	    sB = s.begin(); sE = s.end();
	    max = 0;
	    p.resize(s.size()+1);
	    std::fill(p.begin(), p.end(), 0);
	    i = 0;
	    pB = p.begin()+1;
	
    	for( auto ris = s.rbegin(); sE-- != sB; ris++ ){
    		auto is = sB;	tp[i]=0;
    		for( ip = pB; is!=sE; is++, ip++ ){
    			tp[!i] = *ip;
    			if( *is == *ris )
    				*ip = tp[i]+1;
    			else
    				*ip = std::max( ip[0], ip[-1] );
    			i=!i;
    		}
    		max = std::max( max, static_cast<short>(std::max( (( (*is==*ris)?tp[i]+1:std::max(ip[0], ip[-1]) )<<1)-1, (*ip)<<1 ) ) ) ;
	    }

	    std::cout << max << std::endl;
	}

	return 0;
}
