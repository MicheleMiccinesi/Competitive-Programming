/* Box Hedge */
/* Problem Source: codeforces 101597J (from ACM-ICPC Swiss) */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <algorithm>

struct pt{
	int32_t x;
	int32_t y;
};


int main(){
	std::ios_base::sync_with_stdio( false );


	int32_t n;
	std::cin >> n;
	std::vector<pt> pts(n);
	for( auto &p: pts ) std::cin >> p.x >> p.y;
	std::sort(pts.begin(), pts.end(), [](pt& a, pt& b){ return a.x < b.x; } );

	int64_t circumference, size, area{0};
	auto lcl = pts.begin();		//last corner left
	auto lcr = pts.end()-1;		//last corner right
	size = lcl->y + lcr->y + 2;
	auto cl = lcl;
	auto cr = lcr;
	int32_t ll, lr;
	while( cl != cr ){
		if( lcl->y <= lcr->y ){
			cl++;
			if( cl->y > lcl->y ){
				size += static_cast<uint64_t>( cl->y-lcl->y+cl->x-lcl->x );
				area += static_cast<uint64_t>( lcl->y+1 )*( cl->x-lcl->x );
				lcl = cl;
			}
		}
		if( lcl->y > lcr->y ){
			cr--;
			if( cr->y > lcr->y ){
				size += static_cast<uint64_t>( cr->y-lcr->y+lcr->x-cr->x );
				area += static_cast<uint64_t>( lcr->y+1 )*( lcr->x-cr->x );
				lcr = cr;
			}
		}
	}
	size += static_cast<uint64_t>( lcr->x-lcl->x )+3;
	area += static_cast<uint64_t>( lcr->x-lcl->x +1 )*( lcl->y + 1 );
	circumference = size+2;

	std::cout << circumference <<' ' << size <<' ' << area << std::endl;

	return 0;
}
