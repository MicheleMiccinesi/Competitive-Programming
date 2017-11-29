#include <iostream>
#include <vector>

unsigned int M[20][20];

int main() {
    std::ios_base::sync_with_stdio(false);
    
	unsigned short T;
	std::cin >> T;
	unsigned short N,i,j;
	unsigned int m;
	while(T--){
	   m=0;
	   std::cin >> N; 
	   for( i=0; i!= N; i++)
	        for( j=0; j!=N; j++)
	            std::cin >> M[i][j];
	   for( i=1; i!=N; i++){
	       M[i][0]+=std::max(M[i-1][0],M[i-1][1]);
	       for( j=1; j!=N-1; j++)
	            M[i][j]+=std::max(M[i-1][j-1],std::max(M[i-1][j],M[i-1][j+1]));
	       M[i][N-1]+=std::max(M[i-1][N-2],M[i-1][N-1]);
	   }
	   
	   for( j=0; j!=N; j++)
	        if(M[N-1][j]>m) 
	            m=M[N-1][j];
	   std::cout << m<<'\n';
	}
	std::cout << std::flush;
	return 0;
}
