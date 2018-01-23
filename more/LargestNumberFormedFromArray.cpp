/* Largest Number Formed From Array */
/* Problem Source: I'll think about it */
/* Solution License: contact Michele Miccinesi */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::vector<std::string> numbers;
    std::string line;
    short T,N;
    std::cin >> T;
    while(T--){
        std::cin >> N;
        numbers.resize(N);
        for( auto &n: numbers ) std::cin >> n;
        //The simplest way would be:
/*        std::sort(numbers.begin(), numbers.end(), [](std::string& a, std::string& b){
        	std::string s1, s2;
        	(s1=a)+=b;
        	(s2=b)+=a;
        	return s1>s2;
        });*/
        //but at the expense of time and memory, so analogously:
        std::sort(numbers.begin(), numbers.end(), [](std::string& a, std::string& b){
        	std::string *(s[2]) = {&a,&b};
        	if( a.size()==b.size() ) return a>b;
        	bool i{a.size()<b.size()};	//s[i] is the longer string
        	int j,k;
        	for( j=0; j!=s[!i]->size(); ++j )
        		if( a[j]!=b[j] ) return a[j]>b[j];
        	for( k=0; j!=s[i]->size(); ++j, ++k )
        		if( (*(s[i]))[j]!=(*(s[i]))[k] ) return i!=((*(s[i]))[j]>(*(s[i]))[k]);
        	for( j=0; k!=s[i]->size(); ++j, ++k )
        		if( (*(s[i]))[k]!=(*(s[!i]))[j] ) return i!=((*(s[!i]))[j]>(*(s[i]))[k]);
        	return false;
        });

        for( auto i=numbers.begin(); i!=numbers.end(); ++i )
            std::cout << *i;
        std::cout << '\n';
    }
    std::cout << std::flush;
    
	return 0;
}
