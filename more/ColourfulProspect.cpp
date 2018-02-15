/* Problem Source: codeforces 934E (div2) == 933C (div1) */
/* Solution License: contact Michele Miccinesi */
/* exact solution (without approximations) */

/* Note: I wanted to compare the performance of switch vs explicit jump table with function pointers */

#include <iostream>
#include <type_traits>

template <int n, class INT>
std::enable_if_t<n==0, INT> pow(const INT& x){
	return static_cast<INT>(1);
}
template <int n, class INT>
std::enable_if_t<(n>0), INT> pow(const INT& x){
	return x*pow<n-1>(x);
}


int main(){
	std::ios_base::sync_with_stdio(false);

	short c;
	std::cin >> c;

	int x[3], y[3], r[3];
	auto get = [&x, &y, &r](const int &i){
		std::cin >> x[i] >> y[i] >> r[i];
	};

	auto dist = [&x, &y](const int& i, const int &j){
		return pow<2>((x[i]-x[j]))+pow<2>((y[i]-y[j]));
	};

	auto collinear = [&x, &y](){
		return (y[1]-y[0])*(x[2]-x[0])==(y[2]-y[0])*(x[1]-x[0]);
	};

	auto tan_inside = [&x, &y, &r](){
		for( char i=0, j, k; i!=3; ++i ){
			j=(i+1)%3;
			k=(j+1)%3;
			if(r[i]!=r[j]+r[k]){
				continue;
			}
			if(r[j]<r[k]){
				std::swap(j, k);
			}
			if( (x[i]-x[j])*r[j]==(x[k]-x[i])*r[k] ){
				return true;
			}
			else{ 
				return false;
			}
		}
		return false;
	};

	auto discrimina = [&x, &y, &r](const int& i, const int& j, const int& k){	//i,j: secanti; j,k: secanti; i,k: tangenti;
		return pow<2>(pow<2>(x[j]-x[i])+pow<2>(y[j]-y[i])+pow<2>(r[i])-pow<2>(r[j]))*\
				(pow<2>(x[k]-x[i])+pow<2>(y[k]-y[i])) == \
				4*pow<2>(r[i])*pow<2>((x[j]-x[i])*(x[k]-x[i])+(y[j]-y[i])*(y[k]-y[i]));
	};

	auto discrimina1 = [&x, &y, &r](){		//return true if the triple intersection is a point
		int64_t a1=x[1]-x[0], a2=x[2]-x[0], b1=y[1]-y[0], b2=y[2]-y[0];
		int64_t det=a1*b2-a2*b1;
		int64_t l1=a1*a1+b1*b1+r[0]*r[0]-r[1]*r[1];
		int64_t l2=a2*a2+b2*b2+r[0]*r[0]-r[2]*r[2];
		int64_t det1=l1*b2-l2*b1;
		int64_t det2=a1*l2-a2*l1;
		if( det==0 ){
			if( det1==0 )
				return 2;
			else
				return 0;
		}
		return (pow<2>(det1)+pow<2>(det2)==4*r[0]*r[0]*det*det)?1:0;
	};

	if( c==1 ){
		std::cout << 2 << std::endl;
		return 0;
	}
	if( c==2 ){
		get(0);
		get(1);
		int D=dist(0,1);
		int r_R=pow<2>(r[0]-r[1]);
		int rR=pow<2>(r[0]+r[1]);
		if( D>=rR || D<=r_R ){
			std::cout << 3 << std::endl;
			return 0;
		} else {
			std::cout << 4 << std::endl;
			return 0;
		}
	}
	if( c==3 ){
		get(0);
		get(1);
		get(2);
		int regions;
		char t[3][3];
		for( char i=0; i!=3; ++i ){
			for( char j=i+1; j!=3; ++j ){
				int d2=dist(i,j);
				int r_R=pow<2>(r[i]-r[j]);
				int rR=pow<2>(r[i]+r[j]);
				if( d2==rR || d2==r_R ){
					t[i][j]=t[j][i]=1;
				}
				else if( d2<rR && d2>r_R ){
					t[i][j]=t[j][i]=2;
				}
				else {
					t[i][j]=t[j][i]=0;
				}
			}
		}

		/*
		for( int i=0; i!=3; ++i ){
			for( int j=0; j!=3; ++j )
				std::cout << static_cast<int>(t[i][j]) << '\t';
			std::cout << '\n';
		}*/

		int in=t[0][1]+3*t[1][2]+9*t[2][0];
		//std::cout << in << std::endl;
		switch(in){
		case 0:
		case 1:
		case 3:
		case 9:
		case 4:
		case 10:
		case 12:
			regions=4;
			break;
		case 13:
			if( collinear() ){
				if( tan_inside() )
					regions=5;
				else
					regions=4;
			}
			else
				regions=5;
			break;
		case 2:
		case 6:
		case 18:
		case 5:
		case 7:
		case 11:
		case 15:
		case 19:
		case 21:
			regions=5;
			break;
		case 8:
		case 20:
		case 24:
		case 14:
		case 16:
		case 22:
			regions=6;
			break;
		case 17:
			if( discrimina(0,1,2) )
				regions=6;
			else 
				regions=7;
			break;
		case 25:
			if( discrimina(1,2,0) )
				regions=6;
			else
				regions=7;
			break;
		case 23:
			if( discrimina(2,0,1) )
				regions=6;
			else
				regions=7;
			break;
		case 26:
			switch(discrimina1()){
			case 0:
				regions=8;
				break;
			case 1:
				regions=7;
				break;
			case 2:
				regions=6;
				break;
			}
			break;
		}
		std::cout << regions << std::endl;
	}
		
	return 0;
}
