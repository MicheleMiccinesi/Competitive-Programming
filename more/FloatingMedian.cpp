/* Problem Source: topcoder FloatingMedian */
/* Solution License: contact Michele Miccinesi */

#include <iostream>
#include <vector>
#include <algorithm>
/* user is counting from 0 */
class rBIT16{
	std::vector<int> c;
public:
    rBIT16(): c(65536,0){}
    void add(uint16_t i, int&& j){
        c[++i]+=j;
        do {
            i+=(i&-i);
            c[i]+=j;
        } while(i);    
    }
    /* move 1 increment from i to j */
    void move(uint16_t i, uint16_t j){
        ++i; ++j;
        while(i && (i!=j) && j){
            while((i<j) && i){
                --c[i];
                i+=(i&-i);
            }
            while((j<i) && j){
                ++c[j];
                j+=(j&-j);
            }
        }        
        if(!i) 
            while(j){
                ++c[j];
                j+=(j&-j);
            }
        else if(!j)
            while(i){
                --c[i];
                i+=(i&-i);
            }
    }
    uint16_t lowerBound(int x){
        uint16_t p, i;
        for( p=(1<<15), i=0; p; p>>=1 )
            if( c[i|p]<x )
                x-=c[i|=p];
		return i;
    }
    void clear(){
        std::fill(c.begin(), c.end(), 0);
    }
};

class FloatingMedian{
	rBIT16 B;
    int N;
public:     
    FloatingMedian(): B(){};
    long long sumOfMedians(int,int,int,int,int){}
};
long long FloatingMedian::sumOfMedians(int seed, int mul, int add, int N, int K){
	uint16_t s=seed,m=mul,a=add,md=((K+1)>>1),i;
    N-=K;
    i=s;
    B.clear();
    long long S=0;
    while(K--){
        B.add( s, 1 );
        (s*=m)+=a;
    } S += B.lowerBound(md);

    while(N--){
        B.move(i,s);
        (i*=m)+=a;
        (s*=m)+=a;
        S += B.lowerBound(md);
    }

    return S;
}
