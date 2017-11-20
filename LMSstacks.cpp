#include <iostream>
#include <string>
#include <stack>
#include <vector>

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string stringa;
	stringa.reserve(100000);
	std::vector<std::stack<int32_t>> alphabet('z'-'a'+1, std::stack<int32_t>());
	auto talphabet = alphabet.begin()-'a';

	std::cin >> stringa;
	for(auto x = stringa.begin(); x != stringa.end(); x++)
		talphabet[*x].push(int32_t(x-stringa.begin()));


	int32_t lastLetter[] = {-1,-1};
	bool i = 0, j = 1;
	std::string LMS;
	LMS.reserve(stringa.size());
	for( char l = 'z'+1; l!='a'; ){
		l--;
		i = !i; j = !j;
		lastLetter[j]=lastLetter[i];
		if( !talphabet[l].empty() )
			if( talphabet[l].top() > lastLetter[i] ) {
				lastLetter[j] = talphabet[l].top();
				LMS += l;	
				talphabet[l].pop();

				while(!talphabet[l].empty()){	
					if(talphabet[l].top() > lastLetter[i]){
						LMS += l;
						talphabet[l].pop();
					}
					else break;
				}
			}
		if( lastLetter[j] == stringa.size()-1 ) break;
	}

	std::cout << LMS << std::endl;
}
