#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

struct n64{
    uint16_t v;  
    uint16_t q;
    uint16_t r;
    uint16_t cr;
};

int main(){
    std::ios_base::sync_with_stdio(false);
    
    std::vector<uint64_t> T[] = { std::vector<uint64_t>(50001), std::vector<uint64_t>(50001) };
    std::vector<uint64_t>::iterator iT, jT, kT;
    const uint64_t m_r = (1<<6)-1;
    uint16_t qS, rS, rstep, qstep;
    std::vector<n64> V(100);
    short maxv;
    
    uint32_t S, tS, step;
    
    short t, N;
    std::cin >> t;
    int32_t i, j;
    bool a{0},b{1};
    while(t--){
        std::cin >> N;
        V.resize(N);
        S = 0; maxv = 0;
        for( auto &v: V)
            std::cin >> v.v;
        for( auto &v: V){
            S += v.v;
            if(v.v>maxv) maxv=v.v;
            v.q = v.v>>6;
            v.r = v.v&m_r;
            v.cr = 64-v.r;
        }
        if( S&1 || (S>>=1) < maxv ) 
            std::cout << "NO" << '\n';
        else{
            a=0; b=1;
            qS = S>>6;  rS = S&m_r;
            step = S+1;
            qstep = step>>6;      rstep = step&m_r;
            T[0].resize(qstep+1);  T[1].resize(qstep+1);
            
            std::fill(T[0].begin(), T[0].end(), 0);
            T[0][0]=1; T[0][V[0].q] |= 1<<(V[0].r);

            for( i = 1; i != N; i++ ){
                a=!a;   b=!b;
                jT = T[b].begin();
                for( iT = T[a].begin(); iT!= T[a].begin()+V[i].q; iT++, jT++ )
                    *iT = *jT;
                kT = T[b].begin();
                *iT = *jT | ((*kT)<<V[i].r);
                iT++;   jT++;
                for( ; iT!=T[a].end(); iT++, jT++ ){
                    *iT = *jT | ((*kT)>>V[i].cr);
                    *iT |= ((*++kT)<<V[i].r);
                }
               /* for( auto ii = T[a].rbegin(); ii!=T[a].rend(); ii++ )
                    std::cout << std::bitset<64>(*ii);
                std::cout << std::endl << std::endl;*/
            }

            if(T[a][qS]&(static_cast<uint64_t>(1)<<rS)) std::cout << "YES\n";
            else std::cout << "NO\n";
            
        }
    }
    return 0;
}
