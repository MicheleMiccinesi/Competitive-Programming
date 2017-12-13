/* Knuth Morris Pratt */
/* Here I am recording more: given a string s and a pattern p 	*/
/* I am writing the vector with longest prefix of p that are 	*/
/* suffix of s, for each letter in s */

#include <iostream>
#include <string>
#include <vector>

struct pre_suf_string : std::string{
	pre_suf_string(): std::string(), lp() {}
	std::vector<int> lp;
	void lps(pre_suf_string *);
	void lps();
private:
	bool lpsed{false};
};


void pre_suf_string::lps(){
	auto& s  =*this;
	auto& lp = s.lp;
	int  E  = s.size();
		  lp.resize(E);

	int i;
	lp[0]=0;
	for( i=1; i!=E; ++i ){
		lp[i] = lp[i-1];
		while( s[lp[i]]!=s[i] && lp[i] )
			lp[i] = lp[lp[i]-1];
		lp[i] += s[lp[i]] == s[i];
	}
	s.lpsed = true;
}

void pre_suf_string::lps(pre_suf_string *pp){
	if(!pp->lpsed) pp->lps(), pp->lpsed = true;

	auto& s  =   *this;		auto& p   = 	   *pp;
	auto&slp =    s.lp;		auto& plp = 	  p.lp;
	int sE   =s.size(),			  pE  =p.size();
		slp.resize(sE);

	int i;
	slp[0] = s[0] == p[0];
	for( i=1; i!=sE; i++ ){
		slp[i] = slp[i-1]==pE ? plp[slp[i-1]-1] : slp[i-1];
		while( p[slp[i]]!=s[i] && slp[i] )
			slp[i] = plp[slp[i]-1];
		slp[i] += p[slp[i]] == s[i];
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);
	pre_suf_string A, B;
	int N;
	A.reserve(1000000);	B.reserve(2000000);
	A.lp.reserve(1000000); B.lp.reserve(2000000);
	std::cin >> N;
	std::cin >> A >> B;
	
	B += B;
	B.lps(&A);
	
	int i,im,m;
	i=im=m=0;
	for( auto &b: B.lp ){
		if(b>m){
			 m = b;
			im = i;
		}
		++i;
	}
	std::cout << im+1-m << std::endl;

	return 0;
}
