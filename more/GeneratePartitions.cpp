/* Generate Partition in decreasing Lexycographic Order */
/* Problem Source: geeksforgeeks */
/* Solution License: contact Michele Miccinesi */


#include <iostream>

int p[30];
void print_partition(int i){
    for( int j=0; j!=i; ++j) std::cout << p[j] << ' ';
    std::cout << p[i] << ' ';//'\n';
}
void gen_partition(int i, int n){
    if(!n) {
        print_partition(i);
        return;
    }
    if(p[i]>=n) {
        p[i+1]=n;
        print_partition(i+1);
    }
    for( p[i+1]=std::min(n-1,p[i]); p[i+1]; --p[i+1])
        gen_partition(i+1,n-p[i+1]);
}
int main() {
    int T;
    std::cin >> T;
    int N;
    while(T--){
        std::cin >> N;
        for( p[0]=N; p[0]; --p[0] ) gen_partition(0,N-p[0]);
        std::cout << '\n';
    }
    std::cout << std::flush;
	
	return 0;
}
