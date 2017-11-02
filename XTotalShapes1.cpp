#include <iostream>
#include <array>
#include <vector>

template <int NMAX, int MMAX,char X> 
struct shapesMat{
	int refill(const int NN, const int MM)
	{
		N=NN,M=MM,shapesCounter=0;

		if(!(N*M)) return 0;
		if(N>NMAX || M>MMAX) { std::cout << "Matrix is too big" << std::endl; return 0; }
		for(int a=r[0]=rr[0]=0; a!=N-1; r[a+1]=r[a]+M, rr[a+1]=rr[a]+M+1, a++);
		shapes.fill(0);

		std::cin >> std::ws;
		std::cin.read(input.data(), N*(M+1)-1);
		for(auto i=0; i!=N; ++i)
			for(auto j=0; j!=M; ++j)
				if(input[rr[i]+j]==X) if(!shapes[r[i]+j]) {  shapes[r[i]+j]=++shapesCounter; markShape(i,j); }
		return 1;
	};

	std::array<char, NMAX*(MMAX+1)> input;
	std::array<int, NMAX*MMAX> shapes;

	inline int const& operator() (int&& i, int&& j){
		return shapes[r[i]+j];
	};
	inline int const& operator() (int& i, int& j){
		return shapes[r[i]+j];
	};
	inline int const& operator() (){ return shapesCounter; };

	int printShapes(){
 		for(auto i=0; i!=N; i++){
 			for(auto j=0; j!=M; j++) std::cout << shapes[r[i]+j];
 			std::cout << '\n';
 		} std::cout << std::flush;
	}

private:
	int shapesCounter;
	void markShape(int& row, int& column){
		if(row){
			row--;
			if(input[rr[row]+column]==X) if(!shapes[r[row]+column]) { shapes[r[row]+column]=shapesCounter; markShape(row,column); }
			row++;
		}
		if(column){
			column--;
			if(input[rr[row]+column]==X) if(!shapes[r[row]+column]) { shapes[r[row]+column]=shapesCounter; markShape(row,column); }
			column++;
		}
		if(row!=N-1){
			row++;
			if(input[rr[row]+column]==X) if(!shapes[r[row]+column]) { shapes[r[row]+column]=shapesCounter; markShape(row,column); }
			row--;
		}
		if(column!=M-1){
			column++;
			if(input[rr[row]+column]==X) if(!shapes[r[row]+column]) { shapes[r[row]+column]=shapesCounter; markShape(row,column); }
			column--;
		}
	};
	int r[NMAX],rr[NMAX];
	int N,M;
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	int N,M;
	shapesMat<50,50,'X'> matrices;
	while( T-- ){
 		std::cin >> N >> M;
 		matrices.refill(N,M);
 		std::cout << matrices() << std::endl;
// 		matrices.printShapes();
	}
	return 0;
}
