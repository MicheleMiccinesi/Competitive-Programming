#include <iostream>
#include <stack>

uint64_t emploLang[102][2];
uint64_t mPred, mSucc, mLang = 0;

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	/* Masks for emploLang[][0] : 13 unused 7 Pred 7 Succ 37 Lang */
	mLang = ~mLang;
	mSucc = ((mLang << 57)>>20);
	mPred = mSucc << 7;
	mLang >>= 27;

	short result{0};

	short pred, succ;
	short n,m,k,l;
	uint64_t h;
	short i;
	bool oneLanguage{false};
	std::stack<unsigned short> biknownLang;
	std::cin >> n >> m;
	for( i=2; i!=n ; i++) {
		emploLang[i][0] = ((uint64_t(i+1))<<37)|((uint64_t(i-1))<<44);
		emploLang[i][1] = 0; }
	emploLang[1][0] = (uint64_t(1) << 38);
	emploLang[101][0] = 0; emploLang[101][1] = emploLang[101][0] = ~ emploLang[101][0];
	emploLang[0][0] = emploLang[0][1] = emploLang[1][1] = 0;
	emploLang[n][0] = ((uint64_t(n-1))<<44); emploLang[n][1] = 0;

	for( i = 1; i!= n+1; i++){
		std::cin >> k;
		if(k) {
			oneLanguage = true;
			while( k--){
				std::cin >> l;
				if(l>>6) {
					h = ((uint64_t(1))<<(l-(uint64_t(1)<<6)));
					emploLang[i][0] |= h;
					if(emploLang[0][0] & h){
						if(emploLang[101][0] & h){
						biknownLang.push(l);
						emploLang[101][0] ^= h; 
						}
					}
					else emploLang[0][0] |= h; 
				}
				else {
					h = (uint64_t(1)<<l);
					emploLang[i][1] |= h;
					if(emploLang[0][1] & h){
						if(emploLang[101][1] & h){
							biknownLang.push(l);
							emploLang[101][1] ^= h;
						}
					}
					else emploLang[0][1] |= h; 
				}
			}
		}
	}

	if(oneLanguage){
		while(!biknownLang.empty()){
			l = biknownLang.top();
			biknownLang.pop();

			if(l>>6) {
				h = ((uint64_t(1))<<(l-(uint64_t(1)<<6)));
				k = 0;
			}
			else {
				h = (uint64_t(1)<<l);
				k = 1;
			}

			for( i = 1; !(emploLang[i][k] & h); i = ( (emploLang[i][0] & mSucc ) >> 37) );
			m = i;

			while( i = short((emploLang[i][0] & mSucc ) >> 37) )
				if(emploLang[i][k] & h){
					emploLang[m][1] |= emploLang[i][1];
					emploLang[m][0] |= ( emploLang[i][0] & mLang );
					pred = ((emploLang[i][0] & mPred) >> 44);
					succ = ((emploLang[i][0] & mSucc) >> 37);
					(emploLang[pred][0] &= ~mSucc) |= (emploLang[i][0] & mSucc);
					(emploLang[succ][0] &= ~mPred) |= (emploLang[i][0] & mPred);
				}
		}
		i = 1;
		while ( i = short((emploLang[i][0] & mSucc ) >> 37) ) result++;
		std::cout << result << std::endl;
	} else std::cout << n << std::endl;

	return 0;
}
